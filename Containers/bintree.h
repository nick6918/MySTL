#include "treenode.h"

template <typename ContentType>
class binarytree{
private:
	treenode<ContentType>* root;
	int size;
public:
	updateNodeHeight(binnode<ContentType>* node){
		node->height = (node->leftChild->height > node->rightChild->height) ? node->rightChild->height : node->leftChild->height;
	}
	updateHeight(binnode<ContentType>* node){
		while(node){
			updateNodeHeight(node);
			node = node->parent;
		}
	}
}