#pragma once

#include "adjacency_list.h"
#include "bellman_ford.h"
#include "cost_matrix.h"
#include <memory>

class johnson
{
public:
   johnson();
   ~johnson();

   std::unique_ptr<adjacency_list> adjust_cost(adjacency_list* graph, cost_list* costs);

   bool run(adjacency_list* graph, cost_matrix& costs);
};

