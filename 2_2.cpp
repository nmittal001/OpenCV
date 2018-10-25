#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
void colorReduce(cv::Mat image, int div)
{
	int nl=image.rows;
	int nc=image.cols*image.channels();
	for(int j=0;j<nl;j++)
	{
		uchar* data= image.ptr<uchar>(j);
		for(int i=0;i<nc;i++)
		{
			//std::cout<<"data"<<i<<"->"<<data[i]<<endl;
			data[i]=data[i]/div*div+div/2;
			//data[i]=data[i]/2;
		}
	}


}
int main()
{
	cv::Mat image=cv::imread("img.jpg");
	cv::imshow("image",image);
	cv::waitKey(5000);
	colorReduce(image,64);
	cv::imshow("image",image);
	cv::waitKey(5000);
	return 0;


}
