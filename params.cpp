#include "params.h"

Params::Params(int IF_, int A_, int w_, double dw_, int dt_, Color baseColor_,
               Color testColor_, const QString & baseEye_)
    : IF(IF_), A(A_), w(w_), dw(dw_), dt(dt_), baseColor(baseColor_), testColor(testColor_)
    , minW(w_), maxW(w_), baseEye(baseEye_)
{}

Params &Params::operator =(const Params & p)
{
	IF = p.IF;
	A = p.A;
	w = p.w;
	dw = p.dw;
	dt = p.dt;
	baseColor = p.baseColor;
	testColor = p.testColor;
	maxW = p.maxW;
	minW = p.minW;
	baseEye = p.baseEye;
	return *this;
}
