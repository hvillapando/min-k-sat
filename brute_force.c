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

bool evaluate_literal(int literal, bool assignment[]) {
  int var_index = abs(literal) - 1;
  bool value = assignment[var_index];
  return (literal > 0) ? value : !value;
}

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

int count_true_vars(bool assignment[]) {
  int count = 0;
  for (int i = 0; i < n_vars; ++i) {
    if (assignment[i]) count++;
  }
  return count;
}

bool solve_min_k_sat() {
  int total_assignments = 1 << n_vars;
  bool assignment[MAX_VARS];
  bool best_assignment[MAX_VARS];
  int min_true_vars = n_vars + 1;
  bool found_solution = false;

  printf("Truth Table:\n");
  for (int i = 0; i < n_vars; ++i) {
    printf("x%d ", i + 1);
  }
  printf("| Satisfies?\n");
  for (int i = 0; i < n_vars * 3 + 12; ++i) printf("-"); // divider
  printf("\n");

  for (int i = 0; i < total_assignments; ++i) {
    for (int j = 0; j < n_vars; ++j) {
      assignment[j] = (i & (1 << (n_vars - j - 1))) != 0;
    }

    bool satisfies = is_satisfying_assignment(assignment);

    // Print row
    for (int j = 0; j < n_vars; ++j) {
      printf("%2d ", assignment[j]);
    }
    printf("|     %s\n", satisfies ? "YES" : "NO");

    // Track min-k-SAT
    if (satisfies) {
      int true_count = count_true_vars(assignment);
      if (true_count < min_true_vars) {
        min_true_vars = true_count;
        for (int j = 0; j < n_vars; ++j) {
          best_assignment[j] = assignment[j];
        }
        found_solution = true;
      }
    }
  }

  printf("\n");

  if (found_solution) {
    printf("Minimum-k-SAT satisfying assignment (with %d true variables): ", min_true_vars);
    for (int j = 0; j < n_vars; ++j) {
      printf("x%d=%d ", j + 1, best_assignment[j]);
    }
    printf("\n");
    return true;
  } else {
    return false;
  }
}

int main() {
  if (solve_min_k_sat()) {
    printf("The formula is satisfiable.\n");
  } else {
    printf("The formula is NOT satisfiable.\n");
  }
  return 0;
}
