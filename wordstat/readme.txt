My wordstat program primarily used a simple hash
table that hashes according to the first letter
of the word, and a basic linked list to deal with
collisions and to store the variations of each
word.

RUN TIME ANALYSIS

processStr()
	This function just calls insert and thus runs
	in insert's time.
printResult()
	This function prints out every node in order.
	Thus, it runs in O(n) where n is the number
	of nodes.
search()
	This function takes in a string and it's
	hashfunction value and returns null if the
	string is not in the hashtable, or it's node
	if it is. In the worst case, where every word
	hashes to the same location, this runs in
	linear time, but generally is closer to O(1).
newStat()
	This function creates a new stat node and
	sets its counters to one and nexts to null.
	Runs in constant time.
hashFunc()
	This function checks the first letter of
	the word and returns a number based on it.
	Runs in constant time.
insert()
	This function calls hashFunc and search, and
	if null is returned, it creates a new node,
	goes to the correct hash row and inserts the
	new node in the correct spot. Otherwise, if a
	node is returned from search, the node's
	information is updated, which includes a
	linear search through the node's variation
	linked list to see if the string passed
	in is a new variation. This function runs
	in about the same time as search.
lowerCase()
	This function takes in a string and converts
	every character to lowercase. Thus, this
	function runs in O(n), where n is the number
	of characters in the word.
