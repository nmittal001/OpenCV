#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include<iostream>
class ColorDetector {

  private:

	  // minimum acceptable distance
	  int maxDist; 

	  // target color
	  cv::Vec3b target; 

	  // image containing color converted image
	  cv::Mat converted;
	  bool useLab;

	  // image containing resulting binary map
	  cv::Mat result;

  public:

	  // empty constructor
	  // default parameter initialization here
	  ColorDetector() : maxDist(100), target(0,0,0), useLab(true) {}//Converting to Lab color space //RGB <-> GRAY//when true

	  // extra constructor for Lab color space example
	  ColorDetector(bool useLab) : maxDist(100), target(0,0,0), useLab(useLab) {}

	  // full constructor
	  ColorDetector(uchar blue, uchar green, uchar red, int mxDist=100, bool useLab=false): maxDist(mxDist), useLab(useLab) { 

		  // target color
		  setTargetColor(blue, green, red);
	  }


//------------------------process-------------------

	  // Processes the image. Returns a 1-channel binary image.
	  cv::Mat process(const cv::Mat &image);

//-------------------------TargetColor----------------------------

	  // Sets the color to be detected
	  // given in BGR color space
	  void setTargetColor(uchar blue, uchar green, uchar red) {

		  // BGR order
		  target = cv::Vec3b(blue, green, red);

		  if (useLab) {
			  // Temporary 1-pixel image
			  cv::Mat tmp(1, 1, CV_8UC3);
			  tmp.at<cv::Vec3b>(0, 0) = cv::Vec3b(blue, green, red);

			  // Converting the target to Lab color space 
			  cv::cvtColor(tmp, tmp, CV_BGR2Lab);

			  target = tmp.at<cv::Vec3b>(0, 0);
		  }
	  }

	
};







//------------------------------------------------OR----------------------------------------------------
//-------We could have achieved the same result by calling a sequence of OpenCV function ---------------

cv::Mat ColorDetector::process(const cv::Mat &image) 
{
	cv::Mat output;
	// compute absolute difference with target color
	cv::absdiff(image,cv::Scalar(target),output);

	// split the channels into 3 images
	std::vector<cv::Mat> images;
	cv::split(output,images);
	
	//cv::imshow("result_Images_check",images);//error
	//std::cout<<"image="<<images.channels()<<std::endl;//error

	// add the 3 channels (saturation might occurs here)
	output= images[0]+images[1]+images[2];
		
	cv::imshow("result_Output= images[0]+images[1]+images[2]",output);
	cv::waitKey(5000);
	
	std::cout<<output.channels();


//seedPoint – Starting point.
//newVal – New value of the repainted domain pixels.
//loDiff – Maximal lower brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.

//upDiff – Maximal upper brightness/color difference between the currently observed pixel and one of its neighbors belonging to the component, or a seed pixel being added to the component.

//rect – Optional output parameter set by the function to the minimum bounding rectangle of the repainted domain.

//flags –
//Operation flags. The first 8 bits contain a connectivity value. The default value of 4 means that only the four nearest neighbor pixels (those that share an edge) are considered. A connectivity value of 8 means that the eight nearest neighbor pixels (those that share a corner) will be considered. The next 8 bits (8-16) contain a value between 1 and 255 with which to fill the mask (the default value is 1). For example, 4 | ( 255 << 8 ) will consider 4 nearest neighbours and fill the mask with a value of 255. The following additional options occupy higher bits and therefore may be further combined with the connectivity and mask fill values using bit-wise or (|):
//FLOODFILL_FIXED_RANGE If set, the difference between the current pixel and seed pixel is considered. Otherwise, the difference between neighbor pixels is considered (that is, the range is floating).
//FLOODFILL_MASK_ONLY If set, the function does not change the image ( newVal is ignored), and only fills the mask with the value specified in bits 8-16 of flags as described above. This option only make sense in function variants that have the mask parameter.

//C++: int floodFill(InputOutputArray image, Point seedPoint, Scalar newVal, Rect* rect=0, Scalar loDiff=Scalar(), Scalar upDiff=Scalar(), int flags=4 )


//FLOODFILL_FIXED_RANGE If set, the difference between the current pixel and seed pixel is considered. Otherwise, the difference between neighbor pixels is considered (that is, the range is floating).
//FLOODFILL_MASK_ONLY If set, the function does not change the image ( newVal is ignored), and only fills the mask with the value specified in bits 8-16 of flags as described above. This option only make sense in function variants that have the mask parameter.

	// apply floodFill
	cv::floodFill(image, //input/output imaage 
		cv::Point(10,10), //location of background of image which we want to convert into white
		cv::Scalar(255,255,255),// repainted color
		(cv::Rect*)0, //bounding rect of the repainted set
		cv::Scalar(35,35,35),//low / high difference threshold
		cv::Scalar(35,35,35),//identical most of the time
		cv::FLOODFILL_FIXED_RANGE);//pixels compared to seeds

	return image;

}

