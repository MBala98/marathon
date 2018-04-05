#include "linked_list.h"
#include "tree.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COMMENT 35
#define NEW_LINE 10
#define SPACE 32
#define LONGEST_COMMAND 10 // the length of the longest command +2 cause space needed for recognizing potential mistakes and for '\0'
#define LONGEST_NUMBER 11 // the length of the longest possible number +1 cause space needed for recognizing potential mistakes
#define MAX_USER_ID 65535
#define MAX_PARAMETER 2147483647
#define MINUS -3

enum commands {ADD_USER, DEL_USER, ADD_MOVIE, DEL_MOVIE, MARATHON, ERROR_WITHOUT_CLEARING_THE_LINE, ERROR = -2, DO_NOTHING}; 
// -2 cause it needs to be negative in order to work properly in function correct_scope_of_user_id(we want it to be false)

void execute_marathon(Tree user, unsigned int k, Tree user_0) {
	if (user != NULL) {
        linked_list list_of_movies = user->movies;
		unsigned int max_value;
		if (list_of_movies != NULL) max_value = list_of_movies->rating;
		else max_value = 0;
		linked_list list_of_ratings = marathon_for_ancestor(user, user_0);
        list_of_ratings = marathon(user->sons, list_of_ratings, max_value, user_0);
		print_list_with_counter(list_of_ratings, 0, k);
        printf("\n");
		clear_list(list_of_ratings);
	}
}

void add_movie(Tree user, unsigned int movie_rating, Tree user_0) {
	if (user != NULL) user->movies = insert_into_sorted_list_with_result_info(user->movies, movie_rating, user_0);
}

void del_movie(Tree user, unsigned int movie_rating) {
	if (user != NULL) user->movies = remove_from_list_with_result_info(user->movies, movie_rating);
}

bool ignore(int mark) {
	return (mark == COMMENT || mark == NEW_LINE || mark == SPACE || mark == EOF);
}

void delete_the_line() {
    char k = getchar();
       while (k != '\n' && !feof(stdin)) k = getchar();
}

bool white_sign(char k) {
    return (k == SPACE || k == NEW_LINE);
}

int compare_commands(char *word) {
    if (strcmp(word, "delUser") == 0) return DEL_USER;
    else if (strcmp(word, "addUser") == 0) return ADD_USER;
    else if (strcmp(word, "addMovie") == 0) return ADD_MOVIE;
    else if (strcmp(word, "delMovie") == 0) return DEL_MOVIE;
    else if (strcmp(word, "marathon") == 0) return MARATHON;
    else return ERROR;
}

int recognize_command() {
	int i = 0;
	char word[LONGEST_COMMAND];
	char mark = getchar();
	if (!ignore(mark)) {
		while (!white_sign(mark) && !feof(stdin) && i < LONGEST_COMMAND) {
			word[i] = mark;
        	mark = getchar();
            i++;
        }
        if(mark == NEW_LINE) return ERROR_WITHOUT_CLEARING_THE_LINE;
        word[i] = '\0';
		return compare_commands(word);
    }
    else {
        if(mark == COMMENT) return COMMENT;
        else if (mark == SPACE) return ERROR;
        else return DO_NOTHING;
    }
}

void adapt_to_int(int number[], int n) {
	for(int i = 0; i < n; i++) number[i] = number[i] - 48;
}

int return_int_from_string_of_ints(int number[], int n) {
    int result = 0;
	int multiplier = 1;
    if (number[0] == MINUS) {
        for(int i = n - 1; i > 0; i--) {
            result = result + number[i] * multiplier;
            multiplier *= 10;
        }
    return -result;
    }
    else {
        for(int i = n - 1; i >= 0; i--) {
            result = result + number[i] * multiplier;
            multiplier *= 10;
        }
    }
    return result;
}

int recognize_parameter(bool *is_there_new_line_after_parameter) {
	int number[LONGEST_NUMBER];
	int i = 0;
	int sign = getchar();
	while (!white_sign(sign) && !feof(stdin) && i < LONGEST_NUMBER) {
		number[i] = sign;
		sign = getchar();
		i++;
	}
	if (sign == NEW_LINE) *is_there_new_line_after_parameter = true;
    if (i == LONGEST_NUMBER || i == 0) return ERROR; // first case: parameter larger than 10 ditigs, hence too large. Second case: no parameter at all, or too many spaces.
	adapt_to_int(number, i);
    return return_int_from_string_of_ints(number, i);
}

void handle_error() {
    wrong_input();
    delete_the_line();
}

