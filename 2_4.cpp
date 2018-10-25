#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;

void colorReduce(cv::Mat image, int div=64)
{
	cv::Mat red;
	if (image.isContinuous())
	{ 	// no padded pixels
		image.reshape(1,  // new number of channels
			     1) ; // new number of rows
	}
	        cout<<"Row-----"<<red.rows<<",  Col-----"<<red.cols<<", channel-="<<red.channels()<<", image size="<<red.size<<endl;

cout<<"Row"<<image.rows<<",  Col"<<image.cols<<", channel="<<image.channels()<<", image size="<<image.size<<"  elemSize"<<image.elemSize()<<endl;
	int nl= image.rows; // number of lines
	int nc= image.cols * image.channels(); // total number of elements per line
	if (image.isContinuous())
	{// then no padded pixels
		nc= nc*nl;
		nl= 1;  // it is now a 1D array
	}
	int n= static_cast<int>(log(static_cast<double>(div))/log(2.0) + 0.5);
	cout<<"n="<<n<<endl;
	// mask used to round the pixel value
	uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0
	cout<<"mask"<<mask<<endl;
	uchar div2 = div >> 1; // div2 = div/2
	// this loop is executed only once
	// in case of continuous images
	for (int j=0; j<nl; j++)
	{
		uchar* data= image.ptr<uchar>(j);
		for (int i=0; i<nc; i++)
		{
			// process each pixel ---------------------
			*data &= mask;
			*data++ += div2;
			// end of pixel processing ----------------
		} // end of line
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
        cout<<"Row"<<image.rows<<",  Col"<<image.cols<<", channel="<<image.channels()<<", image size="<<image.size<<endl;

	colorReduce(image,64);
	cv::imshow("image",image);
	cv::waitKey(5000);
	return 0;


}
