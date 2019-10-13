#include "lifeguard.h"
#include <cmath>
#include <iostream>

/// Update position of actor
void Lifeguard::Update() {

  std::cout << "Lifeguard #: " << id << "\n";

  std::cout << "goal: " << goalX << " , " << goalY << "\n";

  // move lifeguard toward goal
  if (goalX != 0 && goalY !=0) {
    // goal is set
    std::cout << "updating position -> Lifeguard #: " << id << "\n";
    std::cout << "goal: " << goalX << " , " << goalY << "\n";

    _posX += percentPerCycle * dx;
    _posY += percentPerCycle * dy;        
  }

}
void Lifeguard::SetGoal(float gx, float gy) {
  std::cout << "setting goal\n";
  //SDL_Point newGoal = {x, y};
  
  isGoalSet = true;

  goalX = gx;
  goalY = gy;

  dx = gx - _posX;
  dy = gy - _posY;

  float length = sqrt((dx * dx) + (dy * dy));

  percentPerCycle = speed / length;

  std::cout << "set goal\n";

}

// Operators
bool Lifeguard::operator!=(Lifeguard lg2) {
  if (this->id != lg2.id) {
    return true;
  }
  return false;
}

