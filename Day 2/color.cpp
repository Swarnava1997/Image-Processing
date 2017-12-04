//color to black & white
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
int main()
{
  Mat img=imread("a.png",1);
  namedWindow ("win", WINDOW_NORMAL);
  int r=img.rows;
  int c=img.cols;
  int i,j;
  Mat tmp(r, c, CV_8UC1, Scalar(0) );
   for(i=0;i<r;i++)
    {
      for(j=0;j<c;j++)
      {
        tmp.at<uchar>(i,j)=(img.at<Vec3b>(i,j)[0]+img.at<Vec3b>(i,j)[1]+img.at<Vec3b>(i,j)[2])/3;
      }
    } 
  imshow("win", tmp);
  waitKey(0);
}
