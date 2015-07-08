#ifndef TRGB_H_
#define TRGB_H_

#include "classes/tVector.h"
class tRGB {

	public:
		unsigned char red,green,blue,alpha;

		tRGB(void){
			red = 0;
			green = 0;
			blue = 0;
			alpha = 255;
    }

		tRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char al=255){
			red = r;
			green = g;
			blue = b;
			alpha = al;
    }

		static tRGB MSColor(int index){
			index = index % 16;
			tRGB msColor[] = {tRGB(0,0,0), tRGB(0,0,128),  tRGB(0,128,0),  tRGB(0,  128,128),
												tRGB(128,0,0), tRGB(128,0,128),tRGB(128,128,0),tRGB(128,128,128),
												tRGB(64,64,64),tRGB(64,64,128),tRGB(0,255,0),  tRGB(0,0,255),
												tRGB(255,0,0),tRGB(255,0,255),tRGB(255,255,0),tRGB(255,255,255)};
			return msColor[index%16];

		}
//		static tRGB setToMSColor(int index){
//
//			red = MSColor[index%16].red;
//			green = MSColor[index%16].green;
//			blue = MSColor[index%16].blue;
//		};

    void setColor(int r, int g, int b, int a=255){
      red = r;
      green = g;
      blue = b;
      alpha = a;
    }

		int getMSColorIndex(void){
			int msColor,i;
      tRGB cMS;
			tVector x;
			tReal r;
			x.x = red;
			x.y = green;
			x.z = blue;

      r = 256.*256.*3.;
      msColor = 0;
      for (i=0;i<16;i++){
        cMS = MSColor(i);
        if (r > (x-cMS.toVector()).length_squared()){
          r = (x-cMS.toVector()).length_squared();
          msColor = i;
        }
      }
			return msColor;
    }

    tVector toVector(void){
      return tVector(red,green,blue);
    }

		tRGB operator = (tRGB C){
	    red = C.red;
	    green = C.green;
	    blue = C.blue;
	    alpha = C.alpha;
	    return *this;
    }

    tRGB operator = (tVector C){
      red = (unsigned char)C.x;
      green = (unsigned char)C.y;
      blue = (unsigned char)C.z;
      return *this;
    }

    bool operator == (const tRGB& C) const
    {
      return (red == C.red && green == C.green && blue == C.blue && alpha == C.alpha);
    }

    bool operator != (const tRGB& C) const
    {
      return !(*this == C);
    }
};


#endif /*TRGB_H_*/
