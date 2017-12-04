#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img(500,500,CV_8UC3,Scalar(0,255,255));
	namedWindow("yellow",WINDOW_NORMAL);
	imshow("yellow",img);
	waitKey(0);
}
