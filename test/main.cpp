#include "vector.h"
#include <iostream>
using namespace std;


int main(){
	vector<int> a(15, 12, 1);
	a[0]=37;
	a[1]=82;
	a[2]=7;
	a[3]=28;
	a[4]=17;
	a[5]=28;
	a[6]=9;
	a[7]=39;
	a[8]=72;
	a[9]=13;
	a[10]=22;
	a[11]=33;
	a.mergeSort_Iter(0, 12);
	for (int i =0 ; i<a.size();i++){
		cout<< a[i] << "    ";
	}
}