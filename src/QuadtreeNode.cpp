#include "../include/QuadtreeNode.hpp"

// QuadtreeNode::QuadtreeNode() :
// 	bodyIndex(-1),
// 	mass(0.f),
// 	weightedPosition({0.f, 0.f}),
// 	topLeft({0.f, 0.f}),
// 	bottomRight({0.f, 0.f}),
// 	nodes(4) {}

QuadtreeNode::QuadtreeNode(glm::vec2 topLeft, glm::vec2 bottomRight, int parentDepth, std::vector<Body>& bodies) :
	totalMass(0.f),
	weightedPosition({0.f, 0.f}),
	topLeft(topLeft),
	bottomRight(bottomRight),
	nodes(4),
	depth(parentDepth + 1),
	bodies(bodies) {}

QuadtreeNode::~QuadtreeNode() {
	for(QuadtreeNode* node : nodes) {
		delete node;
		node = nullptr;
	}
}

float QuadtreeNode::getWidth() {
	return bottomRight.x - topLeft.x;
}

glm::vec2 QuadtreeNode::getCenterOfMass() {
	return weightedPosition / totalMass;
}

bool QuadtreeNode::subdivideNode() {
	if(depth == MAX_QUADTREE_DEPTH)
		return false;

	nodes[0] = new QuadtreeNode(
		{(topLeft.x + bottomRight.x) / 2, topLeft.y},
		{bottomRight.x, (topLeft.y + bottomRight.y) / 2},
		depth,
		bodies
	);

	nodes[1] = new QuadtreeNode(
		topLeft,
		{(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2},
		depth,
		bodies
	);

	nodes[2] = new QuadtreeNode(
		{topLeft.x, (topLeft.y + bottomRight.y) / 2},
		{(topLeft.x + bottomRight.x) / 2, bottomRight.y},
		depth,
		bodies
	);

	nodes[3] = new QuadtreeNode(
		{(topLeft.x + bottomRight.x) / 2, (topLeft.y + bottomRight.y) / 2},
		bottomRight,
		depth,
		bodies
	);

	return true;
}

bool QuadtreeNode::checkIfPositionInQuadrant(glm::vec2 position) {
	return (
		topLeft.x <= position.x && position.x <= bottomRight.x &&
		topLeft.y >= position.y && position.y >= bottomRight.y
	);
}

void QuadtreeNode::updateCenterOfMass(int bIndex) {
	totalMass += bodies[bIndex].getMass();
	weightedPosition += bodies[bIndex].getMass() * bodies[bIndex].getPosition();
}

bool QuadtreeNode::recursivelyInsertBody(int newBodyIndex) {
	if(!checkIfPositionInQuadrant(bodies[newBodyIndex].getPosition()))
		return false;

	// Check if this is internal node. We pass body to one of it's children
	if(bodyIndex.empty() && nodes[0] != nullptr) {
		for(QuadtreeNode* node : nodes)
			if(node->recursivelyInsertBody(newBodyIndex)) {
				updateCenterOfMass(newBodyIndex);
				return true;
			}
	}

	// This is a leaf node. We add a body if it has space.
	if(bodyIndex.size() < MAX_BODY_PER_NODE) {
		updateCenterOfMass(newBodyIndex);
		bodyIndex.push_back(newBodyIndex);
		return true;
	}

	// We split node if it has to many bodies and pass
	// those bodies to it's children.
	updateCenterOfMass(newBodyIndex);
	bodyIndex.push_back(newBodyIndex);

	if(subdivideNode()) {
		for(int idx : bodyIndex)
			for(QuadtreeNode* node : nodes)
				if(node->recursivelyInsertBody(idx))
					break;

		bodyIndex.clear();
	}

	// If split wasn't successful. We have reached max depth
	return true;
}

void QuadtreeNode::calculateBodyAcceleration(int bIndex, float mass, glm::vec2 centerOfMass) {
	glm::vec2 r = bodies[bIndex].getPosition() - centerOfMass;
	float r_div = glm::pow(glm::max(0.8f, glm::length(r)), 3);

	r *= - G * mass / r_div;
	bodies[bIndex].addAcceleration(r);
}

void QuadtreeNode::recursivelyCalculateBodyAcceleration(int bIndex) {
	// We are at empty leaft
	if(bodyIndex.empty() && nodes[0] == nullptr)
		return;

	float d = glm::length(bodies[bIndex].getPosition() - getCenterOfMass());
	if (d == 0.f)
		return;

	float s = bottomRight.x - topLeft.x;

	// We perform aproximation
	if(s/d < THETA) {
		calculateBodyAcceleration(bIndex, totalMass, getCenterOfMass());
		return;
	}

	// After that we can't perform an aproximation.
	// If we are not at leaf node, we traverse deeper into the tree
	if(nodes[0] != nullptr) {
		for(QuadtreeNode* node : nodes)
			node->recursivelyCalculateBodyAcceleration(bIndex);

		return;
	}

	// ...else we are at leaf node and we do particle to particle interaction
	for(int idx : bodyIndex) {
		if(idx == bIndex)
			continue;

		calculateBodyAcceleration(bIndex, bodies[idx].getMass(), bodies[idx].getPosition());
	}

}