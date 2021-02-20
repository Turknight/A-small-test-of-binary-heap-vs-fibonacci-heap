#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <limits>
#include <time.h>
#include <vector>
#include "fibonacci_heap.h"

using namespace std;

void fibonacci_heap::makeheap()
{
	min=NULL;
	rootnum=0;
	nodenum=0;
	return;
}

void fibonacci_heap::insertrootlist(node* x)
{
	rootnum++;
	//if there is no other root
	if(min==NULL)
		{
			min=x;
			x->right=x;
			x->left=x;
			x->parent=NULL;
		}
	//insert to min's right
	else
		{
			node* tmp=min->right;
			tmp->left=x;
			min->right=x;
			x->right=tmp;
			x->left=min;
			x->parent=NULL;
		}
	//cout<<"right of insert node is node "<<x->right->getname()<<endl;
	//cout<<"left of insert node is node "<<x->left->getname()<<endl;
	return;
}

void fibonacci_heap::insert(node* x)
{
	x->degree=0;
	x->parent=NULL;
	x->child=NULL;
	x->mark=false;
	if(min==NULL)
		{
			min=x;
			x->right=x;
			x->left=x;
			x->parent=NULL;
			rootnum++;
		}
	else//insert into root list
		{
			insertrootlist(x);
			if(x->key<min->key)
				min=x;
		}
	nodenum++;
	return;
}

node* fibonacci_heap::extractmin()
{
	node* z=min;
	//if(z==NULL)
		//cout<<"no min"<<endl;
	if(z!=NULL)
		{
			//cout<<"extract "<<z->getname()<<endl;
			//each child of z
			if(z->child!=NULL)
				{
					node* rmv=z->child;
					while(rmv->right!=rmv)//there is at least two children
						{
							node* rmv_right=rmv->right;
							node* rmv_left=rmv->left;
							rmv_right->left=rmv_left;
							rmv_left->right=rmv_right;
							insertrootlist(rmv);
							rmv->parent=NULL;
							rmv=rmv_right;
						}
					if(rmv->right==rmv)//there is only one children
						{
							insertrootlist(rmv);
							rmv->parent=NULL;
						}
				}
			//remove z from root list
			rootnum--;
			if(z->right==z)
				min=NULL;
			else
				{
					min=z->right;
					//cout<<"min here is "<<min->getname()<<endl;
					node* z_right=z->right;
					node* z_left=z->left;
					z_right->left=z_left;
					z_left->right=z_right;
					consolidate();
				}
			nodenum--;
		}
	return z;
}

void fibonacci_heap::consolidate()
{
	//cout<<"consolidate is called"<<endl;
	//max bound
	double square5=sqrt(5);
	double goldenratio=(double)((1+square5)/2);
	int dn=1+(double)(log(nodenum)/log(goldenratio));
	map<int,node*> conarray;
	for(int i=0;i<dn+1;i++)
		conarray[i]=NULL;
	//for each node w in the root list
	int iter=0;
	//start from min
	node* w=min;
	int d=w->degree;
	while(iter<rootnum)//after (while),iter=1,2,...,rootnum and iter can be reset
		{
			node* x=w;
			d=x->degree;
			while(conarray[d]!=NULL&&conarray[d]!=x)
				{
					//cout<<"node "<<x->getname()<<" with degree= "<<d<<" want to be root"<<endl;
					//cout<<"But A["<<d<<"]"<<" is occupied by "<<conarray[d]->getname()<<endl;
					node* y=conarray[d];
					if(x->key>y->key)//exchange x with y
						{
							node* tmp=y;
							y=x;
							x=tmp;
						}
					link(y,x);
					conarray[d]=NULL;
					d++;
					iter=0;
				}
			conarray[d]=x;
			//next node
			w=x->right;
			iter++;
		}

	min=NULL;
	//update new min from new root list
	for(int i=0;i<dn+1;i++)
		{
			//find the first node
			if(conarray[i]!=NULL)
				{
					min=conarray[i];
					break;
				}
		}
	for(int i=0;i<dn+1;i++)
		{
			//if(conarray[i]!=NULL)
				//cout<<"A["<<i<<"]="<<conarray[i]->getname()<<endl;
		}
	node* tmpmin=min;
	for(int i=0;i<rootnum+1;i++)
		{
			if(tmpmin->key<min->key)
				min=tmpmin;
			tmpmin=tmpmin->right;
		}
	return;
}

