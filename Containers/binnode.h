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
	template <typename T, typename VST> //元素类型、操作器
	void travIn_I3 ( BinNodePosi(T) x, VST& visit ) { //二叉树中序遍历算法（迭代版#3，无需辅助栈）
		bool backtrack = false; //前一步是否刚从右子树回溯——省去栈，仅O(1)辅助空间
		while ( true ){
			if ( !backtrack && HasLChild ( *x ) ) //若有左子树且不是刚刚回溯，则
          			x = x->lc; //深入遍历左子树
       			else { //否则——无左子树或刚刚回溯（相当于无左子树）
          			visit ( x->data ); //访问该节点
          			if ( HasRChild ( *x ) ) { //若其右子树非空，则
             				x = x->rc; //深入右子树继续遍历
            				backtrack = false; //并关闭回溯标志
          			} else { //若右子树空，则
					//回溯
             				if ( ! ( x = x->succ() ) ) break; //回溯（含抵达末节点时的退出返回）
            				backtrack = true; //并设置回溯标志
				}
          		}
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
