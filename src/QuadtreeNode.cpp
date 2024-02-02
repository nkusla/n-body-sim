#include "../include/QuadtreeNode.hpp"

QuadtreeNode::QuadtreeNode() :
	bodyIndex(-1),
	mass(0.f),
	weightedPosition({0.f, 0.f}),
	topLeft({0.f, 0.f}),
	bottomRight({0.f, 0.f}),
	nodes(4) {}

QuadtreeNode::QuadtreeNode(glm::vec2 topLeft, glm::vec2 bottomRight) :
	bodyIndex(-1),
	mass(0.f),
	weightedPosition({0.f, 0.f}),
	topLeft(topLeft),
	bottomRight(bottomRight),
	nodes(4) {}

QuadtreeNode::~QuadtreeNode() {
	if(nodes[0] == nullptr)
		return;

	for(QuadtreeNode* node : nodes) {
		delete node;
	}
}

float QuadtreeNode::getWidth() {
	return bottomRight.x - topLeft.x;
}

glm::vec2 QuadtreeNode::getCenterOfMass() {
	return weightedPosition / mass;
}

void QuadtreeNode::subdivideNode() {
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

void QuadtreeNode::updateNodeData(float m, glm::vec2 pos, int bodyIdx) {
	bodyIndex = bodyIdx;
	mass += m;
	weightedPosition += m * pos;
}

bool QuadtreeNode::recursivelyInsertBody(Body& newBody, int newBodyIndex) {
	if(!checkIfPositionInQuadrant(newBody.getPosition()))
		return false;

	// Node is an empty leaf
	if (mass == 0.f) {
		updateNodeData(newBody.getMass(), newBody.getPosition(), newBodyIndex);
		return true;
	}

	// Node is an internal node with children
	if (nodes[0] != nullptr) {
		for(QuadtreeNode* node : nodes)
			if(recursivelyInsertBody(newBody, newBodyIndex)) {
				updateNodeData(newBody.getMass(), newBody.getPosition(), -1);
				return true;
			}
	}

	// Node is a leaf with mass (one body)
	subdivideNode();
	bool newBodyPassed = false;
	bool nodeBodyPassed = false;
	for(QuadtreeNode* node : nodes) {
		if(node->checkIfPositionInQuadrant(getCenterOfMass()) && !nodeBodyPassed) {
			node->updateNodeData(mass, getCenterOfMass(), bodyIndex);
			nodeBodyPassed = true;
		}

		if(node->checkIfPositionInQuadrant(newBody.getPosition()) && !newBodyPassed) {
			node->updateNodeData(newBody.getMass(), newBody.getPosition(), newBodyIndex);
			newBodyPassed = true;
		}
	}

	updateNodeData(newBody.getMass(), newBody.getPosition(), -1);
	return true;
}

void QuadtreeNode::calculateBodyAcceleration(Body& b, float mass, glm::vec2 centerOfMass) {
	glm::vec2 r = b.getPosition() - centerOfMass;
	float r_div = glm::pow(glm::max(0.8f, glm::length(r)), 3);

	r *= - G * mass / r_div;
	b.addAcceleration(r);
}

void QuadtreeNode::recursivelyCalculateBodyAcceleration(Body& b, int idx, float theta) {
	if(bodyIndex == idx || mass == 0.f)
		return;

	if(bodyIndex != -1) {
		calculateBodyAcceleration(b, mass, getCenterOfMass());
		return;
	}

	float d = glm::length(b.getPosition() - getCenterOfMass());
	float s = bottomRight.x - topLeft.x;

	// This subtree can be aproximated
	// if(theta > s/d) {
	// 	calculateBodyAcceleration(b, mass, getCenterOfMass());
	// 	return;
	// }

	for(QuadtreeNode* node : nodes)
		node->recursivelyCalculateBodyAcceleration(b, idx, theta);

	return;
}