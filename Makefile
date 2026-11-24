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
SRC      := main.cpp
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra
LDLIBS   :=

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

.PHONY: all run bench bench-pantalla clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

bench: $(TARGET)
	@for n in 10 20 40 64; do ./$(TARGET) --bench $$n --sin-pantalla; echo; done

bench-pantalla: $(TARGET)
	@for n in 10 20 40 64; do ./$(TARGET) --bench $$n; echo; done

clean:
	rm -f $(TARGET) $(TARGET).exe
