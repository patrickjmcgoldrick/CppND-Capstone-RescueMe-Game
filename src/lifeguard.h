#ifndef LIFEGUARD_H
#define LIFEGUARD_H

#include "actor.h"
#include "SDL.h"

/**
 * Class to describe a beach patron
 */

class Lifeguard : public Actor {
  public:

  	Lifeguard() {};
	  
	void SetPosition(float x, float y) { 
		this->x = x;
		this->y = y; 
	}
 
  	void Update();

	void setGoal(float x, float y);
	void getGoal(float &x, float &y);

	bool operator!=(Lifeguard lg2);

  private:
    float _goalX;
	float _goalY;

};

#endif