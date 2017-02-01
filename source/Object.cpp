#include "object.h"

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

Object::Object()
{
	m_type = BANANA;
	m_x = 200;
	m_y = 120;
	m_sprite = sfil_load_PNG_file(IMG_BANANA_SPRITE, SF2D_PLACE_RAM);
	m_multipleFrames = false;
	m_numFrames = 1;
	m_sizePerFrame = 32; //32x32px
	m_currentFrame = 0;
	m_secondaryCounter = 0;
}

Object::Object(Object::Type type, sf2d_texture* sprite, int x, int y, int numFrames, int sizePerFrame, bool multipleFrames)
{
	m_type = type;
	m_sprite = sprite;
	m_x = x;
	m_y = y;
	m_numFrames = numFrames;
	m_sizePerFrame = sizePerFrame;
	m_multipleFrames = multipleFrames;
	m_active = false;
	m_secondaryCounter = 0;
}

void Object::Draw()
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

void Object::setActive(bool value)
{
	m_active = value;
}

bool Object::isActive()
{
	return m_active;
}

void Object::Update()
{
	m_secondaryCounter++;

	if (m_type == BANANA)
	{
		if (m_secondaryCounter > FRAMECOUNTERBANANA)
		{
			m_currentFrame++;
			m_secondaryCounter = 0;
		}
	}
	else
	{
		if (m_secondaryCounter > FRAMECOUNTERFIRE)
		{
			m_currentFrame++;
			m_secondaryCounter = 0;
		}
	}

	if (m_currentFrame >= m_numFrames)
	{
		m_currentFrame = 0;
	}
}

void Object::End()
{
	sf2d_free_texture(m_sprite);
}

int Object::getX()
{
	return m_x;
}
void Object::setX(int value)
{
	m_x = value;
}

int Object::getY()
{
	return m_y;
}

void Object::setY(int value)
{
	m_y = value;
}

sf2d_texture* Object::getSprite()
{
	return m_sprite;
}

void Object::setSprite(sf2d_texture* value)
{
	m_sprite = value;
}

Object::Type Object::getType()
{
	return m_type;
}

void Object::setType(Object::Type value)
{
	m_type = value;
}

bool Object::CheckCollision(Monkey* player)
{
	if (m_x == player->getX() && m_y == player->getY())
	{
		return true;
	}

	return false;
}

void Object::moveToCoord(int x, int y)
{
	m_x = x;
	m_y = y;
}