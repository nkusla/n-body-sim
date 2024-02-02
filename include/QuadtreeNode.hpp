#ifndef QUADTREE_NODE_H
#define QUADTREE_NODE_H

#include <vector>
#include <glm/glm.hpp>
#include "Body.hpp"
#include "globals.hpp"

class QuadtreeNode {
	private:
		int bodyIndex;
		float mass;
		glm::vec2 weightedPosition;
		glm::vec2 topLeft;
		glm::vec2 bottomRight;
		std::vector<QuadtreeNode*> nodes;

	public:
		QuadtreeNode();
		QuadtreeNode(glm::vec2 topLeft, glm::vec2 bottomRight);
		~QuadtreeNode();

		float getWidth();
		glm::vec2 getCenterOfMass();
		void subdivideNode();
		bool checkIfPositionInQuadrant(glm::vec2 position);
		bool recursivelyInsertBody(Body& newBody, int newBodyIndex);
		void updateNodeData(float m, glm::vec2 pos, int bodyIdx);
		void calculateBodyAcceleration(Body& b, float mass, glm::vec2 centerOfMass);
		void recursivelyCalculateBodyAcceleration(Body& b, int idx, float theta);
};

#endif
