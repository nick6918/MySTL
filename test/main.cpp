
#include <iostream>
#include "../graphMatrix.h"
using namespace std;

template <typename ContentType>
class Printor{
public:
	void operator()(Vertex<ContentType> a){
		cout<<"(Node: "<<a.data<<",   "<<a.dTime<<",          "<<a.fTime<<")"<<endl;
	}
};

template <typename ContentType>
void printVector(vector<vector<ContentType> >vec){
	for(int i =0; i<vec.size(); i++){
		for (int j=0; j<vec[i].size();j++){
			if(vec[i][j]) cout<<vec[i][j]->data;
			else cout<<" xx ";
		}
		cout<<"."<<endl;
	}
	cout<<"."<<endl;
}

template <typename ContentType>
void printVector(vector<ContentType> vec){
	for(auto ptr = vec.begin(); ptr!=vec.end(); ++ptr){
		cout<< ptr->data;
	}
	cout<<"."<<endl;
}

int main(){
	Printor<int> printor;
	graphMatrix<int, int> gph = graphMatrix<int, int>();
	for(int i=0;i<10;i++){
		gph.insert(i);
	}
	int a=110;
	gph.insert(a, 1, 0, 1);
	gph.insert(a, 1, 1, 0);
	// printVector(gph.vertexGroup);
	printVector(gph.EdgeGroup);
	gph.insert(a, 1, 2, 4);
	gph.insert(a, 1, 4, 2);
	gph.insert(a, 1, 2, 3);
	gph.insert(a, 1, 3, 2);
	gph.insert(a, 1, 3, 9);
	gph.insert(a, 1, 3, 8);
	gph.insert(a, 1, 8, 3);
	gph.insert(a, 1, 9, 3);
	gph.insert(a, 1, 2, 5);
	gph.insert(a, 1, 5, 2);
	gph.insert(a, 1, 4, 6);
	gph.insert(a, 1, 6, 4);
	gph.insert(a, 1, 5, 6);
	gph.insert(a, 1, 6, 5);
	printVector(gph.EdgeGroup);
	cout<<"(Node.data, Node.dTime, Node.fTime)"<<endl;
	gph.bfs(0, printor);
}