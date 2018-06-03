#ifndef PARAMS_H
#define PARAMS_H

enum class Color {
    RED, GREEN, BLUE
};

class Params
{
public:
    Params(int IF_, int A_, int w_, int dw_, int dt_, Color baseColor_, Color testColor_);
    Params &operator = (const Params&);

    int IF, A, w, dw, dt;
    Color baseColor, testColor;
};

#endif // PARAMS_H
