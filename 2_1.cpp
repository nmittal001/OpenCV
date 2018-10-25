#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <random>
using namespace std;
void salt(cv::Mat image, int n)
{
	//c++11 random number generator
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRow(0, image.rows-1);
        std::uniform_int_distribution<int> randomCol(0, image.cols-1);

	int i,j;
	for(int k=0;k<n;k++)
	{
		i=randomCol(generator);
		j=randomRow(generator);
		if(image.type()==CV_8UC1)
		{
			image.at<uchar>(j,i)=255;
		}
		else if(image.type()==CV_8UC3)
		{
			image.at<cv::Vec3b>(j,i)[0]=255;
			image.at<cv::Vec3b>(j,i)[1]=255;
			image.at<cv::Vec3b>(j,i)[2]=255;
		}
	}
}
int main()
{
	cv::Mat image=cv::imread("img.jpg");
	salt(image,3000);
	cv::imshow("image",image);
	cv::waitKey(5000);
	return 0;


}
