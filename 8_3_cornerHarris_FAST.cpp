#include<opencv2/core.hpp>
#include<iostream>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>//not required
//---------------------------------------------------
int main()
{
	// FAST feature:-----------------------------------------------------------
	// Read input image
	cv::Mat image=cv::imread("photo.jpg",0);	
	std::vector<cv::KeyPoint> keypoints;
	cv::Ptr<cv::FastFeatureDetector> ptrFAST = cv::FastFeatureDetector::create(40);	  

	int total(100); // requested number of keypoints
	int hstep(5), vstep(3); // a grid of 4 columns by 3 rows
	//hstep= vstep= 1; // try without grid
	int hsize(image.cols / hstep), vsize(image.rows / vstep);
	int subtotal(total / (hstep*vstep)); // number of keypoints per grid
	cv::Mat imageROI;
	ptrFAST->detect(image,keypoints);

	std::vector<cv::KeyPoint> gridpoints;
	ptrFAST->setThreshold(20); 

	// non-max suppression
	ptrFAST->setNonmaxSuppression(true);	
	std::cout << "Grid of " << vstep << " by " << hstep << " each of size " << vsize << " by " << hsize << std::endl;
	keypoints.clear();
	if(numberOfPoints< keypoints.size())
			std::nth_element(keypoints.begin(),
			keypoints.begin()+numberOfPoints,
			keypoints.end(),
			[](cv::KeyPoint&  a, cv::KeyPoints &b)
			{return a.response>b.response} );
			
	
	for (int i = 0; i < vstep; i++)
	{
		for (int j = 0; j < hstep; j++)
		{
			// create ROI over current grid
			imageROI = image(cv::Rect(j*hsize, i*vsize, hsize, vsize));
			// detect the keypoints in grid
			gridpoints.clear();
			ptrFAST->detect(imageROI, gridpoints);
			std::cout << "Number of FAST in grid " << i << "," << j << ": " << gridpoints.size() << std::endl;
			
			// get the strongest FAST features
			auto itEnd(gridpoints.end());
			if (gridpoints.size() > subtotal)
			{ // select the strongest features
					std::nth_element(gridpoints.begin(),
					gridpoints.begin() + subtotal,
					gridpoints.end(),
					[](cv::KeyPoint& a,
					cv::KeyPoint& b) {return a.response > b.response; });
					itEnd = gridpoints.begin() + subtotal;
			}

			// add them to the global keypoint vector
			for (auto it = gridpoints.begin(); it != itEnd; ++it)
			{
				it->pt += cv::Point2f(j*hsize, i*vsize); // convert to image coordinates
				keypoints.push_back(*it);
				std::cout << "  " <<it->response << std::endl;
			}
		}
	}

	// draw the keypoints
	cv::drawKeypoints(image, keypoints, image, cv::Scalar(255, 255, 255), cv::DrawMatchesFlags::DRAW_OVER_OUTIMG);

	// Display the keypoints
	cv::namedWindow("FAST Features (grid)");
	cv::imshow("FAST Features (grid)", image);


	return 0;
}
