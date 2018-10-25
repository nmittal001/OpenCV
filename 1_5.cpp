#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main()
{
	cv::Mat image= cv::imread("pic.jpg");
	cv::Mat logo= cv::imread("logo_png.png");
	cv::imshow("logo_add",image);
	cv::waitKey(0);
	cv::imshow("logo_add",logo);
	cv::waitKey(0);
	//define image ROI at the botttom-right
	cv::Mat imageROI(image, cv::Rect(image.cols-logo.cols,image.rows-logo.rows, logo.cols, logo.rows));
	//insert logo
	logo.copyTo(imageROI);
	cv::imshow("logo_add",image);
	cv::waitKey(0);



//-----------back ground is transparent------------------------	

	// re-read the original image
	image=  cv::imread("pic.jpg");
	
	// define image ROI at image bottom-right
	imageROI= image(cv::Rect(image.cols-logo.cols,image.rows-logo.rows,
		                     logo.cols,logo.rows));
	// or using ranges:
	// imageROI= image(cv::Range(image.rows-logo.rows,image.rows), 
	// cv::Range(image.cols-logo.cols,image.cols));
	
	// use the logo as a mask (must be gray-level)
	cv::Mat mask(logo);
	
	// insert by copying only at locations of non-zero mask
	logo.copyTo(imageROI,mask);//background value is zero

	cv::imshow("Image", image); // show the image
	cv::waitKey(0); // wait for a key pressed

	return 0;
}
