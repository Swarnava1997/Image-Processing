//diagonal image forming
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
int main()
{
  int i=0,j=0;
  Mat img(50,50,CV_8UC3,Scalar(0,255,255));
  for (i=0; i<50; i++)
  {
   for(j=0;j<50;j++)
    {
      if(j>i)
        img.at<Vec3b>(i,j)[1]=69;
     else
        img.at<Vec3b>(i,j)[0]=0;
    }
  }
  namedWindow ("win", WINDOW_NORMAL);
  imshow("win", img);
  waitKey(0);
}

