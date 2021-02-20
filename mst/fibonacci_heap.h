#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <iostream>
#include <string>

using namespace std;

class node
{
	friend class fibonacci_heap;	

	public:
	node(string inputname,double inputkey):child(NULL),parent(NULL),left(NULL),right(NULL),mark(false),key(inputkey),name(inputname),degree(0) {}
	~node() {}
	string	getname() { return name; }
	double	getkey() { return key; }

	private:
	node*	child;//only one child
	node*	parent;
	node*	left;
	node*	right;
	bool	mark;
	double	key;
	string name;
	int degree;
};

class fibonacci_heap
{
	public:
	fibonacci_heap() { makeheap(); }
	~fibonacci_heap() {}

	void	makeheap();
	void	insert(node* x);
	node*	findmin()	{ return min; }
	node*	extractmin();
	void	consolidate();
	void	link(node* y,node* x); 
	void	decreasekey(node* x,double k);
	void	cut(node* x,node* y);
	void	cascadingcut(node* y);
	void	deletenode(node* x);
	void	insertrootlist(node* x);	//root num ++ here
	int	getrootnum() { return rootnum; }
	int	getnodenum() { return nodenum; }

	private:
	node*	min;//node with min key
	int		rootnum;//number of root nodes
	int		nodenum;//number of nodes
};

#endif
