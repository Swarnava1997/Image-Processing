//erosion and dilution
#include <iostream>
#include <cmath>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;
int min (int *a)
{
   int p, mini=999;
   for (p=0;p<9;p++)
   {
     if(a[p]<mini)
       mini=a[p];
   }
   return mini;
}

int max (int *a)
{
   int p, maxi=0;
   for (p=0;p<9;p++)
   {
     if(maxi<a[p])
       maxi=a[p];
   }
   return maxi;
}

Mat erosion (Mat img)
{
   int i,j;
   int r=img.rows;
   int c=img.cols; int a[9];
   Mat img1(img.rows,img.cols,CV_8UC1,Scalar(0));
   for(i=1;i<r;i++)
    {
      for(j=1;j<c;j++)
      {
                        a[0]=img.at<uchar>(i-1,j-1);
			a[1]=img.at<uchar>(i-1,j);
			a[2]=img.at<uchar>(i-1,j+1);
			a[3]=img.at<uchar>(i,j-1);
			a[4]=img.at<uchar>(i,j);
			a[5]=img.at<uchar>(i,j+1);
			a[6]=img.at<uchar>(i+1,j-1);
			a[7]=img.at<uchar>(i+1,j);
			a[8]=img.at<uchar>(i+1,j+1);
			
			img1.at<uchar>(i,j)=min(a);
			
	}
    }
    return img1;
}

Mat dilution (Mat img)
{
   int i,j;
   int r=img.rows;
   int c=img.cols; int a[9];
   Mat img1(img.rows,img.cols,CV_8UC1,Scalar(0));
   for(i=1;i<r;i++)
    {
      for(j=1;j<c;j++)
      {
                        a[0]=img.at<uchar>(i-1,j-1);
			a[1]=img.at<uchar>(i-1,j);
			a[2]=img.at<uchar>(i-1,j+1);
			a[3]=img.at<uchar>(i,j-1);
			a[4]=img.at<uchar>(i,j);
			a[5]=img.at<uchar>(i,j+1);
			a[6]=img.at<uchar>(i+1,j-1);
			a[7]=img.at<uchar>(i+1,j);
			a[8]=img.at<uchar>(i+1,j+1);
			
			img1.at<uchar>(i,j)=max(a);
			
	}
    }
    return img1;
}

int main()
{
   Mat img=imread("filter4.png", 0);
   int i,j;
   Mat temp=erosion (img);
   Mat temp1=dilution (temp);
   Mat temp2=dilution (temp1);
   
    namedWindow("Window",WINDOW_NORMAL);
    namedWindow("Window1",WINDOW_NORMAL);
	imshow("Window",temp2);
        imshow("Window1",img);
	waitKey(0);
}
