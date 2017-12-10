#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>


using namespace std;
using namespace cv;

Mat noise(Mat img1)
{
	Mat img(img1.rows,img1.cols,CV_8UC3,Scalar(0,0,0));
	
	int i,j,k;
	
	for(i=1;i<img.rows-1;i++)
	{
		for(j=1;j<img.cols-1;j++)
		{
			k=0;
			int a,b;
			int arr0[9];
			int arr1[9];
			int arr2[9];
			
			
			for(a=i-1;a<=i+1;a++)
			{
				for(b=j-1;b<=j+1;b++)
				{
					arr0[k]=img1.at<Vec3b>(a,b)[0];
					arr1[k]=img1.at<Vec3b>(a,b)[1];
					arr2[k]=img1.at<Vec3b>(a,b)[2];
					k++;
				}
			}
			
			sort(arr0,arr0+9);
			sort(arr1,arr1+9);
			sort(arr2,arr2+9);
			
			img.at<Vec3b>(i,j)[0]=arr0[4];
			img.at<Vec3b>(i,j)[1]=arr1[4];
			img.at<Vec3b>(i,j)[2]=arr2[4];
		}
		
	}

	return img;
}