void fibonacci_heap::link(node* y,node* x)
{
	//cout<<"link is called"<<endl;
	rootnum--;
	//remove y from root list
	node* y_left=y->left;
	node* y_right=y->right;
	y_left->right=y_right;
	y_right->left=y_left;
	//make y child of x
	x->degree++;
	if(x->child==NULL)//y is the only child
		{
			y->right=y;
			y->left=y;
			y->parent=x;
			x->child=y;
		}
	else//insert y to the right of the child
		{
			node* child=x->child;
			node* tmp=child->right;
			y->parent=x;
			y->left=child;
			y->right=tmp;
			child->right=y;
			tmp->left=y;
		}
	y->mark=false;
	return;
}

void fibonacci_heap::decreasekey(node* x,double k)
{
	if(k>x->key)
		cout<<"Error"<<endl;
	x->key=k;
	node* y=x->parent;
	if(y!=NULL && x->key<y->key)
		{
			cut(x,y);
			cascadingcut(y);
		}
	if(x->key<min->key)
		min=x;
	return;
}

void fibonacci_heap::cut(node* x,node* y)
{
	//remove x from the child list of y, y->degree--
	y->degree--;
	if(y->child!=x)//x is not pointed by y
		{
			node* x_right=x->right;
			node* x_left=x->left;
			x_right->left=x_left;
			x_left->right=x_right;
		}
	else//x is y's child
		{
			if(x->right==x)//it's only child
				{
					y->child=NULL;
				}
			else//point to right as new child
				{
					node* x_right=x->right;
					node* x_left=x->left;
					x_right->left=x_left;
					x_left->right=x_right;
					y->child=x_right;
				}
		}
	//add x to the root list
	insertrootlist(x);
	x->parent=NULL;
	x->mark=false;
	return;
}

void fibonacci_heap::cascadingcut(node* y)
{
	node* z=y->parent;
	if(z!=NULL)
		{
			if(y->mark==false)
				y->mark=true;
			else
				{
					cut(y,z);
					cascadingcut(z);
				}
		}
	return;
}

void fibonacci_heap::deletenode(node* x)
{
	decreasekey(x,-numeric_limits<double>::max());
	node* tmp=extractmin();
	return;
}
/*
int main()
{
	fibonacci_heap* heap=new fibonacci_heap();
	//cout<<"sucess here"<<endl;
	//insert 3
	//node* node3=new node("3",3);
	//node* node4=new node("4",4);
	//node* node5=new node("5",5);

	//insert 0 to 99999
	int size=1000000;
	vector<node*> nodearray;
	nodearray.resize(1000000);
	
	for(int i=0;i<size;i++)
		{
			string name=to_string(i);
			node* tmp=new node(name,i);
			nodearray[i]=tmp;
		}
	clock_t tttStart = clock();
	for(int i=0;i<size;i++)
		heap->insert(nodearray[i]);
	printf("Make Time taken: %.2fs\n", (double)(clock() - tttStart)/CLOCKS_PER_SEC);
	clock_t tStart = clock();
	//decrease key here
	for(int i=0;i<size;i++)
		heap->decreasekey(nodearray[i],i-10);
	printf("Decrease key Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	clock_t ttttStart = clock();
	for(int i=0;i<size;i++)
		{
			string name=to_string(-(i+size+1));
			node* tmp=new node(name,-(i+size+1));
			heap->insert(tmp);
		}
	printf("Insert Time taken: %.2fs\n", (double)(clock() - ttttStart)/CLOCKS_PER_SEC);
	//cout<<"root number = "<<heap->getrootnum()<<endl;
	//cout<<"node number = "<<heap->getnodenum()<<endl;
	//extract 0 to 99
	clock_t ttStart = clock();
	for(int i=0;i<size;i++)
		{
			node* tmp=heap->extractmin();
			//cout<<"Extract min node "<<tmp->getname()<<" with value "<<tmp->getkey()<<endl;
			//cout<<"root number = "<<heap->getrootnum()<<'\n';
			//cout<<heap->getnodenum()<<" nodes are left"<<endl;
			//printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
		}
	
	printf("Extract min Time taken: %.2fs\n", (double)(clock() - ttStart)/CLOCKS_PER_SEC);
	return 0;
}
*/
