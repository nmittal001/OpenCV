#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
// h(x,y) = (I.cols - x, y )
void Remapped(const cv::Mat &image, cv::Mat &result) {

	// the map functions
	cv::Mat srcX(image.size(),CV_32F); // x-map
	cv::Mat srcY(image.size(),CV_32F); // y-map

	// creating the mapping
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			//horizontal flipping
			srcX.at<float>(i,j)= image.cols-j-1;
			srcY.at<float>(i,j)= i+200;
		}
	}

	// applying the mapping
	cv::remap(image,  // source image
		      result, // destination image
			  srcX,   // x map
			  srcY,   // y map
			  cv::INTER_LINEAR); // interpolation method

//The function that applies the remapping is remap. We give the following arguments:
//
//src: Source image
//dst: Destination image of same size as src
//map_x: The mapping function in the x direction. It is equivalent to the first component of h(i,j)
//map_y: Same as above, but in y direction. Note that map_y and map_x are both of the same size as src
//CV_INTER_LINEAR: The type of interpolation to use for non-integer pixels. This is by default.
//BORDER_CONSTANT: Default

}

int main()
{
	cv::Mat image= cv::imread("photo.jpg",0);

	cv::imshow("Image",image);
	
	//time for repmapped
	double time = static_cast<double>(cv::getTickCount());
	
	// remapped image
	cv::Mat result;
	Remapped(image,result);
	cv::imshow("Remapped",result);
	
	time= (static_cast<double>(cv::getTickCount())-time)/cv::getTickFrequency();
	std::cout << "time 2D= " << time << std::endl;

	cv::waitKey(5000);
	return 0;
}


