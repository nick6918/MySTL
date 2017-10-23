#include "listnode.h"

template <typename ContentType>
class list{
private:
	listnode<ContentType>* root;
	listnode<ContentType>* last;
	int size;
public:
	list(){init();};
	list(list const& ls, int n=ls.size){
		copyNodes(ls, n);
	}
	virtual ~list(){
		clear();
		delete root;
		delete last;
	}
	void insert(listnode<ContentType>* current, ContentType data){
		current->insert(data);
	}
	bool remove(listnode<ContentType>* item){
		listnode<ContentType>* current = root;
		while(current->next!=item){
			current = current->next;
			if (current->next==last) return false;
		}
		current->next = item->next;
		item->next = NULL;
		delete item;
		size--;
		return true;
	}
	Rank size(){
		return size;
	}
	bool empty(){
		return size==0;
	}
	ContentType& operator[](Rank index){
		//index <= size;
		listnode<ContentType>* current = root->next;
		while(index--){
			current = current -> next;
		}
		return current->data;
	}
	bool valid(listnode<ContentType>* p){
		listnode<ContentType>* current = root->next;
		while(current!=last){
			if (current == p) return true;
			current = current->next;
		}
		return false;
	}
	//辅助函数
	void clear(){
		listnode<ContentType>* current = root->next;
		while(current != last){
			item = current;
			current = current->next;
			delete(item);
		}
		root->next = last;
	}
	void init(){
		root = new listnode<ContentType>();
		last = new listnode<ContentType>();
		root->next=last;
		last->next=NULL;
		size=0;
	}
	void copyNodes(listnode<ContentType>* ls, int n)
	{
		init();
		listnode<ContentType>* current = root;
		while(n--) {
			insert(current, ls->get())
			ls = ls->next;
			current = current->next;
		}
	}
	void reverse1(){
		listnode<ContentType>* p, q, r;
		p=root;
		q=p->next;
		r=p->next;
		while(q!=last){
			q->next=p;
			p=q;
			q=r;
			r=q->next;
		}
		root->next=NULL;
		last->next=p;
		last=root;
		root=q;
	}
	void reverse2(){
		listnode<ContentType>* father=root->next;
		listnode<ContentType>* son=father->next;
		while(son!=last){
			father->next=son->next;
			son->next=root->next;
			root->next=son;
			son=father->next;
		}
	}
}