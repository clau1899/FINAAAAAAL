
using namespace std;

struct objetoventa{
    int nid;
    // id imagen
    int id;
    char *nombre;
    int precio;
};


int ifondo_tienda;
int x_tienda;
int y_tienda;
char clista_tienda[30];
vector<objetoventa> vlista_tienda;
bool muestra_tienda;

int inicia_objeto;
int tienda_estado;

int moviendo;
int mdes;


// la lista de objetos para que no se haga muy lento
// se crea con la imagen, nombre, precio
void lee_lista_objetos(){
    char contenido[255];

    packfile_password(NULL);
    PACKFILE *fichero;

    objetoventa elemento;

    fichero = pack_fopen(clista_tienda,"r");

    while ( !pack_feof(fichero) )
    {
        pack_fgets( contenido, 255, fichero);
        elemento.nid = atoi( contenido );

        elemento.id = id_img_objeto( elemento.nid );

        elemento.nombre = nombre_objeto( elemento.nid );

        pack_fgets( contenido, 255, fichero);
        elemento.precio = atoi( contenido );

        vlista_tienda.push_back( elemento );
    }

    pack_fclose(fichero);
};

void borra_lista_objetos(){

    int  it = 0;
    int max = vlista_tienda.size();
    while ( it <  max )
    {
          it++;
          vlista_tienda.pop_back();
    }
}



void lee_tienda(int n){
    char contenido[255];

    packfile_password(NULL);
    PACKFILE *fichero;

    fichero = pack_fopen("tiendas.txt","r");
    int num = 0;
    while ( !pack_feof(fichero) && num != n )
    {
        num++;

        pack_fgets( contenido, 255, fichero);
        ifondo_tienda = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        x_tienda = atoi( contenido );

        pack_fgets( contenido, 255, fichero);
        y_tienda = atoi( contenido );

        pack_fgets( clista_tienda, 255, fichero);
    }

    pack_fclose(fichero);
    borra_lista_objetos();
    lee_lista_objetos();
};


bool sortdes(const objetoventa &i1, const objetoventa &i2)
{
     return strcmp( i1.nombre , i2.nombre ) < 0;
}

bool sortpre(const objetoventa &i1, const objetoventa &i2)
{
     return i1.precio < i2.precio ;
}

