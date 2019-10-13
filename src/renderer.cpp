#include "renderer.h"
#include <iostream>
#include <algorithm>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // where we draw the line between water and sand
  y_water_sand_divide = 2 * screen_height / 3;

  if (LoadTextures()) {
    printf("Textures loaded.");
  } else {
    printf("Textures failed to load.");
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

bool Renderer::LoadTextures() {
	//Loading success flag
	bool success = true;
  
  // convert images to Textures
  textureLifeguard = LoadTexture("../images/buoy_24.png");
  if( textureLifeguard == NULL )
	{
		printf( "Failed to create Texture from 'Lifeguard' image!\n" );
		success = false;
	}

  texturePatronWalking = LoadTexture("../images/one-man-walking_24.png");
  if( textureLifeguard == NULL )
	{
		printf( "Failed to create Texture from 'Patron Walking' image!\n" );
		success = false;
	}

  texturePatronSwimming = LoadTexture("../images/swimming_24.png");
  if( textureLifeguard == NULL )
	{
		printf( "Failed to create Texture from 'Patron Swimming' image!\n" );
		success = false;
	}  
  
  textureRipCurrent = LoadTexture("../images/rip_250.png");
  if( textureLifeguard == NULL )
	{
		printf( "Failed to create Texture from 'Rip Current' image!\n" );
		success = false;
	}  
	return success;
}

/**
 * From: https://lazyfoo.net/tutorials/SDL/06_extension_libraries_and_loading_other_image_formats/index2.php
 */
SDL_Texture* Renderer::LoadTexture(std::string path) {

	//The final texture
	SDL_Texture* texture = NULL;

	//Load image at specified path
	SDL_Surface* surface = IMG_Load( path.c_str() );
	if( surface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
    // convert to Texture
    texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if( texture == NULL )
    {
      printf( "Failed to convert Surface to Texture!\n" );
    }

		//Get rid of old loaded surface
		SDL_FreeSurface( surface );
	}

	return texture;
}

void Renderer::Render(Snake const snake, std::vector<std::shared_ptr<Lifeguard>> lifeguards, std::vector<Patron> const patrons, std::vector<RipCurrent> const ripCurrents, SDL_Point const &food) {

  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;
  SDL_Rect background;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // render water
  SDL_SetRenderDrawColor(sdl_renderer, 0x9A, 0xD2, 0xF0, 0xFF);
  background.x = 0;
  background.w = screen_width;
  background.y = 0;
  background.h = y_water_sand_divide;
  SDL_RenderFillRect(sdl_renderer, &background);

  // render Sand
  SDL_SetRenderDrawColor(sdl_renderer, 0xF0, 0xD9, 0x9A, 0xFF);
  background.x = 0;
  background.w = screen_width;
  background.y = y_water_sand_divide;
  background.h = screen_height;
  SDL_RenderFillRect(sdl_renderer, &background);

  // render Patrons
  for (Patron const &patron : patrons) {
    RenderPatron(patron);
  }

  // render Lifeguards
  std::for_each(lifeguards.begin(), lifeguards.end(), [&](std::shared_ptr<Lifeguard> &lifeguard) {
    RenderLifeguard(lifeguard);
  });

  // Render Ripcurrent
  for (RipCurrent const &ripCurrent : ripCurrents) {
    RenderRipCurrent(ripCurrent);
  }

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // render images
  //Apply the PNG image
	SDL_Rect dstrect = { 100, 110, 32, 32 };
  SDL_RenderCopy(sdl_renderer, texturePatronWalking, NULL, &dstrect);
	dstrect = { 100, 70, 32, 32 };
  SDL_RenderCopy(sdl_renderer, texturePatronSwimming, NULL, &dstrect);
  dstrect = { 277, 100, 177, 350 };
  SDL_RenderCopy(sdl_renderer, textureRipCurrent, NULL, &dstrect);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderLifeguard(std::shared_ptr<Lifeguard> const lifeguard) {
  // render Lifeguard
  float lx, ly;
  lifeguard->getPosition(lx, ly);

  int intx = static_cast <int> (lx);
  int inty = static_cast <int> (ly);
  SDL_Rect dstrect = { intx, inty, 32, 32 };
  SDL_RenderCopy(sdl_renderer, textureLifeguard, NULL, &dstrect);
  if (lifeguard->selected == true) {
    SDL_Rect block;
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
    block.x = intx;
    block.y = inty;
    block.w = 32;
    block.h = 32;
    SDL_RenderDrawRect(sdl_renderer, &block);
  }
}

void Renderer::RenderRipCurrent(RipCurrent const ripCurrent) {

  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0xFF, 0xFF);

  SDL_RenderDrawLine(sdl_renderer, ripCurrent.x, y_water_sand_divide, ripCurrent.x, y_water_sand_divide - ripCurrent.length);

  SDL_Rect block;

  block.x = ripCurrent.x - (ripCurrent.width / 2);
  block.y = y_water_sand_divide - ripCurrent.length;
  block.w = ripCurrent.width;
  block.h = ripCurrent.length;
  SDL_RenderDrawRect(sdl_renderer, &block);
  
}

void Renderer::RenderPatron(Patron patron) {
  float px, py;
  patron.getPosition(px, py);
	int intx = static_cast <int> (px);
	int inty = static_cast <int> (py);
	SDL_Rect dstrect = { intx, inty, 32, 32 };
  SDL_RenderCopy(sdl_renderer, texturePatronWalking, NULL, &dstrect);
/*
  SDL_Rect patron_body;
  patron_body.w = screen_width / grid_width / 3;
  patron_body.h = screen_height / grid_height / 3;

  // Render Patron Arms and Legs - Yellow
  SDL_SetRenderDrawColor(sdl_renderer, 0xF1, 0xE8, 0x69, 0xFF); // Tan / Yellow
  patron_body.x = patron.x * (screen_width / grid_width);
  patron_body.y = patron.y * (screen_height / grid_height);
  SDL_RenderFillRect(sdl_renderer, &patron_body);
  patron_body.x = patron_body.x + (patron_body.w * 2);
  SDL_RenderFillRect(sdl_renderer, &patron_body);
  patron_body.y = patron_body.y + (patron_body.h * 2);
  SDL_RenderFillRect(sdl_renderer, &patron_body);
  patron_body.x = patron_body.x - (patron_body.w * 2);
  SDL_RenderFillRect(sdl_renderer, &patron_body);

  // Render Chest and Head
  patron_body.x = patron_body.x + (patron_body.w);
  patron_body.y = patron_body.y - (patron_body.h * 2);
  SDL_RenderFillRect(sdl_renderer, &patron_body);
  patron_body.y = patron_body.y - (patron_body.h);
  SDL_RenderFillRect(sdl_renderer, &patron_body);

  // Render Patron Body
  SDL_SetRenderDrawColor(sdl_renderer, 0x20, 0xAE, 0x40, 0xFF); // Green
  patron_body.y = patron_body.y + (2 * patron_body.h);
  SDL_RenderFillRect(sdl_renderer, &patron_body);
*/

  if (patron.selected == true) {
    SDL_Rect outline;
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x00, 0x00, 0xFF); // Black outline
    outline.x = intx;
    outline.y = inty;
    outline.w = 32.0;
    outline.h = 32.0;
    SDL_RenderDrawRect(sdl_renderer, &outline);
  }
}
/*
void Renderer::RenderLifeguard(Lifeguard const lifeguard) {
  SDL_Rect lifeguard_body;
  lifeguard_body.w = screen_width / grid_width / 3;
  lifeguard_body.h = screen_height / grid_height / 3;

  // Render Patron Arms and Legs - Yellow
  SDL_SetRenderDrawColor(sdl_renderer, 0xF1, 0xE8, 0x69, 0xFF); // Tan / Yellow
  lifeguard_body.x = lifeguard.x * (screen_width / grid_width);
  lifeguard_body.y = lifeguard.y * (screen_height / grid_height);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);
  lifeguard_body.x = lifeguard_body.x + (lifeguard_body.w * 2);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);
  lifeguard_body.y = lifeguard_body.y + (lifeguard_body.h * 2);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);
  lifeguard_body.x = lifeguard_body.x - (lifeguard_body.w * 2);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);

  // Render Chest and Head
  lifeguard_body.x = lifeguard_body.x + (lifeguard_body.w);
  lifeguard_body.y = lifeguard_body.y - (lifeguard_body.h * 2);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);
  lifeguard_body.y = lifeguard_body.y - (lifeguard_body.h);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);

  // Render Patron Body
  SDL_SetRenderDrawColor(sdl_renderer, 0xDD, 0x0F, 0x0F, 0xFF); // Red shorts
  lifeguard_body.y = lifeguard_body.y + (2 * lifeguard_body.h);
  SDL_RenderFillRect(sdl_renderer, &lifeguard_body);
}
*/
void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
