#pragma once

#include <vector>
#include "infinity.h"

struct cost_list
{

   std::vector< int > _costs;

public:

   cost_list(int node_num)
      : _costs(node_num, infinity)
   {}
   int get_cost(int nodeid)
   {
      return _costs[nodeid];
   }
   void set_cost(int nodeid, int cost)
   {
      _costs[nodeid] = cost;
   }
   int get_size()
   {
      return _costs.size();
   }
};

