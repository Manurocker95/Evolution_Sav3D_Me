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
	void Draw();
	void Update();
	void End();
	bool out();
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
