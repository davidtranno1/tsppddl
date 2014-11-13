#ifndef CUTS_LAZY_CONSTRAINT_H
#define CUTS_LAZY_CONSTRAINT_H

/*************************************************
 INCLUDE THIS OR CPLEX WILL PANIC... DRAMA QUEEN!
*************************************************/
#include <cstring>
/************************************************/

#include <network/graph.h>
#include <parser/program_params.h>
#include <solver/bc/callbacks/callbacks_helper.h>

#include <ilcplex/ilocplex.h>
#include <ilcplex/ilocplexi.h>

#include <utility>

class CutsLazyConstraint : public IloCplex::LazyConstraintCallbackI {
    IloEnv env;
    IloNumVarArray x;
    const Graph& g;
    const Graph& gr;
    double eps;
    
    ch::solution compute_x_values() const;

public:
    CutsLazyConstraint(const IloEnv& env, const IloNumVarArray& x, const Graph& g, const Graph& gr, double eps) : IloCplex::LazyConstraintCallbackI{env}, env{env}, x{x}, g{g}, gr{gr}, eps{eps} {}

    IloCplex::CallbackI* duplicateCallback() const;
    void main();
};

inline IloCplex::Callback CutsLazyConstraintHandle(const IloEnv& env, const IloNumVarArray& x, const Graph& g, const Graph& gr, double eps) {
    return (IloCplex::Callback(new(env) CutsLazyConstraint(env, x, g, gr, eps)));
}

#endif