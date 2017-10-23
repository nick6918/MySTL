template <typename ContentType>
class PQ{
public:
	virtual ContentType getMax() = 0;
	virtual ContentType delMax() = 0;
	virtual void insert(ContentType) = 0;
}