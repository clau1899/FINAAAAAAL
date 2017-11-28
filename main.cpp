// programa principal

#include <iostream>
#include <allegro.h>
#include "global.h"
#include "datosjuego.h"
#include "audio.h"
#include "dialogos.h"
#include "players.h"
#include "mijuego.h"

using namespace std;

void inicia_allegro()
{
 allegro_init();
 install_keyboard();

 set_color_depth(32);
 set_gfx_mode(GFX_AUTODETECT_WINDOWED, PANTALLA_ANCHO, PANTALLA_ALTO, 0, 0);

 buffer = create_bitmap(PANTALLA_ANCHO, PANTALLA_ALTO);
 // incializa el audio en allegro
 if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
   allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);

}

// inicializa todo lo referente al sonido
    set_volume(230, 90);

    LOCK_VARIABLE(contador_tiempo_juego);
    LOCK_FUNCTION(inc_contador_tiempo_juego);

    // Iniciamos el limitador de FPS
    install_int_ex(inc_contador_tiempo_juego, BPS_TO_TIMER( FRAME_RATE ));
    srand (time(NULL));
}

int main()
{
        inicia_allegro();

        carga_juego();

 salir = false;


 while (!salir)
 {
          if ( contador_tiempo_juego )
          {
                while ( contador_tiempo_juego )
                {
                    actualiza_juego();

                    contador_tiempo_juego--;
                }

                clear_to_color(buffer, 0x00000);

                pinta_juego();

                pintar_pantalla();

          }else{

               rest(1);
          }
       // tecla de salida
       if ( key[KEY_ESC] ) salir = true;
    }
 unload_datafile(datosjuego);
 destroy_bitmap(buffer);

 return 0;
}
END_OF_MAIN();
