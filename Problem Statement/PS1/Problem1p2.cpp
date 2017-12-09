#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <limits.h>

using namespace std;
using namespace cv;


int main()
{
	srand(time(NULL));
	int i,j,k,l,c=1,a[9],d,min,b[9],e,temp,min1;
	Mat img=imread("1506626072472.jpg", 1 );
	Mat img1=img.clone();
	Mat img2(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
	Mat img3(img.rows/3,img.cols/3,CV_8UC3,Scalar(0,0,0));
	Mat img4(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));

	for(l=0;l<9;l++)
		{
			a[l]=0;
		}

	for(i=0;i<img.rows/3;i++)
	{
		for(j=0;j<img.cols/3;j++)
		{
			img2.at<Vec3b>(i,j)[0]=img1.at<Vec3b>(i,j)[0];
			img2.at<Vec3b>(i,j)[1]=img1.at<Vec3b>(i,j)[1];
			img2.at<Vec3b>(i,j)[2]=img1.at<Vec3b>(i,j)[2];
			img4.at<Vec3b>(i,j)[0]=img1.at<Vec3b>(i,j)[0];
			img4.at<Vec3b>(i,j)[1]=img1.at<Vec3b>(i,j)[1];
			img4.at<Vec3b>(i,j)[2]=img1.at<Vec3b>(i,j)[2];
		}
	}

	a[0]=1;
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
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[0]=img1.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[0];
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[1]=img1.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[1];
					img2.at<Vec3b>(((c/3)*img.rows/3)+i,((c%3)*img.cols/3)+j)[2]=img1.at<Vec3b>(((k/3)*img.rows/3)+i,((k%3)*img.cols/3)+j)[2];
				}
			}
			c++;
		}
		if(c==9)
		{
			break;
		}
	}

	c=0;
	while(1)
	{
		for(k=1;k<9;k++)
		{	
			d=0;e=0;
			for(i=0;i<img.rows/3;i++)
			{
				for(l=0;l<4;l++)
				{
					d+=abs((img4.at<Vec3b>((c/3)*img.rows/3+i,((c+1)%3)*img.cols/3-1)[l])-(img2.at<Vec3b>((k/3)*img.rows/3+i,(k%3)*img.cols/3)[l]));
				}	
			}
			a[k]=d;
			for(j=0;j<img.cols/3;j++)
			{
				for(l=0;l<4;l++)
				{
					e+=abs((img4.at<Vec3b>((c/3+1)*img.rows/3-1,((c)%3)*img.cols/3+j)[l])-(img2.at<Vec3b>((k/3)*img.rows/3,(k%3)*img.cols/3+j)[l]));		
				}
			}
			b[k]=e;
		}

		min=10000;min1=10000;
		for(i=1;i<9;i++)
		{
			if(a[i]<min)
			{
				min=a[i];
				k=i;
			}
			if(b[i]<min1)
			{
				min1=b[i];
				l=i;
			}
		}
		
		for(i=0;i<img.rows/3;i++)
		{
			for(j=0;j<img.cols/3;j++)
			{
				for(d=0;d<4;d++)
				{
					if(c!=2&&c!=5)
					{
						img4.at<Vec3b>((c/3)*img.rows/3+i,((c+1)%3)*img.cols/3+j)[d]=img2.at<Vec3b>((k/3)*img.rows/3+i,((k)%3)*img.cols/3+j)[d];
					}
					if(c!=6&&c!=7)
					{
						img4.at<Vec3b>((c/3+1)*img.rows/3+i,((c)%3)*img.cols/3+j)[d]=img2.at<Vec3b>((l/3)*img.rows/3+i,((l)%3)*img.cols/3+j)[d];
					}
				}
			}
		}
		c++;
		if(c==8)
		{
			break;
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

