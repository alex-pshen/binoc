#include "params.h"

Params::Params(int IF_, int A_, int w_, int dw_, int dt_, Color baseColor_, Color testColor_)
    : IF(IF_), A(A_), w(w_), dw(dw_), dt(dt_), baseColor(baseColor_), testColor(testColor_)
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
}
