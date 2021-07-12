#pragma once

#include <Eigen/Dense>
#include <vector>


struct node {

	node(Eigen::Vector2d);

	double mass;

	Eigen::Vector2d pos;
	Eigen::Vector2d vel;
	Eigen::Vector2d force;
};

struct rod {

	rod(node*, node*, double);

	node* start;
	node* end;

	double nat_length;
	double stiffness;
};


class World {
private: 
	

	void addForces();
	void updateLocations(double);

public:
	std::vector<node*> nodes;
	std::vector<rod*> rods;

	void addNode(node*);
	void addRod(rod*);

	node* getNearestNode(Eigen::Vector2d);
	void getNodesPos(std::vector<int>*, std::vector<int>*);
	void getRodsPos(std::vector<int>*, std::vector<int>*, std::vector<int>*, std::vector<int>*);

	void makeTestObject();
	void applyPhysicsLoop(double);

};