#include "dijkstra.h"
#include <vector>
#include <memory>

class min_heap
{


   void sift_down(int init) {
      int total = _nodes.size();
      if (init * 2 + 1 >= total) {
         return;
      }

      int lcost = _nodes[init * 2 + 1]._cost;
      int small_child = init * 2 + 1;
      if (init * 2 + 2 < total)
      {
         int rcost = _nodes[init * 2 + 2]._cost;
         if (rcost < lcost)
         {
            small_child = init * 2 + 2;
         }
      }
      swap(init, small_child);
      sift_down(small_child);
   }

   void sift_up(int init) {
      if (init == 0) {
         return;
      }
      int parent = (init - 1) / 2;
      if (_nodes[parent]._cost >= _nodes[init]._cost)
      {
         swap(parent, init);
         sift_up(parent);
      }
   }

   void swap(int loc1, int loc2) {
      heap_node& node1 = _nodes[loc1];
      heap_node& node2 = _nodes[loc2];
      _locations[node1._node] = loc2;
      _locations[node2._node] = loc1;
      std::swap(_nodes[loc1], _nodes[loc2]);
   }

   void pop_back() {
      heap_node& back = _nodes.back();
      _locations[back._node] = -1;
      _nodes.pop_back();
   }

public:

   struct heap_node
   {
      int _cost;
      int _node;
      heap_node(int cost, int node)
         : _cost(cost), _node(node)
      {}
   };

   min_heap(int node_num) : _locations(node_num, -1) {
   }

   void add(int cost, int node) {
      _nodes.push_back(heap_node(cost, node));
      _locations[node] = _nodes.size() - 1;
      sift_up(_nodes.size() - 1);
   }

   heap_node min() {
      if (_nodes.empty())
      {
         throw std::runtime_error("empty heap");
      }
      heap_node small = _nodes[0];
      if (_nodes.size() == 1)
      {
         pop_back();
         return small;
      }
      swap(0, _nodes.size() - 1);
      pop_back();
      sift_down(0);
      return small;
   }

   bool contains(int node) {
      return _locations[node] != -1;
   }

   heap_node remove(int node) {
      int location = _locations[node];
      if (location == -1)
      {
         throw std::runtime_error("heap: node is not in the heap.");
      }
      if (location == 0)
      {
         return min();
      }
      heap_node tnode = _nodes[location];
      if (location == _nodes.size() - 1) {
         pop_back();
         return tnode;
      }
      swap(location, _nodes.size() - 1);
      pop_back();
      int parent_location = (location - 1) / 2;
      if (_nodes[parent_location]._cost >= _nodes[location]._cost) {
         sift_up(location);
      }
      else {
         sift_down(location);
      }
      return tnode;
   }
   
   bool empty() {
      return _nodes.empty();
   }
private:
   std::vector< heap_node > _nodes;
   std::vector< int > _locations;
};

dijkstra::dijkstra(adjacency_list* graph, int initial) : 
   _graph(graph), _initial(initial)
{}


dijkstra::~dijkstra()
{}

void dijkstra::run(cost_list& costs) {
   costs.set_cost(_initial, 0);
   min_heap small_heap(costs.get_size());
   auto& edges = _graph->get_out_edges(_initial);
   for (auto& e : edges) {
      small_heap.add(e->_cost, e->_head);
   }
   while (true)
   {
      if (small_heap.empty()) {
         break;
      }
      auto & smallest = small_heap.min();
      if (smallest._cost == infinity) {
         break;
      }
      costs.set_cost(smallest._node, smallest._cost);
      auto& edges = _graph->get_out_edges(smallest._node);
      for (auto& e : edges)
      {
         if (small_heap.contains(e->_head))
         {
            auto mod = small_heap.remove(e->_head);
            auto new_cost = smallest._cost + e->_cost;
            if (new_cost < mod._cost)
            {
               mod._cost = new_cost;
            }
            small_heap.add(mod._cost, mod._node);
         }
         else if (costs.get_cost(e->_head) == infinity)
         {
            small_heap.add(smallest._cost + e->_cost, e->_head);
         }
      }
   }
}
