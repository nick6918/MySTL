#include "./vector.h"
#include "./PQ.h"

typedef Rank int

Template <typename ContentType>
class ComplexHeap: public PQ<ContentType>, public vector<ContentType>{
//最大堆
public:
	//构造器
	ComplexHeap(){};
	ComplexHeap(ContentType* A, Rank n){
		_elem.copyFrom(A, 0, n);
		//将无序数组建堆
		heapify();
	}
	void heapify(){
		//floyd算法
		for(int i=parent(size-1); i>=0; i--){
			sink(i);
		}
	}
	//基本方法
	Rank insert(ContentType elem){
		_elem[size++]=elem;
		Rank pos = swim(size-1);
		return pos;
	}
	ContentType remove(Rank i){
		ContentType result = _elem[i];
		swap(_elem[i], _elem[--size]);
		sink(i);
		return result;
	}
	ContentType getMax(){
		return _elem[0];
	}
	ContentType delMax(){
		ContentType result = _elem[0];
		remove(0);
		return result;
	}
	//辅助方法
	Rank swim(Rank i){
		while (hasParent(i)){
			if (_elem[i] <=　_elem[parent(i)]) break;
			swap(_elem[i], _elem[parent(i)]);
			i=parent(i);
		}
		return i;
	}
	Rank sink(Rank i){
		while(hasChildren(i)){
			if(_elem[i]>=_elem[bigChildren(i)]) break;
			swap(_elem[i], _elem[bigChildren(i)]);
			i=bigChildren(i);
		}
		return i;
	}
	bool hasParent(i){
		return (i-1)/2 >=0; 
	}
	Rank parent(i){
		//应该有parent;
		return (i-1)/2;
	}
	bool hasChildren(i){
		return 2*i+1 < size;
	}
	bool bigChildren(i){
		//应该有children;
		//只有一个孩子
		if (2*i+2>=size) return 2*i+1;
		//两个孩子
		if(_elem[2*i+1]>=_elem[2*i+2]) return 2*i+1;
		else return 2*i+2;
	}
}