#ifndef QUADTREE_NODE_H
#define QUADTREE_NODE_H

#include <vector>
#include <glm/glm.hpp>
#include <Body.hpp>

class QuadtreeNode {
	private:
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
		void subdivideNote();
		bool checkIfPositionInQuadrant(glm::vec2 position);
		bool recursivelyInsertBody(Body& b);
		void updateMassAndPosition(float mass, glm::vec2 position);
};

#endif
