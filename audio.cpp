// Implementacion del modulo Audio con miniaudio (WAV por software, sin
// dependencias del sistema mas alla del dispositivo de audio).
#include "audio.h"

#define MA_NO_ENCODING
#define MA_NO_GENERATION
#define MA_NO_MP3
#define MA_NO_FLAC
#define MA_NO_VORBIS
#define MINIAUDIO_IMPLEMENTATION
#if defined(__GNUC__)
// miniaudio dispara falsos positivos de -Wstringop-overflow con -O2 en GCC.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#endif
#include "third_party/miniaudio.h"
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

// Rutas reales de los archivos dentro del proyecto.
static const char* RUTA_MUSICA[Audio::MUSICA_TOTAL] = {
    nullptr,
    "MUSIC/JUNE_MENU.wav",
    "MUSIC/JUNE_BATTLE.wav",
    "MUSIC/JUNE_BOSS.wav",
    "MUSIC/JUNE_SHOP.wav",
};

static const char* RUTA_ATAQUE = "MUSIC/JUNE_ATTACK.wav";
static const char* RUTA_DANO   = "MUSIC/JUNE_HURT.wav";
static const char* RUTA_MEJORA = "MUSIC/JUNE_POWER.wav";
static const char* RUTA_DISPARO = "MUSIC/JUNE_SHOOT.wav";
static const char* RUTA_SELECCION = "MUSIC/JUNE_SELECT.wav";

// Volumen relativo de la musica respecto de los efectos: la musica no debe
// tapar los sonidos de combate.
static const float VOLUMEN_MUSICA = 0.65f;

struct Audio::Impl {
    ma_engine motor;
    bool listo = false;
    ma_sound pista[MUSICA_TOTAL];
    bool pistaIniciada[MUSICA_TOTAL] = {};
    bool pistaFallo[MUSICA_TOTAL] = {};
    int actual = MUSICA_NINGUNA;
    int volumen = -1;
};

Audio::~Audio() { cerrar(); }

void Audio::iniciar() {
    if (impl) return;
    impl = new Impl();

    if (ma_engine_init(nullptr, &impl->motor) != MA_SUCCESS) {
        // Sin dispositivo de audio: el juego sigue en silencio.
        impl->listo = false;
        return;
    }
    impl->listo = true;
    ajustarVolumen(60);
}

void Audio::cerrar() {
    if (!impl) return;
    if (impl->listo) {
        for (int i = MUSICA_NINGUNA + 1; i < MUSICA_TOTAL; i++) {
            if (impl->pistaIniciada[i]) ma_sound_uninit(&impl->pista[i]);
        }
        ma_engine_uninit(&impl->motor);
    }
    delete impl;
    impl = nullptr;
}

void Audio::reproducirMusica(Musica m) {
    if (!impl || !impl->listo) return;
    if (m < MUSICA_NINGUNA || m >= MUSICA_TOTAL) return;
    if (m == impl->actual) return;

    if (impl->actual != MUSICA_NINGUNA && impl->pistaIniciada[impl->actual])
        ma_sound_stop(&impl->pista[impl->actual]);
    impl->actual = m;
    if (m == MUSICA_NINGUNA) return;
    if (impl->pistaFallo[m]) { impl->actual = MUSICA_NINGUNA; return; }

    if (!impl->pistaIniciada[m]) {
        ma_uint32 flags = MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_LOOPING |
                          MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION;
        if (ma_sound_init_from_file(&impl->motor, RUTA_MUSICA[m], flags, nullptr, nullptr,
                                    &impl->pista[m]) != MA_SUCCESS) {
            impl->pistaFallo[m] = true;     // no reintentar en cada cuadro
            impl->actual = MUSICA_NINGUNA;
            return;
        }
        impl->pistaIniciada[m] = true;
        ma_sound_set_volume(&impl->pista[m], VOLUMEN_MUSICA);
    }

    // Cada cambio de estado empieza la pista desde el principio.
    ma_sound_seek_to_pcm_frame(&impl->pista[m], 0);
    ma_sound_start(&impl->pista[m]);
}

void Audio::ajustarVolumen(int volumen) {
    if (!impl || !impl->listo) return;
    if (volumen < 0) volumen = 0;
    if (volumen > 100) volumen = 100;
    if (volumen == impl->volumen) return;
    impl->volumen = volumen;
    ma_engine_set_volume(&impl->motor, volumen / 100.0f);
}

void Audio::efecto(const char* ruta) {
    if (!impl || !impl->listo) return;
    // Sonido de una sola vez con mezcla propia: varios efectos pueden sonar a
    // la vez sin cortarse entre si.
    ma_engine_play_sound(&impl->motor, ruta, nullptr);
}

void Audio::ataque()    { efecto(RUTA_ATAQUE); }
void Audio::dano()      { efecto(RUTA_DANO); }
void Audio::mejora()    { efecto(RUTA_MEJORA); }
void Audio::disparo()   { efecto(RUTA_DISPARO); }
void Audio::seleccion() { efecto(RUTA_SELECCION); }
