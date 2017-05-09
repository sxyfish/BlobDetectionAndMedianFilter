#include<public_lib.h>

vector<int> mask_vector;
void PrintMat(Mat &m, int r, int c, string s)
{
    cout<<"#################################################"<<endl;
    cout<<"PRINT THE SELECTED MAT:"<<s<<endl;
    cout<<"#################################################"<<endl;

    cout<<"          ";
    for(int i=0;i<c;i++)
    {
        if(i<10)
            cout<<0<<i<<" ";
        else
            cout<<i<<" ";
        if(i%c==0 && i!=0)
            cout<<endl;
    }
    cout<<endl;

    for(int y=0;y<r;y++)
    {
        if(y<10)
            cout<<"row: "<<0<<y<<"----";
        else
            cout<<"row: "<<y<<"----";

        for(int x=0;x<c;x++)
        {
            cout<<(int)PIXEL(m,y,x)<<" ";
        }
        cout<<endl;
    }

}
void copy_one_pixel(Mat &d, const Mat &s, int yd,int xd,int ys, int xs)
{

    PIXEL(d,yd,xd)=PIXELB(s,ys,xs);

}
void TransformImg(Mat& pixel_mat)
{
    int r=pixel_mat.rows;
    int c=pixel_mat.cols;

    int nr=r+2;
    int nc=c+2;

    Mat tmp(nr,nc,CV_8U,Scalar(0,0,0));


    for(int x=1;x<nc-1;x++)
    {

        copy_one_pixel(tmp,pixel_mat,0,x,0,x-1);
        copy_one_pixel(tmp,pixel_mat,nr-1,x,r-1,x-1);
    }
    //PrintMat(tmp,nr,nc,"tmp");
    //PrintMat(pixel_mat,r,c,"original");

    for(int y=1;y<nr-1;y++)
    {
        copy_one_pixel(tmp,pixel_mat,y,0,y-1,0);
        copy_one_pixel(tmp,pixel_mat,y,nc-1,y-1,c-1);
    }

    copy_one_pixel(tmp,pixel_mat,0,0,0,0);
    copy_one_pixel(tmp,pixel_mat,nr-1,0,r-1,0);
    copy_one_pixel(tmp,pixel_mat,0,nc-1,0,c-1);
    copy_one_pixel(tmp,pixel_mat,nr-1,nc-1,r-1,c-1);

    for(int y=1;y<nr-1;y++)
        for(int x=1;x<nc-1;x++)
        {
            copy_one_pixel(tmp,pixel_mat,y,x,y-1,x-1);
        }

    pixel_mat=tmp.clone();
    //PrintMat(pixel_mat,pixel_mat.rows,pixel_mat.cols,"transformed");
}


void set_mask_vector(Mat& im,int yidx, int xidx)
{

    int w=half_kernel_size;
    mask_vector.clear();
    for(int y=yidx-w;y<=yidx+w;y++)
        for(int x=xidx-w;x<=xidx+w;x++)
            mask_vector.push_back(PIXEL(im,y,x));

}

int get_median()
{
    vector<int>::iterator b=mask_vector.begin();
    nth_element(b,b+median_pos,mask_vector.end());
    return mask_vector[median_pos];


    //sort(mask_vector.begin(),mask_vector.end());
    //return mask_vector[median_pos];

}

void set_median(Mat& m,int yidx, int xidx)
{
    int s=get_median();
    PIXEL(m,yidx,xidx)=s;
    //out_img.SetGrayOnePixel(yidx,xidx,m);
}
void SortAndShowFilteredImg(Mat& im)
{
    TransformImg(im);
    //in_img.ShowImg();

    Mat tmp=Mat(im.size(),CV_8U);
    tmp=im.clone();

    Mat out(im.size(),CV_8U,Scalar(0));


    //PrintMat(tmp,tmp.rows,tmp.cols,"original mat");

    for(int y=1;y<im.rows-1;y++)
        for(int x=1;x<im.cols-1;x++)
        {
//            cout<<"y="<<y<<","<<"x="<<x<<endl;

            set_mask_vector(im,y,x);
            set_median(out,y,x);
//            PrintMat(tmp,6,6,"tmp");
//            PrintMat(out,6,6,"out");

        }

    Rect rec(1,1,(im.cols-2),(im.rows-2));
    Mat outmat=out(rec);
    namedWindow("filtered img");
    imshow("filtered img",outmat);
    waitKey(0);
}
