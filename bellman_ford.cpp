#include "bellman_ford.h"


bellman_ford::bellman_ford()
{
}


bellman_ford::~bellman_ford()
{
}

void copy(cost_list* prev, cost_list* current) {
   int sz = prev->get_size();
   for (int i = 0; i < sz; i++)
   {
      current->set_cost(i, prev->get_cost(i));
   }
}

bool bellman_ford::run(adjacency_list* graph, int start, cost_list& costs) {
   int node_num = graph->get_node_num();
   cost_list v0(node_num);
   cost_list v1(node_num);
   auto& all_edges = graph->get_edges();
   auto edge_num = all_edges.size();
   // Initialization
   v0.set_cost(start, 0);
   // Iterate N - 1 times
   for (int i = 1; i < node_num; i++)
   {
      cost_list* current = (i % 2 == 1) ? &v1 : &v0;
      cost_list* prev = (current == &v1) ? &v0 : &v1;
      // baseline is the same as last iteration
      copy(prev, current);
      for (decltype(edge_num) j = 0; j < edge_num; j++)
      {
         auto& e = all_edges[j];
         auto ncost = prev->get_cost(e->_tail);
         if (ncost != infinity) {
            ncost += e->_cost;
         }
         if (current->get_cost(e->_head) > ncost) {
            current->set_cost(e->_head, ncost);
         }
      }
   }
   // last iteration to detect negative cycle
   cost_list* current = (node_num % 2 == 1) ? &v1 : &v0;
   cost_list* prev = (current == &v1) ? &v0 : &v1;
   copy(prev, current);
   for (decltype(edge_num) j = 0; j < edge_num; j++)
   {
      auto& e = all_edges[j];
      auto ncost = prev->get_cost(e->_tail);
      if (ncost != infinity) {
         ncost += e->_cost;
      }
      if (current->get_cost(e->_head) > ncost) {
         return false;
      }
   }

   copy(prev, &costs);
   return true;
}

