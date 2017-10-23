#include <stack>

template<typename ContentType>
class binnode{
public:
	binnode():leftChild(left), rightChild(right), height(0){};
	binnode(ContentType dt, binnode<ContentType>* left=NULL, binnode<ContentType>* right=NULL):data(dt), leftChild(left), rightChild(right), height(0){};
	virtual ~binnode(){};

	int size(){
		int _size = 1;
		if (leftChild) _size += leftChild->size();
		if (rightChild) _size += rightChild->size();
		return _size;
	}

	void insertAsLeftChild(ContentType& data){
		binnode<ContentType>* node = new binnode<ContentType>(data);
		this->leftChild = node;
	}
	void insertAsrightChild(ContentType& data){
		binnode<ContentType>* node = new binnode<ContentType>(data);
		this->rightChild = node;
	}
	bool isLeftChildren(){
		return this->parent->leftChild==this;
	}
	template <typename VST> 
	void travPre ( VST& visit){
		VST(*this);
		if (leftChild) leftChild->travPre(VST);
		if (rightChild) rightChild->travPre(VST);
	}
	template <typename VST> 
	void travIn ( VST& visit){
		if (leftChild) leftChild->travPre(VST);
		VST(*this);
		if (rightChild) rightChild->travPre(VST);
	}
	template <typename VST> 
	void travPost ( VST& visit){
		if (leftChild) leftChild->travPre(VST);
		if (rightChild) rightChild->travPre(VST);
		VST(*this);
	}
	template <typename VST> 
	void travPreIter1 ( VST& visit){
		//使用栈
		if (this==NULL) return;
		stack<ContentType> stk;
		binnode<ContentType>* current=this;
		while(current){
			visit(*current);
			if (current->rightChild) stk.push_back(current->rightChild);
			if (current->leftChild) current=current->leftChild;
			else current=stk.pop();
		}
	}
	//辅助
	void travelAlongLeft(stack<ContentType> stk){
		binnode<ContentType>* current = this;
		while(current){
			stk.push_back(current);
			current = current->next;
		}
	}
	void travInIter1 ( VST& visit){
		//使用栈
		if (this==NULL) return;
		stack<ContentType> stk;
		binnode<ContentType>* current=this;
		while(current){
			travelAlongLeft(current);
			visit(*mcurrent);
			if (current->rightChild) current=current->rightChild;
			else current=stk.pop();
		}
	}
	//辅助
	binnode<ContentType>* succ(){
		binnode<ContentType>* current = this;
		if (current->rightChild) {
			current = current->rightChild;
			while(current->leftChild){
				current = current->leftChild;
			}
			return current;
		}
		while(current!=root && !current->isLeftChildren()){
			current = current->parent;
		}
		return current->parent;
	}
	void travInIter2(VST& visit){
		binnode<ContentType>* current = this;
		while(current->leftChild) current = current=>leftChild;
		while(current){
			visit(*current);
			current = current->succ();
		}
	}
	binnode<ContentType>* getThrough(){
		binnode<ContentType>* current = this;
		while(current->leftChild or current->rightChild){
			if (current->leftChild) current = current->leftChild;
			current = current->rightChild;
		}
		return current;
	}
	void travPostIter(VST& visit){
		binnode<ContentType>* current = this;
		while(current){
			visit(*current);
			if (current->isLeftChildren()){
				binnode<ContentType>* father = current->parent;
				if (father->rightChild){
					current = father->rightChild->getThrough();
				}
				else{
					current = father;
				}
			}
			else {
				current = father;
			}
		}
	}
private:
	binnode<ContentType>* parent;
	binnode<ContentType>* leftChild;
	binnode<ContentType>* rightChild;
	ContentType data;
	int height;
}