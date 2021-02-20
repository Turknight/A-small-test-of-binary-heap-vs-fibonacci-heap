#include <iostream>
#include "graph.h"

using namespace std;

void graph_generator::drawer(bool completegraph)
{
	//initialization
	edgearray.resize(vertex_num);
	for(int i=0;i<edgearray.size();i++)
		edgearray[i]=NULL;

	//int e=edge_num;//edge available
	if(completegraph==false)//simplest graph	
		{
			for(int i=0;i<vertex_num-1;i++)
				{
					double w=((i*34)%263)+1;
					//int w=1;
					addedge(i,i+1,w);
					//cout<<"vertex "<<i<<" and "<<i+1<<" with weight "<<w<<endl;
					//e--;
				}
		}
	else//complete graph
		{
			for(int i=0;i<vertex_num-1;i++)
				{
					for(int j=i+1;j<vertex_num;j++)
						{
							double w=((i*34+37*j)%263)+1;
							addedge(i,j,w);
						}
				}
		}
	return;
}

void graph_generator::addedge(int s,int v,double weight)
{
	//add to edgearray[s]
	if(edgearray[s]==NULL)
		{
			edge_list* tmp=new edge_list(v,weight);
			edgearray[s]=tmp;
		}
	else//be the new head
		{
			edge_list* tmp=edgearray[s];
			edge_list* head=new edge_list(v,weight);
			edgearray[s]=head;
			head->setnxt(tmp);
		}
	//add to edgearray[v]
	if(edgearray[v]==NULL)
		{
			edge_list* tmp=new edge_list(s,weight);
			edgearray[v]=tmp;
		}
	else//be the new head
		{
			edge_list* tmp=edgearray[v];
			edge_list* head=new edge_list(s,weight);
			edgearray[v]=head;
			head->setnxt(tmp);
		}
	return;
}
/*
int main()
{
	return 0;
}
*/
