#include <iostream>
#include <cmath>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace std;
using namespace cv;

Mat img1=imread ("img1.jpeg", 0);
Mat img2=imread ("img2.jpeg", 0);
int r=img1.rows;
int c=img1.cols;
Mat temp(r,c,CV_8UC1, Scalar(0));
int t;

void callback(int , void *)
{
  int i,j;
   for(i=0;i<r;i++)
   {
     for(j=0;j<c;j++)
     {
       temp.at<uchar>(i,j)=(int)((float)img1.at<uchar>(i,j)*((100-t)/100.0)+(float)img2.at<uchar>(i,j)*(t/100.0)) ;
     }
       
   }
   imshow("win", temp);
}

int main()
{
  namedWindow ("win", WINDOW_NORMAL);
  t=0;
  createTrackbar("track","win",&t,100,callback);
  waitKey(0);
}
