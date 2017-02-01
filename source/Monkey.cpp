#include "Monkey.h"
#define FRAMECOUNTERMONKEY 9

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

//Constructor con valores por defecto
Monkey::Monkey()
{
	m_x = 200;
	m_y = 120;
	m_sprite = sfil_load_PNG_file(IMG_MONKEY_SPRITE, SF2D_PLACE_RAM);
	m_multipleFrames = false;
	m_numFrames = 1;
	m_sizePerFrame = 32; //32x32px
	m_currentFrame = 0;
	m_secondaryCounter = 0;
	m_invincible = false;
	m_state = ALIVE;
}

Monkey::Monkey(int x, int y, sf2d_texture* sprite)
{
	m_x = x;
	m_y = y;
	m_sprite = sprite;
	m_multipleFrames = false;
	m_numFrames = 1;
	m_sizePerFrame = 32; //32x32px
	m_currentFrame = 0;
	m_secondaryCounter = 0;
	m_invincible = false;
	m_state = ALIVE;
}

Monkey::Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames)
{
	m_x = x;
	m_y = y;
	m_sprite = sprite;
	m_multipleFrames = multipleFrames;
	m_numFrames = 1;
	m_sizePerFrame = 32; //32x32px
	m_currentFrame = 0;
	m_secondaryCounter = 0;
	m_invincible = false;
	m_state = ALIVE;
}

Monkey::Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames, int numFrames, int sizePerFrame)
{
	m_x = x;
	m_y = y;
	m_sprite = sprite;
	m_multipleFrames = multipleFrames;
	m_numFrames = numFrames;
	m_sizePerFrame = sizePerFrame;
	m_currentFrame = 0;
	m_secondaryCounter = 0;
	m_invincible = false;
	m_state = ALIVE;
}

void Monkey::Draw()
{
	if (m_multipleFrames)
	{
		sf2d_draw_texture_part(m_sprite, m_x, m_y, m_currentFrame*m_sizePerFrame, 0, m_sizePerFrame, m_sizePerFrame);
	}
	else
	{
		sf2d_draw_texture(m_sprite, m_x, m_y);
	}
}

void Monkey::Update()
{
	m_secondaryCounter++;

	if (m_secondaryCounter > FRAMECOUNTERMONKEY)
	{
		m_currentFrame++;
		m_secondaryCounter = 0;
	}
	
	if (m_currentFrame >= m_numFrames)
	{
		m_currentFrame = 0;
	}
}

void Monkey::moveToCoord(int x, int y)
{
	m_x = x;
	m_y = y;
}

///summary: Si n
void Monkey::move(int value, bool xAxis)
{
	if (xAxis)
	{
		if ((value > 0 && m_x+value<=TOP_WIDTH-CELL_SIZE-CELL_SIZE) || (value < 0 && m_x + value >= 0 + CELL_SIZE))
			m_x += value;
	}
	else
	{
		if ((value > 0 && m_y + value <= HEIGHT - CELL_SIZE - CELL_SIZE) || (value < 0 && m_y + value >= 0 + CELL_SIZE))
			m_y += value;
	}
}

sf2d_texture* Monkey::getSprite()
{
	return m_sprite;
}

void Monkey::setSprite(sf2d_texture* sprite)
{
	m_sprite = sprite;
}

void Monkey::setDeadSprite(sf2d_texture* sprite, int numFrames, int sizePerFrame)
{
	m_sprite = sprite;
	m_currentFrame = 0;
	m_numFrames = numFrames;
	m_sizePerFrame = sizePerFrame;
}

void Monkey::setX(int value)
{
	m_x = value;
}

int Monkey::getX()
{
	return m_x;
}

void Monkey::setY(int value)
{
	m_y = value;
}

int Monkey::getY()
{
	return m_y;
}

void Monkey::end()
{
	sf2d_free_texture(m_sprite);
	delete(this);
}

Monkey::MState Monkey::getState()
{
	return m_state;
}

void Monkey::setState(Monkey::MState value)
{
	m_state = value;
}

void Monkey::setInvincible(bool value)
{
	m_invincible = value;
}

bool Monkey::getInvincible()
{
	return m_invincible;
}

void Monkey::setNumFrames(int value)
{
	m_numFrames = value;
	m_currentFrame = 0;
}

int Monkey::getNumFrames()
{
	return m_numFrames;
}

void Monkey::setFrameSize(int value)
{
	m_sizePerFrame = value;
}

int Monkey::getFrameSize()
{
	return m_sizePerFrame;
}