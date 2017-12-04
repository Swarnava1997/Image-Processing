//scale up contrast
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
int min (int a, int b)
{
  if(a>b)
     return b;
  else 
     return a;
}
int main ()
{
  Mat img=imread("a.png",1);
  int m=img.rows;
  int n=img.cols;
  Mat tmp(m, n, CV_8UC3, Scalar(0) );
  namedWindow ("win", WINDOW_NORMAL);
  int i,j;
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        tmp.at<Vec3b>(i,j)[0]=min(img.at<Vec3b>(i,j)[0]*2,255);
        tmp.at<Vec3b>(i,j)[1]=min(img.at<Vec3b>(i,j)[1]*2,255);
        tmp.at<Vec3b>(i,j)[2]=min(img.at<Vec3b>(i,j)[2]*2,255);
      }
    }
  imshow("win", tmp);
  waitKey(0);
}
