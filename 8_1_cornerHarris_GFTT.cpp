#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>



#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>

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
	public:
//The Sobel operators combine Gaussian smoothing and differentiation, so the result is more or less resistant to the noise. Most often, the function is called with ( xorder = 1, yorder = 0, ksize = 3) or ( xorder = 0, yorder = 1, ksize = 3) to calculate the first x- or y- image derivative.
//the ksize X ksize separable kernel is used to calculate the derivative. When  ksize = 1 , the 3 X 1 or 1 X 3 kernel is used (that is, no Gaussian smoothing is done). ksize = 1 can only be used for the first or the second x- or y- derivatives.

		HarrisDetector(): neighborhood(3),aperture(1),k(0.01),nonMaxSize(3),maxStrength(0.0),threshold(0.01)
		{
			setLocalMaxWindowSize(nonMaxSize);
		}
		// Create kernel used in non-maxima suppression
		void setLocalMaxWindowSize(int size)
		{
			nonMaxSize= size;
			//kernel.create(nonMaxSize,nonMaxSize,CV_8U);
		}
		void detect(const cv::Mat& image)
		{
			//Compute Harrish Corner
			//  cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
			cv::cornerHarris(image,//imput image
					cornerStrength,//image of cornerness
					neighborhood,//neighborhood Size//blockSize - It is the size of neighbourhood considered for corner detection
					aperture,//aperture Size//kernel size - Aperture parameter of Sobel derivative used
					k);//harris Parmeter//k - Harris detector free parameter in the equation.

			
			//internal threshold computation
			cv::minMaxLoc(cornerStrength,0,&maxStrength);
			//std::cout<<"maxStrength=="<<maxStrength;

			//local maxima detection
			cv::Mat dilated;//temporary image
			cv::dilate(cornerStrength,dilated,cv::Mat());
			cv::compare(cornerStrength,dilated,localMax,cv::CMP_EQ);

		}
//-------------------------------------------------		

		// Get the feature points vector from the computed Harris values
		void getCorners(std::vector<cv::Point> &points, double qualityLevel)
		{
			// Get the corner map
			cv::Mat cornerMap= getCornerMap(qualityLevel);
			// Get the corners
			getCorners(points, cornerMap);
		}

		cv::Mat getCornerMap(double qualityLevel)
		{
			cv::Mat cornerMap;
			threshold=qualityLevel*maxStrength;//threshold 
			cv::threshold(cornerStrength,cornerTh,threshold,255,cv::THRESH_BINARY);
			// convert to 8-bit image
			cornerTh.convertTo(cornerMap,CV_8U);
			//non-maxima suppression
			cv::bitwise_and(cornerMap,localMax,cornerMap);
			return cornerMap;
		}
		
		
		// Get the feature points vector from the computed corner map
		void getCorners(std::vector<cv::Point> &points, const cv::Mat& cornerMap)
		{
			// Iterate over the pixels to obtain all feature points
			for( int y = 0; y < cornerMap.rows; y++ )
			{
				const uchar* rowPtr = cornerMap.ptr<uchar>(y);
				for( int x = 0; x < cornerMap.cols; x++ )
				{
					// if it is a feature point
					if(rowPtr[x])
					{
						points.push_back(cv::Point(x,y));
					}
				}
			}
		}
		// Draw circles at feature point locations on an image
		void drawOnImage(cv::Mat &image, const std::vector<cv::Point> &points, cv::Scalar color= cv::Scalar(255,255,255), int radius=3, int thickness=1)
		{
			std::vector<cv::Point>::const_iterator it= points.begin();
			// for all corners
			while(it!=points.end())
			{
				// draw a circle at each corner location
				cv::circle(image,*it,radius,color,thickness);
				++it;
			}
		}
};
//---------------------------------------------------
int main()
{
//-------------------SELF without overlap of circle in the image----------------
	cv::Mat image=cv::imread("photo.jpg",0);	
	// Detect Harris corners
	cv::Mat cornerStrength;
	cv::cornerHarris(image, cornerStrength,
				3,     // neighborhood sizE//block size
				5,     // aperture size//Size of the square kernel(1,3,5,7..odd)//ksize - Aperture parameter of Sobel derivative used.

				0.01); // Harris parameter
	cv::namedWindow("Harris_before threshold");
	cv::imshow("Harris_before threshold", cornerStrength);
	cv::waitKey();


	// threshold the corner strengths
	cv::Mat harrisCorners;
	double threshold= 0.0001; 
	cv::threshold(cornerStrength, harrisCorners,
			threshold,255,cv::THRESH_BINARY_INV);
	 

	// Display the corners
	cv::namedWindow("Harris_self");
	cv::imshow("Harris_self", harrisCorners);
	cv::waitKey();
//--------------------used functions (for overlap of circle)--------------------

	HarrisDetector harris;
	harris.detect(image);
	
	std::vector<cv::Point>pts;
	harris.getCorners(pts,0.02);//
	harris.drawOnImage(image,pts);
	cv::imshow("Harris_photo",image);
	cv::waitKey();


//---------------Good features to track---------------------------------
	// Compute good features to track
	image=cv::imread("photo.jpg",0);	

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
		cv::circle(image,it->pt,3,cv::Scalar(255,255,255),1);
		++it;
	}

	// Display the keypoints
	cv::imshow("Good Features to Track Detector",image);

	cv::waitKey();

	return 0;
}

