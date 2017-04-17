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

#pragma once
#ifndef _RAY_H_
#define _RAY_H_

#include "Monkey.h"
#include "Libraries.h"

#define LASER_TIME 180
#define MIN_LASER_TIME 70

class Ray
{
public:
	enum RayAxis { VERTICAL, HORIZONTAL };
	Ray();
	bool CheckCollision(Monkey* player);
	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	int getCounter();
	u32 getColor();
	void setColor(u32 value);
	void setAlphaColor(int value);
	void loadData();
	RayAxis getAxis();
	void setAxis(RayAxis value);
	void Draw(float offset);
	void Update();
	void End();
	bool out();
	void InitialPos();
	void NewPos();
private:
	int m_x;
	int m_y;
	int m_counter;
	bool m_disappear;
	u32 m_color;
	RayAxis m_axis;
	sound* m_sndLaser;
	sound* m_sndLaserPrev;
	sound* m_sndLaserHit;
	BmpFont* fnt;
};


#endif
