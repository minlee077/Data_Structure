#define _CRT_SECURE_NO_WARNINGS

#include "JsonReader.h"
#include <json/json.h>
bool DataReader::ReadFromFile(const char * filename, char * buffer, int len)
{
	FILE* r = fopen(filename, "rb");
	if (NULL == r)
		return false;
	size_t fileSize = fread(buffer, 1, len, r);
	fclose(r);
	return true;
}

vector<Node> DataReader::ReadNode(string filename, int length)
{
	vector<Node> retV;
	char* jsonBuffer = new char[length];
	if (false == ReadFromFile(filename.c_str(), jsonBuffer, length)){
		delete[] jsonBuffer;
		return retV;
	}
	string config_doc = jsonBuffer;
	Json::Value root;
		
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(config_doc,root);
	if (!parsingSuccessful)
	{
		delete[] jsonBuffer;
		std::cout << "failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
		return retV;
	}
	Json::Value features = root["features"];
	for (int i = 0; i < features.size(); ++i) {
		Node n=Node();
		n.fid = features[i]["attributes"]["FID"].asInt();
		n.x = features[i]["geometry"]["x"].asDouble();
		n.y = features[i]["geometry"]["y"].asDouble();
		retV.push_back(n);
	}
	delete[] jsonBuffer;
	return retV;
}

vector<vector<Edge>> DataReader::ReadEdge(string filename, int length, const vector<Node>& nodes)
{
	vector<vector<Edge>> retV(nodes.size(),vector<Edge>());
	
	char* jsonBuffer = new char[length];
	if (false == ReadFromFile(filename.c_str(), jsonBuffer, length)) {
		delete[] jsonBuffer;
		return retV;
	}
	string config_doc = jsonBuffer;
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(config_doc, root);
	if (!parsingSuccessful)
	{
		std::cout << "failed to parse configuration\n"
			<< reader.getFormattedErrorMessages();
		delete[] jsonBuffer;
		return retV;
	}
	Json::Value features = root["features"];
	for (int i = 0; i < features.size(); ++i) {
		int start = 0;
		int dest = 0;
		double x = features[i]["geometry"]["paths"][0][0][0].asDouble();
		for (int n = 0; n < nodes.size(); ++n) {
			if (nodes[n].x == (int)x){
				start = n;
				break;
			}
		}
		

		x = features[i]["geometry"]["paths"][0][1][0].asDouble();
		for (int n = 0; n < nodes.size(); ++n) {
			if (nodes[n].x == (int)x) {
				dest = n;
				break;
			}
		}
		double weight = features[i]["attributes"]["PMNTN_LT"].asDouble();
		Edge e1 = Edge(start, dest, weight);
		Edge e2 = Edge(dest, start, weight);
		retV[start].push_back(e1);
		retV[dest].push_back(e2);
	}
	delete[] jsonBuffer;
	return retV;
}
