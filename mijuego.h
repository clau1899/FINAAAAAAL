#ifndef MIJUEGO_H_INCLUDED
#define MIJUEGO_H_INCLUDED



#endif // MIJUEGO_H_INCLUDED
/*
   mijuego.h

*/


player jugador;
#include "npc.h"
npc personajes[30];
int npersonaje;

enemigo malos[30];
int nmalos;

MENSAJE texto, dialogo;

int mision;

// para saber si el mapa tiene scroll
bool desplaza;

const int scroll_rango1 = 200;
const int scroll_rango2 = 90;


// carga los datos del escenario segun lugar
void carga_escenario()
{
    jugador.cambia_escenario();
    switch ( lugar )
    {
    case 1:// casa
              fondo  = (BITMAP *)datosjuego[dicasamago].dat;
              choque = (BITMAP *)datosjuego[dimagochoque].dat;
              cielo  = (BITMAP *)datosjuego[dimagosup].dat;

              desplaza = false;

              musica_casa();
         break;

    case 2:// bosque
              fondo  = (BITMAP *)datosjuego[dibosque].dat;
              choque = (BITMAP *)datosjuego[dibosquechoque].dat;
              cielo  = (BITMAP *)datosjuego[dibosquesup].dat;
              jugador.prota =(BITMAP *)datosjuego[dimago].dat;
              desplaza=true;

              sonido_ambiente();
              musica_bosque();
         break;

    case 3:// ciudad
              fondo  = (BITMAP *)datosjuego[dicity1].dat;
              choque = (BITMAP *)datosjuego[dicity1choque].dat;
              cielo  = (BITMAP *)datosjuego[dicity1sup].dat;

              desplaza=true;

              musica_ciudad1();
         break;

    }
}
void pinta_barra_vida()
{

    int n = (jugador.getvida()*150) / jugador.getvidamax() ;

    rectfill( buffer, PANTALLA_ANCHO-162, 10, PANTALLA_ANCHO-8, 25, 0x003300);
    rectfill( buffer, PANTALLA_ANCHO-160, 12, PANTALLA_ANCHO-160+n, 23, 0x00ff00);
    rectfill( buffer, PANTALLA_ANCHO-160, 12, PANTALLA_ANCHO-160+n, 15, 0xbbffaa);
    rect( buffer, PANTALLA_ANCHO-162, 10, PANTALLA_ANCHO-8, 25, 0x000000);

    int nxp = 100 * ( jugador.getnivel() + 1 );
    int n2 = (jugador.getexp()*150) / nxp ;

    rectfill( buffer, PANTALLA_ANCHO-162, 30, PANTALLA_ANCHO-8, 45, 0x000033);
    rectfill( buffer, PANTALLA_ANCHO-160, 32, PANTALLA_ANCHO-160+n2, 43, 0x0000ff);
    rectfill( buffer, PANTALLA_ANCHO-160, 32, PANTALLA_ANCHO-160+n2, 35, 0xbbaaff);
    rect( buffer, PANTALLA_ANCHO-162, 30, PANTALLA_ANCHO-8, 45, 0x000000);
    textprintf_centre_ex( buffer, font, PANTALLA_ANCHO - 80, 34, 0xFFFFFF, -1, "Niv: %d",
                    jugador.getnivel() );
}

void pinta_lvlup()
{
     if ( lvl_up )
     {
          nlvlup = 1;
          lux = jugador.getx();
          luy = jugador.gety();
          lvl_up = false;
     }
     if ( nlvlup > 0 )
     {
          masked_blit ( (BITMAP *)datosjuego[dilvlup].dat, buffer, 0,0, lux, luy - nlvlup*2, 32,32 );
          int num = FRAME_RATE / 10;
           if ( tiempo_total % num == 0 )
           {
              nlvlup++;
           }
           if  ( nlvlup > 40 ) nlvlup = 0;
     }
}

