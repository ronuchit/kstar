#ifndef SEARCH_STATISTICS_H
#define SEARCH_STATISTICS_H

/*
  This class keeps track of search statistics.

  It keeps counters for expanded, generated and evaluated states (and
  some other statistics) and provides uniform output for all search
  methods.
*/

class SearchStatistics {
    // General statistics
    int expanded_states;  // no states for which successors were generated
    int evaluated_states; // no states for which h fn was computed
    int evaluations;      // no of heuristic evaluations performed
    int generated_states; // no states created in total (plus those removed since already in close list)
    int reopened_states;  // no of *closed* states which we reopened
    int dead_end_states;

    int generated_ops;    // no of operators that were returned as applicable

    // Statistics related to f values
    int lastjump_f_value; //f value obtained in the last jump
    int lastjump_expanded_states; // same guy but at point where the last jump in the open list
    int lastjump_reopened_states; // occurred (jump == f-value of the first node in the queue increases)
    int lastjump_evaluated_states;
    int lastjump_generated_states;

	int num_plans_found;	
	int num_opt_plans;
	int num_djkstra_runs;	
	int total_djkstra_node_generations;

    void print_f_line() const;
public:
    SearchStatistics();
    ~SearchStatistics() = default;

    // Methods that update statistics.
    void inc_expanded(int inc = 1) {expanded_states += inc; }
    void inc_evaluated_states(int inc = 1) {evaluated_states += inc; }
    void inc_generated(int inc = 1) {generated_states += inc; }
    void inc_reopened(int inc = 1) {reopened_states += inc; }
    void inc_generated_ops(int inc = 1) {generated_ops += inc; }
    void inc_evaluations(int inc = 1) {evaluations += inc; }
    void inc_dead_ends(int inc = 1) {dead_end_states += inc; }
    void inc_plans_found(int inc = 1){num_plans_found += inc;};
    void inc_opt_plans(int inc = 1){num_opt_plans += inc;};
	
    void reset_plans_found(){num_plans_found = 0;};
    void reset_opt_found(){num_opt_plans = 0;};

    void inc_djkstra_runs(int inc = 1){num_djkstra_runs += inc;};
    void inc_total_djkstra_generations(int inc = 1){total_djkstra_node_generations += inc;};

    // Methods that access statistics.
    int get_expanded() const {return expanded_states; }
    int get_evaluated_states() const {return evaluated_states; }
    int get_evaluations() const {return evaluations; }
    int get_generated() const {return generated_states; }
    int get_num_plans_found() const {return num_plans_found; }
    int get_reopened() const {return reopened_states; }
    int get_generated_ops() const {return generated_ops; }
    
    int get_num_djkstra_runs() const {return num_djkstra_runs; }
    int get_total_djkstra_generations() const {return total_djkstra_node_generations; }
    /*
      Call the following method with the f value of every expanded
      state. It will notice "jumps" (i.e., when the expanded f value
      is the highest f value encountered so far), print some
      statistics on jumps, and keep track of expansions etc. up to the
      last jump.

      Statistics until the final jump are often useful to report in
      A*-style searches because they are not affected by tie-breaking
      as the overall statistics. (With a non-random, admissible and
      consistent heuristic, the number of expanded, evaluated and
      generated states until the final jump is fully determined by the
      state space and heuristic, independently of things like the
      order in which successors are generated or the tie-breaking
      performed by the open list.)
    */
    void report_f_value_progress(int f);

    // output
    void print_basic_statistics() const;
    void print_detailed_statistics() const;
};

#endif