void pinta_tienda()
{
     if (muestra_tienda == true )
     {
          MENSAJE tdesc;
          tdesc.crea("",font,
                     x_tienda+5, y_tienda+415,
                     x_tienda+485, y_tienda+500);

          if (swtienda == 0)
          {
              // muestra flecha e inicia a cero
              swtienda = 1;
              inicia_objeto = 0;
              moviendo = 0;
              tienda_estado = 1;
              swinv = 0;
              sel_obj = -1;
          }

          TBOTON comprar, vender, salir;
          TBOTON descripcion, precios;

          comprar.crear("Comprar",(FONT *)datosjuego[dftextos].dat );
          vender.crear("Vender",(FONT *)datosjuego[dftextos].dat );
          salir.crear("Salir",(FONT *)datosjuego[dftextos].dat );
          descripcion.crear("Descripcion",(FONT *)datosjuego[dftextos].dat );
          precios.crear("Precio",(FONT *)datosjuego[dftextos].dat );

          masked_blit( (BITMAP*)datotiendas[ifondo_tienda].dat, buffer,
                       0,0,0,0, PANTALLA_ANCHO, PANTALLA_ALTO);

          rect(buffer, x_tienda, y_tienda, x_tienda+490, y_tienda+372,0xffffff );

          comprar.pinta( buffer, x_tienda+10, y_tienda+374, 0xffff00, 0xffffff );
          vender.pinta( buffer, x_tienda+125, y_tienda+374, 0xffff00, 0xffffff );
          salir.pinta( buffer, x_tienda+230, y_tienda+374, 0xffff00, 0xffffff );
          descripcion.pinta( buffer, x_tienda+34, y_tienda, 0xffff00, 0xffffff );
          precios.pinta( buffer, x_tienda+390, y_tienda, 0xffff00, 0xffffff );

    textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+305, y_tienda+374, 0xFFFFFF, -1, "Dinero %9d ",
                   jugador.getdinero() );

   if ( tienda_estado == 1 )
   {

          if ( vlista_tienda.size() > 10 )
          {

               rect(buffer, x_tienda+470, y_tienda, x_tienda+490, y_tienda+372,0xffffff );
               rect(buffer, x_tienda+470, y_tienda+30, x_tienda+490, y_tienda+342,0xffffff );
               triangle( buffer, x_tienda+473,y_tienda+25, x_tienda+487,y_tienda+25,
                             x_tienda+480,y_tienda+5,0xffffff );
               triangle( buffer, x_tienda+473,y_tienda+347, x_tienda+487,y_tienda+347,
                             x_tienda+480,y_tienda+367,0xffffff );

               // barra central
               // distancia unidad
               float ny1 = ( 340.0 - 32.0 ) / vlista_tienda.size() ;
               // parte superior por donde se inicia
               int ny2 = int(inicia_objeto * ny1);
               // siempre se muestran 10 - longitud barra
               int ny3 = int(10.0 * ny1);


               rectfill(buffer, x_tienda+472, y_tienda+32+ny2, x_tienda+488, y_tienda+32+ny3+ny2, 0xffffff );


               if ( mouse_x > x_tienda+460 && mouse_x < x_tienda+490 &&
                    mouse_y > y_tienda  && mouse_y < y_tienda+30)
               {
                    // esta situado encima de boton
                    triangle( buffer, x_tienda+473,y_tienda+25, x_tienda+487,y_tienda+25,
                             x_tienda+480,y_tienda+5,0xffff00 );
                    if ( mouse_b&1 )
                    {
                         // pulsa hacia arriba
                         inicia_objeto--;
                         if (inicia_objeto < 0 ) inicia_objeto = 0;
                    }
               }

               if ( mouse_x > x_tienda+460 && mouse_x < x_tienda+490 &&
                    mouse_y > y_tienda+342  && mouse_y < y_tienda+372)
               {
                    // esta situado encima de boton
               triangle( buffer, x_tienda+473,y_tienda+347, x_tienda+487,y_tienda+347,
                             x_tienda+480,y_tienda+367,0xffff00 );
                    if ( mouse_b&1 )
                    {
                         // pulsa hacia arriba
                         inicia_objeto++;
                         if (inicia_objeto+10 > vlista_tienda.size() ) inicia_objeto--;
                    }
               }
          }


          for ( int it=inicia_objeto; it < vlista_tienda.size() && it < inicia_objeto+10; it++ )
          {
              int ty = y_tienda+((it+1)*34) - (inicia_objeto*34);
              masked_blit( (BITMAP*)datobjetos[vlista_tienda[it].id].dat, buffer,
                           0,0,x_tienda,ty, 32,32);

              textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+34, ty, 0xFFFFFF, -1, "%s", vlista_tienda[it].nombre );

              textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+367, ty, 0xFFFFFF, -1, "%8d", vlista_tienda[it].precio );


                int numi = it - inicia_objeto;

                if ( mouse_x > x_tienda+1    && mouse_x < x_tienda+470 &&
                     mouse_y > y_tienda+32+(numi*34) && mouse_y < y_tienda+64+(numi*34))
                {
                     rect(buffer, x_tienda+2, y_tienda+34+(numi*34),
                                  x_tienda+468, y_tienda+63+(numi*34),0xffff00 );


                     tdesc.cambia_texto( descripcion_objeto(vlista_tienda[it].nid) );
                     tdesc.pinta(buffer);
                     textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+274, y_tienda, 0xFFFFFF, -1,
                                    "Tienes:%2d", jugador.cuantos_objetos(vlista_tienda[it].nid) );

                     if (  mouse_b&1 )
                     {
                           // intenta comprar objeto
                           // comprobar que existe hueco para la compra
                           // tiene dinero suficiente ?
                           if ( jugador.num_inventario() < 12 &&
                                jugador.getdinero() > vlista_tienda[it].precio )
                           {
                                sel_obj = it;
                           }else{
                              if ( swerror == 0 )
                              {
                                 swerror = 1;
                              }
                           }
                     }// fin se pulso el raton
                }// fin dentro de un objeto

          }

          if ( swerror == 2 ) swerror=0;
          if ( swerror == 1 && !mouse_b&1)
          {
              sonido_error();
              swerror=2;
          }


          if ( sel_obj != -1 && !mouse_b&1 )
          {
             jugador.menosdinero( vlista_tienda[sel_obj].precio );
             jugador.obtiene_objeto( vlista_tienda[sel_obj].nid );
             sel_obj = -1;
             sonido_boton();
          }

  }
 // fin compras



 //inicia ventas
 if ( tienda_estado == 2 )
 {
      int obj_tienes = jugador.num_inventario();

      if ( obj_tienes == 0 )
      {
           textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat,
                          x_tienda+75, y_tienda+185, 0xFFFFFF, -1, "No tienes objetos en tu inventario" );
      }



      if ( obj_tienes > 10 )
      {
               //pinta barra desplazamiento
               rect(buffer, x_tienda+470, y_tienda, x_tienda+490, y_tienda+372,0xffffff );
               rect(buffer, x_tienda+470, y_tienda+30, x_tienda+490, y_tienda+342,0xffffff );
               triangle( buffer, x_tienda+473,y_tienda+25, x_tienda+487,y_tienda+25,
                             x_tienda+480,y_tienda+5,0xffffff );
               triangle( buffer, x_tienda+473,y_tienda+347, x_tienda+487,y_tienda+347,
                             x_tienda+480,y_tienda+367,0xffffff );

               // barra central
               // distancia unidad
               float ny1 = ( 340.0 - 32.0 ) / obj_tienes ;
               // parte superior por donde se inicia
               int ny2 = int(inicia_objeto * ny1);
               // siempre se muestran 10 - longitud barra
               int ny3 = int(10.0 * ny1);

               rectfill(buffer, x_tienda+472, y_tienda+32+ny2, x_tienda+488, y_tienda+32+ny3+ny2, 0xffffff );


               if ( mouse_x > x_tienda+470 && mouse_x < x_tienda+490 &&
                    mouse_y > y_tienda  && mouse_y < y_tienda+30)
               {
                    // esta situado encima de boton
                    triangle( buffer, x_tienda+473,y_tienda+25, x_tienda+487,y_tienda+25,
                             x_tienda+480,y_tienda+5,0xffff00 );
                    if ( mouse_b&1 )
                    {
                         // pulsa hacia arriba
                         inicia_objeto--;
                         if (inicia_objeto < 0 ) inicia_objeto = 0;
                    }
               }

               if ( mouse_x > x_tienda+460 && mouse_x < x_tienda+490 &&
                    mouse_y > y_tienda+342  && mouse_y < y_tienda+372)
               {
                    // esta situado encima de boton
               triangle( buffer, x_tienda+473,y_tienda+347, x_tienda+487,y_tienda+347,
                             x_tienda+480,y_tienda+367,0xffff00 );
                    if ( mouse_b&1 )
                    {
                         // pulsa hacia arriba
                         inicia_objeto++;
                         if (inicia_objeto+10 > obj_tienes ) inicia_objeto= obj_tienes - 10;
                    }
               }

          }

          int it = 0;
          for ( int i=0; i<12; i++ )
          {
              if ( jugador.getinventario(i) != 0 &&
                   it < 10+inicia_objeto && it >= inicia_objeto)
              {
                   int mid = jugador.getinventario(i);
                   int ty =  y_tienda+((it+1)*34) - (inicia_objeto*34);

                   masked_blit( (BITMAP*)datobjetos[id_img_objeto(mid)].dat, buffer,
                                0,0,x_tienda,ty, 32,32);

              textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+34, ty, 0xFFFFFF, -1, "%s", nombre_objeto(mid) );

              textprintf_ex( buffer, (FONT *)datosjuego[dftextos].dat, x_tienda+367, ty, 0xFFFFFF, -1, "%8d", precio_objeto(mid) );


             int numi = it - inicia_objeto;

            if ( mouse_x > x_tienda+1    && mouse_x < x_tienda+470 &&
                 mouse_y > y_tienda+32+(numi*34) && mouse_y < y_tienda+64+(numi*34))
            {
                 rect(buffer, x_tienda+2, y_tienda+34+(numi*34),
                              x_tienda+468, y_tienda+63+(numi*34),0xffff00 );


                 tdesc.cambia_texto( descripcion_objeto(jugador.getinventario(i)) );
                 tdesc.pinta(buffer);


                 if (  mouse_b&1 )
                 {
                       // vende objeto
                       sel_obj = i;
                 }// fin se pulso el raton

            }// fin dentro de un objeto

                 it++;
              }else{

                 if ( jugador.getinventario(i) != 0  && it < inicia_objeto) it++;
              }
          }

          if ( sel_obj != -1 && !mouse_b&1 )
          {

             jugador.masdinero( precio_objeto(jugador.getinventario(sel_obj)) );
             // objeto con id cero no existe
             jugador.pon_inventario( sel_obj, 0);
             sel_obj = -1;
             sonido_boton();
             obj_tienes = jugador.num_inventario();

             if ( obj_tienes == 11 ) inicia_objeto = 1;
             if ( inicia_objeto > 0 && obj_tienes < 11 ) inicia_objeto=0;


          }


 }
 // fin ventas



          if ( comprar.ratonb() && tienda_estado != 1)
          {
               tienda_estado = 1;
               inicia_objeto = 0;
               sel_obj = -1;
               sonido_boton();
          }

          if ( vender.ratonb() && tienda_estado != 2)
          {
               tienda_estado = 2;
               inicia_objeto = 0;
               sel_obj = -1;
               sonido_boton();
          }

          if ( salir.ratonb() ){
                // oculta la flecha y sale
                swtienda = 0;
                muestra_tienda = false;
                sonido_boton();
          }
     }
}