void cambia_escenario()
{

    switch ( lugar )
    {
    case 1:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 2;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         break;
    case 2:   // bosque
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // casa
              lugar = 1;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 200,440 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              sonido_abrirpuerta();
              para_sonido_ambiente();
              cambio = 0;

         }
         if ( cambio == 3 )
         {
              // cambiamos a otro lugar
              // ciudad
              lugar = 3;
              carga_escenario();
              // situamos al prota en el camino
              jugador.posiciona( 500,540 );
              desplazamiento_map_x=950;
              desplazamiento_map_y=508;
              para_sonido_ambiente();
              cambio = 0;
         }
         break;
    case 3:   // ciudad
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 2;
              carga_escenario();
              // situamos al prota en el camino del bosque
              jugador.posiciona( 650,30 );
              desplazamiento_map_x=200;
              desplazamiento_map_y=0;
              cambio = 0;
         }
         break;
    default:
         break;
    }
}

void scroll_escenario()
{

    int ax,ay;

    ax = jugador.getx();
    ay = jugador.gety();

    if ( desplaza )
    {
         int d = desplazamiento / 2;
         // controla el desplazamiento del mapa si esta en los bordes
         if ( ax < scroll_rango1 && desplazamiento_map_x > 0 )
         {
              desplazamiento_map_x-=d;
              jugador.posiciona(ax+d,ay);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ax < scroll_rango2 && desplazamiento_map_x > 0  )
              {
                  desplazamiento_map_x-=d;
                  jugador.posiciona(ax+d,ay);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }
         if ( ay < scroll_rango1 && desplazamiento_map_y > 0 )
         {
              desplazamiento_map_y-=d;
              jugador.posiciona(ax,ay+d);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ay < scroll_rango2 && desplazamiento_map_y > 0 )
             {
                  desplazamiento_map_y-=d;
                  jugador.posiciona(ax,ay+d);
                 ax = jugador.getx();
                 ay = jugador.gety();
             }
         }
         if ( ax > PANTALLA_ANCHO-scroll_rango1 && desplazamiento_map_x < fondo->w-PANTALLA_ANCHO )
         {
              desplazamiento_map_x+=d;
              jugador.posiciona(ax-d,ay);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ax > PANTALLA_ANCHO-scroll_rango2 && desplazamiento_map_x < fondo->w-PANTALLA_ANCHO  )
              {
                  desplazamiento_map_x+=d;
                  jugador.posiciona(ax-d,ay);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }
         if ( ay > PANTALLA_ALTO-scroll_rango1 && desplazamiento_map_y < fondo->h-PANTALLA_ALTO )
         {
              desplazamiento_map_y+=d;
              jugador.posiciona(ax,ay-d);
              ax = jugador.getx();
              ay = jugador.gety();
              if ( ay > PANTALLA_ALTO-scroll_rango2 && desplazamiento_map_y < fondo->h-PANTALLA_ALTO )
              {
                  desplazamiento_map_y+=d;
                  jugador.posiciona(ax,ay-d);
                 ax = jugador.getx();
                 ay = jugador.gety();
              }
         }

    }

}
void evento_escenario()
{
    int pzx = jugador.getx() + desplazamiento_map_x;
    int pzy = jugador.gety() + desplazamiento_map_y;

    switch ( lugar )
    {
    case 1:// casa

         break;
    case 2:   // bosque
        if ( personajes[0].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Tienes que buscar medicinas para el rey!");
              hablando = 1;
         }
         if ( hablando == 1 && !jugador.accion() )
         {
              hablando = 2;
              jugador.habla();
         }

         // obliga a esperar minimo 1 segundo
         if ( hablando > FRAME_RATE && jugador.accion() ){
              hablando = 0;
         }

         if ( hablando == 0 && !jugador.accion() && jugador.hablando() )
         {
              jugador.no_habla();
         }

         break;
    case 3:   // ciudad

         if ( personajes[4].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Aparta!!, no tengo tiempo para hablar con pueblerinos. Tengo que seguir con mi ronda de vigilancia. " );
              hablando = 1;
         }

         if ( personajes[5].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Soy la reina de los mares!! .. paseando por la calle voy ^_^ " );
              hablando = 1;
         }


         if ( personajes[6].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Me han dicho que han visto un goblin merodeando por el bosque, debes tener cuidado cuando vuelvas a tu casa." );
              hablando = 1;
         }

         if ( hablando == 1 && !jugador.accion() )
         {
              hablando = 2;
              jugador.habla();
         }

         // obliga a esperar minimo 1 segundo
         if ( hablando > FRAME_RATE && jugador.accion() ){
              hablando = 0;
         }

         if ( hablando == 0 && !jugador.accion() && jugador.hablando() )
         {
              jugador.no_habla();
         }

         break;
    default:
         break;
    }
}

