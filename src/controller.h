#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "patron.h"

class Controller {
 public:

  Controller(const std::size_t block_width, const std::size_t block_height) : block_width(block_width),
      block_height(block_height) {};

  void HandleInput(bool &running, Snake &snake, std::vector<Patron> &patrons);

 private:
  void ChangeDirection(Snake &snake, Actor::Direction input,
                       Actor::Direction opposite) const;
  bool DidClickInside(float clickX, float clickY, Patron &patron);

  const std::size_t block_width;
  const std::size_t block_height;

};

#endif