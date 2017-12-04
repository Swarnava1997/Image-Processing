//scale down a image(half)
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
int main ()
{
  Mat img=imread("a.png",0);
  int m=img.rows;
  int n=img.cols;
  Mat tmp(m/2+1, n/2+1, CV_8UC1, Scalar(0) );
  namedWindow ("win", WINDOW_NORMAL);
  int i,j;
  int a,b,c,d;
  for(i=0;i<m/2+1;i++)
    {
      for(j=0;j<n/2+1;j++)
      {
          a=img.at<uchar>(i*2,j*2);
          b=img.at<uchar>(i*2,j*2+1);
          c=img.at<uchar>(i*2+1,j*2);
          d=img.at<uchar>(i*2+1,j*2+1);
          tmp.at<uchar>(i,j)=(a+b+c+d)/4;
      }
    }
  imshow("win", tmp);
  waitKey(0);
}
