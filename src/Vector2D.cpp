#include <vector>
#include "../include/Vector2D.h"


#if defined( _2DVECTOR_H)

_2DVector _2DVector::_2DVector::clrRowColumn(_2DVector v, int r, int c) {
	v.data.erase(v.data.begin() + r);
	v.data.resize(v.data.size());
	v.data.shrink_to_fit();
	for (int i = 0; i < v.data.capacity();i++) {
		v.data[i].erase(v.data[i].begin() + c);
		v.data[i].resize(v.data[i].size());
		v.data[i].shrink_to_fit();
	}
	return v;
}


#endif