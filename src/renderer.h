#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"

#include "patron.h"
#include "lifeguard.h"
#include "snake.h"
#include "ripcurrent.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, std::vector<Patron> const patrons, std::vector<RipCurrent> const ripCurrents, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  void RenderRipCurrent(RipCurrent const ripCurrent);
  void RenderPatron(Patron const patron);
  void RenderLifeguard(Lifeguard const lifeguard);
  
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  std::size_t y_water_sand_divide;
};

#endif