bool correct_scope_of_user_id(int userID) {
    return (userID >= 0 && userID <= MAX_USER_ID);
}

bool correct_scope_of_movie_rating_and_k_parameter(int parameter) {
    return (parameter >= 0 && parameter <= MAX_PARAMETER);
}

void handle_del_user(Tree array_of_users[]){
    bool is_there_new_line_after_parameter = false;
    int userID = recognize_parameter(&is_there_new_line_after_parameter);
    if(!is_there_new_line_after_parameter) handle_error();
    else if (array_of_users[userID] == NULL || !correct_scope_of_user_id(userID) || userID == 0) wrong_input();
    else {
        del_user(array_of_users[userID]);
        array_of_users[userID] = NULL;
        printf("OK\n");
    }
}

void handle_add_user(Tree array_of_users[]){
    bool is_there_new_line_after_parameter = false;
    int parentUserID = recognize_parameter(&is_there_new_line_after_parameter);
    if (is_there_new_line_after_parameter) wrong_input();
    else {
        int userID = recognize_parameter(&is_there_new_line_after_parameter);
        if(!is_there_new_line_after_parameter) handle_error();
        else if (array_of_users[parentUserID] == NULL || array_of_users[userID] != NULL || !correct_scope_of_user_id(parentUserID) || !correct_scope_of_user_id(userID)) wrong_input();
        else {
            array_of_users[userID] = add_user(array_of_users[parentUserID], array_of_users[0]);
            printf("OK\n");
        }
    }
}

void handle_add_movie(Tree array_of_users[]) {
    bool is_there_new_line_after_parameter = false;
    int userID = recognize_parameter(&is_there_new_line_after_parameter);
    if (is_there_new_line_after_parameter) wrong_input();
    else {
        int movieRating = recognize_parameter(&is_there_new_line_after_parameter);
        if (!is_there_new_line_after_parameter) handle_error();
        if (array_of_users[userID] == NULL || !correct_scope_of_user_id(userID) || !correct_scope_of_movie_rating_and_k_parameter(movieRating)) wrong_input();
        else add_movie(array_of_users[userID], movieRating, array_of_users[0]);
    }
}

void handle_del_movie(Tree array_of_users[]) {
    bool is_there_new_line_after_parameter = false;
    int userID = recognize_parameter(&is_there_new_line_after_parameter);
    if (is_there_new_line_after_parameter) wrong_input();
    else {
        int movieRating = recognize_parameter(&is_there_new_line_after_parameter);
        if(!is_there_new_line_after_parameter) handle_error();
        else if (array_of_users[userID] == NULL || !correct_scope_of_user_id(userID) || !correct_scope_of_movie_rating_and_k_parameter(movieRating)) wrong_input();
        else del_movie(array_of_users[userID], movieRating);
    }
}

void handle_marathon(Tree array_of_users[]) {
    bool is_there_new_line_after_parameter = false;
    int userID = recognize_parameter(&is_there_new_line_after_parameter);
    if (is_there_new_line_after_parameter) wrong_input();
    else {
        int k = recognize_parameter(&is_there_new_line_after_parameter);
        if(!is_there_new_line_after_parameter) handle_error();
        if(array_of_users[userID] == NULL || !correct_scope_of_user_id(userID) || !correct_scope_of_movie_rating_and_k_parameter(k)) wrong_input();
        else execute_marathon(array_of_users[userID], k, array_of_users[0]);
    }
}

void handle_commands(Tree array_of_users[]){
   int command = recognize_command();
   switch(command) {

        case DEL_USER:
            handle_del_user(array_of_users);
        break;

        case ADD_USER:
            handle_add_user(array_of_users);
        break;

        case ADD_MOVIE:
          handle_add_movie(array_of_users);
        break;

        case DEL_MOVIE:
          handle_del_movie(array_of_users);
        break;

        case MARATHON:
            handle_marathon(array_of_users);
        break;

        case ERROR:
            handle_error();
        break;

        case ERROR_WITHOUT_CLEARING_THE_LINE:
            wrong_input();
        break;

        case COMMENT:
            delete_the_line();
        break;
    }
}

void initialize_array_of_users(Tree array_of_users[], int n) {
    for(int i = 0; i < n; i++) array_of_users[i] = NULL;
}

int main() {
	Tree test[MAX_USER_ID + 1] = {NULL};
	test[0] = declare_tree_node(NULL);
	while(!feof(stdin)) handle_commands(test);
    clear_tree(test[0]);
	return 0; 
}
