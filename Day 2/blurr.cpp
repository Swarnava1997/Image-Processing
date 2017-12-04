
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

int main()
{
Mat img=imread("a.png",0);
int i,j;
int a[9];
Mat img1(img.rows,img.cols,CV_8UC1,Scaler(0));

for(i=1;i<img.rows;i++)
{
	for(j=1;j<img.cols;j++)
	{
	  a[0]=img.at<uchar>(i,j);
	  a[1]=img.at<uchar>(i-1,j-1);
	  a[2]=img.at<uchar>(i-1,j);
	  a[3]=img.at<uchar>(i,j+2);
	  a[4]=img.at<uchar>(i,j-1);
	  a[5]=img.at<uchar>(i,j+1);
	  a[6]=img.at<uchar>(i+1,j-1);
	  a[7]=img.at<uchar>(i+1,j);
	  a[8]=img.at<uchar>(i+1,j+1);
	  for(k=0
	}

}
namedWindow("win",WINDOW_NORMAL);
imshow("win",img);
waitKey(0);

}
