#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat image,imagepr;
	cout<< image.rows<<"X"<<image.cols<<endl;
	image=imread("img.jpg");
	cout<<"channel"<< image.channels()<<endl;
	image=imread("img.jpg",cv::IMREAD_GRAYSCALE);
	cout<< image.rows<<"X"<<image.cols<<"channel"<< image.channels()<<endl;
	imagepr=imread("img.jpg",cv::IMREAD_COLOR);
	cout<< imagepr.rows<<"X"<<imagepr.cols<<"channel"<< imagepr.channels()<<endl;
	return 1;
}
