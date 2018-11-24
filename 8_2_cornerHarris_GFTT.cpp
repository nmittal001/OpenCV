#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>//not required
//---------------------------------------------------
int main()
{
//---------------Good features to track---------------------------------
	// Compute good features to track
	cv::Mat image=cv::imread("photo.jpg",0);	

	std::vector<cv::KeyPoint> keypoints;
	// GFTT detector
	cv::Ptr<cv::GFTTDetector> ptrGFTT = cv::GFTTDetector::create(
		500,	// maximum number of keypoints to be returned
		0.01,	// quality level
		10);	// minimum allowed distance between points	  
	// detect the GFTT
	ptrGFTT->detect(image,keypoints);
	// for all keypoints
	std::vector<cv::KeyPoint>::const_iterator it= keypoints.begin();
	while (it!=keypoints.end()) {

		// draw a circle at each corner location
		cv::circle(image,it->pt,3,cv::Scalar(255,255,255),2);//2-> thicknesss
		//cv2.circle(img, center, radius, color, thickness=1, lineType=8, shift=0) 
		//lineType – Type of the circle boundary. See the line() description.
		//shift – Number of fractional bits in the coordinates of the center and in the radius value.
		++it;
	}

	// Display the keypoints
	cv::imshow("Good Features to Track Detector",image);
	cv::waitKey();


	return 0;
}
