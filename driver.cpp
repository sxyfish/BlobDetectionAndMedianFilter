
#include "public_lib.h"
#include "imgprofile.h"
#include "medianfilter.h"




int main(int argc,char* argv[])
{
    /*
    if(argc!=2)
    {
        cout<<"need the image's name!"<<endl;
        exit(0);
    }

    char* name=argv[1];
    */

    //string name="saltandpepper_1.jpg";
    string name="bolts_nuts_1.jpg";
    string sn(name);
    cout<<"original file name is:"<<sn<<endl;
    ImgProfile in_img(sn);
//    in_img.ShowImg();
//    ImgProfile median_out(in_img,"median");
//    QuickSortMedian qsm(median_out);
//    qsm.ShowMedianImg();


//    median_out.ShowImg();
    ImgProfile blob_out(in_img,"blob");
//    blob_out.ShowImg();

    blob_out.CountAndShowBlob();
//    bt.CountAndShowBlob();

}

