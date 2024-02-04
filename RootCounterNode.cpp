//Cтруктура счётчика корней
struct RootCounterNode {
	int value = 0;//количество деревьев текущего ранга в куче
	Node* listPointer = nullptr;//указатель на список деревьев текущего ранга
};