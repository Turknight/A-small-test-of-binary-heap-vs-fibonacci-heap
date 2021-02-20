#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class bnode
{
	friend class binary_heap;

	public:
	bnode(string bnodename,double bnodekey):name(bnodename),key(bnodekey) {}
	~bnode() {}
	string getname() { return name; }
	double getkey() { return key; }
	void setkey(double insertkey) { key=insertkey; }
	void setposition(int newposition) { position=newposition; }
	int getposition() { return position; }

	private:
	string name;
	double key;
	int position;//reflect its position in the heap
};

class binary_heap
{
	public:
	binary_heap() {}
	~binary_heap() {}

	void	minheapify(int i);
	//void	buildminheap(vector<double>& array);
	void	buildminheap(vector<bnode*>& array);
	//void	insert(double key);
	void	insert(bnode* insertbnode);
	//double	findmin()	{ return heap[1]; }
	bnode*	findmin() { return heap[1]; }
	//double	extractmin();
	bnode*	extractmin();
	//void	decreasekey(int i,double k);
	void	decreasekey(bnode* decreasenode,double k);
	int		heapsize() { return heap.size(); }
	vector<bnode*> getheap() { return heap; }
	

	private:
	vector<bnode*>	heap;//heap[0] is not used

};


#endif
