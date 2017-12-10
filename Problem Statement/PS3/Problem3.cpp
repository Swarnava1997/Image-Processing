#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <cstdio>
#include <cstdlib>

using namespace cv;
using namespace std;

Mat img,imgHSV,imgThresholded,trajectory,dst,dst_norm,dst_norm_scaled;
Mat canny;
vector< vector<Point> > contours;
vector<Vec4i> heirarchy;
long long int xc=0,yc=0,n=0,pxc,pyc;
int corner=0;
Point p1,p2,pt;
Point stack[10000000];
int top=-1;


int main( int argc, char** argv )
 {
    VideoCapture vid(argv[1]);   // rectangle.mp4 triangle.mp4 circle.mp4

    int iLowH = 9;
    int iHighH = 55;

    int iLowS = 102; 
    int iHighS = 255;

    int iLowV = 40;
    int iHighV = 255;

    int f=0,a=0;
    namedWindow("window",WINDOW_NORMAL);
    namedWindow("tracked",WINDOW_NORMAL);

    while (1)
    {

        if(!(vid.read(img)))break;
        if(f==0)
        {
            trajectory=Mat::zeros(img.rows,img.cols,CV_8UC1);
            f=1;
        }

        imshow("window",img);
        cvtColor(img, imgHSV, COLOR_BGR2HSV);
        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
        erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
        medianBlur(imgThresholded,imgThresholded,3);

        img=imgThresholded.clone();
        for(int i=0;i<img.rows;i++)
        {
            for(int j=0;j<img.cols;j++)
            {
                if(img.at<uchar>(i,j)>200)
                {
                    xc=xc+j;
                    yc=yc+i;
                    n++;
                }
            }
        }
        if(n==0)continue;
        xc=xc/n;
        yc=yc/n;
        if(a==0)
        {
            pxc=xc;
            pyc=yc;
            a=1;
            continue;
        }
        for(int i=-4;i<5;i++)
        {
            for(int j=-4;j<5;j++)
            {
                line(trajectory,Point(pxc,pyc),Point(xc,yc),Scalar(255),10,8,0);
            }
        }
        pxc=xc;pyc=yc;
        xc=yc=n=0;
        imshow("tracked",img);
        waitKey(1);

    }

    cornerHarris( trajectory, dst, 15, 3, 0.04, BORDER_DEFAULT );

    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );

    for( int j = 0; j < dst_norm.rows ; j++ )
    { for( int i = 0; i < dst_norm.cols; i++ )
        {
          if( (int) dst_norm.at<float>(j,i) > 240 )
            {
              corner++;
            }
        }
    }

    namedWindow("corner",WINDOW_NORMAL);
    imshow("corner",dst_norm_scaled);
    if(corner==3)cout<<"\nIt looks like a triangle!\n";
    else if(corner==4)cout<<"\nIt looks like a rectangle!\n";
    else if(corner<=1 || corner>=6)cout<<"\nIt looks like a circle!\n";
    else printf("\nI don't know\n");

    waitKey(0);  
    return 0;
}
