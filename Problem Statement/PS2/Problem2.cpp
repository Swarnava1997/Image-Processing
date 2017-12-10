#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "noise.cpp"
#include "bfs.cpp"

using namespace cv;
using namespace std;

Mat img; 
Mat img1;
Mat img2;
int thresh = 140;
int max_thresh = 255;
RNG rng(12345);
int score=0;

void thresh_callback(int, void* );

int main( int argc, char** argv )
{
  int i,j;
  VideoCapture vid("PS 2.mp4");

  int k=180;

  while(1)
  {

  vid.read(img);
  Mat img3(img.rows,img.cols,CV_8UC1,Scalar(0));
  cvtColor( img, img2, CV_BGR2HSV );
  int sumx, sumy, count;
  sumx=sumy=count=0;
  namedWindow( "win", WINDOW_AUTOSIZE );
  namedWindow( "win1", WINDOW_AUTOSIZE );
  namedWindow( "win0", WINDOW_AUTOSIZE );
  for(i=0;i<img2.rows;i++)
  {
    for(j=0;j<img2.cols;j++)
    {
      if((img.at<Vec3b>(i,j)[2]>=180 && img.at<Vec3b>(i,j)[2]<=210 && img.at<Vec3b>(i,j)[0]>=140 && img.at<Vec3b>(i,j)[0]<=180) || (img.at<Vec3b>(i,j)[2]>=150 && img.at<Vec3b>(i,j)[2]<=180 && img.at<Vec3b>(i,j)[0]>=110 && img.at<Vec3b>(i,j)[0]<=150))
        {
          img3.at<uchar>(i,j)=255;
          sumx+=sumx;
          sumy+=sumy;
          count++;
        }
    }
  }
  Mat img4(img.rows,img.cols,CV_8UC1,Scalar(0));
  int x,y;

  x=(int)(sumx/count);
  y=(int)(sumy/count);

  img4.at<uchar>(x,y)=255;



  for(i=0;i<img2.rows;i++)
  {
    for(j=0;j<img2.cols;j++)
    {
      if(img4.at<uchar>(i,j)==255)
        {
          if((i<=850 && i>=800 && j<=550 && j>=500) || (i<=800 && i>=750 && j<=70 && j>=15))
            score+=30;

          if((i<=770 && i>=700 && j<=200 && j>=150) || (i<=470 && i>=400 && j<=240 && j>=180) || (i<=620 && i>=560 && j<=480 && j>=410))
            score+=40;
        }
    }
  }
  imshow("win", img3 );
  imshow("win1", img4 );
  imshow("win0", img );
  waitKey(10);
  } 

  printf("\n If Square= 40 and Triangle= 30 ==> Score-->%d\n",score);
  return(0);
}

