template <typename ContentType>
class listnode{ 
public:
	listnode(){};
	listnode(ContentType dt, listnode<ContentType>* succ = NULL): data(dt), next(succ){};
	virtual ~listnode(){};

	listnode<ContentType>* insert(ContentType const& dt){
		listnode<ContentType>* current =new listnode<ContentType>(dt, next);
		next=current;
		return current;
	}

	ContentType const& get(){
		return this->data;
	}
	
private:
	listnode<ContentType>* next;
	ContentType data;
}