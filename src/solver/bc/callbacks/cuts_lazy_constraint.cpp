#include <solver/bc/callbacks/cuts_lazy_constraint.h>
#include <solver/bc/callbacks/feasibility_cuts_separator.h>

#include <chrono>
#include <ctime>
#include <ratio>

IloCplex::CallbackI* cuts_lazy_constraint::duplicateCallback() const {
    return (new(getEnv()) cuts_lazy_constraint(*this));
}

void cuts_lazy_constraint::main() {
    using namespace std::chrono;
    
    auto sol = compute_x_values();
    auto start_time = high_resolution_clock::now();    
    auto feas_cuts = feasibility_cuts_separator::separate_feasibility_cuts(g, gr, sol, x);
    auto end_time = high_resolution_clock::now();
    auto time_span = duration_cast<duration<double>>(end_time - start_time);
    data.time_spent_separating_feasibility_cuts += time_span.count();
        
    for(IloRange cut : feas_cuts) {
        add(cut, IloCplex::UseCutForce).end();
        data.total_number_of_feasibility_cuts_added++;
    }
}

ch::solution cuts_lazy_constraint::compute_x_values() const {
    auto n = g.g[graph_bundle].n;
    auto xvals = std::vector<std::vector<double>>(2*n+2, std::vector<double>(2*n+2, 0));
    auto is_integer = true;

    auto col_index = 0;
    for(auto i = 0; i <= 2 * n + 1; i++) {
        for(auto j = 0; j <= 2 * n + 1; j++) {
            if(g.cost[i][j] >= 0) {
                auto n = getValue(x[col_index++]);
                if(n > 0 + ch::eps(1)) {
                    if(n < 1 - ch::eps(1)) {
                        is_integer = false;
                    }
                    xvals[i][j] = n;
                } else {
                    xvals[i][j] = 0;
                }
            }
         }
    }
    
    return ch::solution(is_integer, xvals);
}