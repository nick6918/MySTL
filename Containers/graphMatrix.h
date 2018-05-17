#include "graph.h"
#include "unionFind.h"
#include <queue>
using namespace std;

template<typename ContentType>
class Vertex{
public:
	ContentType data;
	VSTATUS status;
	int priority, parent, dTime, fTime;
	int indegree, outdegree;
	Vertex(ContentType const& dt = (ContentType)0):data(dt), status(UNDESCOVERED), indegree(0), outdegree(0), dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){};
};

template<typename ContentType>
class Edge{
public:
	ETYPE type;
	ContentType data;
	int weight;
	Edge(ContentType const& dt = (ContentType)0, int w = 0):data(dt), type(UNDETERMAINED), weight(w){}
};

template<typename EdgeType, typename VertexType>
class graphMatrix:public graph<EdgeType, VertexType>{
public:
	vector<Vertex<VertexType> > vertexGroup; 
	vector<vector<Edge<EdgeType>*> > EdgeGroup;
public:
	graphMatrix(){
		this->edge_num = 0;
		this->vert_num = 0;
	};
	virtual ~graphMatrix(){
		for(int i=0; i<this->vert_num; i++){
			for(int j=0; j<this->vert_num; j++){
				delete EdgeGroup[i][j];
			}
		}
	};
	//辅助操作
	void reset(){
		for(int i=0; i < this->vert_num; i++){
			status(i)=UNDESCOVERED;
			parent(i)=-1;
			priority(i)=INT_MAX;
			dTime(i)=0;
			fTime(i)=0;
			for(int j=0;j < this->vert_num; j++){
				if(exist(i, j)) {
					type(i, j)=UNDETERMAINED;
				}
			}
		}
	}
	//顶点的基本操作
	virtual int indegree(int index){
		return vertexGroup[index].indegree;
	}
	virtual int outdegree(int index){
		return vertexGroup[index].indegree;
	}
	//与indegree和outdegree不同， 这两者是graph的属性， 只能由内部接口修改， 所有get接口返回值。
	//而parent, priority, dTime和fTime在设计时允许外部通过对象修改， 可以写set方法， 也可以直接返回引用。
	virtual int& parent(int index){
		return vertexGroup[index].parent;
	}
	virtual int& priority(int index){
		return vertexGroup[index].priority;
	}
	virtual int& dTime(int index){
		return vertexGroup[index].dTime;
	}
	virtual int& fTime(int index){
		return vertexGroup[index].fTime;
	}
	virtual VSTATUS& status(int index){
		return vertexGroup[index].status;
	}
	virtual VertexType& vertex(int index){
		return vertexGroup[index].data;
	}
	virtual void insert(VertexType const& vt){
		vertexGroup.push_back(vt);
		for(int i=0; i<this->vert_num;i++){
			EdgeGroup[i].push_back((Edge<EdgeType>*)NULL);
		}
		this->vert_num++;
		EdgeGroup.push_back(vector<Edge<EdgeType>*>(this->vert_num, (Edge<EdgeType>*)NULL));
	}
	virtual void remove(int index){
		vertexGroup.erase(vertexGroup.begin()+index);
		for(int i=0; i<this->vert_num;i++){
			remove(index, i);
			remove(i, index);
		}
		EdgeGroup.erase(EdgeGroup.begin()+index);
		for(int i=0; i<this->vert_num;i++){
			EdgeGroup[i].erase(EdgeGroup[i].begin()+index);
		}
	}
	virtual int firstNbr(int index){
		return nextNbr(index, this->vert_num);
	}
	virtual int nextNbr(int index, int relevant){
		while(relevant>-1 && !exist(index, --relevant));
		return relevant;
	}
	//边的基本操作
	virtual bool exist(int index, int other){
		return index<this->vert_num && other<this->vert_num && index >=0 && other>=0 && EdgeGroup[index][other];
	}
	virtual ETYPE& type(int index, int other){
		return EdgeGroup[index][other]->type;
	}
	virtual int weight(int index, int other){
		return EdgeGroup[index][other]->weight;
	}
	virtual EdgeType& edge(int index, int other){
		return EdgeGroup[index][other]->data;
	}
	virtual void insert(EdgeType const& dt, int w, int index, int other){
		if (EdgeGroup[index][other]) return;
		Edge<EdgeType>* current = new Edge<EdgeType>(dt, w);
		EdgeGroup[index][other]=current;
		this->edge_num++;
		vertexGroup[index].outdegree++;
		vertexGroup[other].indegree++;
	}
	virtual void remove(int index, int other){
		Edge<EdgeType>* current = EdgeGroup[index][other];
		if(!current) return;
		delete current;
		EdgeGroup[index][other]=NULL;
		this->edge_num--;
		vertexGroup[index].outdegree--;
		vertexGroup[other].indegree--;
	}
	//算法
	template <typename VST>
	void bfs_single (int index, VST& visit, int& clock){
		cout<<"clock"<<clock<<endl;
		//这种bfs和dfs都无法详细区分出跨边， 前向边和后向边
		//遍历所有节点， 同时生成最小支撑树(parent和etype两个参数)
		//dTime表示在bfs下discover的顺序, fTime表示visit的顺序
		//在bfs下， 图边氛围最小支撑树的树边tree以及非树边cross
		queue<int> nodes;
		dTime(index)=++clock;
		nodes.push(index);
		while(!nodes.empty()){
			int node=nodes.front();
			nodes.pop();
			fTime(node)=++clock;
			visit(vertexGroup[node]);
			status(node)=VISITED;
			for(int current=firstNbr(node); current>-1; current=nextNbr(node, current)){
				if (status(current)==UNDESCOVERED){
					nodes.push(current);
					status(current)=DISCOVERED;
					dTime(current)=++clock;
					type(node, current)=TREE;
					parent(current)=node;
				}
				else{
					type(node, current)=CROSS;
				}			
			}
		}
	}
	template <typename VST>
	void dfs_single (int start, VST& visit, int& clock){
		dTime(start) = clock++;
		status(start) = DISCOVERED;
		for (int current = firstNbr(start); current > -1; current = nextNbr(start, current) ){
			switch(status(current)){
				case UNDISCOVERED:
					dTime(current) = clock++;
					status(current) = DISCOVERED;
					type(start, current) = TREE;
					dfs_single(current, visit, clock);
					break;
				case DISCOVERED:
					type(start, current) = BACKWARD;
					break;
				default:
					type(start, current) = (dTime(start) <= dTime(current) ? FORWARD : CROSS);
					break;
			}
			visit(start);
			status(start) = VISITED;
			fTime(start) = clock++;
		}
	}
	template <typename VST>
	void bfs (int start, VST& visit){
		reset();
		int index=start;
		int clock=0;
		do {
			//cout<<"a new connected zone root as"<<index<<endl;
			if (status(index)==UNDESCOVERED) bfs_single(index, visit, clock);
			index = (index+1)%this->vert_num;
		}
		while(index!= start);
	}
	template <typename VST>
	void dfs (int start, VST& visit){
		reset();
		int index=start;
		int clock=0;
		do {
			//cout<<"a new connected zone root as"<<index<<endl;
			if (status(index)==UNDESCOVERED) dfs_single(index, visit, clock);
			index = (index+1)%this->vert_num;
		}
		while(index!= start);
	}

