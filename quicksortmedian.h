#ifndef QUICKSORTMEDIAN_H
#define QUICKSORTMEDIAN_H

#include "public_lib.h"
#include "imgprofile.h"

class  QuickSortMedian
{
public:
     QuickSortMedian(ImgProfile& img);

     void ShowMedianImg();

private:

     void init_firstcol(int row);
     vector<int>  get_median();
     void set_median(int yidx, int xidx);
     void sliding(int yidx, int xidx);
     void push_one_pixel(int y, int x);
     void pop_one_pixel();


     vector<list<int>> sliding_vector;
     ImgProfile& in_img;

};

#endif // QUICKSORTMEDIAN_H
