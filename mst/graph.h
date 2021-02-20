#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
using namespace std;

class edge_list
{
	friend class graph_generator;

	public:
	edge_list(int v,double w):nxt(NULL),weight(w),vertex(v) {}
	~edge_list() {}
	void	setnxt(edge_list* newedge) { nxt=newedge; }
	int	getvertex() { return vertex; }
	double	getweight() { return weight; }
	edge_list* getnxtedge() { return nxt; }

	private:
	edge_list*	nxt;//next edge
	double	weight;//edge weight
	int	vertex;//connected vertex
};

class graph_generator
{
	public:
	graph_generator(int vertex):vertex_num(vertex) {}
	~graph_generator() {}
	void drawer(bool completegraph);
	void addedge(int s,int v,double weight);
	vector<edge_list*> getedgearray() { return edgearray; }

	private:
	int	vertex_num;
	//int	edge_num;//it should be at least  vertex_num-1
	vector<edge_list*> edgearray;//v start from 0 to vertex_num-1
};


#endif

