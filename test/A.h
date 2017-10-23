#include <iostream>
using namespace std;

class A{
public:
	A():num(1){};
	A(int parag):num(parag){};
	virtual ~A(){};

	void overwriteTester(){
		cout<<"father"<<endl;
	}
private:
	int num;
};

class B:public A{
public:
	void overwriteTester(){
		A::overwriteTester();
		cout<<"son"<<endl;
	}	
};

