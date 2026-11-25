# Makefile - The Legend of June
# Arquitectura de Computadores, TEC, II Semestre 2026
#
# Uso:
#   make                 compila el juego                        -> ./june
#   make run             compila y ejecuta
#   make bench           corre --bench para N = 10, 20, 40 y 64 (sin pantalla)
#   make bench-pantalla  igual, pero con pantalla (mide refresh() de ncurses)
#   make clean           borra lo compilado
#
# Requisitos en Raspberry Pi OS / Debian:
#   sudo apt install build-essential libncurses-dev
#
# En MSYS2 (Windows):
#   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-ncurses make

CXX      ?= g++
TARGET   := june
SRC      := main.cpp audio.cpp
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDLIBS   :=
UNAME_S  := $(shell uname -s)

# ncurses: en Linux el header es <ncurses.h>; en MSYS2/MinGW queda en
# include/ncursesw, asi que se busca en ambos lugares.
NCURSES_CFLAGS := $(shell pkg-config --cflags ncursesw 2>/dev/null)
NCURSES_LIBS   := $(shell pkg-config --libs ncursesw 2>/dev/null)

ifeq ($(strip $(NCURSES_LIBS)),)
    ifneq ($(wildcard /usr/include/ncurses.h /usr/include/ncursesw/ncurses.h),)
        NCURSES_LIBS := -lncursesw
    else ifneq ($(wildcard /mingw64/include/ncursesw/ncurses.h),)
        NCURSES_CFLAGS := -I/mingw64/include/ncursesw
        NCURSES_LIBS   := -lncursesw
    else
        NCURSES_LIBS := -lncurses
    endif
endif

CXXFLAGS += $(NCURSES_CFLAGS)
LDLIBS   += $(NCURSES_LIBS)

# miniaudio carga ALSA/PulseAudio en Linux (dlopen) y usa los winmm/ole32 de
# Windows; no requiere instalar ninguna biblioteca de audio aparte.
ifneq (,$(findstring MINGW,$(UNAME_S)))
    LDLIBS += -lwinmm -lole32
else ifneq (,$(findstring MSYS,$(UNAME_S)))
    LDLIBS += -lwinmm -lole32
else
    LDLIBS += -lm -ldl -lpthread
    # En Raspberry Pi OS de 32 bits (armhf) el CPU no tiene atomicos de 64
    # bits lock-free, asi que miniaudio termina llamando a __atomic_load_8 /
    # __atomic_store_8 / __atomic_compare_exchange_8, que viven en libatomic.
    # Se enlaza solo si el compilador la tiene disponible.
    LIBATOMIC := $(shell $(CXX) -print-file-name=libatomic.so)
    ifeq ($(LIBATOMIC),libatomic.so)
        LIBATOMIC := $(shell $(CXX) -print-file-name=libatomic.a)
    endif
    ifneq ($(LIBATOMIC),libatomic.a)
        LDLIBS += -latomic
    endif
endif

.PHONY: all run bench bench-pantalla clean

all: $(TARGET)

$(TARGET): $(SRC) audio.h third_party/miniaudio.h
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

bench: $(TARGET)
	@for n in 10 20 40 64; do ./$(TARGET) --bench $$n --sin-pantalla; echo; done

bench-pantalla: $(TARGET)
	@for n in 10 20 40 64; do ./$(TARGET) --bench $$n; echo; done

clean:
	rm -f $(TARGET) $(TARGET).exe
