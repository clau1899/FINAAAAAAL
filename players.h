#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED



#endif // PLAYERS_H_INCLUDED

// players.h

// Esta clase se encarga del manejo del jugador
class player
{
    BITMAP *prota;
 int x,y;
 int direccion;
 int animacion;
    bool hablar;
    int ataca;

    public:
       void inicia();
       void pinta();
       bool choca();
       void teclado();
       int getx(){ return x; };
       int gety(){ return y; };
       void posiciona( int _x, int _y);
       void cambia_escenario();
       bool accion();
       void habla();
       void no_habla();
       bool hablando(){ return hablar; };
       bool atacando(){ return ataca>1; };
       void no_ataca(){ ataca = -3; };
};

bool player::accion()
{
     return key[KEY_ENTER] || key[KEY_ENTER_PAD] ;
}

void player::habla()
{
     hablar = true;
}


void player::no_habla()
{
     hablar = false;
}

void player::inicia()
{
     prota  = (BITMAP *)datosjuego[dipersonaje].dat;
 // inicializar vbles
 direccion = 0;
 animacion = 0;
 x = 540;
 y = 280;
}


void player::pinta()
{
    if ( ataca > 1 && ( direccion == 1 || direccion == 3 ) )
    {
           masked_blit((BITMAP *)datosjuego[diespada].dat, buffer, 0, direccion*96, x-32, y-32, 96,96);
    }

    masked_blit(prota, buffer, animacion*32, direccion*32, x, y, 32,32);

    if ( ataca > 1 && ( direccion == 0 || direccion == 2 ) )
    {
           masked_blit((BITMAP *)datosjuego[diespada].dat, buffer, 0, direccion*96, x-32, y-32, 96,96);
    }
    if ( ataca > 1 || ataca < 0) ataca++;
}

void player::teclado()
{
      int ax = x;
      int ay = y;

         if ( !hablar )
         {
              // teclas control usuario
              if ( key[KEY_UP] )
              {
                   y-=desplazamiento;
                   direccion = 3;
              }
              if ( key[KEY_DOWN] )
              {
                   y+=desplazamiento;
                   direccion = 0;
              }
              if ( key[KEY_LEFT] )
              {
                   x-=desplazamiento;
                   direccion = 1;
              }
              if ( key[KEY_RIGHT] )
              {
                   x+=desplazamiento;
                   direccion = 2;
              }

              if ( key[KEY_SPACE] && ataca == 0 )
              {
                   ataca = 1;
              }
              if ( !key[KEY_SPACE] && ataca == 1 )
              {
                   ataca = 2;
                   sonido_espada_aire();
              }

        }
      if ( ax != x || ay != y )
      {
           // entra si a cambiado alguna de las variables x,y
           if ( choca() )
           {
                x =ax;
                y =ay;
           }else{
               int mx = desplazamiento_map_x;
               int my = desplazamiento_map_y;

               rectfill( choque, ax+4+mx, ay+17+my, ax+28+mx, ay+30+my, 0x000000);

               // control choque para npcs
               rectfill( choque, x+4+mx, y+17+my, x+28+mx, y+30+my, 0xffffff);
           }
           int num = FRAME_RATE / 12;
           if ( tiempo_total % num == 0 )
           {
                   sonido_pasos();

                   animacion++;
                   if ( animacion > 2 ) animacion = 0;
           }
      }
      if ( ataca > (FRAME_RATE / 4) ) ataca = 0;
}

void player::cambia_escenario()
{
     // siempre antes de cambiar a otro escenario se debe de borrar
     // el cuadro de choque
     int mx = desplazamiento_map_x;
     int my = desplazamiento_map_y;

     rectfill( choque, x+4+mx, y+17+my, x+28+mx, y+30+my, 0x000000);
}



void player::posiciona( int _x, int _y)
{
     x=_x;
     y=_y;
}
bool player::choca()
{
    int mx = x+desplazamiento_map_x;
    int my = y+desplazamiento_map_y;

    bool resp=false;
    for (int i=2; i < 30; i++ )
    {
        for (int j=16; j < 32; j++)
        {

            if ( getpixel ( choque, mx+i, my+j) != 0x000000 &&
                 getpixel ( choque, mx+i, my+j) != 0xffffff )
            {
                // si el color no es negro
                resp = true;
                // color verde
                if ( getpixel( choque, mx+i, my+j) == 0x00ff00 ) cambio = 1;
                // color azul
                if ( getpixel( choque, mx+i, my+j) == 0x0000ff ) cambio = 2;
                // color amarillo
                if ( getpixel( choque, mx+i, my+j) == 0xffff00 ) cambio = 3;
            }

        }
    }
    return resp;
}
