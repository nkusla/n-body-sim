#ifndef BODY_H
#define BODY_H

#include <array>

struct vector2 {
	float x;
	float y;
};

class Body {
	private:
		float mass;
		vector2 position;
		vector2 velocity;
		vector2 acceleration;

	public:
		Body();
		Body(float m, vector2 pos, vector2 vel, vector2 acc);

		float getMass();
		vector2 getPosition();
		vector2 getVelocity();
		vector2 getAcceleration();

		void setMass(float mass);
		void setPosition(vector2 pos);
		void setVelocity(vector2 vel);
		void setAcceleration(vector2 acc);

		void resetAcceleration();
};

#endif