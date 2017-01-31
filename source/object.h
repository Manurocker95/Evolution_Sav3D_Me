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
	void Draw();
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
