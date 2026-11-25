// Audio - musica de fondo y efectos de sonido de The Legend of June.
//
// Usa miniaudio (third_party/miniaudio.h), que reproduce WAV en Windows, Linux
// y macOS sin dependencias externas salvo las del sistema. Si el dispositivo de
// audio no esta disponible, todos los metodos quedan en silencio y el juego
// sigue funcionando igual.
#pragma once

class Audio {
public:
    // Pistas de musica de fondo. MUSICA_NINGUNA detiene la musica actual.
    enum Musica {
        MUSICA_NINGUNA = 0,
        MUSICA_MENU,
        MUSICA_BATALLA,
        MUSICA_JEFE,
        MUSICA_TIENDA,
        MUSICA_TOTAL
    };

    Audio() {}
    ~Audio();
    Audio(const Audio&) = delete;
    Audio& operator=(const Audio&) = delete;

    void iniciar();
    void cerrar();

    // Cambia de pista (no hace nada si ya se esta reproduciendo esa misma).
    void reproducirMusica(Musica m);
    void detenerMusica() { reproducirMusica(MUSICA_NINGUNA); }

    // Volumen general 0..100; se aplica a musica y efectos por igual.
    void ajustarVolumen(int volumen);

    // Efectos de sonido (los archivos viven en MUSIC/).
    void ataque();
    void dano();
    void mejora();
    void disparo();
    void seleccion();

private:
    struct Impl;
    Impl* impl = nullptr;

    void efecto(const char* ruta);
};
