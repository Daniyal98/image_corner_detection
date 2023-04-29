#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;

cv::Mat src, src_gray;
int thresh = 100;
int MAX_THRESH = 255;

void detectCornerHarris(int,void*)
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    cv::Mat dst = cv::Mat::zeros( src.size(), CV_32FC1 );
    cv::cornerHarris( src_gray, dst, blockSize, apertureSize, k );
    cv::Mat dst_norm, dst_norm_scaled;
    cv::normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
    cv::convertScaleAbs( dst_norm, dst_norm_scaled );
    for( int i = 0; i < dst_norm.rows ; i++ )
    {
        for( int j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                cv::circle( dst_norm_scaled, cv::Point(j,i), 5,  cv::Scalar(255), 2, 8, 0 );
            }
        }
    }
    cv::namedWindow("Harris Corner Detection");
    cv::imshow("Harris Corner Detection", dst_norm_scaled );
    cv::imwrite("corner_detection.jpg", dst_norm_scaled);
}


int main( int argc, char** argv )
{
    if(argc != 2) {
        std::cout << "Error!!\n\nPlease specify input file..\n";
        return -1;
    }
    src = cv::imread( argv[1] );
    if ( src.empty() )
    {
        std::cout << "Could not open or find the image!\n\n";
        std::cout << "Usage: " << argv[0] << " <Input image>\n" ;
        return -1;
    }
    cv::cvtColor( src, src_gray, cv::COLOR_BGR2GRAY );
    cv::namedWindow("Source Image");
    cv::imshow("Source Image", src );
    detectCornerHarris(0,0);
    cv::waitKey();
    return 0;
}