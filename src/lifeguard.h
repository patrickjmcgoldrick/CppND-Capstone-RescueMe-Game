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
		this->_posX = x;
		this->_posY = y; 
	}
 
  	void Update();

	void SetGoal(float x, float y);

    float goalX;
	float goalY;
	
	bool isGoalSet = false;
  	
  	float speed = 1.0f;  

	bool operator!=(Lifeguard lg2);

  private:
  	float dx;
  	float dy;
  	float percentPerCycle;
};

#endif