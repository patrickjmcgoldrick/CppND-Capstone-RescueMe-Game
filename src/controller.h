#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <thread>
#include "snake.h"
#include "patron.h"
#include "lifeguard.h"

class Controller {
 public:

  Controller(const std::size_t block_width, const std::size_t block_height) : block_width(block_width),
      block_height(block_height) {};

  void HandleInput(bool &running, Snake &snake, std::vector<std::shared_ptr<Lifeguard>> &lifeguards, std::vector<Patron> &patrons);

 private:
  void ChangeDirection(Snake &snake, Actor::Direction input,
                       Actor::Direction opposite) const;
  bool DidClickInside(float clickX, float clickY, std::shared_ptr<Lifeguard> &actor);
  
  std::shared_ptr<Lifeguard> SelectedLifeguard(std::vector<std::shared_ptr<Lifeguard>> &lifeguards);

  const std::size_t block_width;
  const std::size_t block_height;

};

#endif