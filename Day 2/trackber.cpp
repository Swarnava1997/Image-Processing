//testing trackber
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
Mat img=imread("pic2.jpeg",0);
int r=img.rows;
int c=img.cols;
Mat tmp(r, c, CV_8UC1, Scalar(0) );
int t;

void callback(int , void *)
{
  int i,j;

    for(i=0;i<r;i++)
    {
      for(j=0;j<c;j++)
      {
        int p=img.at<uchar>(i,j);
        if(p>t)
          tmp.at<uchar>(i,j)=255;
        else
          tmp.at<uchar>(i,j)=0;
      }
    } 
      imshow("win", tmp);
}

int main()
{
  namedWindow ("win", WINDOW_NORMAL);
  t=0;
  createTrackbar("track","win",&t,255,callback);
/*  for(i=0;i<r;i++)
    {
      for(j=0;j<c;j++)
      {
        int t=img.at<uchar>(i,j);
        if(t>127)
          img.at<uchar>(i,j)=255;
        else
          img.at<uchar>(i,j)=0;
      }
    }  */
  waitKey(0);
}
