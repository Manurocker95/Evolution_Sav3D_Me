#include "Ray.h"

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

Ray::Ray()
{
	
	m_disappear = false;
	m_counter = 0;

	// Color por defecto = Rojo
	m_color = C_SEMI_RED;
	
	//Sonidos
	m_sndLaserPrev = new sound(SND_SFX_LASERPREV, 2, false, false);
	m_sndLaserHit = new sound(SND_SFX_LASERHIT, 2, false, false);
	m_sndLaser = new sound(SND_SFX_LASER, 2, false, false);
	InitialPos();
}

void Ray::InitialPos()
{

	m_axis = HORIZONTAL;

	m_y = -CELL_SIZE;
	m_x = -CELL_SIZE;
}

void Ray::loadData()
{
	m_counter = 0;
	m_disappear = false;

	// Color por defecto = Rojo
	m_color = C_SEMI_RED;

	//Sonidos
	m_sndLaser->play();

	//srand(time(NULL));

	// Vertical / Horizontal
	int _type = rand() % 100;
	if (_type % 2 == 0)
	{
		//srand(time(NULL));
		m_axis = VERTICAL;
		m_y = 0;
		int _x = rand() % (8) + 1;
		m_x = _x*CELL_SIZE;
	}
	else
	{
		//srand(time(NULL));
		m_axis = HORIZONTAL;
		m_x = 0;
		int _y = rand() % (4) + 1;
		m_y = _y*CELL_SIZE;
	}
}

void Ray::NewPos()
{
	// Vertical / Horizontal
	int _type = rand() % 100;
	if (_type % 2 == 0)
	{
		srand(time(NULL));
		m_axis = VERTICAL;
		m_y = 0;
		int _x = rand() % (8) + 1;
		m_x = _x*CELL_SIZE;
	}
	else
	{
		m_axis = HORIZONTAL;
		m_x = 0;
		srand(time(NULL));
		int _y = rand() % (4) + 1;
		m_y = _y*CELL_SIZE;
	}
}

int Ray::getX()
{
	return m_x;
}

void Ray::setX(int value)
{
	m_x = value;
}

int Ray::getY()
{
	return m_y;
}

void Ray::setY(int value)
{
	m_y = value;
}

void Ray::Draw(float offset)
{
	switch (m_axis)
	{
		case VERTICAL:
			sf2d_draw_rectangle(m_x-offset, m_y, CELL_SIZE, HEIGHT+offset, m_color);
			break;
		case HORIZONTAL:
			sf2d_draw_rectangle(m_x-offset, m_y, TOP_WIDTH + offset, CELL_SIZE, m_color);
			break;
	}
}

void Ray::Update()
{
	m_counter++;

	if (m_counter > MIN_LASER_TIME && m_counter <= LASER_TIME)
	{
		m_color = C_RED;
		ndspChnWaveBufClear(2);
		m_sndLaserPrev->play();
	}
	if (m_counter > LASER_TIME) 
	{
		End();
	}
}

void Ray::End()
{
	m_disappear = true;
	m_x = -CELL_SIZE;
	m_y = -CELL_SIZE;
}

int Ray::getCounter()
{
	return m_counter;
}

Ray::RayAxis Ray::getAxis()
{
	return m_axis;
}

void Ray::setAxis(Ray::RayAxis value)
{
	m_axis = value;
}

u32 Ray::getColor()
{
	return m_color;
}

void Ray::setColor(u32 value)
{
	m_color = value;
}

bool Ray::CheckCollision(Monkey* player)
{
	if (m_axis == VERTICAL)
	{
		if ((!player->getInvincible()) && player->getState() == Monkey::ALIVE && m_counter > MIN_LASER_TIME && m_x == player->getX() && (player->getY() > m_y && player->getY() <= HEIGHT))
		{
			ndspChnWaveBufClear(2);
			m_sndLaserHit->play();
			return true;
		}
	}
	else
	{
		if ((!player->getInvincible()) && player->getState() == Monkey::ALIVE && m_counter > MIN_LASER_TIME && (player->getX() > m_x && player->getX() <= TOP_WIDTH) && m_y == player->getY())
		{
			ndspChnWaveBufClear(2);
			m_sndLaserHit->play();
			return true;
		}
	}

	return false;
}

bool Ray::out()
{
	return m_disappear;
}