	void scc_single(int start, int& clock, stack<int>& S){
		int index = start;
		status(index)=DISCOVERED;
		dTime(index)=clock++;
		for(int current=firstNbr(index);current>0;current=nextNbr(current)){
			if (status(current)==UNDESCOVERED){
				status(current)=DISCOVERED;
				type(index, current)=TREE;
				parent(current)=index;
				dTime(current)=clock++;
				scc_single(start, clock, S);
			}
			else if(status(current)==DISCOVERED){
				type(index, current)=BACKWARD;
			}
			else{
				type(index, current)=(dTime(current) < dTime(index) ? FORWARD : CROSS);
			}
		}
		status(index)=VISITED;
		fTime(index)=clock++;
		S.push_back(index);
	}

	int firstNbr_reverse(int index){
		return nextNbr_reverse(index, this->vert_num)
	}

	int nextNbr_reverse(int index, int relevant){
		while(relevant>-1 && !exist(--relevant, index));
		return relevant;
	}

	void scc_reverse(int start, int& clock, stack<int>& S){
		int index = start;
		status(index)=DISCOVERED;
		dTime(index)=clock++;
		for(int current=firstNbr_reverse(index);current>0;current=nextNbr_reverse(current)){
			if (status(current)==UNDESCOVERED){
				status(current)=DISCOVERED;
				type(index, current)=TREE;
				parent(current)=index;
				dTime(current)=clock++;
				scc_single(start, clock, S);
			}
			else if(status(current)==DISCOVERED){
				type(index, current)=BACKWARD;
			}
			else{
				type(index, current)=(dTime(current) < dTime(index) ? FORWARD : CROSS);
			}
		}
		status(index)=VISITED;
		fTime(index)=clock++;
		visit(index);
		S.remove(index);
	}

