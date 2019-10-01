#ifndef ACTOR_H
#define ACTOR_H

class Actor {
  public:
  	enum class Direction { kUp, kDown, kLeft, kRight };
		
    Actor(float x, float y): x(x), y(y) {
      id = _idCnt++;
    }

  	float x = 0.0f;
    float y = 0.0f;
    bool selected = true;
    int id;
    
  protected:

  	float speed{0.03f};
    Direction direction = Direction::kUp;

    
    private:
      static int _idCnt; // global variable for counting object ids

};

#endif