#ifndef ACTOR_H
#define ACTOR_H

class Actor {
  public:
  	enum class Direction { kUp, kDown, kLeft, kRight };
		
    Actor(float x, float y): x(x), y(y) {}

  	float x = 0.0f;
    float y = 0.0f;
    bool selected = true;

  protected:

  	float speed{0.03f};
    Direction direction = Direction::kUp;
    int id;
};

#endif