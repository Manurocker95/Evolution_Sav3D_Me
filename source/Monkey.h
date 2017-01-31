#ifndef _MONKEY_H_
#define _MONKEY_H_

#include "Libraries.h"
#include "filepaths.h"

class Monkey
{
public:
	enum MState { ALIVE, DYING, DEAD };
	Monkey();
	Monkey(int x, int y, sf2d_texture* sprite);
	Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames);
	Monkey(int x, int y, sf2d_texture* sprite, bool multipleFrames, int numFrames, int sizePerFrame);
	void Draw();
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
