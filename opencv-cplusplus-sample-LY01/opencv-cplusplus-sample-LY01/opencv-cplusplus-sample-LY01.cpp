// opencv-cplusplus-sample-LY01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void showImage(string windowName, Mat image)
{
	namedWindow(windowName);
	imshow(windowName, image);
}

int main(int argc, char** argv)
{
	Mat originalImage;
	bool imageLoaded = false;

#if defined _DEBUG
	if (argc < 2)
	{
		// Default image for demo
		originalImage = imread("Sample-01-Rock.jpg", CV_LOAD_IMAGE_COLOR);
		imageLoaded = true;
	}
#endif

	if (argc > 1)
	{
		// Load original image
		Mat originalImage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
		imageLoaded = true;
	}

	if (!imageLoaded)
	{
		return -1;
	}

	showImage("Rock 1 - Original Image", originalImage);

	// Convert color image to grey-scale
	Mat greyImage;
	cvtColor(originalImage, greyImage, COLOR_BGR2GRAY);
	showImage("Rock 2 - cvtColor(originalImage, greyImage, COLOR_BGR2GRAY)", greyImage);

	// Filter by grey-scale depth
	Mat thresholdImage;
	threshold(greyImage, thresholdImage, 120, 255, THRESH_BINARY);
	showImage("Rock 3 - threshold(greyImage, thresholdImage, 120, 255, THRESH_BINARY)", thresholdImage);

	// Invert color
	Mat invertedImage;
	bitwise_not(thresholdImage, invertedImage);
	showImage("Rock 4 - bitwise_not(thresholdImage, invertedImage);", invertedImage);

	// Wait
	waitKey(0);

	// This comment line is added by PatrickWangBit on web

	// This comment line is added by LiYanBit from VS2015@Home

	return 0;
}

