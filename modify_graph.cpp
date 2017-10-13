#include "modify_graph.h"


modify_graph::modify_graph()
{
}


modify_graph::~modify_graph()
{
}

void modify_graph::fill_node_zero(adjacency_list* graph)
{
   int node_num = graph->get_node_num();
   for (int i = 1; i < node_num; i++) {
      edge * e = new edge();
      e->_tail = 0;
      e->_head = i;
      e->_cost = 0;
      graph->add_edge(e);
   }
}
