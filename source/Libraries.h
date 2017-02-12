#ifndef _LIBRARIES_H_
#define _LIBRARIES_H_

/* This file is part of Evolution Sav3D Me!

Copyright (C) 2016 Manuel Rodríguez Matesanz
>    This program is free software: you can redistribute it and/or modify
>    it under the terms of the GNU General Public License as published by
>    the Free Software Foundation, either version 3 of the License, or
>    (at your option) any later version.
>
>    This program is distributed in the hope that it will be useful,
>    but WITHOUT ANY WARRANTY; without even the implied warranty of
>    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
>    GNU General Public License for more details.
>
>    You should have received a copy of the GNU General Public License
>    along with this program.  If not, see <http://www.gnu.org/licenses/>.
>    See LICENSE for information.
*/

// Librerías de la Scene
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include <sftd.h>
#include "sound.h"
#include "BmpFont.h"

// Librerías de C++
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <sstream>
#include <stdarg.h>
#include <cstdio>
#include <math.h>
#include <fstream>
#include <vector> 
#include<fstream>
#include <unistd.h>

// Colores 
#define C_BLACK RGBA8(0, 0, 0, 255)
#define C_WHITE RGBA8(255, 255, 255, 255)
#define C_GREY RGBA8(127, 127, 127, 255)
#define C_RED RGBA8(255, 0, 0, 255)
#define C_BLUE RGBA8(0, 0, 255, 255)
#define C_SEMI_RED RGBA8(255, 0, 0, 120) 

// Fuentes
#define TEXT_SIZE 20

// Tamaños de la pantalla: La de arriba = 400x240 y la de abajo 320x240
#define TOP_WIDTH 400
#define BOTTOM_WIDTH 320
#define HEIGHT 240
#define CELL_SIZE 40

// Versión: La 1.0 es la primera release
#define VERSION "0.8.1"
#define DEBUGMODE false

//Configuración 3D
#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)

//Audio
#define SAMPLERATE 22050
#define SAMPLESPERBUF (SAMPLERATE / 30)
#define BYTESPERSAMPLE 4

#endif