#ifndef _MONKEY_H_
#define _MONKEY_H_

#include "Libraries.h"
#include "filepaths.h"

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

class Monkey
{
public:
	enum MState { ALIVE, DYING, DEAD };
	Monkey();
	Monkey(int x, int y, sf2d_texture* sprite);
	Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames);
	Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames, int numFrames, int sizePerFrame);
	void Draw(float offset);
	void Update();
	int getX();
	void setX(int value);
	int getY();
	void setY(int value);
	void move(int value, bool xAxis);
	void moveToCoord(int x, int y);
	sf2d_texture* getSprite();
	void setSprite(sf2d_texture* sprite);
	void setDeadSprite(sf2d_texture* sprite, int numFrames, int sizePerFrame);
	void end();
	MState getState();
	void setState(MState value);
	void setInvincible(bool value);
	bool getInvincible();
	void setNumFrames(int value);
	int getNumFrames();
	void setFrameSize(int value);
	int getFrameSize();
private:
	int m_x;
	int m_y;
	int m_numFrames;
	int m_sizePerFrame;
	int m_currentFrame;
	int m_secondaryCounter;
	bool m_multipleFrames;
	bool m_invincible;						// Si el modo invencible está activado o no	
	sf2d_texture* m_sprite;
	MState m_state;
};

#endif
