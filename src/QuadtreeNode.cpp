#include "../include/QuadtreeNode.hpp"

QuadtreeNode::QuadtreeNode() :
	mass(0.f),
	weightedPosition({0.f, 0.f}),
	topLeft({0.f, 0.f}),
	bottomRight({0.f, 0.f}),
	nodes(4) {}

QuadtreeNode::QuadtreeNode(glm::vec2 topLeft, glm::vec2 bottomRight) :
	mass(0.f),
	weightedPosition({0.f, 0.f}),
	topLeft(topLeft),
	bottomRight(bottomRight),
	nodes(4) {}

QuadtreeNode::~QuadtreeNode() {
	if(nodes[0] == nullptr)
		return;

	for(QuadtreeNode* node : nodes) {
		node->~QuadtreeNode();
		delete node;
	}
}

glm::vec2 QuadtreeNode::getCenterOfMass() {
	return weightedPosition / mass;
}

void QuadtreeNode::subdivideNote() {
	nodes[0] = new QuadtreeNode(
		{(topLeft.x + bottomRight.x) / 2, topLeft.y},
		{bottomRight.x, (topLeft.y + bottomRight.y) / 2}
	);

	nodes[1] = new QuadtreeNode(
		topLeft,
		{(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2}
	);

	nodes[2] = new QuadtreeNode(
		{topLeft.x, (topLeft.y + bottomRight.y) / 2},
		{(topLeft.x + bottomRight.x) / 2, topLeft.y}
	);

	nodes[3] = new QuadtreeNode(
		{(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2},
		bottomRight
	);
}

bool QuadtreeNode::checkIfPositionInQuadrant(glm::vec2 position) {
	return (
		topLeft.x <= position.x && position.x <= bottomRight.x &&
		topLeft.y >= position.y && position.y >= bottomRight.y
	);
}

void QuadtreeNode::updateMassAndPosition(float m, glm::vec2 pos) {
	mass += m;
	weightedPosition += m * pos;
}

bool QuadtreeNode::recursivelyInsertBody(Body& b) {
	if(!checkIfPositionInQuadrant(b.getPosition()))
		return false;

	// Node is an empty leaf
	if (mass == 0.f) {
		updateMassAndPosition(b.getMass(), b.getPosition());
		return true;
	}

	// Node is an internal node with children
	if (nodes[0] != nullptr) {
		for(QuadtreeNode* node : nodes)
			if(recursivelyInsertBody(b)) {
				updateMassAndPosition(b.getMass(), b.getPosition());
				return true;
			}
	}

	// Node is a leaf with mass (body)
	subdivideNote();
	for(QuadtreeNode* node : nodes) {
		if(node->checkIfPositionInQuadrant(weightedPosition))
			node->updateMassAndPosition(mass, weightedPosition);

		if(node->checkIfPositionInQuadrant(b.getPosition()))
			node->updateMassAndPosition(b.getMass(), b.getPosition());
	}
	updateMassAndPosition(b.getMass(), b.getPosition());
	return true;
}