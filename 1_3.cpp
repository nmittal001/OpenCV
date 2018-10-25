#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
void onMouseMyFun(int event, int x, int y, int flags, void* param)
{
	cv::Mat *im=reinterpret_cast<cv::Mat*>(param);
	switch(event)
	{
		case cv::EVENT_LBUTTONDOWN: std::cout<<"at("<<x<<","<<y<<") value is:" << static_cast<int>(im->at<uchar>(cv::Point(x,y)))<<std::endl;
		break;
	}
}


int main()
{
	cv::Mat image; // create an empty image
	
	// read the input image as a gray-scale image
	image=  cv::imread("img1.jpg", cv::IMREAD_GRAYSCALE); 

	// create image window named "My Image"
	cv::namedWindow("Original Image"); // define the window (optional)
	cv::imshow("Original Image", image); // show the image

	// set the mouse callback for this image
	cv::setMouseCallback("Original Image", onMouseMyFun, reinterpret_cast<void*>(&image));

	image=  cv::imread("img.jpg");
	// create another image window named
	cv::namedWindow("Drawing on an Image"); // define the window

	cv::circle(image,              // destination image 
		       cv::Point(155,110), // center coordinate
			   65,                 // radius  
			   0,                  // color (here black)
			   5);                 // thickness
	
	cv::putText(image,                   // destination image
		        "Hello!!!",        // text
				cv::Point(40,200),       // text position
				cv::FONT_HERSHEY_PLAIN,  // font type
				6.0,                     // font scale
				255,                     // text color (here white)
				6);                      // text thickness

	cv::imshow("Drawing on an Image", image); // show the image

	cv::waitKey(0); // 0 to indefinitely wait for a key pressed
	
	return 0;
}

