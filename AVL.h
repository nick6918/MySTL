include "BST.h"

<Template typename ContentType>
class AVL:public BST<ContentType>{
	int balanceFactor(binnode<ContentType>* node){
		return node->leftChild->height - node->rightChild->height
	}
	bool isBalanced(binnode<ContentType>* node){
		return balanceFactor(node)>-2 && balanceFactor(node) < 2;
	}	
	binnode<ContentType>* fisrtUnbalanced(binnode<ContentType>* node){
		while(node){
			if !isBalanced(node) return node;
			node = node->parent;
		}
		return NULL;
	}
	binnode<ContentType>* tallerChild(binnode<ContentType>* node){
		return node->leftChild->height <= node->rightChild->height ? node->leftChild : node->rightChild;
	}
	//connect34 and rotate
	void rotate(binnode<ContentType>* v){
		//Rotate assert there is an unbalanced node and it's in the subtree of v
		//v is the grandson node of first unbalanced node g
		binnode<ContentType>* p = v -> parent;
		binnode<ContentType>* g = p -> parent;
		if (p->isLeftChildren()){
			if (v->isLeftChildren()){
				//left-left -> zig
				p->parent = g->parent;
				connect34(p, v, g, v->leftChild, v->rightChild, p->rightChild, g->rightChild);
			}
			else{
				//left-right -> zag-zig
				v->parent = g->parent;
				connect34(v, p, g, p->leftChild, v->leftChild, v->rightChild, g->rightChild);
			}
		}
		else {
			if (v->isLeftChildren()){
				//right-left -> zig-zag
				v->parent = g->parent;
				connect34(v, g, p, g->leftChild, v->leftChild, v->rightChild, p->rightChild);
			}
			else{
				//right-right -> zag
				p->parent = g->parent;
				connect34(p, g, v, g->leftChild, p->leftChild, v->leftChild, v->rightChild);
			}
		}
	}
	void connect34(binnode<ContentType>* a, binnode<ContentType>* b, binnode<ContentType>* c, binnode<ContentType>* t0, binnode<ContentType>*t1, binnode<ContentType>* t2, binnode<ContentType>* t3){
		a->leftChild = b;
		b->parent = a;
		a->rightChild = c;
		c->parent = a;
		b->leftChild = t0;
		b->rightChild = t1;
		c->leftChild = t2;
		c->rightChild = t3;
		if (t0) t0->parent = b;
		if (t1) t1->parent = b;
		if (t2) t2->parent = c;
		if (t3) t3->parent = c;
		updateHeight(b);
		updateHeight(c);
	}
	//重写可变操作
	binnode<ContentType>* insert(const ContentType& data){
		binnode<ContentType>* father = search(data);
		binnode<ContentType>* node = new binnode<ContentType>(data);
		if (father) {
			if (data <= father->data) father ->leftChild=node;
			else father->rightChild = node;
			binnode<ContentType>* g = fisrtUnbalanced(node);
			if (g) {
				binnode<ContentType>* p = tallerChild(g);
				binnode<ContentType>* v = tallerChild(p);
				rotate(v);
			}
			else{
				updateHeight(node);
			}
		}
		else root = node;
		size++;
		return node;
	}
	ContentType& remove(const ContentType& data){
		
	}
};