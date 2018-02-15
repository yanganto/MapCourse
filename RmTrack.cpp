#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;



int main()
{
	Mat imgSrc = imread("osm.png");

	Mat imgDst(imgSrc.size().height, imgSrc.size().width, CV_8UC3);
	Mat imgDstGray(imgSrc.size().height, imgSrc.size().width, CV_8U);
	Mat imgDstGray2(imgSrc.size().height, imgSrc.size().width, CV_8U);;

	if (imgSrc.empty())
	{
		cout << "Load image fail" << endl;
		return -1;
	}

	imshow("winImg", imgSrc);		


	int colNumber = imgSrc.cols;	
	int rowNumber = imgSrc.rows;
	uchar thr = 200;
	uchar diff = 20;

	for (int i = 0; i<rowNumber; i++)
	{
		for (int j = 0; j<colNumber; j++)
		{
			if(
                // Red line
				(	imgSrc.at<Vec3b>(i, j)[2] > thr 
					&& imgSrc.at<Vec3b>(i, j)[2]-imgSrc.at<Vec3b>(i, j)[1]>diff 
					&& imgSrc.at<Vec3b>(i, j)[2]-imgSrc.at<Vec3b>(i, j)[0]>diff
				)
				||
                // Blue line
				(	imgSrc.at<Vec3b>(i, j)[0] > thr 
					&& imgSrc.at<Vec3b>(i, j)[0]-imgSrc.at<Vec3b>(i, j)[1]>diff 
					&& imgSrc.at<Vec3b>(i, j)[0]-imgSrc.at<Vec3b>(i, j)[2]>diff
				)
				||
                // Light blue line
				(	imgSrc.at<Vec3b>(i, j)[0] > 235
					&& imgSrc.at<Vec3b>(i, j)[1] > thr 
					&& imgSrc.at<Vec3b>(i, j)[2] > thr 
				)
					
					){
					imgDst.at<Vec3b>(i, j)[0] = 255;		
					imgDst.at<Vec3b>(i, j)[1] = 255;
					imgDst.at<Vec3b>(i, j)[2] = 255;
			}else{
				imgDst.at<Vec3b>(i, j)[0] = imgSrc.at<Vec3b>(i, j)[0];		
				imgDst.at<Vec3b>(i, j)[1] = imgSrc.at<Vec3b>(i, j)[1];		
				imgDst.at<Vec3b>(i, j)[2] = imgSrc.at<Vec3b>(i, j)[2];
			}
		}
	}

	cvtColor(imgDst, imgDstGray, CV_BGR2GRAY);
	
	for (int i = 1; i<rowNumber-1; i++)
	{
		for (int j = 1; j<colNumber-1; j++)
		{
			if(
				imgDstGray.at<uchar>(i-1, j) == 255
				&& imgDstGray.at<uchar>(i+1, j) == 255
				&& imgDstGray.at<uchar>(i, j-1) == 255
				&& imgDstGray.at<uchar>(i, j+1) == 255
			)
				imgDstGray2.at<uchar>(i, j) = 255;
			else
				imgDstGray2.at<uchar>(i, j) = imgDstGray.at<uchar>(i,j);
		}
	}
	imshow("winRmTrack", imgDstGray2);		
	imwrite("osm-map.png", imgDstGray2);

	waitKey(0);
	return 0;
}
