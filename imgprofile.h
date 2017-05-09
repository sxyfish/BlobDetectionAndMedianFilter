#ifndef IMGPROFILE_H
#define IMGPROFILE_H

#include "public_lib.h"

class ImgProfile
{

public:
    ImgProfile(const string &name);
    ImgProfile(const ImgProfile& img,const string& name);


    void ShowImg();
    void TransformImg();
    Mat GetBinaryAuxiMat();
    void SetOnePixel(int y, int x, vector<int> s);
    vector<int> GetOnePixel(int y, int x);
    uchar GetBinaryOnePixel(int y,int x);
    void CountAndShowBlob();
    void PrintMat();
    Mat getPixel_mat() const;

private:
    const string& img_name;
    Mat pixel_mat;
    int read_img();
    void copy_one_pixel(Mat &d, const Mat& s, int yd, int xd, int y, int x);
//    Mat get_gray_mat();
    Mat get_binary_mat();
    void show_blob_num(int b);

};

#endif // IMGPROFILE_H
