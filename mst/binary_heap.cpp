#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <limits>
#include "binary_heap.h"

using namespace std;

void binary_heap::minheapify(int i)
{
	//cout<<"minheapify heap["<<i<<"]"<<endl;
	int left=2*i;
	int right=2*i+1;
	int heapsize=heap.size()-1;
	int min=0;
	if(left<=heapsize && heap[left]->getkey()<heap[i]->getkey())
		min=left;
	else
		min=i;
	if(right<=heapsize && heap[right]->getkey()<heap[min]->getkey())
		min=right;
	if(min!=i)
		{
			//exchange a[i] with a[min]
			//int minpos=min;
			//int ipos=i;
			
			bnode* tmp=heap[min];
			heap[min]=heap[i];
			heap[i]=tmp;
			heap[min]->setposition(min);
			heap[i]->setposition(i);
			

			minheapify(min);
		}
	return;
}

void binary_heap::buildminheap(vector<bnode*>& array)
{
	//cout<<"buildminheap"<<endl;
	//clear the previous content
	heap.clear();
	heap.resize(array.size()+1);
	heap[0]=NULL;//not used
	for(int i=1;i<heap.size();i++)
		{
			heap[i]=array[i-1];
			array[i-1]->setposition(i);
		}
	//for(int i=0;i<array.size();i++)
		//cout<<"vertex "<<i<<" with position "<<array[i]->getposition()<<endl;
	int mid=(array.size())/2;
	for(int i=mid;i>=1;i--)
		minheapify(i);
	//for(int i=0;i<array.size();i++)
		//cout<<"vertex "<<i<<" with position "<<array[i]->getposition()<<endl;
	return;
}

bnode* binary_heap::extractmin()
{
	//cout<<"extractmin"<<endl;
	if(heap.size()<2)
		cout<<"heap underflow"<<endl;
	bnode* min=heap[1];
	heap[1]=heap[heap.size()-1];
	//record new position!!!
	heap[1]->setposition(1);
	//cout<<"change node "<<min->getname()<<" with node "<<heap[1]->getname()<<endl;
	heap.resize(heap.size()-1);
	//cout<<"heap size is now "<<heap.size()-1<<endl;
	minheapify(1);
	return min;
}

void binary_heap::decreasekey(bnode* decreasenode,double k)
{
	//cout<<"decrease key"<<endl;
	int i=decreasenode->getposition();
	if(heap[i]!=decreasenode)
		cout<<"Wrong number!!!"<<endl;
	if(k>heap[i]->getkey())
		cout<<"error when decrease key"<<endl;
	heap[i]->setkey(k);
	int j=i;
	while(j>1 && heap[j/2]->getkey()>heap[j]->getkey())
		{
			//exchange a[i] with a[parent]
			//int ipos=i;
			//int parentpos=i/2;
			//cout<<"decrease key change node "<<heap[j/2]->getname()<<" in ["<<j/2<<"]"<<" with node "<<heap[j]->getname()<<" in ["<<j<<"]"<<endl;
			bnode* tmp=heap[j/2];
			heap[j/2]=heap[j];
			heap[j]=tmp;
			heap[j]->setposition(j);
			heap[j/2]->setposition(j/2);
			
			j=j/2;
		}
	return;
}

void binary_heap::insert(bnode* insertbnode)
{
	double key=insertbnode->getkey();
	heap.resize(heap.size()+1);
	//heap[heap.size()-1]=numeric_limits<double>::max();
	heap[heap.size()-1]=insertbnode;
	heap[heap.size()-1]->setposition(heap.size()-1);
	insertbnode->setkey(numeric_limits<double>::max());
	decreasekey(heap[heap.size()-1],key);
	return;
}
