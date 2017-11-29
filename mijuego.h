

#include "npc.h"

npc personajes[30];
int npersonaje;

enemigo malos[30];
int nmalos;

int mision;

bool desplaza;

MENSAJE dialogo;

const int scroll_rango1 = 200;
const int scroll_rango2 = 90;

void carga_escenario();

void carga_inicio()
{
    packfile_password(evalc);

    datosjuego = load_datafile("datosjuego.dat");
    if ( !datosjuego ){
       allegro_message("Error: archivo datosjuego.dat no encontrado\n%s\n", allegro_error);
    }

    datobjetos = load_datafile("objetos.dat");
    if ( !datobjetos ){
       allegro_message("Error: archivo objetos.dat no encontrado\n%s\n", allegro_error);
    }

    datotiendas = load_datafile("datostienda.dat");
    if ( !datobjetos ){
       allegro_message("Error: archivo datostienda.dat no encontrado\n%s\n", allegro_error);
    }

    lee_objetos();


    menufondo = (BITMAP *)datosjuego[dimenu].dat;
    menufondo2 = (BITMAP *)datosjuego[dimenu2].dat;
}


void carga_mapa_choque()
{
    clear_to_color( cbuffer, makecol(0, 0, 0));
    blit ( choque, cbuffer, desplazamiento_map_x, desplazamiento_map_y,0,0, PANTALLA_ANCHO, PANTALLA_ALTO);
    jugador.pon_choque();
}

// carga todo lo necesario antes de empezar el juego
void carga_juego()
{
    cambio = 0;
    carga_escenario();

    dialogo.crea("", (FONT *)datosjuego[dftextos].dat, 10, PANTALLA_ALTO-100, PANTALLA_ANCHO-10, PANTALLA_ALTO-10);
    hablando = 0;

    mision = 1;
    swraton=-1;

    swinv=0;
    muestra_tienda = false;
    swtienda=0;
}



void control_inventario(){
     if ( swinv == 0 && key[KEY_I] ){
          swinv = 1;
     }

     if ( swinv == 3 && !key[KEY_I] ) swinv=0;

     if ( swinv == 2 && key[KEY_I] ){
          swinv = 3;
     }
}

