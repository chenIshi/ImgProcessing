#include <stdio.h>
#include "colorCodeTranslate.c"

int main(){
    double c, m, y, k;
    double *pc = &c;
    double *pm = &m;
    double *py = &y;
    double *pk = &k;
    /*
    int a = 1;
    int b = 2;
    int p = 3;
    int d = 4;
    c= &a;
    m= &b;
    y= &p;
    k= &d;
    */
    RGBtoCMYK(28,28,28, pc, pm, py, pk);
    printf("C: %lf, M: %lf, Y: %lf, K: %lf\n", c, m, y, k);
    return 0;
}