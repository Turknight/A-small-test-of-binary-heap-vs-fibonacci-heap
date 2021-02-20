#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <limits>
#include <time.h>
#include "graph.h"
#include "fibonacci_heap.h"
#include "binary_heap.h"

using namespace std;

int main()
{
	//whether it is a conplete graph or a sparse graph
	bool completegraph=false;
	

	//choose fibonacci or binary heap
	bool binheap=false;

	//modify the vertex number here
	int vertex=150;

	//new graph

	int edge;
	if(completegraph==true)
		edge=vertex*(vertex-1)/2;
	else
		edge=vertex-1;
	graph_generator* mygraph=new graph_generator(vertex);
	mygraph->drawer(completegraph);
	cout<<"Vertex number is "<<vertex<<endl;
	cout<<"Edge number is "<<edge<<endl;

	//prim's algorithm
	clock_t tStart = clock();
	int root=0;
	vector<double> key;//key for every vertex
	vector<int> parent;//parent of each vertex 
	vector<bool> isq;//whether vertex is in the heap
	key.resize(vertex);
	parent.resize(vertex);
	isq.resize(vertex);
	for(int i=0;i<vertex;i++)
		{
			key[i]=numeric_limits<double>::max();
			parent[i]=-1;//nil
			isq[i]=true;
		}
	key[root]=0;

	vector<double> timerecord;
	vector<double> ttimerecord;
	if(binheap==false)
		{
			cout<<"Use Fibonacci heap"<<endl;
			//make heap=every vertex
			fibonacci_heap* q=new fibonacci_heap();
			map<int,node*> findnode;
			for(int i=0;i<vertex;i++)
				{
					string name=to_string(i);//i= vertex i
					node* tmp=new node(name,key[i]);
					findnode[i]=tmp;
					q->insert(tmp);
				}
			while(q->getnodenum()>0)
				{
					clock_t tttStart = clock();
					node* u=q->extractmin();
					ttimerecord.push_back((double)(clock() - tttStart)/CLOCKS_PER_SEC);
					int nodeu=stoi(u->getname());
					isq[nodeu]=false;
					

					//for each vertex v adjacent to u
					edge_list* v=mygraph->getedgearray()[nodeu];
					while(v!=NULL)
						{
							int nodev=v->getvertex();
							double weight=v->getweight();
							//if v in Q and w(u,v) < v.key
							if(isq[nodev]==true && weight<key[nodev])
								{
									parent[nodev]=nodeu;
									key[nodev]=weight;
									clock_t ttStart = clock();
									q->decreasekey(findnode[nodev],weight);
									timerecord.push_back((double)(clock() - ttStart)/CLOCKS_PER_SEC);
								}
							//find next v
							v=v->getnxtedge();
						}
				}
		}
	else
		{
			cout<<"Use Binary heap"<<endl;
			//make heap=every vertex
			binary_heap* q=new binary_heap();
			map<int,bnode*> findnode;
			vector<bnode*> array;
			array.resize(vertex);
			for(int i=0;i<vertex;i++)
				{
					string name=to_string(i);//i= vertex i
					bnode* tmp=new bnode(name,key[i]);
					findnode[i]=tmp;
					//q->insert(tmp);
					array[i]=tmp;
				}
			q->buildminheap(array);//save time than insert
			
			while(q->heapsize()>1)
				{
					//cout<<"min is node "<<q->findmin()->getname()<<endl;
					//print out every node's position information
					/*
					for(int i=1;i<q->getheap().size();i++)
						{
							cout<<"heap["<<i<<"] has vertex "<<q->getheap()[i]->getname()<<" with key= "<<q->getheap()[i]->getkey()<<endl;
						}
					*/
					clock_t tttStart = clock();
					bnode* u=q->extractmin();
					ttimerecord.push_back((double)(clock() - tttStart)/CLOCKS_PER_SEC);
					int bnodeu=stoi(u->getname());
					isq[bnodeu]=false;
					//cout<<"extract node "<<u->getname()<<endl;
					

					//for each vertex v adjacent to u
					edge_list* v=mygraph->getedgearray()[bnodeu];
					while(v!=NULL)
						{
							int bnodev=v->getvertex();
							double weight=v->getweight();
							//if v in Q and w(u,v) < v.key
							if(isq[bnodev]==true && weight<key[bnodev])
								{
									//cout<<"relax edge "<<u->getname()<<" , "<<findnode[bnodev]->getname()<<" to weight "<<weight<<endl;
									parent[bnodev]=bnodeu;
									key[bnodev]=weight;
									clock_t ttStart = clock();
									q->decreasekey(findnode[bnodev],weight);
									timerecord.push_back((double)(clock() - ttStart)/CLOCKS_PER_SEC);
								}
							//find next v
							v=v->getnxtedge();
						}
				}
			/*
			//check position
			for(int i=0;i<vertex;i++)
				{
					cout<<"vertex "<<array[i]->getname()<<" is in position "<<array[i]->getposition()<<endl;
				}
			*/
		}
	//end of prim
	printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	//print result
	int totalcost=0;
	for(int i=0;i<vertex;i++)
		{
			//if(key[i]<0)
				//cout<<"Illegal vertex "<<i<<endl;
			//cout<<"Vertex "<<i<<" has parent "<<parent[i]<<" with adding weight "<<key[i]<<endl;
			totalcost+=key[i];
		}
	cout<<"Cost of the tree is "<<totalcost<<endl;
	double acctime=0;
	for(int i=0;i<timerecord.size();i++)	
		acctime+=timerecord[i];
	printf("Decrease key time taken: %.2fs\n", acctime);
	double aacctime=0;
	for(int i=0;i<ttimerecord.size();i++)	
		aacctime+=ttimerecord[i];
	printf("Extract min key time taken: %.2fs\n", aacctime);

	return 0;
}
