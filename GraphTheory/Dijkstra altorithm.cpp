#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

class Edge {
public:
	char vertex1;
	char vertex2;
	char type;
	int distance;
	bool impassable;
	//Constructor
	Edge(char v1, char v2, char t, int d) :
		vertex1(v1),
		vertex2(v2),
		type(t),
		distance(d),
		impassable(false)
	{}
};

class VisitedVertex {
public:
	char vertex;
	int distance;
	std::string path;
};

std::vector<Edge> map;

void Dijkstra(char startVertex, char endVertex, char otherCondition);
bool isVertexVisited(char vertex, std::vector<VisitedVertex> &visitedVertices);

bool compare(const VisitedVertex &X, const VisitedVertex &Y) {
	return X.distance < Y.distance;
}

int main(int argc, char* argv[]) {

	//Test in loops
	char startVertex = '\0', endVertex = '\0', otherCondition = '\0';
	std::cout << "Please input the start vertex, the end vertex and the other condition:" << std::endl;
	while (std::cin >> startVertex >> endVertex >> otherCondition) {
		Dijkstra(startVertex, endVertex, otherCondition);
		std::cout << "Please input the start vertex, the end vertex and the other condition : " << std::endl;
	}

	return 0;
}

void Dijkstra(char startVertex, char endVertex, char otherCondition) {
	/*This function is used to find a shortest path from startVertex to endVertex, using Dijkstra algorithm*/
	//Initialize the map if necessary
	if (map.empty()) {
		map.push_back(Edge('A', 'B', 'H', 4));
		map.push_back(Edge('A', 'D', 'H', 8));
		map.push_back(Edge('B', 'D', 'P', 14));
		map.push_back(Edge('B', 'D', 'R', 9));
		map.push_back(Edge('B', 'C', 'P', 20));
		map.push_back(Edge('B', 'C', 'W', 15));
		map.push_back(Edge('B', 'C', 'R', 8));
		map.push_back(Edge('A', 'C', 'H', 14));
		map.push_back(Edge('C', 'D', 'H', 5));
		map.push_back(Edge('C', 'D', 'R', 6));
		map.push_back(Edge('D', 'E', 'P', 8));
		map.push_back(Edge('C', 'E', 'W', 20));
		map.push_back(Edge('C', 'E', 'R', 6));
	}

	//For other conditions
	if (startVertex == endVertex) {
		std::cout << "Error:Same start vertex and end vertex!!!" << std::endl;

		//Reset all the edges to passable
		for (std::vector<Edge>::iterator it = map.begin(); it != map.end(); it++) {
			it->impassable = false;
		}
		return;
	}
	for (std::vector<Edge>::iterator iter = map.begin(); iter != map.end(); iter++) {
		if (iter->type == otherCondition) {
			iter->impassable = true;
		}
	}


	//Initialize the visited vertices
	std::vector<VisitedVertex> visitedVertices;
	VisitedVertex startVisitedVertex;
	startVisitedVertex.vertex = startVertex;
	startVisitedVertex.distance = 0;
	visitedVertices.push_back(startVisitedVertex);

	//Loop until endVertex is visited
	while (1) {
		//Visit the next vertex
		std::vector<VisitedVertex> adjacentVertices;
		bool unReachable = true;
		for (std::vector<Edge>::iterator iter = map.begin(); iter != map.end(); iter++) {
			if (iter->impassable) { //Skip the impassable edges
				continue;
			}

			VisitedVertex temp;
			temp.distance = 0;
			char vertex1 = iter->vertex1;
			char vertex2 = iter->vertex2;
			bool v1 = isVertexVisited(vertex1, visitedVertices);
			bool v2 = isVertexVisited(vertex2, visitedVertices);
			if (v1 ^ v2) {
				temp.vertex = v1 ? vertex2 : vertex1;
				std::vector<VisitedVertex>::iterator visitedAdjacentVertexIter;
				for (std::vector<VisitedVertex>::iterator it = visitedVertices.begin(); it != visitedVertices.end(); it++) {
					if (it->vertex == (v1 ? vertex1 : vertex2)) {
						temp.distance = iter->distance + it->distance;
						temp.path = it->path + it->vertex + iter->type;
						break;
					}
				}

				adjacentVertices.push_back(temp);
			}
		}
		//In case the end vertex is unreachable
		if (adjacentVertices.empty()) {
			std::cout << "Error:end vertex is unreachable!!!" << std::endl;

			//Reset all the edges to passable
			for (std::vector<Edge>::iterator it = map.begin(); it != map.end(); it++) {
				it->impassable = false;
			}
			return;
		}
		std::sort(adjacentVertices.begin(), adjacentVertices.end(), compare);
		visitedVertices.push_back(*adjacentVertices.begin());

		//Check if endVertex is visited
		for (std::vector<VisitedVertex>::iterator iter = visitedVertices.begin(); iter != visitedVertices.end(); iter++) {
			if (iter->vertex == endVertex) {
				//Print out the result
				int NodeNumber = iter->path.length() / 2 + 1;
				int Time = iter->distance;
				std::cout << "Path:";
				int length = iter->path.length();
				for (int i = 0; i < length; i += 2) {
					std::cout << iter->path[i] << "(" << iter->path[i + 1] << ")->";
				}
				std::cout << iter->vertex << std::endl;
				std::cout << "Time:" << iter->distance << std::endl;

				//Reset all the edges to passable
				for (std::vector<Edge>::iterator it = map.begin(); it != map.end(); it++) {
					it->impassable = false;
				}
				return;
			}
		}
	}
}

bool isVertexVisited(char vertex, std::vector<VisitedVertex> &visitedVertices) {
	/*This function is used to judge if a vetex is already visited*/
	for (std::vector<VisitedVertex>::iterator iter = visitedVertices.begin(); iter != visitedVertices.end(); iter++) {
		if (vertex == iter->vertex) {
			return true;
		}
	}

	return false;
}
