
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <stdlib.h>
#include "queue.h"

using namespace std;
using namespace cv;

int x;

Mat bfs(Mat img)
{
	Mat visited(img.rows,img.cols,CV_8UC1,Scalar(255));
	//namedWindow("Visit",WINDOW_NORMAL);


	queue Q1;
	queue* Q=&Q1;
	init(Q);

	node* res;

	int a,b,k,l;

	for(k=1;k<img.rows-1;k++)
	{
		for(l=1;l<img.cols-1;l++)
		{
			if(img.at<uchar>(k,l)==0 && visited.at<uchar>(k,l)==255)
			{
				enqueue(Q,k,l);
				x=random()%40+30;
				while(!isEmpty(Q))
				{	
					res=(Q->head);
					dequeue(Q);

					for(a=res->i-1;a<=res->i+1;a++)
					{
						for(b=res->j-1;b<=res->j+1;b++)
						{
							if(a>=0 && b>=0 && a<img.rows && b<img.cols)
							{		
								if(visited.at<uchar>(a,b)==255 && img.at<uchar>(a,b)==0)
								{
									enqueue(Q,a,b);	
									visited.at<uchar>(a,b)=x;
								}
							}
						}
					}
				}
			}
		}
	}		
	return visited;
}