// carga los datos del escenario segun lugar
void carga_escenario()
{
    switch ( lugar )
    {

    case 1:// bosque
              fondo  = (BITMAP *)datosjuego[dimenut].dat;
              choque = (BITMAP *)datosjuego[dimenutchoque].dat;
              cielo  = (BITMAP *)datosjuego[dimenutsup].dat;

              desplaza=true;
              carga_mapa_choque();
              sonido_ambiente();
              musica_bosque();
         break;


    case 2:// casa
              fondo  = (BITMAP *)datosjuego[dicasa].dat;
              choque = (BITMAP *)datosjuego[dicasachoque].dat;
              cielo  = (BITMAP *)datosjuego[dicasasup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;

    case 3:// bosque
              fondo  = (BITMAP *)datosjuego[dibosque].dat;
              choque = (BITMAP *)datosjuego[dibosquechoque].dat;
              cielo  = (BITMAP *)datosjuego[dibosquesup].dat;

              desplaza=true;
              carga_mapa_choque();
              sonido_ambiente();
              musica_bosque();
         break;

    case 4:// ciudad
              fondo  = (BITMAP *)datosjuego[dicity1].dat;
              choque = (BITMAP *)datosjuego[dicity1choque].dat;
              cielo  = (BITMAP *)datosjuego[dicity1sup].dat;

              desplaza=true;
              carga_mapa_choque();
              if ( cambio == 0 ) musica_ciudad1();
         break;
    case 5:// tienda1
              fondo  = (BITMAP *)datosjuego[ditienda1].dat;
              choque = (BITMAP *)datosjuego[ditienda1choque].dat;
              cielo  = (BITMAP *)datosjuego[ditienda1sup].dat;
              carga_mapa_choque();
              desplaza=false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              if ( cambio == 0 ) musica_ciudad1();
         break;

    case 6:// elfo1 ciudad
              fondo  = (BITMAP *)datosjuego[dieciudad].dat;
              choque = (BITMAP *)datosjuego[dieciudadchoque].dat;
              cielo  = (BITMAP *)datosjuego[dieciudadsup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;

    case 7:// guerrero1 campo
              fondo  = (BITMAP *)datosjuego[digcampo].dat;
              choque = (BITMAP *)datosjuego[digcampochoque].dat;
              cielo  = (BITMAP *)datosjuego[digcamposup].dat;

              desplaza=false;
              carga_mapa_choque();
              if ( cambio == 0 ) musica_ciudad1();
         break;
    case 8:// elfo2 camino
              fondo  = (BITMAP *)datosjuego[diecaminochoque].dat;
              choque = (BITMAP *)datosjuego[diecaminochoque].dat;
              cielo  = (BITMAP *)datosjuego[diecaminosup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 9:// elfo3 castillo
              fondo  = (BITMAP *)datosjuego[diecastillo].dat;
              choque = (BITMAP *)datosjuego[diecastillochoque].dat;
              cielo  = (BITMAP *)datosjuego[diecastillosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 10:// elfo4 cuarto
              fondo  = (BITMAP *)datosjuego[diecuarto].dat;
              choque = (BITMAP *)datosjuego[diecuartochoque].dat;
              cielo  = (BITMAP *)datosjuego[diecuartosup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 11:// elfo5 goal
              fondo  = (BITMAP *)datosjuego[diegoal].dat;
              choque = (BITMAP *)datosjuego[diegoalchoque].dat;
              cielo  = (BITMAP *)datosjuego[diegoalsup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 12:// guerrero2 pueblo
              fondo  = (BITMAP *)datosjuego[digpueblo].dat;
              choque = (BITMAP *)datosjuego[digpueblochoque].dat;
              cielo  = (BITMAP *)datosjuego[digpueblosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 13:// guerrero3 torre
              fondo  = (BITMAP *)datosjuego[digtorre].dat;
              choque = (BITMAP *)datosjuego[digtorrechoque].dat;
              cielo  = (BITMAP *)datosjuego[digtorresup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 14:// guerrero4 castillo
              fondo  = (BITMAP *)datosjuego[digcastillo].dat;
              choque = (BITMAP *)datosjuego[digcastillochoque].dat;
              cielo  = (BITMAP *)datosjuego[digcastillosup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 15:// mago1 cuarto
              fondo  = (BITMAP *)datosjuego[dimcuarto].dat;
              choque = (BITMAP *)datosjuego[dimcuartochoque].dat;
              cielo  = (BITMAP *)datosjuego[dimcuartosup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 16:// mago2 castillo
              fondo  = (BITMAP *)datosjuego[dimcastillo].dat;
              choque = (BITMAP *)datosjuego[dimcastillochoque].dat;
              cielo  = (BITMAP *)datosjuego[dimcastillosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 17:// mago3 bosque
              fondo  = (BITMAP *)datosjuego[dimbosque].dat;
              choque = (BITMAP *)datosjuego[dimbosquechoque].dat;
              cielo  = (BITMAP *)datosjuego[dimbosquesup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 18:// mago4 oasis
              fondo  = (BITMAP *)datosjuego[dimoasis].dat;
              choque = (BITMAP *)datosjuego[dimoasischoque].dat;
              cielo  = (BITMAP *)datosjuego[dimoasissup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 19:// mago5 pueblo1
              fondo  = (BITMAP *)datosjuego[dimpueblo1].dat;
              choque = (BITMAP *)datosjuego[dimpueblo1choque].dat;
              cielo  = (BITMAP *)datosjuego[dimcastillosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 20:// mago6 pueblo2
              fondo  = (BITMAP *)datosjuego[dimpueblo2].dat;
              choque = (BITMAP *)datosjuego[dimpueblo2choque].dat;
              cielo  = (BITMAP *)datosjuego[dimcastillosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 21:// rogue1 cuarto
              fondo  = (BITMAP *)datosjuego[dircuarto].dat;
              choque = (BITMAP *)datosjuego[dircuartochoque].dat;
              cielo  = (BITMAP *)datosjuego[dircuartosup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 22:// rogue2 casa
              fondo  = (BITMAP *)datosjuego[dircasa].dat;
              choque = (BITMAP *)datosjuego[dircasachoque].dat;
              cielo  = (BITMAP *)datosjuego[dircasasup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 23:// rogue3 pueblo
              fondo  = (BITMAP *)datosjuego[dirpueblo].dat;
              choque = (BITMAP *)datosjuego[dirpueblochoque].dat;
              cielo  = (BITMAP *)datosjuego[dirpueblosup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 24:// rogue4 ladrones
              fondo  = (BITMAP *)datosjuego[dirladrones].dat;
              choque = (BITMAP *)datosjuego[dirladroneschoque].dat;
              cielo  = (BITMAP *)datosjuego[dirladronessup].dat;

              carga_mapa_choque();
              desplaza = true;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;
    case 25:// rogue5 goal
              fondo  = (BITMAP *)datosjuego[dirgoal].dat;
              choque = (BITMAP *)datosjuego[dirgoalchoque].dat;
              cielo  = (BITMAP *)datosjuego[dirgoalsup].dat;

              carga_mapa_choque();
              desplaza = false;
              if ( cambio != 0 ) sonido_abrirpuerta();
              musica_casa();
         break;

    }
}

// ***** inicio scroll

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

//****** fin scroll


//***** inicia cambio escenario

void cambia_escenario()
{

    switch ( lugar )
    {

    case 1:
          if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // warrior1
              lugar = 7;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 382,264 );
              jugador.prota =(BITMAP *)datosjuego[diguerrero].dat;
              desplazamiento_map_x=-160;

              desplazamiento_map_y=-160;

              sonido_abrirpuerta();
              para_sonido_ambiente();
              cambio = 0;
         }
         if ( cambio == 3 )
         {
              // cambiamos a otro lugar
              // elfo1
              lugar = 6;
              carga_escenario();
              // situamos al prota en el camino
              jugador.posiciona( 360,300 );
              jugador.prota =(BITMAP *)datosjuego[dielfo].dat;
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              para_sonido_ambiente();
              musica_ciudad1();
              cambio = 0;
         }
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // mago1
              lugar = 15;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 382,264 );
              jugador.prota =(BITMAP *)datosjuego[dimago].dat;
              desplazamiento_map_x=-160;

              desplazamiento_map_y=-160;

              sonido_abrirpuerta();
              para_sonido_ambiente();
              cambio = 0;
         }
         if ( cambio == 4 )
         {
              // cambiamos a otro lugar
              // rogue1
              lugar = 21;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 382,264 );
              jugador.prota =(BITMAP *)datosjuego[dipicaro].dat;
              desplazamiento_map_x=-160;

              desplazamiento_map_y=-160;

              sonido_abrirpuerta();
              para_sonido_ambiente();
              cambio = 0;
         }
         break;
    case 2:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 3;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         break;
    case 3:   // bosque
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // casa
              lugar = 2;
              carga_escenario();
              // situamos al prota cerca de la puerta
              jugador.posiciona( 290,440 );
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
              lugar = 4;
              carga_escenario();
              // situamos al prota en el camino
              jugador.posiciona( 500,540 );
              desplazamiento_map_x=950;
              desplazamiento_map_y=508;
              para_sonido_ambiente();
              musica_ciudad1();
              cambio = 0;
         }
         break;
    case 4:   // ciudad
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 3;
              carga_escenario();
              // situamos al prota en el camino del bosque
              jugador.posiciona( 650,30 );
              desplazamiento_map_x=200;
              desplazamiento_map_y=0;
              cambio = 0;
         }
         // color amarillo que existen muchos
         if ( cambio == 3 && desplazamiento_map_x > 800 )
         {
              // cambiamos a otro lugar
              // tienda1
              lugar = 5;
              carga_escenario();
              // situamos al prota en el camino del bosque
              jugador.posiciona( 376,460 );
              desplazamiento_map_x=-170;
              desplazamiento_map_y=-100;

              cambio = 0;
         }
         break;
    case 5:   // tienda1
         if ( cambio == 1)
         {
              // cambiamos a la ciudad
              lugar=4;
              carga_escenario();
              jugador.posiciona( 400,300 );
              desplazamiento_map_x=1090;
              desplazamiento_map_y=85;
              cambio = 0;
              sonido_abrirpuerta();
         }
         break;
    case 6:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 8;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;


         }
         break;
    case 7:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 12;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 490,446 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         break;
    case 8:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 6;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 9;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;
         }
         break;
    case 9:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 11;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 10;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;
         }
         break;
    case 10:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 9;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;


         }
         break;
    case 11:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 9;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;


         }
         break;
    case 12:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 7;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 13;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 658,454 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;
         }
         break;
    case 13:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 14;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;
              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 12;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;
         }
         break;
    case 14:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 13;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         break;
    case 15:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 16;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;
              cambio = 0;


         }
         break;
    case 16:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 15;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 17;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 17:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 18;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 480,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 16;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
             desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 18:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 19;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;


         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 17;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 19:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 20;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 18;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 480,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 20:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 19;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=160;
              cambio = 0;


         }
         break;
    case 21:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 22;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
             desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;


         }
         break;
    case 22:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 21;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;


         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 23;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 23:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 24;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;


         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 22;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
             desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;
         }
         break;
    case 24:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 23;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
             desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;


         }
         if ( cambio == 2 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 25;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=-160;
              desplazamiento_map_y=-160;

              cambio = 0;
         }
         break;
    case 25:   // casa
         if ( cambio == 1 )
         {
              // cambiamos a otro lugar
              // bosque
              lugar = 24;
              carga_escenario();
              // situamos al prota dentro de la casa
              jugador.posiciona( 410,370 );
              desplazamiento_map_x=0;
              desplazamiento_map_y=0;

              cambio = 0;


         }
         break;
   default:
         break;
    }
    carga_mapa_choque();
}

