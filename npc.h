#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED



#endif // NPC_H_INCLUDED

// npc.h

/*
    la posicion x,y es una posicion directa al mapa, por tanto debe pintarse
    directamente en el fondo, y no en el buffer
*/

class npc {
protected:
          // posicion
      int x,y;
      int ax,ay;

      BITMAP* mifondo;
      bool primer;

      int direccion;

      int animacion;

      int escena;

      int estado;

      BITMAP* imagen;

    public:

      void actualiza();
      bool posicion_cerca(int _x, int _y);
      bool chocanpc();
      void crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar );
      void pinta();
};

bool npc::posicion_cerca(int _x, int _y)
{
     int d = 32 + (desplazamiento*2);
     int d2 =abs ( _x - x ) + abs ( _y - y );
     return d2 <= d && lugar == escena ;
}

void npc::crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar )
{
     x = _x;
     y = _y;
     direccion = dir;
     animacion = 0;
     escena = _lugar;
     mifondo = create_bitmap(32, 32);
     primer = false;

     imagen = create_bitmap(_img->w, _img->h);

     blit( _img, imagen, 0,0, 0,0, _img->w, _img->h);

     // NPC parado
     estado = _estado;
}


void npc::pinta()
{
     if ( lugar == escena )
     {

          if ( !primer )
          {
               // obtiene una copia de lo anterior
               blit( fondo, mifondo, x,y,0,0,32,32);
               primer = true;

          }
          actualiza();
          masked_blit(imagen, fondo, animacion*32, direccion*32, x, y, 32,32);
     }
}

bool npc::chocanpc()
{
    int ninix,niniy;
    int nfinx,nfiny;

    if ( direccion == 0 )
    {
         // abajo
         ninix = 0;
         niniy = 32 - desplazamiento;
         nfinx = 32;
         nfiny = 32;
    }
    if ( direccion == 1 )
    {
         // izquierda
         ninix = 0;
         niniy = 0;
         nfinx = desplazamiento;
         nfiny = 32;
    }
    if ( direccion == 2 )
    {
         // derecha
         ninix = 32 - desplazamiento;
         niniy = 0;
         nfinx = 32;
         nfiny = 32;
    }
    if ( direccion == 3 )
    {
         // arriba
         ninix = 0;
         niniy = 0;
         nfinx = 32;
         nfiny = desplazamiento;
    }

    // comprobar si colisiona con el mapa
    for ( int ci=ninix; ci < nfinx; ci++)
    {
        for (int cj=niniy; cj < nfiny; cj++)
        {

            // color rojo
            if ( getpixel( choque, x+ci, y+cj) == 0xff0000 ){
                 return true;
            }
            // color blanco prota
            if ( getpixel( choque, x+ci, y+cj) == 0xffffff ){
                 return true;
            }
        }
    }
    return false;
}
void npc::actualiza()
{
    // para indicar que se ejecuta dos veces
    int num = FRAME_RATE / 6;

    if ( tiempo_total % num == 0 )
    {
        if ( estado != 0 )
        {
           animacion++;
           if ( animacion > 2 ) animacion = 0;
        }

        switch ( estado )
        {
        case 1: // camina horizontal
             ax = x;
             ay = y;
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 2;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 1;
                  }
             }

             if ( ax != x )
             {
                  // borrar antiguo choque
                  rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

                  // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);

             }

              // cambie o no se cambia el fondo por la animacion

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, ax,ay, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

             break;
        case 2: // camina vertical
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 3;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 0;
                  }
             }

             if ( ay != y )
             {

                  // borrar antiguo choque
                  rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

                  // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);

             }

              // cambie o no se cambia el fondo por la animacion

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, ax,ay, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

             break;
        case 3: // camina giro derecha
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 1;
                  }
             }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 3;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 0;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 2;
                  }
             }
             if ( ax != x || ay != y )
             {
                  // se ha movido en una de las direcciones

                  // borrar antiguo choque
                  rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

                  // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);
             }

              // cambie o no se cambia el fondo por la animacion

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, ax,ay, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

         break;
         case 4: // camina giro izquierda
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                  // camina abajo
                  y+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 2;
                  }
             }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 0;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = 3;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = 1;
                  }
             }
             if ( ax != x || ay != y )
             {
                  // se ha movido en una de las direcciones

                  // borrar antiguo choque
                  rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

                  // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);

             }

              // cambie o no se cambia el fondo por la animacion

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, ax,ay, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

             break;
        case 5: // camina libre
             if ( tiempo_total % 200 == 0 )
             {
                  direccion = rand()%4;
             }
             ax = x;
             ay = y;
             if ( direccion == 0 )
             {
                      // camina abajo
                      y+=desplazamiento;
                      if ( chocanpc() )
                      {
                           // posicion no valida
                           y = ay;
                           direccion = rand()%4;
                      }
                 }
             if ( direccion == 1 )
             {
                  // camina izquierda
                  x-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = rand()%4;
                  }
             }
             if ( direccion == 2 )
             {
                  // camina derecha
                  x+=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       x = ax;
                       direccion = rand()%4;
                  }
             }
             if ( direccion == 3 )
             {
                  // camina arriba
                  y-=desplazamiento;
                  if ( chocanpc() )
                  {
                       // posicion no valida
                       y = ay;
                       direccion = rand()%4;
                  }

             }

             if ( ax != x || ay != y )
             {
                  // se ha movido en una de las direcciones

                  // borrar antiguo choque
                  rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

                  // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);
             }

              // cambie o no se cambia el fondo por la animacion

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, ax,ay, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

             break;
        default: // parado
             if ( tiempo_total % 300 == 0 )
             {
                  direccion = rand()%4;
             }
             // pinta el nuevo choque
                  rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);

              // restaura fondo anterior antes de pintar la nueva imagen
              blit( mifondo, fondo, 0,0, x,y, 32,32);

              // obtiene una copia del nuevo fondo que va a ser ocupado
               blit( fondo, mifondo, x,y,0,0,32,32);

             break;
        }

    }
}

class enemigo : public npc {
      int vida;
      int v_actual;
      bool muerto;

     public:
        void crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar, int v );
        void herida( int d );
        void pinta();
        bool ha_muerto() { return muerto; };
};


void enemigo::crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar, int v )
{
    x = _x;
    y = _y;
    direccion = dir;
    animacion = 0;
    escena = _lugar;

    imagen = create_bitmap(_img->w, _img->h);
    mifondo = create_bitmap(32, 32);

    blit( _img, imagen, 0,0, 0,0, _img->w, _img->h);

    estado = _estado;

    primer = false;
    vida = v;
    v_actual = vida;
    muerto = false;
};

void enemigo::herida( int d )
{
  if ( !muerto )
  {
     v_actual-=d;
     if ( v_actual <= 0 )
     {
           muerto = true;
           blit( mifondo, fondo, 0,0, x,y, 32,32);
           rectfill( choque, x+2, y+1, x+30, y+31, 0x000000);
           sonido_muere();
     }
  }
};


void enemigo::pinta()
{
     if ( lugar == escena && !muerto )
     {

          if ( !primer )
          {
               // obtiene una copia de lo anterior
               blit( fondo, mifondo, x,y,0,0,32,32);
               primer = true;

          }
          actualiza();
          masked_blit(imagen, fondo, animacion*32, direccion*32, x, y, 32,32);

          int nm = (v_actual * 30 ) / vida;

          if ( !muerto )
          {
              rectfill( fondo, x+1, y, x+nm, y+5, 0x00ff00);
              rect( fondo, x, y, x+31, y+5, 0x000000);
          }
     }
}
