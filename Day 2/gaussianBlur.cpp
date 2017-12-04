#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;
void gaussian_blur(Mat img);

int main()
{Mat img = imread("test.jpg");
	imshow("original",img);
	gaussian_blur(img);
	waitKey(0);
}

 void gaussian_blur(Mat img)
 {
 	Mat img2(img.rows,img.cols,CV_8UC3, Scalar(0,0,0));
        namedWindow("win",WINDOW_NORMAL);
 	for(int i=1;i<img.rows-1;i++){
 		for(int j=1;j<img.cols;j++){
 			for(int k=0;k<3;k++){
 				int a=0;
 				a = (img.at<Vec3b>(i-1,j-1)[k] + img.at<Vec3b>(i-1,j+1)[k] + img.at<Vec3b>(i+1,j-1)[k] + img.at<Vec3b>(i+1,j+1)[k])/16 + (img.at<Vec3b>(i,j-1)[k] + img.at<Vec3b>(i,j+1)[k] + img.at<Vec3b>(i+1,j)[k] + img.at<Vec3b>(i-1,j)[k])/8 + (img.at<Vec3b>(i,j)[k])/4;
 				img2.at<Vec3b>(i,j)[k] = a;
 			}
 		}
 	}
 	imshow("win",img2);
 }

