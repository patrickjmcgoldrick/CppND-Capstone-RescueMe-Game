#include "lifeguard.h"
#include <cmath>
#include <iostream>

void Lifeguard::Update() {

  double speed = 1.0f;  
  std::cout << "Lifeguard #: " << id << "\n";

  std::cout << "goal: " << goalX << " , " << goalY << "\n";

  // move lifeguard toward goal
  if (goalX != 0 && goalY !=0) {
    // goal is set
    std::cout << "updating goal -> Lifeguard #: " << id << "\n";
    std::cout << "goal: " << goalX << " , " << goalY << "\n";

    double diffX = x - goalX;
    double diffY = y - goalY;
    double percentX = diffY / (diffX + diffY);
    double percentY = diffY / (diffX + diffY); 

    x = x + (speed * percentX);
    y = y + (speed * percentY);        
  }

}
void Lifeguard::SetGoal(float gx, float gy) {
  std::cout << "setting goal\n";
  //SDL_Point newGoal = {x, y};
  
  goalX = gx;
  goalY = gy;
  //std::cout << "created goal object\n";

  //goal = &newGoal;

  std::cout << "set goal\n";

}

// Operators
bool Lifeguard::operator!=(Lifeguard lg2) {
  if (this->id != lg2.id) {
    return true;
  }
  return false;
}

