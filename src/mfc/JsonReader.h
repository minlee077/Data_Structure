#pragma once
#include<vector>
#include<string>
#include"Node.h"
#include"Edge.h"
using namespace std;

class DataReader
{
	static bool ReadFromFile(const char* filename, char* buffer, int len);

public:
	static vector<Node> ReadNode(string filename, int length);
	static vector<vector<Edge>> ReadEdge(string filename, int length,const vector<Node>& nodes);
};