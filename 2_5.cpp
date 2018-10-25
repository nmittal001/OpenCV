#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;

void sharpen(const cv::Mat &image, cv::Mat &result)
{
	//allocate if necessary
	result.create(image.size(),image.type());
	int nchannels= image.channels();
	//for rows(except first and last row)
	for (int j=0; j<image.rows-1; j++)
	{
		const uchar* previous= image.ptr<const uchar>(j-1);// previous row
		const uchar* current= image.ptr<const uchar>(j);//current row
		const uchar* next= image.ptr<const uchar>(j+1);//next row
		uchar* output =result.ptr<uchar>(j);//current of another image
		for (int i=nchannels; i<(image.cols-1)*nchannels; i++)
		{
			// process sharpening operator ---------------------
			*output++=cv::saturate_cast<uchar>(5*current[i]-current[i-nchannels]-current[i+nchannels]-previous[i]-next[i]);
			// end sharpening processing ----------------
		} // end of line
	}
	cv::imshow("image_inside",result);
	cv::waitKey(5000);
/*	
	cout<<result.rows;
	result.row(1000).setTo(cv::Scalar(0,0,255));
        result.row(1001).setTo(cv::Scalar(0,0,255));
        result.row(1002).setTo(cv::Scalar(0,0,255));
	result.row(1003).setTo(cv::Scalar(0,0,255));
        result.row(1004).setTo(cv::Scalar(0,0,255));
	result.row(1005).setTo(cv::Scalar(0,0,255));
	result.row(1006).setTo(cv::Scalar(0,0,255));
        result.row(1007).setTo(cv::Scalar(0,0,255));
	result.row(1008).setTo(cv::Scalar(0,0,255));
	result.row(1009).setTo(cv::Scalar(0,0,255));
        result.row(1010).setTo(cv::Scalar(0,0,255));
	result.col(1006).setTo(cv::Scalar(0,0,255));
	result.col(1007).setTo(cv::Scalar(0,0,255));
	result.col(1008).setTo(cv::Scalar(0,0,255));
	result.col(1009).setTo(cv::Scalar(0,0,255));
*/				        

	result.row(0).setTo(cv::Scalar(0,0,255));
	result.row(result.rows-1).setTo(cv::Scalar(0,0,255));//for gray image-> setTo(cv::Scalar(0))
	result.col(0).setTo(cv::Scalar(0,255,0));
	result.col(result.cols-1).setTo(cv::Scalar(0,0,255));
 //     result.setTo(cv::Scalar(255,255,255));//complete image will be colorful
	cv::imshow("image_inside_check",result);
	cv::waitKey(5000);

}

int main()
{
	cv::Mat image=cv::imread("img.jpg");
	cv::imshow("image1",image);
	cv::waitKey(5000);
	
	cv::Mat image1;//=cv::imread("img1.jpg");
	//cv::imshow("image",image1);
	//cv::waitKey(5000);
        //cout<<"Row"<<image.rows<<",  Col"<<image.cols<<", channel="<<image.channels()<<", image size="<<image.size<<endl;

	sharpen(image,image1);
	cv::imshow("image3",image1);
	cv::waitKey(5000);
	//cv::imwrite("xyz.jpg",image);
	return 0;


}
