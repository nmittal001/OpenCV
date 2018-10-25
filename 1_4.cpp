#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//test function that create an image
cv::Mat function()
{
	cv::Mat ima(500,500,CV_8U,255);//255->white, 1-> black
	return ima;
}

int main()
{
	cv::Mat image1(240,320,CV_8U,100);//row->240, coloum->320
	cv::imshow("Image",image1);
	cv::waitKey(0);

	//re-allocate a new image
	image1.create(200,200,CV_8U);//only three arg
	image1=255;//color-> white, for black value is 1;
        cv::imshow("Image",image1);
	cv::waitKey(0);

	cv::Mat image2(240,320,CV_8UC3,cv::Scalar(0,0,255));
        cv::imshow("Image",image2);
	cv::waitKey(0);
	
	cv::Mat image3= cv::imread("img.jpg");
	cv::Mat image4(image3);
	cv::imshow("Image3",image3);
        cv::waitKey(0);
	cv::imshow("Image4",image4);
        cv::waitKey(0);

	cv::Mat image5=image3;
	cv::imshow("Image5",image5);
        cv::waitKey(0);
	
	cv::Mat imagex= cv::imread("img1.jpg");
	imagex.copyTo(image3);
	//image3=imagex.clone();
	cv::imshow("Image6",image3);
        cv::waitKey(0);

	cv::imshow("Image7",image4);
        cv::waitKey(0);

	cv::imshow("Image8",image5);
        cv::waitKey(0);

	cv::Mat gray=function();
	cv::imshow("Image9",gray);
	cv::waitKey(0);

	image1=cv::imread("nit.jpg",CV_LOAD_IMAGE_GRAYSCALE);

	cv::imshow("Image_CV_LOAD_IMAGE_GRAYSCALE",image1);
	cv::waitKey(0);

	image1.convertTo(image2,CV_32F,1/255.0,0.0);
	cv::imshow("Image_convertTo",image2);
	cv::waitKey(0);
	
	//matix
	cv::Matx31d matix(3,2,1);
	cv::Matx13d mat(2,2,2);
	cv::Matx33d re=matix*mat;
	std::cout<<re;
	
        cv::Mat image= cv::imread("pic.jpg");
        cv::Mat logo= cv::imread("logo.jpg");
	//define image ROI at the botttom-right
	cv::Mat imageROI(image, cv::Rect(image.cols-logo.cols,image.rows-logo.rows, logo.cols, logo.rows));
	//insert logo
	logo.copyTo(imageROI);
	cv::imshow("logo_add",imageROI);
	cv::waitKey(0);
	return 0;
}
