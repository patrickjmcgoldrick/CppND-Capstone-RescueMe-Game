#include "controller.h"
#include <iostream>
#include <algorithm>
#include "SDL.h"

void Controller::ChangeDirection(Snake &snake, Actor::Direction input,
                                 Actor::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, std::vector<std::shared_ptr<Lifeguard>> &lifeguards, std::vector<Patron> &patrons) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {

      switch(e.button.which) {
        case SDL_BUTTON_LEFT:
          std::cout << "Button LEFT - at: " << e.button.x << ", " << e.button.y << std::endl;
          break;
        case SDL_BUTTON_RIGHT:
          std::cout << "Button RIGHT - at: " << e.button.x << ", " << e.button.y << std::endl;
          break;
        default:
          std::cout << "Unknown Button - at: " << e.button.x << ", " << e.button.y << std::endl;
          float clickX = (float)e.button.x;
          float clickY = (float)e.button.y;
          
          bool selectedNewLifeguard = false;

          // check Lifeguards for clicks
          std::for_each(lifeguards.begin(), lifeguards.end(), [&, clickX, clickY, &selectedNewLifeguard](std::shared_ptr<Lifeguard> &lifeguard) {
            std::cout << "lifeguard at: " << lifeguard->x << " , " << lifeguard->y << "\n";
            if (DidClickInside(clickX, clickY, lifeguard)) {
              lifeguard->selected = true;
              selectedNewLifeguard = true;
              std::cout << "Lifeguard selected #: " <<  lifeguard->id << "\n";

              // unselect, previously selected
              std::for_each(lifeguards.begin(), lifeguards.end(), [lifeguard](std::shared_ptr<Lifeguard> &temp) {
                if (temp->selected && temp != lifeguard) {
                  temp->selected = false;
                  return;
                }
              });
            }
          });
          
          if (!selectedNewLifeguard) {
            // set new goal for currently selected.
            std::cout << "get selected" << "\n";

            std::shared_ptr<Lifeguard> selected = SelectedLifeguard(lifeguards);
            std::cout << "Lifeguard #: " <<  selected->id << "\n";
            std::cout << "setting new goal: " << clickX << " , " << clickY << "\n";

            //SDL_Point newGoal = {clickX, clickY};
            if (selected == NULL) {
              std::cout << "NULL ref" << "\n";
            } else {
              std::cout << "good ref" << "\n";
              selected->SetGoal(clickX, clickY);
            }
            
            //selected->SetGoal(clickX, clickY);
            std::cout << "test new Goal: " << selected->goalX << " , " << selected->goalY << "\n";

            
          }
          break;
      } 

    }
  }
}

bool Controller::DidClickInside(float clickX, float clickY, std::shared_ptr<Lifeguard> &actor) {

  float px = actor->x + block_width;
  float py = actor->y + block_height;

  std::cout << "Click @ " << clickX << ", " << clickY << std::endl;
  std::cout << "Actor @ " << actor->x << ", " << actor->y << std::endl;
  std::cout << "Actor Block @ " << px << ", " << py << std::endl;

  if (clickX < actor->x) {  // left of
    return false;
  } else if (clickX > px) {  // right of
    return false;
  } else if (clickY < actor->y) { // above
    return false;
  } else if (clickY > py) { // below
    return false;
  }
  
  // otherwise inside
  return true;
}

std::shared_ptr<Lifeguard> Controller::SelectedLifeguard(std::vector<std::shared_ptr<Lifeguard>> &lifeguards) {

  std::shared_ptr<Lifeguard> temp = lifeguards.at(0);

  std::for_each(lifeguards.begin(), lifeguards.end(), [temp](std::shared_ptr<Lifeguard> &lifeguard) {
    if (lifeguard->selected) {
      std::shared_ptr<Lifeguard> temp(lifeguard);
    }
  });

  return temp;
}