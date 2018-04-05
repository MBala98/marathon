#ifndef STRUCT_TREE
#define STRUCT_TREE
#include "linked_list.h"

struct Node;

struct list;

typedef struct Node* Tree;


struct Node {
	Tree sons;
	struct list* movies;
	Tree lsibling, rsibling;
};

extern void clear_tree(Tree t);

extern void del_user(Tree user);

// due comment: implementetion is as following: every user is a part of doubly linked list
// of users with dummies on both ends used to delete and add user in constant time. Every member
// of that list is a son of user, which [that user] has a pointer in "sons" variable to the first dummy of that list.
// Pointer to user_0 is needed in case malloc fails and we need to free all memory before exiting the program
extern Tree create_dummy(Tree next_node, Tree last_node_in_list, Tree user_0); 

extern Tree add_user(Tree parent, Tree user_0);

extern Tree declare_tree_node(Tree user_0);


#endif // STRUCT_TREE 
