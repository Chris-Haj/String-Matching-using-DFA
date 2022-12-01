207824772
Christopher Haj 207824772
String Pattern Matching Algorithm
dbllist.c - Contains basic functions for instantiating, destroying and creating new nodes to doubly linked lists.
pattern_matching.c - Contains the functions for instantiating a DSA structure, creating and finding states in the DSA and basic functions.

void destroyer(...):
 This function was used to help delete the data structure in a recursive way...
 In the same way, a queue was used to go through the tree, layer by layer (BFS Algorithm)
 DFS Algorithm was used to go through the DFA in a recursive way and destroy all its data

Extra Notes:
  1) main.c has to allocate memory for pm_t* before calling any functions.
  2) Any data created by main, has to be freed in main!
  3) If pm_fsm_search(...) function is called in main,
   the returned result must be freed using the dbllist_destroy(result, dbllist_destroy_t des = DBLLIST_FREE_DATA) function.