#pragma once
#include "adjacency_list.h"
#include "cost_list.h"
#include <vector>

class bellman_ford
{
public:
   
   bellman_ford();
   ~bellman_ford();

   bool run(adjacency_list* graph, int start, cost_list& costs);
};

