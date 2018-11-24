#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
//g++ -ggdb majoritycolor.cpp -o face `pkg-config --cflags --libs opencv`
int main(int argc, char *argv[] )
{
	Mat3b img = imread(argv[1]);
	Mat hsv_img;
	//cv::namedWindow("Original");
	//imshow("Original",img);
	waitKey();
	//-----------cvt--------------	
	cvtColor(img,hsv_img,CV_BGR2HSV);
	Vec3b pixel;
	float color[7]={0,0,0,0,0,0,0};
	for(int i=0; i<hsv_img.rows; i++)
	{
		for (int j=0; j<hsv_img.cols; j++)
		{	
			pixel= hsv_img.at<Vec3b>(i,j);

			//cout<<"1= "<<pixel.val[2]<<"0= "<<pixel[3]<<endl;
			if(pixel.val[0]>=20 && pixel.val[0]<=30 && pixel[1]>=100 && pixel[1]<=255 && pixel[2]>=100 && pixel[2]<=255)
				color[2]++;//Yellow ////(20, 100, 100)to (30, 255, 255)
			else if (pixel[0]>11 && pixel[0]<15 && pixel[1]>100 && pixel[1]<255 && pixel[2]>20 && pixel[2]<255)
				color[1]++;//Orange ////(10, 100, 20), (25, 255, 255)//OR//(5,50,50) - (15,255,255)
			else if((pixel[0]>0 && pixel[0]<9 && pixel[1]>100 && pixel[1]<255 && pixel[2]>100 && pixel[2]<255) || (pixel[0]>151 && pixel[0]<180 && pixel[1]>100 && pixel[1]<255 && pixel[2]>100 && pixel[2]<255))
				color[3]++;//Red ////(0, 100, 100), cv::Scalar(10, 255, 255)//(160, 100, 100), cv::Scalar(179, 255, 255)
			else if(pixel[0]>110 && pixel[0]<130 && pixel[1]>50 && pixel[1]<255 && pixel[2]>50 && pixel[2]<255) 
				color[4]++;//Blue // //[110,50,50] to [130,255,255]
			else if(pixel[0]>65 && pixel[0]<80 && pixel[1]>60 && pixel[1]<255 && pixel[2]>60 && pixel[2]<255)
				color[5]++;//Green // //[60 - 15, 100, 50] to [60 + 15, 255, 255]//OR//[65,60,60] to [80,255,255]
			//else if(pixel[0]>5 && pixel[0]<30 && pixel[1]>100 && pixel[1]<255 && pixel[2]>20 && pixel[2]<200) 
			//	color[6]++;//brown //(20,100,100) to (30,255,255)
		}
	}

	cout<<"Orange= "<<color[1]<<endl;
	cout<<"Yellow= "<<color[2]<<endl;
	cout<<"Red= "<<color[3]<<endl;
	cout<<"Blue= "<<color[4]<<endl;
	cout<<"Green= "<<color[5]<<endl;
	//cout<<"Brown= "<<color[6]<<endl;
	//cout<<"size"<<hsv_img.rows*hsv_img.cols;

bool checkt=true,checkf=false;
//cout<<checkt;
if(color[1]<color[2]&&color[3]<color[2]&&color[4]<color[2]&&color[5]<color[2])
{
	//cout<<checkt;
	cout<<"Yellow color is dominant in the image"<<endl;
	return checkt;
}
else
{
	cout<<"Yellow color is not dominant in the image"<<endl;;
	return checkf;
}


//int K = 1;
//	int n = img.rows * img.cols;
//	Mat data = img.reshape(1, n);
//	cv::Mat another;
//	another.create(img.size(), img.type());
	
//	//data.convertTo(data, CV_32F);
//	vector<int> labels;
//	Mat1f colors;
//data.at<float>(1, 0) = colors(labels[1], 0);
//vector<int> labels;
//Mat1f colors;
// Cluster
//kmeans(data, K, labels, cv::TermCriteria(), 1, cv::KMEANS_PP_CENTERS, colors);
//cv::Mat cm_img;
//applyColorMap(img, cm_img, COLORMAP_JET);
//imshow("cm_img", cm_img);
//waitKey();
//cout<<data;
    return 0;
}
