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

## Equipo

| Integrante |
| :--- |
| Andrés Rodríguez Orozco |
| Sebastián Marín Mora |
| Julián Solórzano Hernández |
| Abril González Morales |

## Postscript

This version of The Legend of June was developed collaboratively by me and several other contributors. Unfortunately, due to time constraints, it was never fully prepared for its original presentation. Nevertheless, I decided to finish the project and bring it to a completed state. While it may not have made it to the intended showcase, the work put into it deserves recognition. Credit where credit is due: everyone who contributed to making this project possible. The link for the original game is: https://github.com/Moth-Logic/The-Legend-of-June

## Licencia

Dominio público — [The Unlicense](LICENSE).
