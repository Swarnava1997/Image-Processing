#include<iostream>
#include<algorithm>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int median(int *a)
{
	sort(a,a+9);
	return a[4];
}
int main()
{
	int a[9];
	Mat img=imread("veg.jpg",0);
	Mat img1(img.rows,img.cols,CV_8UC1,Scalar(0));
	for(int i=1;i<img.rows-1;i++)
	{
		for(int j=1;j<img.cols-1;j++)
		{
			a[0]=img.at<uchar>(i-1,j-1);
			a[1]=img.at<uchar>(i-1,j);
			a[2]=img.at<uchar>(i-1,j+1);
			a[3]=img.at<uchar>(i,j-1);
			a[4]=img.at<uchar>(i,j);
			a[5]=img.at<uchar>(i,j+1);
			a[6]=img.at<uchar>(i+1,j-1);
			a[7]=img.at<uchar>(i+1,j);
			a[8]=img.at<uchar>(i+1,j+1);
			img1.at<uchar>(i,j)=median(a);
		}
	}
	namedWindow("Window",WINDOW_NORMAL);
	imshow("Window",img1);
        imshow("Window1",img);
	waitKey(0);
}
