#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "3_2_colordetector_floodFill.h"

int main()
{
    // 1. Create image processor object
	ColorDetector cdetect;

    // 2. Read input image
	cv::Mat image= cv::imread("photo.jpg");
	if (image.empty())
		return 0; 
	cv::namedWindow("Original Image");
	cv::imshow("Original Image", image);

    // 3. Set input parameters
	//cdetect.setTargetColor(230,190,130); // here blue sky
	cdetect.setTargetColor(0,0,0); // here blue sky


    // 4. Process the image and display the result
	cv::Mat result = cdetect.process(image);
	cv::imshow("result_floodFill",result);
	cv::waitKey();
	return 0;
}
