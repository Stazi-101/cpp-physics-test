
#include "Physics.h"

#include <iostream>


node::node(Eigen::Vector2d start_location) {
	pos = start_location;
	mass = 1;

	vel = Eigen::Vector2d(0, 0);
	force = Eigen::Vector2d(0, 0);
}

rod::rod(node* start_node, node* end_node, double length) {
	start = start_node;
	end = end_node;
	nat_length = length;
	stiffness = 0.0000001;
}


void World::addNode(node* new_node) {
	nodes.push_back(new_node);
}

void World::addRod(rod* new_rod) {
	rods.push_back(new_rod);
}


void World::makeTestObject() {
	node* new_node_1 = new node(Eigen::Vector2d(20, 20));
	addNode(new_node_1);
	node* new_node_2 = new node(Eigen::Vector2d(40, 40));
	addNode(new_node_2);
	rod* new_rod = new rod(new_node_1, new_node_2, 100);
	addRod(new_rod);
}

void World::addForces() {
	Eigen::Vector2d start_pos;
	Eigen::Vector2d end_pos;
	Eigen::Vector2d displacement;
	double distance;
	double extension;
	double force;


	for (rod* r : rods) {
		start_pos = r->start->pos;
		end_pos = r->end->pos;

		displacement = end_pos - start_pos;
		distance = displacement.norm();
		extension = distance - r->nat_length;
		force = r->stiffness * extension;
		//std::cout << force << '\n';
 
		r->start->force += displacement.normalized() * force;
		r->end->force   -= displacement.normalized() * force;
		
		}
}

node* World::getNearestNode(Eigen::Vector2d to_pos) {
	double closest_dis = 100000;
	node* closest = nodes.front();


	for (node* n : nodes) {
		Eigen::Vector2d from_pos = n->pos;
		double dis = (from_pos - to_pos).norm();
		if (dis < closest_dis) {
			closest_dis = dis;
			closest = n;
		}
	}
	return closest;
}

void World::getNodesPos(std::vector<int>* xs, std::vector<int>* ys) {

	for (auto n : nodes) {
		Eigen::Vector2d node_pos = n->pos;
		xs->push_back( int( std::floor(node_pos(0)) ) );
		ys->push_back( int( std::floor(node_pos(1)) ) );
	}
}

void World::getRodsPos(std::vector<int>* x1s, std::vector<int>* y1s, std::vector<int>* x2s, std::vector<int>* y2s) {

	for (auto r : rods) {
		Eigen::Vector2d rod_start = r->start->pos;
		Eigen::Vector2d rod_end = r->end->pos;
		x1s->push_back(int(std::floor(rod_start(0))));
		y1s->push_back(int(std::floor(rod_start(1))));
		x2s->push_back(int(std::floor(rod_end(0))));
		y2s->push_back(int(std::floor(rod_end(1))));
	}
}


void World::updateLocations(double dt) {
	Eigen::Vector2d acc;
	for (node* n : nodes) {
		n->pos += n->vel * dt/1000;
		

		acc = n->force / n->mass;

		//std::cout << n->pos << ' ' << n->vel << ' ' << acc << '\n';

		n->force = Eigen::Vector2d(0, 0);

		n->vel += acc * dt;
	}
}




void World::applyPhysicsLoop(double dt) {
	addForces();
	updateLocations(dt);
}
