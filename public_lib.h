#ifndef PUBLIC_LIB_H
#define PUBLIC_LIB_H

#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
#include "mytuple.h"


#include"opencv2/opencv.hpp"
#include"opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

#define PIXELB(m,y,x)  m.data[m.step[0]*y+m.step[1]*(x)]
#define PIXELG(m,y,x)  m.data[m.step[0]*y+m.step[1]*(x+1)]
#define PIXELR(m,y,x)  m.data[m.step[0]*y+m.step[1]*(x+2)]
#define PIXEL(m,y,x)   m.data[m.step[0]*y+m.step[1]*(x)]
//#define COLOR

#ifdef COLOR
const int channel[3]={0,1,2};
#else
const int channel[1]={0};
#endif

const int kernel_size=3;
const int half_kernel_size=kernel_size/2;
const int median_pos=kernel_size*kernel_size/2;

#endif // MEDIAN_CONTOUR_H

