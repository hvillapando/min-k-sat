#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VARS 10
#define MAX_CLAUSES 100
#define MAX_K 3

int n_vars = 3;
int n_clauses = 3;
int k = 3;

// 3-SAT formula: (x1 v ~x2 v x3) ^ (~x1 v x2 v ~x3) ^ (x1 v x2 v x3)
int clauses[MAX_CLAUSES][MAX_K] = {
  {1, -2, 3},
  {-1, 2, -3},
  {1, 2, 3}
};

// Check if clause is satisfied with the current assignment
bool is_clause_satisfied(int clause[], bool assignment[], bool assigned[]) {
  for (int i = 0; i < k; ++i) {
    int literal = clause[i];
    int var_index = abs(literal) - 1;
    if (!assigned[var_index]) continue;

    bool value = assignment[var_index];
    if ((literal > 0 && value) || (literal < 0 && !value)) {
      return true;
    }
  }
  return false;
}

// Check if clause becomes unsatisfiable under current partial assignment
bool is_clause_unsatisfiable(int clause[], bool assigned[]) {
  for (int i = 0; i < k; ++i) {
    int var_index = abs(clause[i]) - 1;
    if (!assigned[var_index]) {
      return false; // Still has unassigned variable
    }
  }
  return true;
}

// DPLL recursive solver
bool dpll(bool assignment[], bool assigned[], int var_index) {
  if (var_index == n_vars) {
    // All variables assigned — check if the formula is satisfied
    for (int i = 0; i < n_clauses; ++i) {
      if (!is_clause_satisfied(clauses[i], assignment, assigned)) {
        return false;
      }
    }
    return true;
  }

  for (int value = 0; value <= 1; ++value) {
    assignment[var_index] = value;
    assigned[var_index] = true;

    bool conflict = false;
    for (int i = 0; i < n_clauses; ++i) {
      if (!is_clause_satisfied(clauses[i], assignment, assigned) &&
          is_clause_unsatisfiable(clauses[i], assigned)) {
        conflict = true;
        break;
      }
    }

    if (!conflict && dpll(assignment, assigned, var_index + 1)) {
      return true;
    }

    assigned[var_index] = false; // backtrack
  }

  return false;
}

int main() {
  bool assignment[MAX_VARS] = {false};
  bool assigned[MAX_VARS] = {false};

  if (dpll(assignment, assigned, 0)) {
    printf("Satisfying assignment found using DPLL:\n");
    for (int i = 0; i < n_vars; ++i) {
      printf("x%d = %d\n", i + 1, assignment[i]);
    }
    printf("The formula is satisfiable.\n");
  } else {
    printf("The formula is NOT satisfiable.\n");
  }

  return 0;
}
