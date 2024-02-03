#ifndef QUADTREE_NODE_H
#define QUADTREE_NODE_H

#include <vector>
#include <glm/glm.hpp>
#include "Body.hpp"
#include "Globals.hpp"

class QuadtreeNode {
	private:
		int depth;
		glm::vec2 topLeft;
		glm::vec2 bottomRight;
		float totalMass;
		glm::vec2 weightedPosition;
		std::vector<QuadtreeNode*> nodes;
		std::vector<int> bodyIndex;
		std::vector<Body>& bodies;

	public:
		//QuadtreeNode();
		QuadtreeNode(glm::vec2 topLeft, glm::vec2 bottomRight, int depth, std::vector<Body>& bodies);
		~QuadtreeNode();

		float getWidth();
		glm::vec2 getCenterOfMass();
		bool subdivideNode();
		bool checkIfPositionInQuadrant(glm::vec2 position);
		bool recursivelyInsertBody(int newBodyIndex);
		void updateCenterOfMass(int bodyIndex);
		void calculateBodyAcceleration(int bIndex, float mass, glm::vec2 centerOfMass);
		void recursivelyCalculateBodyAcceleration(int bIndex);
};

#endif
