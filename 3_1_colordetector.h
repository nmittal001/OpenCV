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


//--------------------------getColorDistance-------------

	  // Computes the distance from target color.
	  int getDistanceToTargetColor(const cv::Vec3b& color) const {
		  return getColorDistance(color, target);
	  }//             \|/
	//		   |
	  // Computes the city-block distance between two colors.
	  int getColorDistance(const cv::Vec3b& color1, const cv::Vec3b& color2) const {

		  return abs(color1[0]-color2[0])+
					abs(color1[1]-color2[1])+
					abs(color1[2]-color2[2]);

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

	  // Sets the color to be detected
	  void setTargetColor(cv::Vec3b color) {

		  target= color;
	  }

	  // Gets the color to be detected
	  cv::Vec3b getTargetColor() const {

		  return target;
	  }
};


//-------processing---------------

cv::Mat ColorDetector::process(const cv::Mat &image) 
{

	  // re-allocate binary map if necessary
	  // same size as input image, but 1-channel
	  result.create(image.size(),CV_8U);

	  // Converting to Lab color space 
	//RGB <-> GRAY
	//Transformations within RGB space like adding/removing the alpha channel, reversing the channel order, conversion to/from 16-bit RGB color (R5:G6:B5 or 					R5:G5:B5), as well as conversion to/from grayscale using:
	//RGB[A] to Gray:Y←0.299⋅R+0.587⋅G+0.114⋅B//in our BRG
	//and
	//Gray to RGB[A]:R←Y,G←Y,B←Y,A←max(ChannelRange)

	  if (useLab)
		  cv::cvtColor(image, converted, CV_BGR2Lab);

	  // get the iterators
	  cv::Mat_<cv::Vec3b>::const_iterator it= image.begin<cv::Vec3b>();
	  cv::Mat_<cv::Vec3b>::const_iterator itend= image.end<cv::Vec3b>();
	  cv::Mat_<uchar>::iterator itout= result.begin<uchar>();

	  // get the iterators of the converted image 
	  if (useLab) {
		  it = converted.begin<cv::Vec3b>();
		  itend = converted.end<cv::Vec3b>();
	  }

	//cv::imshow("result_converted_CV_BGR2Lab",converted);//check
	//cv::waitKey(5000);//check
	//std::cout<<converted.channels();//check

	  // for each pixel
	  for ( ; it!= itend; ++it, ++itout)
	{
        
		// process each pixel ---------------------

		  // compute distance from target color
		  if (getDistanceToTargetColor(*it)<=maxDist) {
			  *itout= 255;//white
		  } else {
			  *itout= 0;//black
	  }

        // end of pixel processing ----------------
	  }
	//std::cout<<"2";
	  return result;
}






//------------------------------------------------OR----------------------------------------------------
//-------We could have achieved the same result by calling a sequence of OpenCV function ---------------
/*
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

	// apply threshold
	cv::threshold(output,  // input image
			output,  // output image
			maxDist, // threshold (must be < 256)
			255,     // max value//saturation
			cv::THRESH_BINARY_INV); // thresholding type
//cv::THRESH_BINARY: the regular thresholding mode
//cv::THRESH_BINARY_INV: we used inverse mode in which the defined maximum value is assigned to the pixels that have lower than or equal to the thresold.

	return output;

}
*/
