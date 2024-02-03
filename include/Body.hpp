#ifndef BODY_H
#define BODY_H

#include <array>
#include <glm/glm.hpp>

class Body {
	private:
		float mass;
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;

	public:
		Body();
		Body(float m, glm::vec2 pos, glm::vec2 vel);

		float getMass();
		glm::vec2 getPosition();
		glm::vec2 getVelocity();
		glm::vec2 getAcceleration();

		void setMass(float mass);
		void setPosition(glm::vec2 pos);
		void setVelocity(glm::vec2 vel);
		void setAcceleration(glm::vec2 acc);

		void addPosition(glm::vec2 pos);
		void addAcceleration(glm::vec2 acc);
		void addVelocity(glm::vec2 vel);
};

#endif