#include "DijkstraMake.h"
#include <queue>
#include<iostream>
using namespace std;
vector<int> Djikstra::findPath(int start, int dest)
{
	vector<int> path;
	priority_queue<pair<int,int>>buffer;
	buffer.push(pair<int, int>(start, 0));
	node[start] = 0;
	while (!buffer.empty()) {
		int startIDX = buffer.top().first;
		buffer.pop();
		for (unsigned i = 0; i < edges[startIDX].size(); ++i) {
			int weight = (int)(node[startIDX] + edges[startIDX][i].getWeight());
			int dest = (int)(edges[startIDX][i].getDest());
			if (weight < node[dest]) {
				node[dest] = weight;
				pLocation[dest] = startIDX;
				buffer.push(pair<int, int>(dest, node[dest]));
				cout << startIDX << " " << dest << " " << weight << endl;
			}
		}
	}
	int tmp = dest;
	path.push_back(tmp);
	while (tmp != start) {
		if (tmp == pLocation[tmp])
			break;
		tmp = pLocation[tmp];
		path.push_back(tmp);
	}
	if (tmp != start && tmp == pLocation[tmp])
		return vector<int>();
	return path;
}

