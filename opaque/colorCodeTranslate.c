//2018-03-06 written by ChenIshi
//Image Processing Project 01 - color encoding transfer

#include "rightInput.c"


//color code data type, similar to python dict key-value implementation
struct rgb_color {
    int r;
    int g;
    int b;
};

struct cmyk_color {
    double c;
    double m;
    double y;
    double k;
};

//From RGB
//To CMYK
void RGBtoCMYK(int rgb_color_r, int rgb_color_g, int rgb_color_b, double *ret_c, double *ret_m, double *ret_y, double *ret_k){
    struct cmyk_color ret_val;

    //formula from Adobe https://forums.adobe.com/thread/428899
    //RGB to CMY

    ret_val.c = 1-(rgb_color_r/255.0);
    ret_val.m = 1-(rgb_color_g/255.0);
    ret_val.y = 1-(rgb_color_b/255.0);

    //CMY to CMYK
    //k indicates "black"
    ret_val.k = 1;
    
    //side effect trial

    (ret_val.c < ret_val.k) && (ret_val.k = ret_val.c);
    (ret_val.m < ret_val.k) && (ret_val.k = ret_val.m);
    (ret_val.y < ret_val.k) && (ret_val.k = ret_val.y);

    printf("During Fuction call: C: %lf, M: %lf, Y: %lf, K: %lf\n", ret_val.c, ret_val.m, ret_val.y, ret_val.k);

    if(ret_val.k == 1){
        ret_val.c = ret_val.m = ret_val.y = 0;
    }else{
        ret_val.c = (ret_val.c - ret_val.k)/(1-ret_val.k);
        ret_val.m = (ret_val.m - ret_val.k)/(1-ret_val.k);
        ret_val.y = (ret_val.y - ret_val.k)/(1-ret_val.k);
    }

    ret_c = &(ret_val.c);
    ret_m = &(ret_val.m);
    ret_y = &(ret_val.y);
    ret_k = &(ret_val.k);

    printf("End of the function call: ret_c: %lf, ret_m: %lf, ret_y: %lf, ret_k: %lf\n", *ret_c, *ret_m, *ret_y, *ret_k);

}