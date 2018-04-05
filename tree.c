#include "linked_list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void clear_tree(Tree t) {
	if (t != NULL) {
		clear_tree(t->sons);
		clear_tree(t->rsibling);
		clear_list(t->movies);
		free(t);
	}
}

static void memory_fail(Tree user_0) {
        clear_tree(user_0);
        exit(1);
}

Tree declare_tree_node(Tree user_0) {
	Tree user = malloc(sizeof*user);
	if (user == NULL) memory_fail(user_0);
	else user->lsibling = user->rsibling = user->sons = NULL;
	user->movies = NULL;
	return user;
}

void del_user(Tree user) {
	if (user != NULL) {
        bool only_user = (user->lsibling->lsibling == user);
        bool last_user = (user->rsibling->rsibling == NULL);
        Tree next_node = user->rsibling;
        Tree previous_node = user->lsibling;
        Tree son = user->sons;
        clear_list(user->movies);
        if (son == NULL) {
            if (last_user && only_user) {
                Tree first_dummy = previous_node;
                first_dummy->lsibling = next_node; // which equals to last_dummy
                first_dummy->rsibling = next_node;
                free(user);
            }
            else if (last_user) {
                Tree first_dummy =next_node->lsibling;
                first_dummy->lsibling = previous_node;
                previous_node->rsibling = next_node;
                free(user);
            }
            else {
                previous_node->rsibling = next_node;
                next_node->lsibling = previous_node;
                free(user);
            }
        }
        else {
            bool no_real_sons = (son->rsibling->rsibling == NULL); // that means that there are only two dummies as sons
            if (last_user && no_real_sons && only_user) {
                Tree first_dummy = previous_node;
                first_dummy->lsibling = first_dummy->rsibling = next_node;
                free(son->rsibling);
                free(son);
                free(user);
            }
            else if (last_user && no_real_sons) {
                Tree first_dummy = next_node->lsibling;
                first_dummy->lsibling = previous_node;
                previous_node->rsibling = next_node;
                free(son->rsibling);
                free(son);
                free(user);
            }
            else if (last_user) {
                Tree first_dummy = next_node->lsibling;
                Tree last_node = son->lsibling;
                Tree first_node = son->rsibling;
                Tree last_dummy = last_node->rsibling;
                previous_node->rsibling = first_node;
                first_node->lsibling = previous_node;
                last_node->rsibling = next_node;
                first_dummy->lsibling = last_node;
                free(last_dummy);
                free(son);
                free(user);
            }
            else if (no_real_sons) {
                previous_node->rsibling = next_node;
                next_node->lsibling = previous_node;
                free(son->rsibling);
                free(son);
                free(user);
            }
            else {
                Tree first_node = son->rsibling;
                Tree last_node = son->lsibling;
                Tree last_dummy = last_node->rsibling;
                previous_node->rsibling = first_node;
                first_node->lsibling = previous_node;
                last_node->rsibling = next_node;
                next_node->lsibling = last_node;
                free(last_dummy);
                free(son);
                free(user);
            }
        }

	}
}

// rsibling is a first node in the list, lsibling is dummy on the opposite end
Tree create_dummy(Tree next_node, Tree last_node_in_list, Tree user_0) {
	Tree dummy = declare_tree_node(user_0);
	dummy->rsibling = next_node;
	dummy->lsibling = last_node_in_list;
	return dummy;
}

Tree add_user(Tree parent, Tree user_0) {
	if (parent != NULL) {
		Tree new_node = declare_tree_node(user_0);
		Tree son_dummy = parent->sons;
		if (son_dummy != NULL) {
			Tree right_sibling = son_dummy->rsibling;
			new_node->rsibling = right_sibling;
			new_node->lsibling = son_dummy;
			right_sibling->lsibling = son_dummy->rsibling = new_node;
            if (right_sibling->rsibling == NULL) {  // a case when we add a user to existing 2 dummies without users
                son_dummy->lsibling = new_node; 
                right_sibling->lsibling = son_dummy;
            }
			return new_node;
		}
        else {
            new_node->lsibling = parent->sons = create_dummy(new_node, new_node, user_0);
            new_node->rsibling = create_dummy(NULL, new_node->lsibling, user_0);
            return new_node;
        }
	}
	else {
		return NULL;
	}
}





