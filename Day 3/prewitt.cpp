#include <iostream>
#include <cmath>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;
int gx(Mat img,int i,int j) 
{
int g=-img.at<uchar>(i-1,j-1)+img.at<uchar>(i-1,j+1)-img.at<uchar>(i,j-1)+img.at<uchar>(i,j+1)-img.at<uchar>(i+1,j-1)+img.at<uchar>(i+1,j+1);
return g;
}


int gy(Mat img,int i,int j)
{
int g1=img.at<uchar>(i-1,j-1)+img.at<uchar>(i-1,j)+img.at<uchar>(i-1,j+1)-img.at<uchar>(i+1,j-1)-img.at<uchar>(i+1,j)-img.at<uchar>(i+1,j+1);
return g1;
}
int modadd(int g,int g1)
{if(g<0){g=-g;}
if(g1<0){g1=-g1;}
return (sqrt(g*g+g1*g1));

}


int main()
{int i,j;
Mat img=imread("a.png",0);
Mat img1(img.rows,img.cols,CV_8UC1);
for(i=1;i<img.rows-1;i++){
	for(j=1;j<img.cols-1;j++){
		img1.at<uchar>(i,j)=modadd((gx(img,i,j)),(gy(img,i,j)));
	}
}
namedWindow("win1",WINDOW_NORMAL);
imshow("win1",img);
namedWindow("win",WINDOW_NORMAL);
imshow("win",img1);
waitKey(0);
}

