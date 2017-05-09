#ifndef BLOBDETECTION_H
#define BLOBDETECTION_H

#include "public_lib.h"
#include "imgprofile.h"

class BlobDetection
{
public:
    BlobDetection(ImgProfile &im);
    ~BlobDetection();
    void CountAndShowBlob();

private:
    ImgProfile& img;
    void show_blob_num(int b);


};

#endif // BLOBDETECTION_H