	void scc(int start, int& clock, stack<int>& S){
		//korasaju算法: 正向反向dfs法
		reset();
		int clock=0;
		do {
			//cout<<"a new connected zone root as"<<index<<endl;
			if (status(index)==UNDESCOVERED) scc_single(index, clock, S);
			index = (index+1)%this->vert_num;
		}
		while(index!= start);
		reset();
		while(!S.empty()){
			start = S.top();
			scc_reverse(start, clock, S);
		}
	}

	int nextPrior(){
		int index = -1;
		int value = -1;
		for(int i=0; i < this->vert_num; i++){
			if(status(i)!=VISITED and priority(i)<value){
				index = i;
				value = priority(i);
			}
		}
		type(parent(index), index)=TREE;
		return index;
	}

	void kruscal(){
		//将MST的所有边定义为TREE即可。
		EdgeGroup.mergeSort();//O(elge)
		unionFind UF(this->vert_num);
		int edge_count = 0;
		for(int i =0;i<edge_num;i++){//O(elg*n)
			if (!UF.connected(EdgeGroup[i].u, EdgeGroup[i].v)){
				type(EdgeGroup[i].u, EdgeGroup[i].v)==TREE;
				union(u, v);
				edge_count++;
			}
			if (edge_count >= this->vert_num-1) break;
		}

	}

	void prim(int start){
		//O(n2)
		reset();
		int index = start;
		while(index > -1){
			status(index)==VISITED;
			for(int current = fisrtNbr(index); current > -1; current = nextNbr(index, current)){
				if (status(current)!=VISITED and priority(current) > weight(index, current)){
					parent(current)=index;
					priority(current)=weight(index, current);
				}
			}
			index = nextPrior();
		}
	}

	bool Bellman-Ford(){
		reset();
		stack<int> vert_stack;
		this->tSort(start, clock, vert_stack); //O(e)
		if (vert_stack){
			//DSG
			while(!vert_stack.empty()){//O(e)
				int index = vert_stack.top();
				vert_stack.pop();
				status(index)=VISITED;
				if (parent(index)!=-1) type(index, current)=TREE;
				for(int current = fisrtNbr(index); current > -1; current = nextNbr(index, current)){
					if(priority(current) > weight(index, current)){
						parent(current)=index;
						priority(current) = weight(index, current);
					}
				}
			}
			return true;
		}
		else{
		//存在环
			for(int i = 0; i < this->vert_num-1; i++){//O(ne)
				for (int j = 0; j < this->edge_num; j++){
					if(priority(EdgeGroup[j].v) > priority(EdgeGroup[j].u) + weight(EdgeGroup[j].u, EdgeGroup[j].v)){
						parent(EdgeGroup[j].v)=EdgeGroup[j].u;
						priority(EdgeGroup[j].v) = priority(EdgeGroup[j].u) + weight(EdgeGroup[j].u, EdgeGroup[j].v);
					}
				}
			}
			for(int i = 0; i < this->edge_num; i++){//O(ne)
				if(priority(EdgeGroup[j].v) > priority(EdgeGroup[j].u) + weight(EdgeGroup[j].u, EdgeGroup[j].v)){
					return false;
				}
			}
			return true;
		}
	}
};
