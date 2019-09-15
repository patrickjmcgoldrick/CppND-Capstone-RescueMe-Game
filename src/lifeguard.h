#ifndef LIFEGUARD_H
#define LIFEGUARD_H

#include "actor.h"
#include "SDL.h"

/**
 * Class to describe a beach patron
 */

class Lifeguard : public Actor {
  public:

  	Lifeguard(float x, float y): Actor(x, y) {}
 
  	void Update();
    

};

#endif