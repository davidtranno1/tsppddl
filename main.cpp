#include <cli/program.h>

#include <iostream>

long g_node_number {0};
double g_total_time_spent_by_heuristics {0};
double g_total_time_spent_separating_cuts {0};
long g_total_bb_nodes_explored {0};
long g_total_number_of_cuts_added {0};
long g_number_of_cuts_added_at_root {0};
double g_time_spent_at_root {0};
double g_ub_at_root {0};
double g_lb_at_root {0};
double g_ub {0};
double g_lb {0};
double g_total_cplex_time {0};
long g_search_for_cuts_every_n_nodes {100};

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Not enough parameters!" << std::endl;
        return -1;
    }
    
    std::vector<std::string> args(argv + 1, argv + argc);
    
    Program p;
    
    // p.prompt();
    
    p.autorun(args);
    
    return 0;
}