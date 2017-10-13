#pragma once

#include <vector>
#include "infinity.h"

struct cost_matrix
{
private:
   std::vector< std::vector< int > > _costs;
public:
   int get_node_num()
   {
      return _costs.size();
   }
   cost_matrix(int node_num)
      : _costs(node_num, std::vector< int >())
   {
      for (int i = 0; i < node_num; i++)
      {
         _costs[i] = std::vector<int>(node_num, infinity);
      }
   }
   void set_cost(int s, int t, int cost)
   {
      _costs[s][t] = cost;
   }
   int get_cost(int s, int t)
   {
      return _costs[s][t];
   }
};
