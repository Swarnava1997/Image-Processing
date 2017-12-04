#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
using namespace std;
int main()
{
  VideoCapture vid(0);
  Mat img;
  namedWindow("win", WINDOW_NORMAL);
  while(1)
  {  vid>>img;
     imshow("win", img);
     waitKey(100);
     }
     waitKey(0);
}
