#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
//---------------------------------------------------
int main()
{
//---------------SURF---------------------------------

	
	// Compute SURF
	cv::Mat image=cv::imread("photo.jpg",0);	
	std::vector<cv::KeyPoint> keypoints;
	
	// GFTT detector
	cv::Ptr<cv::xfeatures2d::SiftFeatureDetector> ptrSIFT = cv::xfeatures2d::SiftFeatureDetector::create(2000.0);	  

	// detect the Keypoints
	ptrSIFT->detect(image,keypoints);
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

	//cv::drawKeypoints(image,keypoints,image,cv::Scalar(255,255,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	// Display the keypoints
	cv::namedWindow("SIFT");
	cv::imshow("SIFT",image);

	std::cout << "Number of SIFT keypoints: " << keypoints.size() << std::endl; 
	cv::waitKey();

	return 0;
}

