#include "johnson.h"
#include "modify_graph.h"
#include "dijkstra.h"

johnson::johnson()
{}


johnson::~johnson()
{}

std::unique_ptr<adjacency_list> 
johnson::adjust_cost(adjacency_list* graph, cost_list* costs) {
   std::unique_ptr<adjacency_list> ngraph(new adjacency_list(graph->get_node_num()));
   auto& all_edges = graph->get_edges();
   for (auto & e : all_edges)
   {
      if (e->_tail == 0) {
         continue;
      }
      auto tcost = costs->get_cost(e->_tail);
      auto hcost = costs->get_cost(e->_head);
      edge * ee = new edge();
      ee->_tail = e->_tail;
      ee->_head = e->_head;
      ee->_cost = e->_cost + tcost - hcost;
      ngraph->add_edge(ee);
   }
   return ngraph;
}

bool johnson::run(adjacency_list * graph, cost_matrix & costs)
{
   int node_num = graph->get_node_num();
   modify_graph().fill_node_zero(graph);
   cost_list bellman_ford_costs(node_num);
   bool res = bellman_ford().run(graph, 0, bellman_ford_costs);
   if (!res) {
      return false;
   }
   auto adjusted_graph = adjust_cost(graph, &bellman_ford_costs);
   for (int i = 1; i < node_num; i++) {
      dijkstra di(adjusted_graph.get(), i);
      cost_list ci(node_num);
      di.run(ci);
      for (int j = 1; j < node_num; j++) {
         auto cost = ci.get_cost(j);
         if (cost != infinity) {
            cost = cost - bellman_ford_costs.get_cost(i) + bellman_ford_costs.get_cost(j);
            costs.set_cost(i, j, cost);
         }
      }
   }
   return true;
}
