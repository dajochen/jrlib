class tRGB {

%TypeHeaderCode
#include "tRGB.h"
%End

  public:
    tRGB();
    tRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char al=255);


    void setColor(int r, int g, int b, int a=255);

    static tRGB MSColor(int index);
    int getMSColorIndex();

//    tVector toVector();
};