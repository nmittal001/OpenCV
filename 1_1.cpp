#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace std;
int main()
{
	cv::Mat imagepr;
	cout<< imagepr.rows<<"X"<<imagepr.cols<<endl;
	// read an image
	cv::Mat image1= cv::imread("img1.jpg");
	cv::Mat image= cv::imread("img.jpg");
	// create image window named "My Image"
	cv::namedWindow("Mittal");
	// show the image on window
	cv::imshow("Mittal", image);
	cv::waitKey(5000);
	cv::imshow("Mittal", image1);
	cv::waitKey(0);//0 to indefinitely wait for a key pressed// other then 0 value will wait for given amount of msec
	cv::flip(image,image1,1);//positive for ->horizontal, 0->vertical
	cv::imshow("Mittal",image1);
	cv::imwrite("nit.jpg",image1);
	// wait key for 5000 ms
	cv::waitKey(5000);
	return 1;
}
