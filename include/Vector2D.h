#pragma once
#include <vector>

#ifndef _2DVECTOR_H
#define _2DVECTOR_H

struct _2DVector {
	std::vector< std::vector< double> > data;
	static _2DVector clrRowColumn(_2DVector v, int r, int c);
};
#endif