#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace std;
using namespace cv;

typedef struct _node
{
	int x;
	int y;
}node;

Mat img=imread("dfs_path.jpg",0);
Mat M(img.rows,img.cols,CV_8UC1,Scalar(0));
node stack[100000];
node p;
int top=-1;

void dfs(int i,int j)
{
    M.at<uchar>(i,j)=255;cout<<i<<" "<<j<<" ";
    stack[++top]={i,j};
    while(top!=-1){
    p=stack[top--];
    int i=p.x,j=p.y;
	for(int p=-1;p<=1;p++)
	{
		for(int q=-1;q<=1;q++)
		{
			if((i+p)>=0 && (j+q)>=0 && (i+p)<img.rows && (j+q)<img.cols)
			{
				if(M.at<uchar>(i+p,j+q)==0 && img.at<uchar>(i+p,j+q)<200)
				{
					M.at<uchar>(i+p,j+q)=255;
					stack[++top]={i+p,j+q};
				}
			}
		}
	}
    }
}

int count()
{
	int ct=0;
	for(int i=1;i<img.rows-1;i++)
	{
		for(int j=1;j<img.cols-1;j++)
		{
			if(M.at<uchar>(i,j)==0 && img.at<uchar>(i,j)<200)
			{
				dfs(i,j);
				ct++;
			}
		}
	}
	return ct;
}

int main()
{
	cout<<count();
	namedWindow("w",WINDOW_NORMAL);
	imshow("w",M);
	waitKey(0);
}
