#include <vector>
#include <stack>
using namespace std;

typedef enum {UNDESCOVERED, DISCOVERED, VISITED} VSTATUS;
typedef enum {TREE, CROSS, FORWARD, BACKWARD, UNDETERMAINED} ETYPE;

template<typename EdgeType, typename VertexType>
class graph{
protected:
	int edge_num;
	int vert_num;
public:
	//顶点操作
	virtual int indegree(int index) = 0;
	virtual int outdegree(int index) = 0;
	virtual int& parent(int index) = 0;
	virtual int& priority(int index) = 0;
	virtual int& dTime(int index) = 0;
	virtual int& fTime(int index) = 0;
	virtual int firstNbr(int index) = 0;
	virtual int nextNbr(int index, int relevant) = 0;
	virtual VSTATUS& status(int index) = 0;
	virtual VertexType& vertex(int index) = 0;
	virtual void insert(VertexType const& vt) = 0;
	virtual void remove(int index) = 0;
	//边操作
	virtual bool exist(int index, int other) = 0; 
	virtual ETYPE& type(int index, int other) = 0;
	virtual int weight(int index, int other) = 0;
	virtual EdgeType& edge(int index, int other) = 0;
	virtual void insert(VertexType const& dt, int weight, int index, int other) = 0;
	virtual void remove(int index, int other) = 0;
	//算法
	void bfs ( int ); //广度优先搜索算法
	void dfs ( int ); //深度优先搜索算法
	void bcc ( int ); //基于DFS的双连通分量分解算法
	stack<VertexType>* tSort ( int ); //基于DFS的拓扑排序算法
	void prim ( int ); //最小支撑树Prim算法
	void dijkstra ( int ); //最短路径Dijkstra算法
	template <typename PU> void pfs ( int, PU ); //优先级搜索框架

};