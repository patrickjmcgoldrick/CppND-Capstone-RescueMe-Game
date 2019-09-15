#ifndef RIPCURRENT_H
#define RIPCURRENT_H

class RipCurrent {
  public:
	
	RipCurrent(float x, float length, float width): x(x), length(length), width(width) {}
  	float x = 0.0f; // x position from shore
    float length = 0.0f; // size of
    float width = 0.0f; // size of

  protected:

    int id;
};

#endif