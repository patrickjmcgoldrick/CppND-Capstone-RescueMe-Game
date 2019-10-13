#ifndef ACTOR_H
#define ACTOR_H

class Actor {
  public:
  	enum class Direction { kUp, kDown, kLeft, kRight };
		
    Actor() {
      id = _idCnt++;
    }

    Actor(float x, float y) : _posX(x), _posY(y) {
      id = _idCnt++;
    }

    void getPosition(float &x, float &y);
    

    bool selected = true;
    int id;

  protected:

  	float speed{0.03f};
    Direction direction = Direction::kUp;

    float _posX = 0.0f;
    float _posY = 0.0f;
    
    private:
      static int _idCnt; // global variable for counting object ids

};

#endif