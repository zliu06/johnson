#include "adjacency_list.h"
#include "edge.h"
#include <fstream>
#include <sstream>
#include <string>

adjacency_list::adjacency_list(int node_num)
   : _nodes(node_num, std::vector<edge*>())
{
}


adjacency_list::~adjacency_list()
{
   for (auto& e : _edges)
   {
      delete (e);
   }
}

std::vector< edge* >& adjacency_list::get_out_edges(int node_id)
{
   return _nodes[node_id];
}

void adjacency_list::add_edge(edge* e)
{
   _edges.push_back(e);
   _nodes[e->_tail].push_back(e);
}

std::unique_ptr<adjacency_list> read_graph(char* filename)
{
   std::ifstream fin(filename);
   std::string line;
   std::getline(fin, line);
   std::istringstream iss(line);
   int node_num;
   int edge_num;
   iss >> node_num;
   iss >> edge_num;
   std::unique_ptr<adjacency_list> graph(new adjacency_list(node_num + 1));
   for (int i = 0; i < edge_num; i++)
   {
      std::getline(fin, line);
      int tail;
      int head;
      int cost;
      std::istringstream iss(line);
      iss >> tail;
      iss >> head;
      iss >> cost;
      edge* e = new edge();
      e->_tail = tail;
      e->_head = head;
      e->_cost = cost;
      graph->add_edge(e);
   }
   return graph;
}

