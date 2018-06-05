#ifndef PARAMS_H
#define PARAMS_H

#include <QString>

enum class Color {
	RED, GREEN, BLUE
};

class Params
{
public:
	Params(int IF_, int A_, int w_, double dw_, int dt_, Color baseColor_, Color testColor_,
	       const QString &baseEye_);
	Params &operator = (const Params&);

	int IF, A, w;
	double dw;
	int dt;
	Color baseColor, testColor;
	double minW, maxW;
	QString baseEye;
};

#endif // PARAMS_H
