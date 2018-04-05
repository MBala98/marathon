#ifndef STRUCT_LIST
#define STRUCT_LIST
#include "tree.h"

struct list;

typedef struct list* linked_list;

struct list {
	unsigned int rating;
	linked_list next;
};

extern void wrong_input();

extern void clear_list(linked_list l);

// user_0 is being used to free all memory in case malloc fails
extern linked_list declare_list_node(linked_list right, unsigned int x, Tree user_0);

// result info means that we have message OK or ERROR depending on how the process goes 
extern linked_list insert_into_sorted_list_with_result_info(linked_list l, unsigned int x, Tree user_0);

extern linked_list remove_from_list_with_result_info(linked_list l, unsigned int x);

// there are two insert functions because one is used to add or remove movies, when we need to have result
// and the second one is used to create list of ratings for marathon
extern linked_list insert_into_sorted_list_without_result_info(linked_list l, unsigned int x, Tree user_0);

extern int max(int a, int b);

extern linked_list marathon(Tree user, linked_list list_of_ratings, unsigned int current_max, Tree user_0);

// that means that we print only $max_index things from the list, or less if there are <$max_index elements in it
extern void print_list_with_counter(linked_list l, unsigned int i, unsigned int max_index);

// there's need to distinguish that function from "marathon" because we cant pass it recursively to brothers of user
extern linked_list marathon_for_ancestor(Tree user, Tree ancestor);

#endif // STRUCT_LIST 
