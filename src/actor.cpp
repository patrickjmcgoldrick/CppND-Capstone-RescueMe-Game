#include "actor.h"

// init static variable
int Actor::_idCnt = 0;

void Actor::getPosition(float &x, float &y) {
  x = _posX;
  y = _posY;
}