#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main()
{
	cv::Mat image= cv::imread("photo.jpg");

	// define bounding rectangle 
	cv::Rect rectangle(400,160,660,1200);
	cv::Mat result;// segmentation (4 possible values)
	cv::Mat bgModel,fgModel;
	//GrabCut segmantation
	cv::grabCut(image,// input image
		result,// segmentation result
		rectangle,// rectangle containing foreground 
		bgModel,fgModel,//Models
		5,//number of iterations
		cv::GC_INIT_WITH_RECT	//use Rectangle
	);
	// Get the pixels marked as likely foreground
	cv::compare(result,cv::GC_PR_FGD, result, cv::CMP_EQ);

	cv::Mat foreground(image.size(),CV_8UC3, cv::Scalar(255,255,255));

	cv::imshow("foreground_before", foreground);
	cv::waitKey(5000);
	image.copyTo(foreground,result);//result-> non-zero(black), foreground-> image location(white)// copied the image and placed in foreground in the result position
	result=result&1;
	cv::imshow("GrabCut_result", result);
	cv::waitKey(5000);



	// draw rectangle on original image
	cv::rectangle(image, rectangle, cv::Scalar(255,255,255),1);
	cv::namedWindow("Image with rectangle");
	cv::imshow("Image with rectangle",image);

	// display result
	cv::namedWindow("Foreground object");
	cv::imshow("Foreground object",foreground);

	cv::waitKey();
	return 0;

}
