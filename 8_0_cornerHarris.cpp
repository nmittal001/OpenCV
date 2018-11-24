#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
//#include<stdio.h>
using namespace cv;
using namespace std;

class HarrisDetector
{
	private:
		cv::Mat cornerStrength;
		cv::Mat cornerTh;
		cv::Mat localMax;
		int neighborhood;
		int aperture;
		double k;
		double maxStrength;
		double threshold;
		int nonMaxSize;
		cv::Mat kernel;

	};
//---------------------------------------------------
int main()
{

	cv::Mat image=cv::imread("photo.jpg",0);	
	// Detect Harris corners
	cv::Mat cornerStrength;
	cv::cornerHarris(image, cornerStrength,
				3,     // neighborhood sizE//block size
				5,     // aperture size//Size of the square kernel(1,3,5,7..odd)
				0.01); // Harris parameter
	
	cv::imshow("Harris_before threshold", cornerStrength);
	cv::waitKey();


	// threshold the corner strengths
	cv::Mat harrisCorners;
	double threshold= 0.0001; 
	cv::threshold(cornerStrength, harrisCorners,
			threshold,255,cv::THRESH_BINARY_INV);
	 
	// Display the corners
	cv::namedWindow("Harris");
	cv::imshow("Harris_self", harrisCorners);
	cv::waitKey();
//--------------------
	return 0;
}
