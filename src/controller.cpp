#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::ChangeDirection(Snake &snake, Actor::Direction input,
                                 Actor::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, std::vector<Patron> &patrons) {
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
          float clickX = e.button.x;
          float clickY = e.button.y;

          // check Patrons for clicks
          for (Patron &patron : patrons) {
            if (DidClickInside(clickX, clickY, patron)) {
              std::cout << "Clicked Inside" << std::endl;
              patron.selected = !(patron.selected);
            }
          }
          

          break;
      } 

    }
  }
}

bool Controller::DidClickInside(float clickX, float clickY, Patron &patron) {

  float px = patron.x * block_width;
  float py = patron.y * block_height;
 
  std::cout << px << ", " << py << std::endl;

  if (clickX < px) {  // left of
    return false;
  } else if (clickX > px + block_width) {  // right of
    return false;
  } else if (clickY < py) { // above
    return false;
  } else if (clickY > (py + block_height)) { // below
    return false;
  }
  
  // otherwise inside
  return true;
}
