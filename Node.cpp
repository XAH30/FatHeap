//Класс узла
class Node {
private:
	int value;//Значение
	Node* parent;//Родитель
	Node* left;//Ближайший левый брат
	Node* right;//Ближайший правый брат
	Node* leftChild;//Самый левый ребёнок
	int rank = 0;//Ранг узла
public:
	Node(int value) : value(value), parent(nullptr), left(nullptr), right(nullptr), leftChild(nullptr), rank(0) {}

	int getValue() { return value; }
	virtual Node* getParent() { return parent; }
	virtual Node* getLeft() { return left; }
	virtual Node* getRight() { return right; }
	virtual Node* getLeftChild() { return leftChild; }
	int getRank() { return rank; }

	virtual void setValue(int v) { value = v; }
	virtual void setParent(Node* p) { parent = p; }
	virtual void setLeft(Node* l) { left = l; }
	virtual void setRight(Node* r) { right = r; }
	virtual void setLeftChild(Node* lc) { leftChild = lc; }
	virtual void setRank(int r) { rank = r; }
};