#include "mygraph.h"

void dfs(Graph * graph, int v) {
	graph->setMark(v, GRAPH_VISITED);
	for (int v2 = graph->getFirst(v);
		v2 < graph->getN();
		v2 = graph->getNext(v, v2))
		if (graph->getMark(v2) == GRAPH_UNVISITED)
			dfs(graph, v2);
	
}
