#include "../vector.h"

template <typename ContentType>
class KSelection{
	ContentType quickSelect()(vector<ContentType> vec, Rank k){
		//Suppose: 0<k<hi-lo
		int lo=0;
		int hi=vec.size(); 
		while(lo<hi){
			Rank pivot = vec.partition(lo, hi);
			if (pivot==k) return vec[k];
			else{
				if (pivot > k){
					hi = pivot;
				}
				else {
					lo = pivot+1;
				}
			}
		}
	}
	ContentType select()(vector<ContentType> vec, Rank lo, Rank hi){
		int Q=5;
		vector<ContentType> midianArray;
		if (vec.size()<Q) return quickSelect(vec, vec.size()/2);
		for (int i=0; i<n;i=i+Q){
			midianArray.put(select(vec, i, i+Q));
		}
		ContentType pivot = select(midianArray, 0, midianArray.size());
		//?
	}
}