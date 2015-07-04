/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib>


#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/moduleinfo.h>


#include "utils.h"
#include "draw.h"

#include <vector>

using namespace std;

const int SZ = 12;

struct Punto
{
	int x, y;
};


void cuadrado(const Punto& p, uint32_t color)
{
	draw_rectangle(p.x*SZ, p.y*SZ, SZ, SZ, color);
}


bool colision(const Punto &cabeza, const vector<Punto> &cola)
{
	if (cabeza.x >= SCREEN_W || cabeza.x < 0) {
		return true;
	}
	if (cabeza.y >= SCREEN_H || cabeza.y < 0) {
		return true;
	}
	vector<Punto>::const_iterator it;
	for (it = cola.begin(); it != cola.end(); it++) {
		if (cabeza.x == it->x && cabeza.y == it->y) {
			return true;
		}
	}

	return false;
}

Punto aletorio()
{
	Punto p = {rand() % SCREEN_W, rand() % SCREEN_H};
	return p;
}


PSP2_MODULE_INFO(0, 0, "SNAKE")
int main()
{

	SceCtrlData pad;
	init_video();

	Punto cabeza = {30, 20};

	Punto comida = aletorio();


	int vx = 1, vy = 0;

	vector <Punto> cola;

	int frames = 0, engorda = 0;
 	bool colision_bool = false;
	while(1)
	{
		frames ++;

		sceCtrlPeekBufferPositive(0, &pad, 1);

		if (pad.buttons & PSP2_CTRL_START) {
			break;
			break;
		}

		if(pad.buttons & PSP2_CTRL_UP)
		{
			vx = 0, vy = -1;
		}else if(pad.buttons & PSP2_CTRL_DOWN)
		{
			vx = 0, vy = 1;
		} else if(pad.buttons & PSP2_CTRL_LEFT)
		{
			vx = -1, vy = 0;
		} else if(pad.buttons & PSP2_CTRL_RIGHT)
		{
			vx = 1, vy = 0;
		} else if(pad.buttons & PSP2_CTRL_CROSS)
		{
			engorda = 5;
		}


		if( frames == 8)
		{

			cola.insert(cola.begin(), cabeza);

			if(engorda > 0)
			{
				engorda--;
			} else
			{

				cola.pop_back();
			}

			cabeza.y += vy;
			cabeza.x += vx;
			if (colision(cabeza, cola)) {
				colision_bool = true;
			}

			frames = 0;
		}
		if (!colision_bool) {
			clear_screen();
			vector<Punto>::const_iterator it;
			for (it = cola.begin(); it != cola.end(); it++)
			{
				cuadrado(*it, GREEN);
			}
			cuadrado(cabeza, RED);

			swap_buffers();
			sceDisplayWaitVblankStart();
		}

	}

	end_video();
	return 0;
}
