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
		//originalImage = imread("Sample-03-Face.jpg", CV_LOAD_IMAGE_COLOR);
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

	int threshold, Y, X_shift;

	showImage(0, 0, "Original Image", originalImage);
	// Convert color image to grey-scale
	Mat greyImage;
	cvtColor(originalImage, greyImage, COLOR_BGR2GRAY);
	showImage(400, 0, "COLOR_BGR2GRAY", greyImage);

	threshold = 120;
	Y = 300;
	X_shift = 400;
	{
		// Filter by grey-scale depth
		Mat thresholdImage;
		cv::threshold(greyImage, thresholdImage, threshold, 255, THRESH_BINARY);
		showImage(0, Y, to_string(threshold)+" - threshhold", thresholdImage);
		// Invert color
		Mat invertedImage;
		bitwise_not(thresholdImage, invertedImage);
		showImage(X_shift, Y, to_string(threshold) + " - bitwise_not", invertedImage);

		cv::Mat kernel = cv::getStructuringElement(CV_SHAPE_CROSS, cv::Size(3, 3));
		std::vector<std::vector<cv::Point> > contours;
		cv::Mat contourOutput;
		cv::Mat contourImage;

		// Find the contours on threshold image
		contourOutput = thresholdImage.clone();
		cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		// Draw the contours
		contourImage = cv::Mat(contourOutput.size(), CV_8UC3, cv::Scalar(0, 0, 0));
		for (size_t idx = 0; idx < contours.size(); idx++)
		{
			cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
		}
		showImage(X_shift*2, Y, to_string(threshold) + " - contours", contourImage);

		// Find the contours of dilated inverted image
		cv::Mat dilated;
		cv::dilate(invertedImage, dilated, kernel, cv::Point(-1, -1), 9);
		contourOutput = dilated.clone();
		cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		// Draw the contours
		contourImage = cv::Mat(contourOutput.size(), CV_8UC3, cv::Scalar(0, 0, 0));
		for (size_t idx = 0; idx < contours.size(); idx++) {
			cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
		}
		showImage(X_shift*3, Y, to_string(threshold) + " - dilated contours", contourImage);
	}

	threshold = 60;
	Y = 600;
	X_shift = 400;
	{
		// Filter by grey-scale depth
		Mat thresholdImage;
		cv::threshold(greyImage, thresholdImage, threshold, 255, THRESH_BINARY);
		showImage(0, Y, to_string(threshold) + " - threshhold", thresholdImage);
		// Invert color
		Mat invertedImage;
		bitwise_not(thresholdImage, invertedImage);
		showImage(X_shift, Y, to_string(threshold) + " - bitwise_not", invertedImage);

		cv::Mat kernel = cv::getStructuringElement(CV_SHAPE_CROSS, cv::Size(3, 3));
		std::vector<std::vector<cv::Point> > contours;
		cv::Mat contourOutput;
		cv::Mat contourImage;

		// Find the contours on threshold image
		contourOutput = thresholdImage.clone();
		cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		// Draw the contours
		contourImage = cv::Mat(contourOutput.size(), CV_8UC3, cv::Scalar(0, 0, 0));
		for (size_t idx = 0; idx < contours.size(); idx++)
		{
			cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
		}
		showImage(X_shift * 2, Y, to_string(threshold) + " - contours", contourImage);

		// Find the contours of dilated inverted image
		cv::Mat dilated;
		cv::dilate(invertedImage, dilated, kernel, cv::Point(-1, -1), 9);
		contourOutput = dilated.clone();
		cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		// Draw the contours
		contourImage = cv::Mat(contourOutput.size(), CV_8UC3, cv::Scalar(0, 0, 0));
		for (size_t idx = 0; idx < contours.size(); idx++) {
			cv::drawContours(contourImage, contours, idx, colors[idx % 3]);
		}
		showImage(X_shift * 3, Y, to_string(threshold) + " - dilated contours", contourImage);
	}

	// Wait
	waitKey(0);

	return 0;
}

