#include "linked_list.h"
#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

static void memory_fail(Tree user_0) {
    clear_tree(user_0);
    exit(1);
}

void wrong_input() {
	fprintf(stderr, "ERROR\n");
}

void clear_list(linked_list l) {
	if (l != NULL) {
		clear_list(l->next);
		free(l);
	}
}

linked_list declare_list_node(linked_list right, unsigned int x, Tree user_0) {
	linked_list l = malloc(sizeof*l);
	if (l == NULL) memory_fail(user_0);
	l->rating = x;
	l->next = right;
	return l;
}

linked_list insert_into_sorted_list_with_result_info(linked_list l, unsigned int x, Tree user_0) {
	if (l == NULL) {
        printf("OK\n");
        return declare_list_node(NULL, x, user_0);
    }
	else {
		if (x < l->rating) {
			l->next = insert_into_sorted_list_with_result_info(l->next, x, user_0);
			return l;
		}
		else if (x == l->rating) {
			wrong_input();
			return l;
		}
		else {
            printf("OK\n");
            return declare_list_node(l, x, user_0);
        }
	}
}

linked_list remove_from_list_with_result_info(linked_list l, unsigned int x) {
	if (l == NULL) {
		wrong_input();
		return NULL;
	}
	else if (l->rating == x) {
		linked_list tmp = l->next;
		free(l);
		printf("OK\n");
		return tmp;
	}
	else {
		l->next = remove_from_list_with_result_info(l->next, x);
		return l;
	}
}

linked_list insert_into_sorted_list_without_result_info(linked_list l, unsigned int x, Tree user_0) {
	if (l == NULL) return declare_list_node(NULL, x, user_0);
    else {
        if (x < l->rating) {
            l->next = insert_into_sorted_list_without_result_info(l->next, x, user_0);
            return l;
        }
        else if (x > l->rating) return declare_list_node(l, x, user_0);
        else return l;
    }

}

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

linked_list marathon(Tree user, linked_list list_of_ratings, unsigned int current_max, Tree user_0) {
	if (user != NULL) {
		linked_list list_of_movies = user->movies;
		unsigned int new_max;
		if (list_of_movies != NULL) new_max = list_of_movies->rating;
		else new_max = 0;
        new_max = max(current_max, new_max);
		while (list_of_movies != NULL && list_of_movies->rating >= current_max) {
			list_of_ratings = insert_into_sorted_list_without_result_info(list_of_ratings, list_of_movies->rating, user_0);
			list_of_movies = list_of_movies->next;
		}
        list_of_ratings = marathon(user->rsibling, list_of_ratings, current_max, user_0);
		list_of_ratings = marathon(user->sons, list_of_ratings, new_max, user_0);
		return list_of_ratings;
	}
	else return list_of_ratings;
}

void print_list_with_counter(linked_list l, unsigned int i, unsigned int max_index) {
	if (l != NULL && i < max_index) {
        if (i == 0) {
            printf("%d", l->rating);
            print_list_with_counter(l->next, i+1, max_index);
        }
        else {
            printf(" %d", l->rating);
            print_list_with_counter(l->next, i+1, max_index);
        }
	}
	else if (i == 0) printf("NONE");
}

linked_list marathon_for_ancestor(Tree user, Tree user_0) {
    if (user != NULL) {
        linked_list list_of_ratings = NULL;
        linked_list list_of_movies = user->movies;
        while (list_of_movies != NULL) {
            list_of_ratings = insert_into_sorted_list_without_result_info(list_of_ratings, list_of_movies->rating, user_0);
            list_of_movies = list_of_movies->next;
        }
        return list_of_ratings;
    }
    else return NULL;
}




















