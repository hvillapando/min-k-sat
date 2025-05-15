#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VARS 10
#define MAX_CLAUSES 100
#define MAX_K 3

int n_vars = 3;    // Number of variables
int n_clauses = 3; // Number of clauses
int k = 3;         // Number of literals per clause (k-SAT)

// 3-SAT formula: (x1 v ~x2 v x3) ^ (~x1 v x2 v ~x3) ^ (x1 v x2 v x3)
int clauses[MAX_CLAUSES][MAX_K] = {
  {1, -2, 3},
  {-1, 2, -3},
  {1, 2, 3}
};

// Evaluate the truth value of a literal given an assignment
bool evaluate_literal(int literal, bool assignment[]) {
  int var_index = abs(literal) - 1;
  bool value = assignment[var_index];
  bool result;

  if (literal > 0) {
    result = value;
  } else {
    result = !value;
  }

  return result;
}

// Check if a full assignment satisfies all clauses
bool is_satisfying_assignment(bool assignment[]) {
  for (int i = 0; i < n_clauses; ++i) {
    bool clause_satisfied = false;
    for (int j = 0; j < k; ++j) {
      if (evaluate_literal(clauses[i][j], assignment)) {
        clause_satisfied = true;
        break;
      }
    }
    if (!clause_satisfied) {
      return false;
    }
  }
  return true; 
}

// Brute force
bool solve_k_sat() {
  int total_assignments = 1 << n_vars; // 2^n_vars combinations
  bool assignment[MAX_VARS];

  for (int i = 0; i < total_assignments; ++i) {
    printf("\nIteration %i\n", i+1);
    // Create the truth table from i
    for (int j = 0; j < n_vars; ++j) {
      printf("Variable %i - ", j+1);
      if ((i & (1 << j)) != 0) {
        assignment[j] = true;
      } else {
        assignment[j] = false;
      }
      printf("%i\n", assignment[j]);
    }

    // Check if the recent truth values satisfy the clause, early return if satisfied
    if (is_satisfying_assignment(assignment)) {
      printf("\nSatisfying assignment found: ");
      for (int j = 0; j < n_vars; ++j) {
        printf("x%d=%d ", j + 1, assignment[j]);
      }
      printf("\n\n");
      return true;
    }
  }

  return false;
}

int main() {
  if (solve_k_sat()) {
    printf("The formula is satisfiable.\n");
  } else {
    printf("The formula is NOT satisfiable.\n");
  }
  return 0;
}
