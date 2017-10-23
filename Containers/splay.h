include "BST.h"

<Template typename ContentType>
class splay:public BST<ContentType>{
public:
	//辅助函数
	void doublefold(binnode<ContentType>* a, binnode<ContentType>* b, binnode<ContentType>* c, binnode<ContentType>* t0, binnode<ContentType>*t1, binnode<ContentType>* t2, binnode<ContentType>* t3, isZig=true){
		if (isZig){
			a->leftChild = t1;
			a->rightChild = b;
			b->leftChild = t2;
			b->rightChild = c;
			c->leftChild = t3;
			c->rightChild = t4;
			b->parent = a;
			c->parent = b;
			updateHeight(c);
		}else{
			a->leftChild = b;
			a->rightChild = t1;
			b->leftChild = c;
			b->rightChild = t2;
			c->leftChild = t4;
			c->rightChild = t3;
			b->parent = a;
			c->parent = b;
			updateHeight(c);
		}
	}
	//伸展
	void splayNode(binnode<ContentType>* v){
		//assertion: node should be in the splay tree;
		if (!v or v==root) return;
		if (v->parent==root){
			//单层旋转
			if (root->leftChild==v){
				root->leftChild=v->rightChild;
				root->
			}
			else{

			}
		}
		else{
			//双层旋转
			binnode<ContentType>* p = v->parent;
			binnode<ContentType>* g = p->parent;
			if (g->leftChild == p){
				if (p->leftChild == v){
					//zig-zig
					doublefold(v, p, g, v->leftChild, v->rightChild, p->rightChild, g->rightChild);
				}
				else{
					//zag-zig
					v->parent = g->parent;
					connect34(v, p, g, p->leftChild, v->leftChild, v->rightChild, g->rightChild);
				}
			}
			else{
				if (father->leftChild == v){
					//zig-zag
					v->parent = g->parent;
					connect34(v, p, g, p->leftChild, v->leftChild, v->rightChild, g->rightChild);
				}
				else{
					//zag-zag
					doublefold(v, p, g, v->rightChild, v->leftChild, p->leftChild, g->leftChild);
				}
			}

		}
	}
};