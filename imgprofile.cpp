#include "imgprofile.h"


ImgProfile::ImgProfile(const string& name):img_name(name)
{

    read_img();
    //cout<<"img_name:   "<<img_name<<endl;
    //cout<<"size:  "<<pixel_mat.size()<<endl;
    cout<<"original constructor: "<<endl;
    cout<<"img_name:   "<<img_name<<endl;
    cout<<"size:  "<<pixel_mat.size()<<endl;
    cout<<"one pixel:  "<<PIXEL(pixel_mat,1,1)<<endl;


}

ImgProfile::ImgProfile(const ImgProfile &img, const string &name):img_name(name)
{
#ifdef COLOR
    pixel_mat(img.pixel_mat.size(),CV_8UC3,Scalar(0,0,0));
#else
    pixel_mat=Mat(img.pixel_mat.rows,img.pixel_mat.cols,CV_8U,Scalar(0));
#endif
    pixel_mat=img.pixel_mat.clone();

    cout<<"before copy: "<<endl;
    cout<<"img_name:   "<<img.img_name<<endl;
    cout<<"size:  "<<img.pixel_mat.size()<<endl;
    cout<<"rows:  "<<img.pixel_mat.rows<<endl;
    cout<<"cols:  "<<img.pixel_mat.cols<<endl;
    //cout<<"one pixel:  "<<PIXEL(img.pixel_mat,0,0)<<endl;

    cout<<"after copy: "<<endl;
    cout<<"img_name:   "<<img_name<<endl;
    cout<<"size:  "<<pixel_mat.size()<<endl;
    cout<<"rows:  "<<pixel_mat.rows<<endl;
    cout<<"cols:  "<<pixel_mat.cols<<endl;
    //cout<<"one pixel:  "<<PIXEL(pixel_mat,0,0)<<endl;

    //for(int x=0;x<pixel_mat.cols;x++)
    //    cout<<PIXEL(pixel_mat,0,x)<<"   ";
    //pixel_mat.create(img.pixel_mat.size(),CV_8UC3);
}

int ImgProfile::read_img()
{

#ifdef COLOR
    pixel_mat = imread(img_name, CV_LOAD_IMAGE_COLOR);
#else
    pixel_mat = imread(img_name,0);
#endif // COLOR
    if(! pixel_mat.data)
    {

            cout<<"*****************************"<<endl;
            cout <<  "Could not open or find the image" << endl;
            cout<<"*****************************"<<endl;
            return -1;

    }
    else
    {
        cout<<"*****************************"<<endl;
        cout <<  "Open the image Successfully!" << endl;
        cout<<"*****************************"<<endl;
        return 0;
    }
}

void ImgProfile::ShowImg()
{
    namedWindow(img_name);
    //cout<<"img_name:   "<<img_name<<endl;
    imshow(img_name,pixel_mat);
    waitKey(0);
}

void ImgProfile::TransformImg()
{
    int r=pixel_mat.rows;
    int c=pixel_mat.cols;

    int nr=r+2;
    int nc=c+2;

#ifdef COLOR
    Mat tmp(nr,nc,CV_8UC3);
#else
    Mat tmp(nr,nc,CV_8U);
#endif // COLOR

    for(int x=1;x<nc-1;x++)
    {
        copy_one_pixel(tmp,pixel_mat,0,x,0,x-1);
        copy_one_pixel(tmp,pixel_mat,nr-1,x,r-1,x-1);
    }
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
}

Mat ImgProfile::GetBinaryAuxiMat()
{
    int r=pixel_mat.rows;
    int c=pixel_mat.cols;

    int nr=r+2;
    int nc=c+2;

    Mat binary=get_binary_mat();
    Mat tmp(nr,nc,CV_8U,Scalar(0));
    for(int y=0;y<r;y++)
        binary.row(y).copyTo(tmp.row(y+1));
    return tmp;
}

