# A-small-test-of-binary-heap-vs-fibonacci-heap
C++ implementation of Prim's algorithm on two kinds of priority queues

This is a small test of whether a fibonacci heap is better than binary heap on minimum spanning tree problem run by Prim's algorithm

Type "make" to compile the project

Type "./mst" to run the Prim's algorithm after compile

You can modifty the graph's structure by modifying graph_generator::drawer in graph.cpp

In main.cpp,

if completegraph=false, a simplest graph is used
                =true,  a complete graph is used

if binheap=false, a fibonacci heap is used
          =true, a binary heap is used

Vertex number is set to 150 by default

If there is any improvement to my code, I welcome any suggestion!!!
