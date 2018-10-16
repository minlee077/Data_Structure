#pragma once
#include<vector>
#include"Edge.h"
#include"Node.h"
using namespace std;

class Djikstra
{
	vector<bool> visited;
	vector<int> node;
	vector<int> pLocation;
	vector<vector<Edge>> edges;
public:
	Djikstra(const vector<Node>& n, const vector<vector<Edge>>& e) :node(n.size(),0), edges(e), pLocation(node.size(), 0), visited(node.size(), false) {
		for (unsigned i = 0; i < node.size(); ++i) {
			pLocation[i] = i;
			node[i] = INT_MAX;
		}
	}
	Djikstra(const vector<int>& n, const vector<vector<Edge>>& e) :node(n), edges(e), pLocation(node.size(),0 ), visited(node.size(),false) {
		for (unsigned i = 0; i < node.size(); ++i) {			
			pLocation[i] = i;
			node[i] = INT_MAX;
		}
	}
	vector<int> findPath(int start, int dest);
};
