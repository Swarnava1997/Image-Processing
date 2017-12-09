#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <ctime>

using namespace std;
using namespace cv;

int main()
{
	srand(time(NULL));
	int i,j,k,l,c=0,a[9];
	Mat img=imread("1506626072472.jpg", 1 );
	Mat img2(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
	Mat img3(img.rows/3,img.cols/3,CV_8UC3,Scalar(0,0,0));
	Mat img4(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

	for(l=0;l<9;l++)
		{
			a[l]=0;
		}

	while(1)
	{
		k=rand()%9;
		if(a[k]!=1)
		{
			a[k]=1;
			for(i=0;i<img.rows/3;i++)
			{
				for(j=0;j<img.cols/3;j++)
				{
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[0]=img.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[0];
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[1]=img.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[1];
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[2]=img.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[2];
				}
			}
			c++;
		}
		if(c==9)
		{
			break;
		}
	}

	for(k=0;k<9;k++)
	{
		for(i=0;i<img.rows/3;i++)
		{
			for(j=0;j<img.cols/3;j++)
			{
				img3.at<Vec3b>(i,j)[0]=img2.at<Vec3b>((k/3)*img.rows/3+i,(k%3)*img.cols/3+j)[0];
				img3.at<Vec3b>(i,j)[1]=img2.at<Vec3b>((k/3)*img.rows/3+i,(k%3)*img.cols/3+j)[1];
				img3.at<Vec3b>(i,j)[2]=img2.at<Vec3b>((k/3)*img.rows/3+i,(k%3)*img.cols/3+j)[2];
			}
		}
		Mat result(img2.rows-img3.rows+1,img2.cols-img3.cols+1,CV_8UC1,Scalar(0));
  		matchTemplate( img, img3, result, CV_TM_SQDIFF );
  		double minVal,maxVal;Point maxLoc,minLoc;
  		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc);
  		
  		for(i=0;i<img.rows/3;i++)
		{
			for(j=0;j<img.cols/3;j++)
			{
				img4.at<Vec3b>(minLoc.y+i,minLoc.x+j)[0]=img3.at<Vec3b>(i,j)[0];
				img4.at<Vec3b>(minLoc.y+i,minLoc.x+j)[1]=img3.at<Vec3b>(i,j)[1];
				img4.at<Vec3b>(minLoc.y+i,minLoc.x+j)[2]=img3.at<Vec3b>(i,j)[2];
			}
		}
	}

	
	namedWindow("win",WINDOW_AUTOSIZE);
	imshow("win",img);
	waitKey(0);
	imshow("win",img2);
	waitKey(0);
	imshow("win",img4);
	waitKey(0);
	return 0;
}
