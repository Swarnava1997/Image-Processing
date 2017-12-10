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

node p;
Mat img1=imread("dfs_path.jpg",0);
int r=img1.rows;
int c=img1.cols;
Mat img2(r,c, CV_8UC1, Scalar(0));
node stack[100000];
int top=-1;

void dfs(int a, int b)
{
  stack[++top]={a,b};
  img2.at<uchar>(a,b)=255;
  while(top!=-1)
  {
    p=stack[top--];
    a=p.x;b=p.y;
	for(int x=-1;x<=1;x++)
	{
		for(int y=-1;y<=1;y++)
		{
			if((a+x)>=0 && (b+y)>=0 && (a+x)<img1.rows && (b+y)<img1.cols)
			{
				if(img2.at<uchar>(a+x,b+y)==0 && img1.at<uchar>(a+x,b+y)<200)
				{
					img2.at<uchar>(a+x,b+y)=255;
					stack[++top]={a+x,b+y};
				}
			}
		}
	}
    }
  
}

int main()
{
  int i,j;
  int ct=0;
  for (i=0; i<r; i++)
  {
    for (j=0; j<c; j++)
    {
      if (img2.at<uchar>(i,j)==0  && img1.at<uchar>(i,j)<200)
      {
        dfs(i, j);
        ct++;
      }
    }
  }
  cout<<"Total blob is: "<<ct;
  namedWindow("WIN1", WINDOW_NORMAL);
  imshow("WIN1", img1);
  namedWindow("WIN2", WINDOW_NORMAL);
  imshow("WIN2", img2);
  waitKey(0);
}
