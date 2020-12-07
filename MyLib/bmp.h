#ifndef BMP_H
#define BMP_H

#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <ctime>
#include <iostream>

#pragma GCC diagnostic error "-Wold-style-cast"

struct BITMAPFILEHEADER
{
    BITMAPFILEHEADER (char* bf);
    unsigned int       bfType;
    unsigned int       bfSize;
    unsigned short int bfReserved1;
    unsigned short int bfReserved2;
    unsigned int       bfOffBits;
};


struct pixel {
    u_char blue;
    u_char green;
    u_char red;
    u_char alpha;    
};



class bmp
{
private:
    char* bf;
    uint size_bf;
    BITMAPFILEHEADER* header;
    pixel* image;
    uint width;
    uint height;
public:
    
    bmp                          (const char* path);

    bmp                          (const bmp& image) = delete;
    bmp& operator=               (const bmp& image) = delete;

    void get_bf                  (FILE* f_in);
    pixel* get_image             () const;
    BITMAPFILEHEADER* get_header () const;
    uint get_height              () const;
    uint get_width               () const;

    void load_to_image           (const char* path) const;
    
    void alpha_blend             (const bmp& front, unsigned int pos_x = 0, unsigned int pos_y = 0, 
                                  const char* path_result = "blend_result.bmp");
    void alpha_blend_fast        (const bmp& front, unsigned int pos_x = 0, unsigned int pos_y = 0,
                                  const char* path_result = "blend_result.bmp");
    
    ~bmp                         ();
};

#endif //BMP_H