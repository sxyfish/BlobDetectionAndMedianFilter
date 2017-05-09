#include "quicksortmedian.h"

QuickSortMedian::QuickSortMedian(ImgProfile& img):in_img(img)
{

    /*
    for(int i:channel)
        sliding_vector[i]={0};
        */
   vector< list<int> > tmp(1);
   sliding_vector=tmp;

}

void QuickSortMedian::ShowMedianImg()
{

    in_img.TransformImg();
    Mat m=in_img.getPixel_mat();
//    for(int y=1;y<m.rows-1;y++)
    for(int y=1;y<200;y++)
    {

        init_firstcol(y);
        get_median();
        set_median(y,1);
        for(int x=2;x<m.cols-1;x++)
        {
            sliding(y,x);
            get_median();
            set_median(y,x);
        }

    }
    Rect rec(1,1,(m.cols-2),(m.rows-2));
    Mat out=m(rec);
    namedWindow("filtered img");
    imshow("filtered img",out);
    waitKey(0);

}

void QuickSortMedian::init_firstcol(int row)
{

//    for(int y=row-half_kernel_size;y<=row+half_kernel_size;y++)
//        for(int x=0;x<kernel_size;x++)
//            push_one_pixel(y,x);
    for(int x=0;x<kernel_size;x++)
       for(int y=row-half_kernel_size;y<=row+half_kernel_size;y++)
            push_one_pixel(y,x);
}



void QuickSortMedian::sliding(int yidx,int xidx)
{

    for(int y=yidx-half_kernel_size;y<=yidx+half_kernel_size;y++)
    {
        pop_one_pixel();
        push_one_pixel(y,xidx+1);
    }

}

void QuickSortMedian::push_one_pixel(int y, int x)
{
    for(int i:channel)
        sliding_vector[i].push_back(in_img.GetOnePixel(y,x)[i]);
}

void QuickSortMedian::pop_one_pixel( )
{

    for(int i:channel)
        sliding_vector[i].pop_front();
}

vector<int> QuickSortMedian::get_median( )
{
    vector<int> ms(1);

    for(int i:channel)
    {
        sliding_vector[i].sort();
        list<int>::iterator itr=sliding_vector[i].begin();
        advance(itr,median_pos);
        ms[i] = *itr;
    }

    return ms;

}

void QuickSortMedian::set_median(int yidx,int xidx)
{
    vector<int> s=get_median();
    in_img.SetOnePixel(yidx,xidx,s);
}



