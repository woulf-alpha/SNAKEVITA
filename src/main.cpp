/*
 * Copyright (c) 2015 Sergi Granell (xerpi)
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <cstdlib>


#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/display.h>
#include <psp2/gxm.h>
#include <psp2/types.h>
#include <psp2/moduleinfo.h>


#include "utils.h"
#include "draw.h"
#include <list>

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


PSP2_MODULE_INFO(0, 0, "SNAKE")
int main()
{
	
	SceCtrlData pad;
	init_video();
	
	Punto cabeza = {30, 20};
	int vx = 1, vy = 0;
	
	list<Punto> cola;
	
	int frames = 0, engorda = 0;
	
	while(1)
	{
		frames ++;
		clear_screen();
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
			cola.push_back(cabeza);
			if(engorda > 0)
			{
				engorda--;
			} else
			{
				cola.pop_back();
			}
		
			cabeza.y += vy;
			cabeza.x += vx;
			frames = 0;
		}
		list<Punto>::iterator it = cola.begin();
		while( it != cola.end() )
		{
			cuadrado(*it, GREEN);
		}

			
		cuadrado(cabeza, RED);

		swap_buffers();
		sceDisplayWaitVblankStart();
	}

	end_video();
	return 0;
}
