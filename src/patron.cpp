#include "patron.h"
#include <iostream>

void Patron::Update() {
  _posY = _posY - speed;
}
