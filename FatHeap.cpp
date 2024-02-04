//Класс толстой кучи
class FatHeap {
private:
	int size = 0;
	int maxRank;
	Node* minNode = nullptr;
	vector<RootCounterNode> rootCounter;
	// Вставляет дерево ранга k в список деревьев k-го элемента корневого счетчика
	void insertTreeInList(Node* tree)
	{
		if (tree->getRank() > maxRank || rootCounter[tree->getRank()].value == 3)
			return;
		tree->setRight(rootCounter[tree->getRank()].listPointer);
		rootCounter[tree->getRank()].listPointer = tree;
	}
	// Удаляет дерево ранга k из списка деревьев k-го элемента корневого счетчика
	void deleteTreeFromList(Node*& tree)
	{
		int rank = tree->getRank();
		if (rank > maxRank)
			return;

		Node* currentPointer = rootCounter[rank].listPointer;
		if (currentPointer == tree)
		{
			rootCounter[rank].listPointer = currentPointer->getRight();
			tree->setRight(nullptr);
			return;
		}

		while (currentPointer->getRight() != tree)
			currentPointer = currentPointer->getRight();

		currentPointer->setRight(tree->getRight());
		tree->setRight(nullptr);
	}
	// Возвращает указатель на минималный узел списочной части корневого счетчика
	Node* getMinFromList(Node*& listPointer)
	{
		Node* curp = listPointer;
		Node* minp = listPointer;
		while (curp != nullptr)
		{
			if (curp->getValue() < minp->getValue())
				minp = curp;

			curp = curp->getRight();
		}
		return minp;
	}
	// Связывает три толстых дерева ранга k в одно дерево ранга k + 1
	Node* fastening(Node* p1, Node* p2, Node* p3)
	{
		Node* minp = nullptr;
		bool foundmin = false;

		if (p1->getRank() == minNode->getRank())
		{
			minp = (p1 == minNode) ? (p1 = p3, p1) : ((p2 == minNode) ? (minp = p2, p2 = p3, p2) : (minp = p3, p3)); 
			foundmin = true;
		}

		if (!foundmin)
		{
			minp = (p1->getValue() <= p2->getValue() && p1->getValue() <= p3->getValue()) ? (p1 = p3, p1) : ((p2->getValue() <= p3->getValue() && p2->getValue() <= p1->getValue()) ? (minp = p2, p2 = p3, p2) : (minp = p3, p3));
		}

		p1->setLeft(nullptr);
		p1->setRight(p2);
		p1->setParent(minp);
		p2->setLeft(p1);
		p2->setRight(minp->getLeftChild());
		p2->setParent(minp);

		if (minp->getLeftChild() != nullptr)
		{
			minp->getLeftChild()->setLeft(p2);
		}

		minp->setLeftChild(p1);
		minp->setLeft(nullptr);
		minp->setRight(nullptr);
		minp->setParent(nullptr);
		minp->setRank(minp->getRank() + 1);

		return minp;
	}
	// Связывает 3 дерева ранга k в одно дерево ранга k + 1, поддерживая корневой счетчик [операция фиксации]
	void fixRootNode(int rank)
	{
		if (rank > maxRank || rootCounter[rank].value != 3)
			return;

		rootCounter[rank].value = 0;
		Node* p1 = rootCounter[rank].listPointer;
		Node* p2 = p1->getRight();
		Node* p3 = p2->getRight();
		p1->setRight(nullptr);
		p2->setRight(nullptr);
		Node* newp = fastening(p1, p2, p3);
		rootCounter[rank].listPointer = nullptr;
		insertTree(newp);
	}
	// Вставка дерева в кучу
	void insertTree(Node* tree)
	{
		int rank = tree->getRank();
		if (rank > maxRank + 1)
			return;

		if (rank == maxRank + 1)
			increaseMaxRank();

		// Если вставить не можем, освобождаем место
		if (rootCounter[rank].value == 3)
			fixRootNode(rank);

		insertTreeInList(tree);
		rootCounter[rank].value++;
	}
	// Удаление дерева из кучи
	void deleteTree(Node* tree)
	{
		if (tree->getRank() > maxRank || rootCounter[tree->getRank()].value == 0)
			return;
		deleteTreeFromList(tree);
		rootCounter[tree->getRank()].value--;
	}
	// Возвращает указатель на минимальный узел среди корневых узлов
	Node* minNodeInRoot()
	{
		Node* minp = nullptr;
		int minKey = numeric_limits<int>::max(); // Инициализируем минимальное значение ключа

		for (int i = 0; i <= maxRank; ++i)
		{
			Node* p1 = getMinFromList(rootCounter[i].listPointer);
			int key = getKey(p1);

			if (key < minKey)
			{
				minKey = key;
				minp = p1;
			}
		}
		return minp;
	}
	// Увеличивает значение maxRank, добавляя узлы в соотв. счетчики
	void increaseMaxRank()
	{
		maxRank++;
		rootCounter.push_back(RootCounterNode());
	}
	// Возвращает значение узла, либо +inf, если узел null
	int getKey(Node* p){
		return (p == nullptr) ? INF : p->getValue();
	}
public:
	//Констурктор
	FatHeap() {
		maxRank = -1;
	}
	//Возвращение размера
	int getSize() {
		return size;
	}
	//Куча пуста
	bool isEmpty() {
		return this->size == 0;
	}
	//Добавление числа в кучу
	void insert(int value){
		size++;
		Node* newNode = new Node(value);
		minNode = (getKey(newNode) < getKey(minNode)) ? newNode : minNode;
		this->insertTree(newNode);
	}
	//Получение минимального элемента
	int getMin() const {
		return (minNode == nullptr ? 0 : minNode->getValue());
	}
	//Удаление минимального элемента
	int deleteMin()
	{
		if (minNode == nullptr)
			return 0;

		size--;
		deleteTree(minNode);

		minNode->setLeft(nullptr);
		minNode->setRight(nullptr);
		minNode->setParent(nullptr);

		Node* cur = minNode->getLeftChild();
		while (cur != nullptr)
		{
			Node* temp = cur;
			cur = cur->getRight();

			temp->setLeft(nullptr);
			temp->setRight(nullptr);
			temp->setParent(nullptr);
			insertTree(temp);
		}

		int minValue = minNode->getValue();
		minNode = minNodeInRoot();
		return minValue;
	}
};