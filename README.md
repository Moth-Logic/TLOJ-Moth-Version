<p align="center">
  <img src="ASSETS/LOGO.png" alt="The Legend of June" width="460">
</p>

Juego ASCII de supervivencia para la terminal, inspirado en *The Legend of Zelda*. Esquivá
proyectiles, atacá con la espada y sobreviví oleadas cada vez más difíciles.

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++17">
  <img src="https://img.shields.io/badge/ncurses-UI-4E4E4E?style=for-the-badge&logo=gnometerminal&logoColor=white" alt="ncurses">
  <img src="https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt="Linux">
  <img src="https://img.shields.io/badge/Raspberry%20Pi%204%20B-A22846?style=for-the-badge&logo=raspberrypi&logoColor=white" alt="Raspberry Pi 4 B">
  <img src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=gnumake&logoColor=white" alt="GNU Make">
  <img src="https://img.shields.io/badge/30%20FPS-punto%20fijo-8A2BE2?style=for-the-badge" alt="30 FPS, punto fijo">
  <img src="https://img.shields.io/badge/Licencia-Unlicense-blue?style=for-the-badge&logo=opensourceinitiative&logoColor=white" alt="Unlicense">
</p>

Proyecto del curso **Arquitectura de Computadores** (TEC). Esta versión es la **Etapa 2**:
el juego completo en C++ con ncurses, probado en Raspberry Pi 4 B.

### Tecnologías

| | Tecnología | Qué aporta |
| :---: | :--- | :--- |
| 🧠 | **C++17** | Todo el juego en un solo `main.cpp`: lógica, IA de enemigos y render. |
| 🖥️ | **ncurses** | Dibujado en la terminal y lectura de teclado sin bloqueo. |
| 🍓 | **Raspberry Pi 4 B** | Plataforma de prueba del rendimiento. |
| ⚙️ | **GNU Make** | Compilación y objetivos `run`, `bench`, `bench-pantalla`. |
| 📟 | **Punto fijo (8 bits)** | Posiciones y velocidades sin punto flotante. |

## Cómo se juega

- 10 puntos de vida, dibujados como `[##########]`; cada golpe quita uno.
- Al morir, un enemigo puede soltar un corazón que recupera vida.
- Tres tipos de enemigo: soldados, arqueros y magos.
- La partida corre a 30 cuadros por segundo, sin punto flotante (posiciones en punto fijo).

## Controles

| Acción | Teclas |
| :--- | :--- |
| Iniciar | `Enter` |
| Mover | Flechas o `W` `A` `S` `D` |
| Atacar | `Espacio` |
| Pausa | `P` |
| Salir | `Q` o `Esc` |

## Mapas

Quince mapas de 60×20 celdas, en `mapa1.txt` … `mapa15.txt`: Clasico, Cruz, Cuatro cuartos,
Barras, Columnas, Serpiente, Pasillos, Anillos, Zigzag, Gemelos, Aspa, Fortaleza, Puertas,
Espiral y Campos. Para crear uno propio, copiá cualquiera y respetá el tamaño.

## Compilar y ejecutar

Requisitos: g++ con C++17, ncurses y una terminal de al menos 80×24.

```bash
sudo apt install build-essential libncurses-dev
make
./june
```

`make run` compila y ejecuta en un paso.

## Rendimiento

```bash
make bench              # N = 10, 20, 40 y 64, sin pantalla
make bench-pantalla     # igual, pero midiendo también refresh() de ncurses
./june --bench N        # una sola medición
```

Reporta microsegundos por cuadro (lógica, dibujado y `refresh()`), el costo aislado de
`mover_entidades`, `colisiones` y `copiar_sprite`, y la fracción del cuadro que ocupan las
rutinas (dato para la Ley de Amdahl). `--sin-pantalla` no dibuja, así que no mide `refresh()`.

## Equipo

| Integrante |
| :--- |
| Andrés Rodríguez Orozco |
| Sebastián Marín Mora |
| Julián Solórzano Hernández |
| Abril González Morales |

## Licencia

Dominio público — [The Unlicense](LICENSE).
