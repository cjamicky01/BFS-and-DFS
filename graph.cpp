#include "graph.h"

Graph::Graph() {
	vertices = nullptr;
}
// Graph()
// Constructor initializes vertices linked list to empty

Graph::~Graph() {
	VertexNode *temp = vertices;
	VertexNode *tempDel = temp;
	EdgeNode *temp2 = vertices->edgePtr;
	EdgeNode *temp2Del = temp->edgePtr;

	while(temp != nullptr) {
		if(temp->edgePtr != nullptr){
			temp2 = temp->edgePtr->nextEdge;

			while (temp2 != nullptr) {
				temp2Del = temp2;
				temp2 = temp2->nextEdge;
				delete temp2Del;
			}
		}

		tempDel = temp;
		temp = temp->nextVertex;
		delete tempDel;
	}
}
// ~Graph()
// For each VertexNode in the vertices list, Destructor deallocates all EdgeNodes before
// deallocating the VertexNode itself

void Graph::AddVertex(string v) {
	VertexNode *temp = new VertexNode();
	if (vertices == nullptr) {
		temp->vname = v;
		temp->mark = false;
		temp->edgePtr = nullptr;
		temp->nextVertex = nullptr;
		vertices = temp;
	}
	else {
		VertexNode *temp = new VertexNode();
		temp = vertices;
		while (temp->nextVertex != nullptr) {
			temp = temp->nextVertex;
		}
		VertexNode *temp2 = new VertexNode();
		temp2->vname = v;
		temp->nextVertex = temp2;

	}
}
// AddVertex()
// Adds vertex to graph assuming vertex not already present

void Graph::AddEdge(string s, string d, int w) {
	VertexNode *tempS = VertexExists(s);
	VertexNode *tempD = VertexExists(d);
	
	EdgeNode *tempEdge = new EdgeNode();
	EdgeNode *tempSedge = tempS->edgePtr;
	
	tempEdge->destination = tempD;
	tempEdge->weight = w;
	tempEdge->nextEdge = nullptr;

	if(tempS->edgePtr == nullptr){
		tempS->edgePtr = tempEdge;
	
	} else {
		while(tempSedge->nextEdge != nullptr){
			tempSedge = tempSedge->nextEdge;
		}
		
		tempSedge->nextEdge = tempEdge;
	}
	
}
// AddEdge()
// Adds edge from source S  to destination D with specified weight W.
// If there is not enough memory to add the edge, throw the GraphFull exception

VertexNode* Graph::VertexExists(string v) const {
	VertexNode *temp = vertices;
	while (temp->vname != v || temp == nullptr ) {
		temp = temp->nextVertex;
	}
	if(temp == nullptr){
		return NULL;
	}


	return temp;
}
// VertexExists()
// Returns pointer to corresponding VertexNode if vertex V in graph 
// Returns NULL otherwise

EdgeNode* Graph::EdgeExists(string s, string d) const {
	VertexNode *tempS = VertexExists(s);
	VertexNode *tempD = VertexExists(d);
	EdgeNode *tempSedge = tempS->edgePtr;

	while (tempSedge->destination != tempD || tempSedge == nullptr) {
		tempSedge = tempSedge->nextEdge;
	}

	if (tempSedge == nullptr) {
		return NULL;
	}

	return tempSedge;		
}
// EdgeExists()
// Returns pointer to edge node if edge from vertex s to vertex d exists in graph 
// Returns NULL otherwise

int  Graph::WeightIs(string s, string d) {
	if (EdgeExists(s, d) == NULL) {
		throw GraphEdgeNotFound();
	}

	return EdgeExists(s, d)->weight;
}
// WeightIs()
// Returns weight of edge (s,d).  Throws GraphEdgeNotFound if edge not present.

void Graph::ClearMarks() {

}
// ClearMarks()
// Clears all vertex marks

void Graph::MarkVertex(string v) {

}
// MarkVertex()
// Marks vertex V as visited
// Throws GraphVertexNotFound if not present

bool Graph::IsMarked(string v) {

}
// IsMarked()
// Returns true if vertex V is marked, false if not marked
// Throws GraphVertexNotFound if not present

void Graph::GetToVertices(string V, queue<string>& q) {

}
// GetToVertices()
// Returns queue Q of vertex names of those vertices adjacent to vertex V
// The queue here is from the Standard Template Library
// Throws GraphVertexNotFound if not present

void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path) {

}
// DepthFirstSearch()
// Notes:
// (1) This algorithm is flawed in that as it searches for a path, it may
// output some additional vertices that it visited but were not part
// of the actual path.  
// 
// (2) This algorithm requires use of the stack and queue containers from the
// Standard Template Library.  

void Graph::BreadthFirstSearch(string startVertex, string endVertex, queue<string>& visitedq)
{
	queue<string> q;
	queue<string> adjQ;

	if ((VertexExists(startVertex) == NULL) || (VertexExists(endVertex) == NULL))
		throw GraphVertexNotFound();
	bool found = false;
	string vertex;
	string item;

	ClearMarks();
	q.push(startVertex);
	do
	{
		vertex = q.front();
		q.pop();
		if (vertex == endVertex)
		{
			found = true;
			visitedq.push(vertex);
		}
		else
		{
			if (!IsMarked(vertex))
			{
				MarkVertex(vertex);
				visitedq.push(vertex);
				GetToVertices(vertex, adjQ);

				while (!adjQ.empty())
				{
					item = adjQ.front();
					adjQ.pop();

					if (!IsMarked(item))
						q.push(item);
				}
			}
		}
	} while (!q.empty() && !found);

	if (!found)
	{
		while (!visitedq.empty())
		{
			visitedq.pop();
		}
	}

} // End BreadthFirstSearch()
// BreadthFirstSearch()
// Uses the BFS algorithm to determine a path from the
// startVertex to the endVertex.  If a path is found, the path vertices should
// be in the visited queue.  If no path is found, the visited queue should be emptied
// as a signal to the client code that no path exists between the start and
// end vertices.