void carga_juego()
{

    packfile_password(evalc);
    datosjuego = load_datafile("datosjuego.dat");
    if ( !datosjuego ){
       allegro_message("Error: archivo datosjuego.dat no encontrado\n%s\n", allegro_error);
    }

    jugador.inicia();

    fondo  = (BITMAP *)datosjuego[dicasamago].dat;
    choque = (BITMAP *)datosjuego[dimagochoque].dat;
    cielo  = (BITMAP *)datosjuego[dimagosup].dat;

    lugar = 1;

    desplazamiento_map_x=-160;
    desplazamiento_map_y=-160;
    desplaza = false;

    cambio = 0;
npersonaje = 8;
nmalos = 2;
malos[0].crea( (BITMAP *)datosjuego[diene001].dat, 380, 280, 3,5,2,100);
malos[1].crea( (BITMAP *)datosjuego[diene001].dat, 400, 720, 0,5,2,100);
personajes[0].crea( (BITMAP *)datosjuego[diper001].dat, 410,380, 1,1,2);
personajes[1].crea( (BITMAP *)datosjuego[diper005].dat, 280, 450, 0,2,3);
personajes[2].crea( (BITMAP *)datosjuego[diper005].dat, 230, 280, 3,2,3);
personajes[3].crea( (BITMAP *)datosjuego[diper003].dat, 960, 310, 2,3,3);
personajes[4].crea( (BITMAP *)datosjuego[diper005].dat, 1120, 450, 0,4,3);
personajes[5].crea( (BITMAP *)datosjuego[diper004].dat, 900, 650, 1,5,3);
personajes[6].crea( (BITMAP *)datosjuego[diper006].dat, 850, 800, 0,0,3);
personajes[7].crea( (BITMAP *)datosjuego[diper001].dat, 530, 280, 1,5,3);

texto.crea("Test Dialogos. Ejemplo para el Curso de CCOMP I para Manuel Loaiza ",
   font, 5,5,230,60 );

dialogo.crea("", font, 10, PANTALLA_ALTO-100, PANTALLA_ANCHO-10, PANTALLA_ALTO-10);
hablando = 0;
    musica_casa();
}

// actualiza el estado del juego
void actualiza_juego()
{

    scroll_escenario();

    evento_escenario();

    jugador.teclado();

    cambia_escenario();
}

// Se encarga de pintar todo sobre el buffer
void pinta_juego()
{
    int ancho, alto;
    int ax=0;
    int ay=0;
    int bx=0;
    int by=0;

    switch ( lugar )
    {
    case 1:   // casa
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
    case 2:   // bosque
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
    case 3:  // ciudad1
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
    default:
         break;
    }
    for ( int z=0; z < npersonaje; z++ )
{
     personajes[z].pinta();
}

for ( int z=0; z < nmalos; z++ )
 {
     malos[z].pinta();
 }
blit( fondo, buffer, ax, ay, bx, by, ancho, alto);
    blit( fondo, buffer, ax, ay, bx, by, ancho, alto);
    jugador.pinta();
    masked_blit( cielo, buffer, ax, ay, bx, by, ancho, alto);
    texto.pinta(buffer);

    if ( hablando > 1 )
        {
     dialogo.pinta(buffer);
     hablando++;
        }
    pinta_barra_vida();
    pinta_lvlup();
}
