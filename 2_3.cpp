#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
void colorReduce(cv::Mat image,cv::Mat image1, int div)
{
	int nl=image.rows;
	int nc=image.cols*image.channels();
	//result.create(image.rows, image.cols,image.type());
	for(int j=0;j<nl;j++)
	{
		uchar* data= image.ptr<uchar>(j);
		//uchar* data1= result.ptr<uchar>(j);
		uchar* data1= image1.ptr<uchar>(j);
		//cout<<"image.elemSize()->"<< image.elemSize()<<endl;
		for(int i=0;i<nc;i++)
		{
			//cout<<"image1.elemSize()->"<< image1.elemSize()<<endl;
			//std::cout<<"data"<<i<<"->"<<data[i]<<endl;
			data[i]=data1[i]/div*div+div/2;//copying the froma another image
			//data[i]=data[i]/2;
		}
	}


}
int main()
{
	cv::Mat image=cv::imread("img.jpg");
	cv::imshow("image",image);
	cv::waitKey(5000);
	
	cv::Mat image1=cv::imread("img1.jpg");
	cv::imshow("image",image1);
	cv::waitKey(5000);

	colorReduce(image,image1,64);
	cv::imshow("image",image);
	cv::waitKey(5000);
	return 0;


}
