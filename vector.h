typedef int Rank;
#define DEFAULT_CAPACITY 10

#include "complexHeap.h"

int power(int base, int power){
	//only power >=0 and power is integer
	if (power==0) return 1;
	int count = 0;
	int result = 1;
	while (count < power){
		result *= base;
		count ++;
	}
	return result;
}

template <typename ContentType>
class vector{
public:
	//构造与析构
	vector(int cap = DEFAULT_CAPACITY, int s = 0, ContentType content = 0){
		//可以将任意类型的对象赋值为0， 表示赋予空对象;
		_elem = new ContentType[cap];
		for (_size=0; _size < s; _elem[_size++]=content);
	};
	vector(vector<ContentType> const& other){
		copyFrom(other._elem, 0, other._size);
	} 
	vector(vector<ContentType> const& other, Rank lo, Rank hi){
		copyFrom(other._elem, lo, hi);
	} 
	~vector(){
		delete[] _elem;
	}
	//基本接口
	int size(){
		return _size;
	}
	bool empty(){
		return !_size;
	}
	int disordered() const{
		//const对象只能调用const函数， 非const对象可以调用所有函数。
		int count = 0;
		for (int i=0;i<_size;i++){
			if (_elem[i+1] > _elem[i]) {
				count++;
			}
		}
		return count;
	}
	ContentType remove(Rank r){
		ContentType old = _elem[r];
		for (int i=r; i<_size; i++){
			_elem[i] = _elem[i+1];
		}
		_size--;
		return old;
	}
	Rank insert(Rank r, ContentType v){
		if (_size + 1 > _capacity) expand();
		for(int i = _size; i > r; i--){
			_elem[i] = _elem[i-1];
		}
		_elem[r]=v;
		_size++;
		return r;
	}
	//重载 
	ContentType& operator[](Rank r) const{
		return _elem[r];
	}
	vector<ContentType> & operator=(vector<ContentType> other){
		//=重载返回引用。
		if (_elem) delete[] _elem;
		copyFrom(other._elem, 0, other._size);
		return *this;
	}
	//乱序与排序
	void unsort(Rank lo, Rank hi){
		ContentType* base = _elem + lo;
		for(int i = hi - lo; i > 0; i--){
			swap(base[i-1], base[rand() % i]);
		}
	}
	void merge(Rank lo, Rank md, Rank hi){
		int lc = md - lo;
		int lh = hi - md;
		ContentType* front = new ContentType[lc];
		ContentType* end = _elem + md;
		for (int i = 0; i < lc; i++){
			front[i] = _elem[lo + i];
		}
		for (int i =0, j=0, k=lo; i < lc || j < lh; ){
			if(i < lc && (j >= lh || front[i] <= end[j])) _elem[k++]=front[i++];
			if(j < lh && (i >= lc || front[i] > end[j])) _elem[k++]=end[j++];
		}
		delete[] front;
	}
	void mergeSort(Rank lo, Rank hi){
		if (hi - lo < 2) return;
		int md = (lo + hi) / 2;
		mergeSort(lo, md);
		mergeSort(md, hi);
		merge(lo, md, hi);
	}
	void mergeSort_Iter(Rank lo, Rank hi){
		 int index = 1;
		 int inter = power(2, index);
		 int size = hi -lo;
		 while(inter <  size){
		 	for (int i = 0; i<size; i=i+inter){
		 		if (lo+i+inter < size) merge(lo+i, lo+i+inter/2, lo+i+inter);
		 		if (lo+i+inter/2 < size) merge(lo+i, lo+i+inter/2, size);
		 	}
		 	index++;
		 	inter = power(2, index);
		 }
		 for (int i = 0; i<size; i=i+inter){
		 	if (lo+i+inter < size) merge(lo+i, lo+i+inter/2, lo+i+inter);
		 	if (lo+i+inter/2 < size) merge(lo+i, lo+i+inter/2, size);
		 }
	}
	Rank partition(Rank lo, Rank hi){
		swap(_elem[lo], _elem[lo+rand(0, _elem.size())]);
		ContentType pivot = _elem[lo];
		hi=hi-1;
		while(lo < hi){
			if(_elem[hi]>pivot) hi--;
			else _elem[lo++]=_elem[hi];
			if((lo < hi) && (_elem[lo]<pivot)) lo++;
			else _elem[hi--]=_elem[lo]
		}
		_elem[lo]=pivot;
		return lo;
	}
	void quickSort(Rank lo, Rank hi){
		Rank pos = partition(lo, hi);
		quickSort(lo, pos);
		quickSort(pos, hi);
		merge(lo, pos, hi);
	}
	void heapSort(Rank lo, Rank hi){
		complexHeap<ContentType> heap(_elem+lo, hi-lo);
		int pivot = hi;
		while(){

		}
	}
	//辅助函数
	void copyFrom(ContentType const* other, Rank lo, Rank hi){
		_elem = new ContentType[2* (hi - lo)];
		//按照倍增法， capacity永远在[50%,100%)之间
		for (_size=lo; _size < hi; _elem[_size++]=other[lo++]);
	}
	void expand(){
		if (_size < _capacity) return;
		_capacity = 2*_capacity;
		ContentType* _old = _elem;
		_elem = new ContentType[_capacity];
		for(int count=0; count < _size; count++){
			_elem[count] = _old[count];
		}
		delete[] _old;
	}
private:
	Rank _size;
	int _capacity;
	ContentType* _elem;
};