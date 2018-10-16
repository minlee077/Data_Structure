#pragma once

class Edge {
	int start, dest;
	double weight;
public:
	Edge(){}
	Edge(int s,int d, double w):start(s),dest(d),weight(w){}
	int getStart() { return start; }
	int getDest() { return dest; }
	double getWeight() { return weight; }
};