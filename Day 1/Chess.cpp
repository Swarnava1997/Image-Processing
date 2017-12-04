#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
using namespace cv;
using namespace std;

int main()
{
Mat img(640,640,CV_8UC3,Scalar(255,255,255));
namedWindow("win",WINDOW_NORMAL);
for(int i=0;i<640;i++)
{
    for(int j=0;j<640;j++)
    {
        if(j/80%2==0)
        {
            if(i/80%2==0)
            {
                img.at<Vec3b>(i,j)[0]=0;
                img.at<Vec3b>(i,j)[1]=0;
                img.at<Vec3b>(i,j)[2]=0;
            }    
        }
        else
        {
            if(i/80%2==1)
            {
                img.at<Vec3b>(i,j)[0]=0;
                img.at<Vec3b>(i,j)[1]=0;
                img.at<Vec3b>(i,j)[2]=0;
            }            
        }
    }
}
imshow("win",img);
	waitKey(0);
}