void ImgProfile::SetOnePixel(int y, int x, vector<int> s)
{
#ifdef COLOR
    PIXELB(pixel_mat,y,x)=s[0];
    PIXELG(pixel_mat,y,x)=s[1];
    PIXELR(pixel_mat,y,x)=s[2];
#else
    PIXEL(pixel_mat,y,x)=s[0];
#endif // COLOR
}

vector<int> ImgProfile::GetOnePixel(int y, int x)
{
    vector<int> tmp(1);
#ifdef COLOR
    tmp[0]=PIXELB(pixel_mat,y,x);
    tmp[1]=PIXELG(pixel_mat,y,x);
    tmp[2]=PIXELR(pixel_mat,y,x);
#else
    tmp[0]=PIXEL(pixel_mat,y,x);
#endif // COLOR
    return tmp;
}

uchar ImgProfile::GetBinaryOnePixel(int y, int x)
{
    uchar i=PIXELB(pixel_mat,y,x);
    return i;
}

void ImgProfile::CountAndShowBlob()
{
    int nb=0;
    Mat m=GetBinaryAuxiMat();
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
                vector<int> pv;
                pv.push_back(PIXEL(m,y-1,x-1));
                pv.push_back(PIXEL(m,y-1,x));
                pv.push_back(PIXEL(m,y-1,x+1));
                pv.push_back(PIXEL(m,y,x-1));
                int first_set=-1;
                int second_set=-1;
                for(int p:pv)
                {
                    if(p!=0)
                        first_set=auximat[]
                }
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




/*
Mat ImgProfile::get_gray_mat()
{
    Mat tmp;
    tmp.create(pixel_mat.size(),CV_8U);
    cvtColor(pixel_mat,tmp,CV_BGR2GRAY);
    return tmp;
}
*/

Mat ImgProfile::get_binary_mat()
{
    Mat tmp1,tmp2;
    tmp1.create(pixel_mat.size(),CV_8U);
//    cvtColor(pixel_mat,tmp1,CV_BGR2GRAY);
    threshold(tmp1,tmp2,128,255,THRESH_BINARY);
    return tmp2;
}

void ImgProfile::show_blob_num(int b)
{
    char text[20];
    sprintf(text,"%d",b);
    int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
    double fontScale = 2;
    int thickness = 3;
    Point textOrg(10, 30);
    putText(pixel_mat, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness,8);
    ShowImg();
}

void ImgProfile::PrintMat()
{
    for(int y=0;y<pixel_mat.rows;y++)
        for(int x=0;x<pixel_mat.cols;x++)
        {
            cout<<PIXEL(pixel_mat,y,x)<<"  "<<endl;
        }
}

Mat ImgProfile::getPixel_mat() const
{
    return pixel_mat;
}

void ImgProfile::copy_one_pixel(Mat &d, const Mat &s, int yd,int xd,int ys, int xs)
{
#ifdef COLOR
    PIXELB(d,yd,xd)=PIXELB(s,ys,xs);
    PIXELG(d,yd,xd)=PIXELG(s,ys,xs);
    PIXELR(d,yd,xd)=PIXELR(s,ys,xs);
#else
    PIXEL(d,yd,xd)=PIXELB(s,ys,xs);
#endif // COLOR
}




//using the raw pointer of the Mat data,maybe the efficient way to access pixels
//void ImgProfile::copy_mat(const Mat &m)
//{
//    for(int y=0;y<m.rows;y++)
//    {
//        uchar* pixel=m.ptr<uchar>(y);
//        uchar* pixel_this=pixel_mat.ptr<uchar>(y);
//        for(int x=0;x<m.cols;x++)
//        {
//            pixel_this[x][0]=pixel[x][0];
//            pixel_this[x][1]=pixel[x][1];
//            pixel_this[x][2]=pixel[x][2];
//            pixel+=3;
//            pixel_this+=3;
//        }
//}
