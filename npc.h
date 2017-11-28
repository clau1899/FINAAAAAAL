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
      bool posicion_cerca();
      bool chocanpc();
      void crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar );
      void pinta();
};

bool npc::posicion_cerca()
{
     int _x = jugador.getx() + desplazamiento_map_x;
     int _y = jugador.gety() + desplazamiento_map_y;
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
      int golpeado;
      int exp;
     public:
        void crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar, int v );
        void herida( int d );
        void pinta();
        bool ha_muerto() { return muerto; };
        void movimiento();
        bool frente();
        void daexp(int e){ exp = e; };
};

void enemigo::crea( BITMAP *_img, int _x, int _y, int dir, int _estado, int _lugar, int v )
{
    x = _x;
    y = _y;
    direccion = dir;
    animacion = 0;
    escena = _lugar;
    golpeado = 0;
    exp = 50;
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
     int num = FRAME_RATE / 2;
     v_actual-=d;

     if ( v_actual <= 0 )
     {
           muerto = true;
           blit( mifondo, fondo, 0,0, x,y, 32,32);
           rectfill( choque, x+2, y+1, x+30, y+31, 0x000000);
           sonido_muere();
           jugador.sube_experiencia(exp);
     }else{
        // daño defensivo del enemigo
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%2 == 1 )
             {
                 sonido_herido();
                 jugador.herido(5+rand()%5);
             }
        }
     }
  }
};

bool enemigo::frente()
{
    int jx = jugador.getx() + desplazamiento_map_x;
    int jy = jugador.gety() + desplazamiento_map_y;

    int d =  jugador.dire();

    if ( jx > x )
    {
        if ( abs ( jy - y ) < desplazamiento*2 )
        {
             if ( d == 1 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jx < x )
    {
        if ( abs ( jy - y ) < desplazamiento*2 )
        {
             if ( d == 2 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jy < y )
    {
        if ( abs ( jx - x ) < desplazamiento*2 )
        {
             if ( d == 0 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    if ( jy > y )
    {
        if ( abs ( jx - x ) < desplazamiento*2 )
        {
             if ( d == 3 )
             {
                  return true;
             }else{
                  return false;
             }
        }
    }

    return false;
}

void enemigo::movimiento()
{
    ax = x;
    ay = y;
    int jx = jugador.getx() + desplazamiento_map_x;
    int jy = jugador.gety() + desplazamiento_map_y;

    // para indicar que se ejecuta dos veces
    int num = FRAME_RATE / 6;

    int esta = 0;

    // mira hacia donde este el jugador
    if ( jx > x )
    {
         direccion = 2;
    }else{
         direccion = 1;
    }

    if ( jy > y )
    {
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 0;
        }
    }else{
        if ( abs ( jx - x ) < desplazamiento*3 )
        {
            direccion = 3;
        }
    }

    // enemigo te persigue

    if ( tiempo_total % num == 0 )
    {

        if ( x+32 < jx )
        {
             x+=desplazamiento;
             esta = 1;
        }

        if ( x > jx+32 )
        {
             x-=desplazamiento;
             esta = 1;
        }
        if ( y+32 < jy )
        {
             y+=desplazamiento;
             esta = 1;
        }

        if ( y > jy+32  )
        {
             y-=desplazamiento;
             esta = 1;
        }

    }


    if ( ax != x || ay != y )
    {
      // se ha movido en una de las direcciones

      if ( chocanpc() )
      {
           x = ax;
           y = ay;
           esta = 0;
      }
      if ( esta != 0 )
      {
           animacion++;
           if ( animacion > 2 ) animacion = 0;
      }

      // borrar antiguo choque
      rectfill( choque, ax+2, ay+1, ax+30, ay+31, 0x000000);

      // pinta el nuevo choque
      rectfill( choque, x+2, y+1, x+30, y+31, 0xff0000);
    }


    if ( posicion_cerca() )
    {
        int num = FRAME_RATE / 3;
        if ( tiempo_total % num == 0 )
        {
             if ( rand()%3 == 1 )
             {
                 sonido_herido();
                 jugador.herido(2+rand()%2);
                 animacion++;
                 if ( animacion > 2 ) animacion = 0;
             }
        }
    }


    // cambie o no se cambia el fondo por la animacion

    // restaura fondo anterior antes de pintar la nueva imagen
    blit( mifondo, fondo, 0,0, ax,ay, 32,32);

    // obtiene una copia del nuevo fondo que va a ser ocupado
    blit( fondo, mifondo, x,y,0,0,32,32);
}

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

          if ( v_actual == vida )
          {
               actualiza();
          }else{
               movimiento();
          }
          masked_blit(imagen, fondo, animacion*32, direccion*32, x, y, 32,32);

        if ( golpeado == 1 )
        {
            int xn = 2 + rand()%2;
            jugador.no_ataca();
            if ( rand()%10 != 1 )
            {
               sonido_espada_da();
               herida(xn);
            }else{
               sonido_espada_choca();
            }
            golpeado = 0;

        }

        if ( golpeado == 0 && jugador.atacando() && posicion_cerca()
             && frente() )
        {
              golpeado = 1;
        }

          if ( !muerto )
          {
              int nm = (v_actual * 30 ) / vida;
              rectfill( fondo, x+1, y, x+nm, y+5, 0x00ff00);
              rect( fondo, x, y, x+31, y+5, 0x000000);
          }
     }

     if ( lugar != escena && v_actual < vida )
     {
        int num = FRAME_RATE / 5;
        if ( tiempo_total % num == 0 )
        {
            v_actual++;
        }
     }
}

