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
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Monkey.h"
#include "Libraries.h"
#define FRAMECOUNTERBANANA 9
#define FRAMECOUNTERFIRE 9

class Object
{
public:
	enum Type { BANANA, FIRE };
	Object();
	Object(Type type, sf2d_texture* sprite, int x, int y, int numFrames, int sizePerFrame, bool multipleFrames);
	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	void moveToCoord(int x, int y);
	sf2d_texture* getSprite();
	void setSprite(sf2d_texture* value);
	Type getType();
	void setType(Type value);
	bool CheckCollision(Monkey* player);
	bool isActive();
	void setActive(bool value);
	void Draw(float offset);
	void Update();
	void End();
private:
	int m_x;
	int m_y;
	int m_numFrames;
	int m_sizePerFrame;
	int m_currentFrame;
	int m_secondaryCounter;
	bool m_multipleFrames;
	bool m_active;
	sf2d_texture* m_sprite;
	Type m_type;
};

#endif
