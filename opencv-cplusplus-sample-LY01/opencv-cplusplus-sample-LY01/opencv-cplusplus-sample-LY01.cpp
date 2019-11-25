// opencv-cplusplus-sample-LY01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void showImage(int x, int y, string windowName, Mat image)
{
	namedWindow(windowName);
	moveWindow(windowName, x, y);
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
		// Another sample image
		//originalImage = imread("Sample-02-ColorBlocks.jpg", CV_LOAD_IMAGE_COLOR);
		// Another sample image
		originalImage = imread("Sample-03-Face.jpg", CV_LOAD_IMAGE_COLOR);
		imageLoaded = true;
	}
#endif

	if (argc > 1)
	{
		// Load original image
		originalImage = imread(argv[1], CV_LOAD_IMAGE_COLOR);
		imageLoaded = true;
	}

	if (!imageLoaded)
	{
		// Something wrong when loading image
		return -1;
	}

	cv::Scalar colors[3];
	colors[0] = cv::Scalar(255, 90, 0);
	colors[1] = cv::Scalar(0, 255, 0);
	colors[2] = cv::Scalar(0, 0, 255);

	int thresholdA = 120;
	int thresholdB = 40;

	showImage(0, 0, "Original Image", originalImage);

	// 0 - Convert color image to grey-scale
	Mat greyImage;
	cvtColor(originalImage, greyImage, COLOR_BGR2GRAY);
	showImage(0, 300, "0 - COLOR_BGR2GRAY", greyImage);

	// A - Filter by grey-scale depth
	Mat thresholdImageA;
	threshold(greyImage, thresholdImageA, thresholdA, 255, THRESH_BINARY);
	showImage(400, 0, "A - threshold", thresholdImageA);
	// A - Invert color
	Mat invertedImageA;
	bitwise_not(thresholdImageA, invertedImageA);
	showImage(400, 300, "A - bitwise_not", invertedImageA);

	// B - Filter by grey-scale depth
	Mat thresholdImageB;
	threshold(greyImage, thresholdImageB, thresholdB, 255, THRESH_BINARY);
	showImage(800, 0, "B - threshold", thresholdImageB);
	// B - Invert color
	Mat invertedImageB;
	bitwise_not(thresholdImageB, invertedImageB);
	showImage(800, 300, "B - bitwise_not", invertedImageB);

	// 0 - Find the contours
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat contourOutput = greyImage.clone();
	cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	// A - Find the contours
	std::vector<std::vector<cv::Point> > contoursA;
	cv::Mat contourOutputA = thresholdImageA.clone();
	cv::findContours(contourOutputA, contoursA, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
	// B - Find the contours
	std::vector<std::vector<cv::Point> > contoursB;
	cv::Mat contourOutputB = thresholdImageB.clone();
	cv::findContours(contourOutputB, contoursB, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

	// 0 - Draw the contours
	cv::Mat contourImage(contourOutput.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	for (size_t idx = 0; idx < contours.size(); idx++)
	{
		cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
	}
	showImage(0, 600, "0 - contours", contourImage);
	// A - Draw the contours
	cv::Mat contourImageA(contourOutputA.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	for (size_t idx = 0; idx < contoursA.size(); idx++)
	{
		cv::drawContours(contourImageA, contoursA, idx, colors[idx % 3]);
	}
	showImage(400, 600, "A - contours", contourImageA);
	// B - Draw the contours
	cv::Mat contourImageB(contourOutputB.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	for (size_t idx = 0; idx < contoursB.size(); idx++) {
		cv::drawContours(contourImageB, contoursB, idx, colors[idx % 3]);
	}
	showImage(800, 600, "B - contours", contourImageB);

	// Wait
	waitKey(0);

	return 0;
}

