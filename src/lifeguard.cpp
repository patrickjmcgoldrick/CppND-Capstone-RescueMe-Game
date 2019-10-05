#include "lifeguard.h"
#include <cmath>
#include <iostream>

void Lifeguard::Update() {

  double speed = 1.0f;  
  std::cout << "Lifeguard #: " << id << "\n";

  std::cout << "goal: " << _goalX << " , " << _goalY << "\n";

  // move lifeguard toward goal
  if (_goalX != 0.0f && _goalY != 0.0f) {
    // goal is set
    std::cout << "updating goal -> Lifeguard #: " << id << "\n";
    std::cout << "goal: " << _goalX << " , " << _goalY << "\n";

    double diffX = x - _goalX;
    double diffY = y - _goalY;
    double percentX = diffY / (diffX + diffY);
    double percentY = diffY / (diffX + diffY); 

    x = x + (speed * percentX);
    y = y + (speed * percentY);        
  }

}
void Lifeguard::setGoal(float gx, float gy) {
  std::cout << "setting goal\n";
  //SDL_Point newGoal = {x, y};
  
  _goalX = gx;
  _goalY = gy;
  //std::cout << "created goal object\n";

  //goal = &newGoal;

  std::cout << "set goal\n";

}

void Lifeguard::getGoal(float &x, float &y) {
  x = _goalX;
  y = _goalY;
}

// Operators
bool Lifeguard::operator!=(Lifeguard lg2) {
  if (this->id != lg2.id) {
    return true;
  }
  return false;
}

