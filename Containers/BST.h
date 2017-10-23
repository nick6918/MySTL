import "binTree.h"

<template typename ContentType>
class BST: public bintree<ContentType>{
protected:
	binnode<ContentType>* _hot;
public:
	binnode<ContentType>* searchIn(binnode<ContentType>* _node, const ContentType& data){
		if (!_node) return NULL;
		binnode<ContentType>* current = _node;
		while(1){
			if (data<=current->data){
				if (current->leftChild) current = current->leftChild;
				else {
					_hot = current;
					return current;
				}
			}
			else{
				if (current->rightChild) current = current->rightChild;
				else {
					_hot = current;
					return current;
				}
			}
		}
	}
	binnode<ContentType>* search(const ContentType& data){
		return searchIn(root, data);
	}
	binnode<ContentType>* insert(const ContentType& data){
		binnode<ContentType>* father = search(data);
		if (!father) root = newNode;
		else {
			if (data <= father->data) father->leftChild = newNode;
			else father->rightChild = newNode;
			updateHeight(newNode);
			size++;
		}
		return newNode;
	}
	ContentType removeAt(binnode<ContentType>* node){
		ContentType data = node->data;
		binnode<ContentType>* father = root;
		if (node->parent) father = node->parent;
		if(!node->leftChild){
			if(father->leftChild==node) father->leftChild=node->rightChild;
			else father->rightChild=node->rightChild;
		}
		else if(!node->rightChild){
			if(father->leftChild==node) father->leftChild=node->leftChild;
			else father->rightChild=node->leftChild;
		}
		else {
			binnode<ContentType>* succ_node = node->succ();
			binnode<ContentType>* succ_father = succ->parent;
			swap(father->data, node->data);
			succ_father==node?father->rightChild:father->leftChild = succ->rightChild;
			delete succ_node->data;
			delete succ_node;
			_hot = succ_father;
		}
		size--;
		return data;
	}
};