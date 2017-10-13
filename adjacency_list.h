#pragma once
#pragma once

#include <vector>
#include <memory>
#include <limits>
#include "edge.h"
class edge;

class adjacency_list
{

   std::vector< std::vector<edge*> > _nodes;
   std::vector< edge* > _edges;
public:
   static int infinity;
   adjacency_list(int node_num);
   ~adjacency_list();
   std::vector< edge* >& get_out_edges(int node_id);
   void add_edge(edge* e);
   int get_node_num() {
      return _nodes.size();
   }
   std::vector< edge* >& get_edges() {
      return _edges;
   }
   int edge_cost(int tail, int head) {
      auto& edges = _nodes[tail];
      for (auto& e : edges) {
         if (e->_head == head) {
            return e->_cost;
         }
      }
      return infinity;
   }
};


std::unique_ptr<adjacency_list> read_graph(char* filename);