# The implementation of the tree is supposed to add and delete users in constant time. To achieve that, two dummies for each list of sons are used, on both ends of that list. These dummies have pointers to beginning and end of the list.
Commands:
addUser <ParentUserID> <UserID> adds user with <UserID> ID as a son of user with <ParentUserID>
  delUser <UserID> deletes a user with <UserID>
  addMovie <UserID> <MovieRating>  adds movie with <MovieRating> to user with <UserID>
  delMovie <UserID> <MovieRating> deletes a movie with <MovieRating> to user with <UserID>
  marathon <UserID> <k> creates a list with maximum <k> movie ratings, according to following rules:
        take <k> or less movie ratings with highest values from user with <UserID> preferences, or less if there are less than <k> preferences
        If any of the sons of user with <UserID> has higher rated film than the highest movie rating of <UserID> then add that to the list
        Repeat it revursively for every son of user with <UserID>
UserID parameter can be any vaule between 0 and 65535
MovieRating and k parameter can be any value between 0 and 2147483647
Output:
  For every correct command other than marathon program returns "OK"
  For every wrong command, including trying to add already existing user, trying to delete non-existing user etc, program returns "ERROR"
  For marathon command program returns list of movie ratings created in that command
  
