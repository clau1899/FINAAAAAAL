#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED



#endif // AUDIO_H_INCLUDED
// audio.h

// funcion que carga todos los ficheros de audio
void musica_ciudad1(){
     play_midi((MIDI *)datosjuego[dmcity1].dat,1);
}
void sonido_pasos(){
    play_sample ( (SAMPLE *)datosjuego[dspasos].dat, 160,128, 3300, 0 );
}

void sonido_abrirpuerta(){
     play_sample ( (SAMPLE *)datosjuego[dsabrirpuerta].dat, 100,128, 1300, 0 );
}

void sonido_ambiente(){
      play_sample ( (SAMPLE *)datosjuego[dsbosque].dat, 80,128, 900, 1 );
}

void para_sonido_ambiente(){
      stop_sample( (SAMPLE *)datosjuego[dsbosque].dat );
}

void musica_casa(){
      play_midi((MIDI *)datosjuego[dmmusica1].dat,1);
}

void musica_bosque(){
      play_midi((MIDI *)datosjuego[dmmusica2].dat,1);
}
void sonido_espada_aire(){
    play_sample ( (SAMPLE *)datosjuego[dsespada1].dat, 100,128, 1200, 0 );
}

void sonido_espada_da(){
    play_sample ( (SAMPLE *)datosjuego[dsespada2].dat, 160,128, 2300, 0 );
}

void sonido_muere(){
    play_sample ( (SAMPLE *)datosjuego[dsmuerte01].dat, 120,128, 1000, 0 );
}

void sonido_espada_choca(){
    play_sample ( (SAMPLE *)datosjuego[dsespada3].dat, 110,128, 900, 0 );
}

void sonido_herido(){
    play_sample ( (SAMPLE *)datosjuego[dsaa].dat, 160,128, 900, 0 );
}

void sonido_sube_nivel(){
    play_sample ( (SAMPLE *)datosjuego[dsubenivel].dat, 110,128, 1300, 0 );
}
