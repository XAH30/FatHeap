# Fat heap as a data structure
Merged priority heaps are data structures, used to store items with priorities. They are binary trees, where each node contains items and its priority. The priorities determine the order in which items will be are retrieved from the heap.
However, in some cases, it may be necessary to combine several priority heaps into one large heap. For this purpose a data structure called a fat heap is used.
Fat heap ("Fat heap", "Thick heap") is one of the extensions of the of the idea of mergeable priority heaps and a modification of the binomial heap, in which each node determines the number of descendants of that node.
Thus, a thick heap allows to have more than two descendants at of each node.
Thick trees of rank Fk of rank k (k=0,1,2,...)(k=0,1,2,...) are represented as follows:
![image](https://github.com/XAH30/FatHeap/assets/73390555/d022c8c7-49b4-4c21-aabc-f9d4daaccd6a)
- A fat tree F0 0 of rank zero consists of a single node.
- Each thick tree consists of three thick trees of rank k-1, and the roots of two of them are left descendants of the third.
# Properties of thick trees
1.	A thick tree of rank k has exactly 3k nodes. The rank of a node of a thick tree is the rank of the thick subtree of which this node is the root.
2.	For any natural number n, there exists a forest of thick trees with exactly n nodes. Such a forest can be constructed by including in it as many trees of rank i as the value of the i-th digit of the ternary representation of the number n.
3. A thick forest of n n nodes contains O(log n) trees.
A forest of several thick trees whose ranks are not necessarily pairwise different and whose nodes are mutually unambiguously matched by elements of a weighted set (nodes are weighted) will be called a loaded forest. A loaded forest will be called a heap forest if its nodes satisfy the heap property: the value of the child node is greater than the value of the parent node
Thick heap -- a heap-loaded thick forest containing at most three thick trees of each rank.
Each node in the thick heap contains information about: the element key assigned to the tree node; a pointer to the parent; pointers to the nearest left and right sibling; a pointer to the leftmost sibling; and the rank of the node. "Brothers" (the root tree nodes as well as the sons of each node) will later be merged into a doubly-linked list using the left and right pointers.
# Thick heap forest according to the parameters selected for the node.
![image](https://github.com/XAH30/FatHeap/assets/73390555/8e84ee07-de13-4db5-8b4b-ffac9fe29b4c)
Inside the nodes, their ranks are indicated. A rank is an integer value that reflects the height of the tree in the heap. The use of ranks in thick heaps allows to achieve efficiency of merge and minimum element removal operations, which is an important aspect of working with this data structure. The higher the number of ranks, the higher the priority of the key stored in that node.
# The heap structure itself can be represented as follows:
FatHeap = (RootCount, CountViolation, MinPointer, MaxRank), where RootCount is the array corresponding to the root count; CountViolation is the array corresponding to the violation count; MinPointer is a pointer to the heap element that has the minimum key; MaxRank is the highest rank among the tree ranks.
For efficient implementation of the priority queue, such parameters as redundant counters are involved in the thick heap structure. In a thick heap, ranks determine the order in which elements are retrieved from the queue. The redundant representation of numbers allows for quick incrementing and decrementing of the priority of an element. When performing an increment or decrement operation, a commit operation is used to update and maintain the correctness of the redundant number representation in the thick heap. This allows the operation to be performed in a constant O(1) time, regardless of the size of the number or the number of digits. Thus, the redundant representation of numbers provides a fast operation to change the priority of an element.
To have an idea of how the thick heap structure works, we need to consider separately data structures such as the root counter and the violation counter.
The root counter is a data structure used to count the number of elements in a tree or heap. It consists of a redundant ternary representation of the number of elements in the heap and a set of list elements rootCount.
- rootCount[i].Value is the i-th digit equal to the number of trees of rank i.
- rootCount[i].fowardPointer - direct pointer of the i-th digit.
- rootCount[i].listPointer - pointer to the list of trees of the same rank. The trees in this list are linked using the Right pointer of the root nodes of the trees being linked. If there is no rank in the heap, this pointer is null.
The root counter allows to perform insertion and deletion operations of elements in the heap in record time. When deleting an element, the counter decreases by 1 unit, when adding it increases. The root counter is also associated with many necessary methods for creating the most efficient and convenient structure of a thick heap, such as: updating the direct pointer, correcting the list part during insertion and deletion, linking of three trees into one, defining a node with a minimum key, fixing, removing a tree from the heap, finding a tree with a minimum counter. These methods will be discussed in detail in the second part of the term paper.
The violation counter is very similar to the root counter, but performs different tasks.
The counter consists of an extended redundant binary representation of a set of list elements. The existence of this counter allows access to any irregular node of rank i in time
O(1).	Incrementing and decrementing operations are also performed in the least time.
It can be represented by a self-expanding array countViolation, whose elements consist of four fields:
- countViolation[i].Value - the number of invalid nodes of rank i that violate certain rules or conditions set for the heap.
- countViolation[i].forwardPointer -- a forward pointer of rank i.
- countViolation[i].firstViolation -- pointer to an invalid node of rank i.
- countViolation[i].secondViolation -- pointer to an invalid node of rank i.
Decreasing the key of an element of rank i corresponds to the operation of incrementing the i-th bit of the violation counter, but only when the new value of the key of the node being changed becomes less than the value of the key of its parent.
To initialise a new link in the counter, it is only necessary to zero its value in the new bit. This is done when a new tree is introduced into the heap ranked by maxRank + 1. For those violations that may occur in nodes of rank less than or equal to maxRank + 1, the corresponding bits of the violation counter are already initiated, and there are no nodes of higher rank in the heap yet.
Because the thick heap uses a thick tree structure, which requires additional pointers and data structures to store and maintain information, it consumes significantly more memory. The memory consumption may depend on the particular implementation of the heap and the amount of data such a heap handles. In some cases, a thick heap may be more memory efficient.
The purpose of this structure is obvious - to allow to get the minimum (maximum, etc.) values from some set of elements as fast as possible, as well as to modify it.
Due to the high speed of the above operations, heaps have found many uses:
1.	Pyramidal sorting.
2. search algorithms: minimum, maximum, median, etc.
3. Algorithms on graphs: Prim's algorithm, Dijkstra's algorithm.
4.	Applications to complex systems (e.g., dynamic computer memory).
# Basic operations for a thick heap
![image](https://github.com/XAH30/FatHeap/assets/73390555/e3b9c6f8-f553-4d31-b4ea-68f672e16d2d)
#  Comparison of data structures
![image](https://github.com/XAH30/FatHeap/assets/73390555/c9a31415-30d6-4b4b-bfd5-476fe2711e8f)

