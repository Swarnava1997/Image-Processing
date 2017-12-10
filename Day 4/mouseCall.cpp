#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

void Callback (int event, int x, int y, int f, void* )
{
    if(event == CV_EVENT_LBUTTONDOWN){  
        cout<<"x= "<<x<<" and y= "<<y;
        }
}

int main()
{
   Mat img=imread("dfs_path.jpg",0);
   namedWindow("Window", WINDOW_AUTOSIZE);
   setMouseCallback ("Window",Callback);
   imshow("Window", img);
   waitKey(0);
}
