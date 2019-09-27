#ifndef PATRON_H
#define PATRON_H

#include "actor.h"
#include "SDL.h"
/**
 * Class to describe a beach patron
 */

class Patron : public Actor {
  public:

  	Patron(float x, float y): Actor (x, y) {
      speed = 0.01f;
    }

  	void Update();
    
  private:
    bool inRipcurrent{false};

};

#endif
