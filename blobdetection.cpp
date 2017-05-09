#include "blobdetection.h"

BlobDetection::BlobDetection(ImgProfile& im):img(im)
{

}

void BlobDetection::CountAndShowBlob()
{
    int nb=0;
    Mat m=img.GetBinaryAuxiMat();
    vector< vector<MyTuple> > blob_set;
    vector< vector<int> > auximat(m.rows,vector<int>(m.cols,-1));
    int counter=-1;

    for(int y=1;y<m.rows-1;y++)
        for(int x=1;x<m.cols-1;x++)
        {

            int i=PIXEL(m,y,x);
            int left=PIXEL(m,y,x-1);
            int upper=PIXEL(m,y-1,x);

            if(i!=0)
            {
                if( (left !=0) || (upper!= 0) )
                {
                    int left_set=auximat[y][x-1];
                    int upper_set=auximat[y-1][x];
                    if( (left_set!=-1) && (upper_set!=-1))
                    {
                        for(MyTuple t:blob_set[left_set])
                            blob_set[upper_set].push_back(t);

                        blob_set[left_set].clear();

                    }
                    else {
                        int s=(left_set==-1 ? upper_set : left_set);
                        blob_set[s].push_back(MyTuple(y,x));
                        auximat[y][x]=s;
                    }
                }
                else {
                    counter+=1;
                    blob_set[counter].push_back(MyTuple(y,x));
                    auximat[y][x]=counter;
                }

            }

        }
    for(vector<MyTuple> v:blob_set)
    {
        if(! v.empty())
            nb++;
    }
    show_blob_num(nb);

}

void BlobDetection::show_blob_num(int b)
{
    char text[20];
    sprintf(text,"%d",b);
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;
    Point textOrg(10, 30);
    putText(img.getPixel_mat(), text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
    img.ShowImg();
}
