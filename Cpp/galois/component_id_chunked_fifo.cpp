#include "Galois/Galois.h"
#include "Galois/Accumulator.h"
#include "Galois/Bag.h"
#include "Galois/Statistic.h"
#include "Galois/UnionFind.h"
#include "Galois/Graphs/LCGraph.h"
#include "Galois/ParallelSTL/ParallelSTL.h"
#include "llvm/Support/CommandLine.h"
#include "Galois/Runtime/WorkList.h"

#include "Lonestar/BoilerPlate.h"
#include<sys/time.h>

#include <utility>
#include <algorithm>
#include <iostream>
#include "Galois/Statistic.h"


struct SNode{
	unsigned int dist;
};

typedef Galois::Graph::LC_CSR_Graph<SNode,void> Graph;
typedef Graph::GraphNode GNode;
Graph graph;
unsigned int number_of_threads;

struct GNodeIndexer: public std::unary_function<GNode,unsigned int> {
	unsigned int operator()(const GNode& val) const {
		return (graph.getData(val, Galois::NONE).dist % 64);
	}
};

struct AsyncAlgo {

	std::string name() const { return "Parallel (Async)"; }

	void operator()(GNode& source) const {
		using namespace GaloisRuntime::WorkList;
		typedef dChunkedFIFO<64> dChunk;
		typedef ChunkedFIFO<64> Chunk;
		typedef OrderedByIntegerMetric<GNodeIndexer,dChunk> OBIM;

		std::deque<GNode> initial;

		for (Graph::iterator ii = graph.begin(), ei = graph.end(); ii != ei; ++ii) {
			GNode src = *ii;
			graph.getData(src, Galois::NONE).dist = src;
			initial.push_back(src);
		}

		//set the number of active threads
		Galois::setActiveThreads(number_of_threads);

		std::cout << "graph size: " << graph.size() << std::endl;
		std::cout << "workset size: " << initial.size() << std::endl;

		Galois::for_each<OBIM>(initial.begin(), initial.end(), *this);
	}

	void operator()(GNode& n, Galois::UserContext<GNode>& ctx) const {
		//std::cout << Galois::getActiveThreads() << std::endl;
		SNode& data = graph.getData(n, Galois::NONE);

		unsigned int newDist = data.dist;

		for (Graph::edge_iterator ii = graph.edge_begin(n, Galois::NONE),
				ei = graph.edge_end(n, Galois::NONE); ii != ei; ++ii) {
			GNode dst = graph.getEdgeDst(ii);
			SNode& ddata = graph.getData(dst, Galois::NONE);
			if(ddata.dist > newDist){
				graph.getData(dst, Galois::NONE).dist= newDist;
				ctx.push(dst);
			}
		}
	}
};



void print_componentIds(){
	for (Graph::iterator ii = graph.begin(), ei = graph.end(); ii != ei; ++ii) {
		Graph::GraphNode src = *ii;
		std::cout << src << " " << graph.getData(src, Galois::NONE).dist << std::endl;
	}
}


/*Extremely slow for large graphs*/
void print_edges_in_graph(){
	for (Graph::iterator ii = graph.begin(), ei = graph.end(); ii != ei; ++ii) {
		Graph::GraphNode src = *ii;

		for (Graph::edge_iterator jj = graph.edge_begin(src), ej = graph.edge_end(src); jj != ej; ++jj) {
			Graph::GraphNode dst = graph.getEdgeDst(jj);

			std::cout << "Edge: " << src << " " << dst << std::endl;
		}
	}
}

struct timeval start, end;

int main(int argc, char **argv){


	char *filename;

	if(argc > 2){
		filename  = argv[1];
		number_of_threads = atoi(argv[2]);
	}else{
		std::cout << "You need to give filename and number of threads to run on" << std::endl;
	}

	//graph.structureFromFile("/work/02681/ankitg/basic_programs/Cpp/random4-2e25-sym.gr");
//	graph.structureFromFile("/scratch/01011/xinsui/graphdata/rmat8-2e24-sym.gr");
	//graph.structureFromFile("/work/02681/ankitg/Galois-2.1.8/inputs/structured/torus5.gr");

	graph.structureFromFile(filename);

	std::cout << "in main graph loaded" << std::endl;

	//Initialize the component ids of the nodes with the node number
	for (Graph::iterator ii = graph.begin(), ei = graph.end(); ii != ei; ++ii) {
		Graph::GraphNode src = *ii;
		graph.getData(src, Galois::NONE).dist = src;
	}


	Galois::preAlloc((16 + (graph.size() * sizeof(SNode) * 2) / GaloisRuntime::MM::pageSize)*8);
	Galois::Statistic("MeminfoPre", GaloisRuntime::MM::pageAllocInfo());

	Galois::StatTimer T;
	T.start();
	GNode gn1;
	gettimeofday(&start, NULL); //start time of the actual page rank algorithm

	AsyncAlgo a;
	a(gn1);

	gettimeofday(&end, NULL); //page rank ends here
	T.stop();

	Galois::Statistic("MeminfoPost", GaloisRuntime::MM::pageAllocInfo());

	print_componentIds();

	std::cout << "Time taken by parallel galois chunked fifo queue implementation on " << graph.size() << " nodes is " <<  (((end.tv_sec  - start.tv_sec) * 1000000u +  end.tv_usec - start.tv_usec) / 1.e6) << std::endl;

	return 0;
}

