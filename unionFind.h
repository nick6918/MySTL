Template <typename ContentType>
class unionFind{
public:
	unionFind(int n){
		_parent = int[n];
		_size = int[n];
		for (int i = 0; i<n ; i++){
			_parent[i]=i;
			_size[i]=1;
		}
	}

	int root(int index){
		int i = index;
		while(true){
			if(_parent[i]!=i){
				_parent[i] = _parent[_parent[i]];
				i=_parent[i];
			}
			else{
				return i;
			}
		}
	}

	bool connected(int index, int other){
		return root[index] == root[other];
	}

	void union(int index, int other){
		if (connected(index, other)) return;
		if (_size[index] <= _size[other]) {
			_parent[root(index)]=root(other);
			_size[other]+=_size(index);
		}
		else{
			_parent[root(other)]=root(index);
			_size[index]+=_size(other);
		}
	}

private:
	vector<int> _parent;
	vector<int> _size;
};