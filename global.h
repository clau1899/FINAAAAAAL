#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED



#endif // GLOBAL_H_INCLUDED

// clave del fichero datafile
char evalc[19]="cursoRPGkodaygames";

DATAFILE *datosjuego;

// Ancho y alto de la pantalla
const int PANTALLA_ANCHO = 800;
const int PANTALLA_ALTO  = 600;

// En este BITMAP dibujaremos todo
BITMAP *buffer;

bool lvl_up;
int nlvlup;
int lux, luy;

// Copiar el buffer a la pantalla del juego (screen)
void pintar_pantalla()
{
    blit(buffer, screen, 0, 0, 0, 0, PANTALLA_ANCHO, PANTALLA_ALTO);
}

// controla el bucle principal
bool salir;


int cambio;

// indicará en que lugar estamos
// 1: casa
// 2: bosque
// 3: ciudad

int lugar;

int hablando;

int desplazamiento_map_x;
int desplazamiento_map_y;

BITMAP *fondo;
BITMAP *choque;
BITMAP *cielo;


// Variable usada para la velocidad
volatile unsigned int contador_tiempo_juego = 0;//fps
volatile unsigned int tiempo_total = 0;

const int FRAME_RATE =30;

// es el espacio en pixel que recorre el jugador al andar
const int desplazamiento= 120 / FRAME_RATE;

// Función para controlar la velocidad
void inc_contador_tiempo_juego()
{
    contador_tiempo_juego++;
    tiempo_total++;
}
END_OF_FUNCTION(inc_contador_tiempo_juego)