//***** fin cambio escenario


//*** inicia eventos escenario
void evento_escenario()
{
    int pzx = jugador.getx() + desplazamiento_map_x;
    int pzy = jugador.gety() + desplazamiento_map_y;


    switch ( lugar )
    {
    case 2:// casa
         break;
    case 3:   // bosque
         break;
    case 4:   // ciudad

        if ( personajes[0].posicion_cerca()
               && jugador.accion() && !jugador.hablando() )
         {
              dialogo.cambia_texto(" Dejame!! estoy ocupadooooo!! ");
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

    case 5: // en la tienda

         if ( personajes[8].getestado() == 6 && cambio == 0 && !personajes[8].posicion_cerca())
         {
              personajes[8].cambia_estado(0);
         }
         if ( personajes[9].getestado() == 6 && cambio == 0 && !personajes[9].posicion_cerca())
         {
              personajes[9].cambia_estado(0);
         }

         if ( cambio == 2 && jugador.getx()< 400 )
         {
              personajes[9].cambia_estado(6);
              cambio = 0;
         }
         if ( cambio == 2 && jugador.getx()> 400 )
         {
              personajes[8].cambia_estado(6);
              cambio = 0;
         }

         if ( personajes[8].posicion_cerca() )
         {
              personajes[8].cambia_estado(6);
         }

         if ( personajes[9].posicion_cerca() )
         {
              personajes[9].cambia_estado(6);
         }

         if ( personajes[8].posicion_cerca(9) &&  personajes[8].alineado_vertical()
              && jugador.accion() && !personajes[8].posicion_cerca(2) )
         {
              lee_tienda(2);
              muestra_tienda = true;
         }

         if ( personajes[9].posicion_cerca(9) &&  personajes[9].alineado_vertical()
              && jugador.accion() && !personajes[9].posicion_cerca(2) )
         {
              lee_tienda(1);
              muestra_tienda = true;
         }


         if (  personajes[8].frente() && jugador.accion() &&
               !jugador.hablando() && personajes[8].posicion_cerca())
         {
                  dialogo.cambia_texto(" Y tu que estas mirando!! " );
                  hablando = 1;
         }

         if ( personajes[9].frente() && jugador.accion() &&
              !jugador.hablando() && personajes[9].posicion_cerca())
         {
                  dialogo.cambia_texto(" Vienes a comprar ? " );
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

//*** fin eventos escenario


// nuevo actualiza
void actualiza_juego()
{

    scroll_escenario();

    evento_escenario();

    jugador.teclado();

    control_inventario();

    cambia_escenario();
}


void pinta_inventario()
{
     if ( swinv >  0 )
     {

          int jx = jugador.getx();
          int jy = jugador.gety();
          int posx;
          int posy;

          if ( jx > PANTALLA_ANCHO/2 ){
               jx = (PANTALLA_ANCHO/4) - 160;
          }else{
               jx = (PANTALLA_ANCHO*3/4) - 160;
          }

          if ( jy > PANTALLA_ALTO/2 ){
               jy = (PANTALLA_ALTO/4) - 81;
          }else{
               jy = (PANTALLA_ALTO*3/4) - 81;
          }

          // se muestra fondo inventario
          masked_blit( (BITMAP *)datosjuego[diinventario].dat, buffer, 0,0, jx,jy, 320,162);

    if ( swraton == 1 && mouse_b&2 )
    {
         swraton = -2;
    }

          masked_blit( jugador.getimg(), buffer, 32,0, jx+65,jy+60, 32,32);

    if ( jugador.getcasco() != -1 )
    {
         masked_blit((BITMAP *)datobjetos[equipo_personaje(jugador.getcasco())].dat, buffer, 32, 0, jx+65, jy+60, 32,32);
    }


          posx=jx+116;
          posy=jy+40;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic
                         swraton = 1;
                         nsel = -4;
                         nid = jugador.getanillo();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getanillo() && tipo(nid) == 4 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getanillo() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getanillo());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_anillo(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }


          if ( jugador.getanillo() != -1 )
          {
             masked_blit( (BITMAP *)datobjetos[id_img_objeto( jugador.getanillo())].dat, buffer, 0,0, jx+116,jy+40, 32,32);
          }

          posx=jx+116;
          posy=jy+74;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -1;
                         nid = jugador.getarmadura();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getarmadura() && tipo(nid) == 3 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getarmadura() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getarmadura());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_armadura(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }

          if ( jugador.getarmadura() != -1 )
          {
             masked_blit( (BITMAP *)datobjetos[id_img_objeto( jugador.getarmadura())].dat, buffer, 0,0, jx+116,jy+74, 32,32);
          }


          posx=jx+13;
          posy=jy+74;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -2;
                         nid = jugador.getarma();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getarma() && tipo(nid) == 1 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getarma() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getarma());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_arma(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }


          if ( jugador.getarma() != -1 )
          {
             masked_blit( (BITMAP *)datobjetos[id_img_objeto( jugador.getarma())].dat, buffer, 0,0, jx+13,jy+74, 32,32);
          }

          posx=jx+13;
          posy=jy+40;
          if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
          {
              if ( mouse_b&1 && swraton != -2)
               {
                    // se ha pulsado dentro de un hueco
                    if ( swraton == -1 )
                    {
                         // primer clic

                         swraton = 1;
                         nsel = -3;
                         nid = jugador.getcasco();
                         if ( nid == -1 ){
                               swraton = -1;
                         }else{
                            sonido_boton2();
                         }
                    }else{

                         if ( nid != jugador.getcasco() && tipo(nid) == 2 )
                         {
                              // cambia objeto de sitio
                              if ( jugador.getcasco() != -1 ){
                                 jugador.pon_inventario(nsel,jugador.getcasco());
                              }else{
                                 jugador.pon_inventario(nsel,0);
                              }


                              jugador.pon_casco(nid);
                              sonido_boton();

                              swraton = -2;
                          }
                    }
               }
          }

          if ( jugador.getcasco() != -1 )
          {
             masked_blit( (BITMAP *)datobjetos[id_img_objeto( jugador.getcasco())].dat, buffer, 0,0, jx+13,jy+40, 32,32);
          }

          int id;
          for ( int i=0; i< 4; i++){
              for ( int j=0; j<3; j++){
                  int num = (j*4) + i ;
                  id = jugador.getinventario( num );
                  posx = jx + 172 + i*34;
                  posy = jy + 40 + j*34;
                  if ( id != 0 ){
                      masked_blit( (BITMAP *)datobjetos[id_img_objeto( id)].dat, buffer, 0,0, posx,posy, 32,32);
                  }
                  if ( mouse_x > posx && mouse_x < posx+32 && mouse_y > posy && mouse_y < posy+32 )
                  {
                       if ( mouse_b&1 && swraton != -2)
                       {
                            // se ha pulsado dentro de un hueco
                            if ( swraton == -1 )
                            {
                                 // primer clic
                                 if ( id != 0 )
                                 {
                                      swraton = 1;
                                      nsel = num;
                                      nid  = id;
                                      sonido_boton2();
                                 }
                            }else{

                               if ( nsel >= 0 )
                               {
                                 if ( nsel != num && nsel != -1)
                                 {
                                      // cambia objeto de sitio
                                      jugador.cambia_inventario(nsel,num);
                                      sonido_boton();
                                      swraton = -2;
                                  }
                               }else{

                                 // ha quitado algo del ekipo
                                 if ( nsel == -1 && (tipo(id) == 3 || id == 0) )
                                 {
                                      // armadura
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_armadura( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                                 if ( nsel == -2 && (tipo(id) == 1 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_arma( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                                 if ( nsel == -3 && (tipo(id) == 2 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_casco( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }

                                 if ( nsel == -4 && (tipo(id) == 4 || id == 0) )
                                 {
                                      // arma
                                      jugador.pon_inventario( num, nid );
                                      if ( id == 0 ) id = -1;
                                      jugador.pon_anillo( id );
                                      sonido_boton();
                                      swraton = -2;
                                 }
                               }
                            }
                       }

                  }
                  if ( swraton == -2 && !mouse_b&1 ) swraton=-1;
              }
          }

          if ( !key[KEY_I]) swinv = 2;
     }
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
    case 1:   // charselect
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;

    case 2:   // casa
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
    case 3:   // bosque
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
    case 4:  // ciudad1
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
  case 5: // tienda1
             bx = 170;
             by = 100;
             ancho = 448;
             alto = 416;
             break;
 case 6:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;

case 7:   // g1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 8:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 9:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 10:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 11:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 12:   // elfo1
              ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;

case 13:   // elfo1
              ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 14:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 15:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;

case 16:   // elfo1
             ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;

case 17:   // elfo1
              ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 18:   // elfo1
              ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 19:   // elfo1
              ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;

case 20:   // elfo1
             ax = desplazamiento_map_x;
             ay = desplazamiento_map_y;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;

case 21:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
case 22:   // elfo1
             ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 23:   // elfo1
             ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 24:   // elfo1
             ax = 0;
             ay = 0;
             ancho = PANTALLA_ANCHO;
             alto  = PANTALLA_ALTO;
             break;
case 25:   // elfo1
             bx=160;
             by=160;
             ancho = 480;
             alto = 325;
             break;
    default:
         break;
    }


    blit( fondo, buffer, ax, ay, bx, by, ancho, alto);

    for ( int z=0; z < npersonaje; z++ )
    {
         personajes[z].pinta();
    }

    for ( int z=0; z < nmalos; z++ )
    {
        malos[z].pinta();
    }

    jugador.pinta();

    masked_blit( cielo, buffer, ax, ay, bx, by, ancho, alto);

    if ( hablando > 1 )
    {
         dialogo.pinta(buffer);
         hablando++;
    }

    pinta_barra_vida();
    pinta_lvlup();
    pinta_inventario();

    pinta_tienda();
}
