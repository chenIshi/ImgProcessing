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
    int c;
    int m;
    int y;
    int k;
};

//From RGB
//To CMYK
struct cmyk_color RGBtoCMYK(int rgb_color_r, int rgb_color_g, int rgb_color_b){
    struct cmyk_color ret_val;

    //formula from Adobe https://forums.adobe.com/thread/428899
    //RGB to CMY
    ret_val.c = 1-(rgb_color_r/255);
    ret_val.m = 1-(rgb_color_g/255);
    ret_val.y = 1-(rgb_color_b/255);

    //CMY to CMYK
    //k indicates "black"
    ret_val.k = 1;
    
    //side effect trial
    (ret_val.c < ret_val.k) && (ret_val.k = ret_val.c);
    (ret_val.m < ret_val.k) && (ret_val.k = ret_val.m);
    (ret_val.y < ret_val.k) && (ret_val.k = ret_val.y);

    if(ret_val.k == 1){
        ret_val.c = ret_val.m = ret_val.y = 0;
    }else{
        ret_val.c = (ret_val.c - ret_val.k)/(1-ret_val.k);
        ret_val.m = (ret_val.m - ret_val.k)/(1-ret_val.k);
        ret_val.y = (ret_val.y - ret_val.k)/(1-ret_val.k);
    }

    return ret_val;
}