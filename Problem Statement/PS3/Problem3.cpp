#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/core/core.hpp>

#include <math.h>

#include <iostream>


using namespace cv;

using namespace std;


int thresh=200;

RNG rng(12345);

Mat imgHSV,imgThresholded,imgInput,imgFlip,imgCanny,imgFinal,imgFinal1,imgFinal_gray;


void Center(Mat img1,int arr[2])

{

    int i,j,c=0;

    Vec<unsigned char,3> def=(0,0,0);

    for(i=0;i<img1.rows;i++)

    {

        for(j=0;j<img1.cols;j++)

        {

            if(img1.at<Vec3b>(i,j)==def)

            {

                arr[0]+=i;

                arr[1]+=j;

                c++;

            }

        }

    }

    arr[0]/=c;

    arr[1]/=c;

}


void kernel(Mat img,int arr[2])

{

    int a=arr[0],b=arr[1];

    int i,j;

    for(i=a-1;i<=a+1;i++)

    {

        for(j=b-1;j<=b+1;j++)

            img.at<Vec3b>(i,j)[2]=255;

    }

}


void lines(Mat img,int pt1[2],int pt2[2])

{

    int a = pt2[1]-pt1[1];

    int b = pt2[0]-pt1[0];

    double slope;

    if(b!=0)

    {

        slope=atan(a/b);

    }

    

    double dist = sqrt(pow(a,2)+pow(b,2));

    int x,y,i;

    for(i=0;i<=dist;i++)

    {

        x=(int)(pt1[0]+i*cos(slope*3.14/180));

        y=(int)(pt1[1]+i*sin(slope*3.14/180));

        img.at<Vec3b>(x,y)[2]=255;

        img.at<Vec3b>(x,y)[1]=255;

        img.at<Vec3b>(x,y)[0]=255;

    }

}


void Bright(Mat img)

{

    int i,j;

    for(i=0;i<img.rows;i++)

    {

        for(j=0;j<img.cols;j++)

        {

            if(img.at<Vec3b>(i,j)[2]>0||img.at<Vec3b>(i,j)[1]>0||img.at<Vec3b>(i,j)[0]>0)

            {

                img.at<Vec3b>(i,j)[2]=255;

                img.at<Vec3b>(i,j)[1]=255;

                img.at<Vec3b>(i,j)[0]=255;

            }

        }

    }

}


int cornerHarris_demo(int,void*)

{

    Mat dst_norm,dst_norm_scaled;

    Mat dst(imgFinal.rows,imgFinal.cols,CV_32FC1);

    int blockSize=2;

    int apertureSize=3;

    int count=0;

    double k=0.04;

    cornerHarris(imgFinal_gray,dst,blockSize,apertureSize,k,BORDER_DEFAULT) ;

    normalize(dst,dst_norm,0,255,NORM_MINMAX,CV_32FC1,Mat()) ;

    convertScaleAbs(dst_norm,dst_norm_scaled);

    for(int j=0;j<dst_norm.rows;j++)

    {

        for(int i=0;i<dst_norm.cols;i++)

        {

            if((int)dst_norm.at<float>(j,i)>thresh)

            {

                count++;

            }

        }

    }

    return count;

}


int main()

{

    

    VideoCapture cap(0);

    cap.read(imgInput);

    Mat imgLocus(imgInput.rows,imgInput.cols,CV_8UC3,Scalar(0,0,0));

    namedWindow("window",WINDOW_AUTOSIZE);

    namedWindow("window2",WINDOW_AUTOSIZE);

    namedWindow("window3",WINDOW_AUTOSIZE);

    int lower_blue[3],upper_blue[3];

    int LowH = 0;

    int HighH = 255;

    int LowS = 0; 

    int HighS = 140;

    int LowV = 0;

    int HighV = 255;

    int prev[2],next[2];

    next[0]=0;

    next[1]=0;

    int i,j,def;

    /*createTrackbar("LowH","window",&LowH,255);

    createTrackbar("HighH","window",&HighH,255);

    createTrackbar("LowS","window",&LowS,255);

    createTrackbar("HighS","window",&HighS,255);

    createTrackbar("LowV","window",&LowV,255);

    createTrackbar("HighV","window",&HighV,255);*/

    while(1)

    {

        cap.read(imgInput);

        cvtColor(imgInput,imgHSV,COLOR_BGR2HSV);

        inRange(imgHSV, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), imgThresholded);

        erode(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE,Size(5,5)) );

        dilate(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE,Size(5,5)) ); 

        dilate(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE,Size(5,5)) ); 

        erode(imgThresholded,imgThresholded,getStructuringElement(MORPH_ELLIPSE,Size(5,5)) );

        flip(imgThresholded,imgFlip,1);

        prev[0]=next[0];

        prev[1]=next[1];

        Center(imgFlip,next);

        imgLocus.at<Vec3b>(next[0],next[1])[2]=255;

        imgLocus.at<Vec3b>(next[0],next[1])[1]=255;

        imgLocus.at<Vec3b>(next[0],next[1])[0]=255;

        lines(imgLocus,next,prev);

        GaussianBlur(imgLocus,imgFinal1,Size(3,3),0,0);

        Bright(imgFinal1);

        GaussianBlur(imgFinal1,imgFinal1,Size(3,3),0,0);

        Bright(imgFinal1);

        GaussianBlur(imgFinal1,imgFinal1,Size(3,3),0,0);

        imshow("window3",imgFinal1);

        imshow("window2",imgLocus);

        imshow("window",imgFlip);

        if(waitKey(27)>=30)

        {

            break;

        }

    }    

    vector<vector<Point> > contours;

    vector<Vec4i> hierarchy;

    erode(imgFinal1,imgFinal1,getStructuringElement(MORPH_ELLIPSE,Size(5,5)));

    Bright(imgFinal1);

    GaussianBlur(imgFinal1,imgFinal1,Size(3,3),0,0);

    Canny(imgFinal1,imgFinal,0,255,3);

    findContours(imgFinal,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(imgFinal.size(),CV_8UC3);

    for(i=0;i<contours.size();i++)

    {

        Scalar color=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));

        drawContours(drawing,contours,i,color,2,8,hierarchy,0,Point());

    }

    imshow("window",imgFinal);

    int k=cornerHarris_demo(0,0);

    switch(k)

    {

        case 0: cout<<"Circle";

            break;

        case 1: cout<<"Point";

            break; 

        case 2: cout<<"Line";

            break;

        case 3: cout<<"Triangle";

            break;

        case 4: cout<<"Square";

            break;

        case 5: cout<<"Pentagon";

            break;

    }

waitKey(0);

return 0;

}
