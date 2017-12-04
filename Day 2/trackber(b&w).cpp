//showing a yellow block
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
int main()
{
  Mat img(500,500,CV_8UC3,Scalar(0,255,255));
  namedWindow ("win", WINDOW_NORMAL);
  imshow("win", img);
  waitKey(0);
}

