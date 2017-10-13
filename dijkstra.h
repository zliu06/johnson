#pragma once

#include "adjacency_list.h"
#include "cost_list.h"

class dijkstra
{
public:
   dijkstra(adjacency_list* graph, int initial);
   void run(cost_list& costs);
   ~dijkstra();
private:
   adjacency_list* _graph;
   int _initial;
};

