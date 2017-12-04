//testing trackber
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
Mat img=imread("a.png",1);
int m=img.rows;
int n=img.cols;
Mat tmp(m, n, CV_8UC3, Scalar(0,0,0) );
int r1=0,r2=0,g1=0,g2=0,b1=0,b2=0;

void callback (int , void *)
{
  int i,j;
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
         int b=img.at<Vec3b>(i,j)[0];
         int g=img.at<Vec3b>(i,j)[1];
         int r=img.at<Vec3b>(i,j)[2];
         if(b>=b1 && b<=b2 && g>=g1 && g<=g2 && r>=r1 && r<=r2)
            tmp.at<Vec3b>(i,j)=img.at<Vec3b>(i,j);
         else
            tmp.at<Vec3b>(i,j)=(0,0,0);
      }
    }
 imshow("win", tmp);
}

int main()
{
  namedWindow ("win", WINDOW_NORMAL);
  createTrackbar("RL","win",&r1,255,callback);
  createTrackbar("RH","win",&r2,255,callback);
  createTrackbar("GL","win",&g1,255,callback);
  createTrackbar("GH","win",&g2,255,callback);
  createTrackbar("BL","win",&b1,255,callback);
  createTrackbar("BH","win",&b2,255,callback);
  /*for(i=0;i<r;i++)
    {
      for(j=0;j<c;j++)
      {
         if(b>=b1 && b<=b2)
            img.at<Vec3b>(i,j)=tmp.at<Vec3b>(i,j);
         else
            tmp.at<Vec3b>(i,j)[0]=0;
            
         if(g>=g1 && g<=g2)
            img.at<Vec3b>(i,j)=tmp.at<Vec3b>(i,j);
         else
            tmp.at<Vec3b>(i,j)[1]=0;
            
         if(r>=r1 && r<=r2)
            img.at<Vec3b>(i,j)=tmp.at<Vec3b>(i,j);
         else
            tmp.at<Vec3b>(i,j)[2]=0;
      }
    }  */
  waitKey(0);
}
