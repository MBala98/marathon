# The implementation of the tree is supposed to add and delete users in constant time. To achieve that, two dummies for each list of sons are used, on both ends of that list. These dummies have pointers to beginning and end of the list.
Commands:
addUser <ParentUserID> <UserID> adds user with <UserID> ID as a son of user with <ParentUserID>
delUser <UserID> deletes a user with <UserID>
addMovie <UserID> <MovieRating> 
