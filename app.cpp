#include "johnson.h"
#include <iostream>
using namespace std;

int shortest_shortest_path(cost_matrix& costs) {
   auto node_num = costs.get_node_num();
   int shortest = infinity;
   for (int i = 1; i < node_num; i++) {
      for (int j = 1; j < node_num; j++) {
         auto c = costs.get_cost(i, j);
         if (c < shortest) {
            shortest = c;
         }
      }
   }
   return shortest;
}

int main(int argc, char ** argv) {
   if (argc != 2) {
      return 1;
   }
   auto origin_graph = read_graph(argv[1]);
   cost_matrix costs(origin_graph->get_node_num());
   bool res = johnson().run(origin_graph.get(), costs);
   if (res == false) {
      cout << "NULL" << endl;
   }
   else {
      cout << shortest_shortest_path(costs) << endl;
   }

   return 0;
}
