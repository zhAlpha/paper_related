#include <iostream>

#include "opencv2/opencv.hpp"
#include "../include/EDLines.h"

#define WAIT_TIME 4000

using namespace cv;

int main(int argc, const char * argv[])
{

    //Mat imageRGB = imread("/Users/demonfromrussia/Desktop/photo-1480714378408-67cf0d13bc1b.jpg");
   // Mat image = imread("/Users/demonfromrussia/Desktop/photo-1480714378408-67cf0d13bc1b.jpg", 0);

    Mat imageRGB;
    imageRGB = imread("/home/zh/1_paper_related/opencv_idz/opencv_idz/bin/1_1.jpg");

    Mat image ;
    image = imread("/home/zh/1_paper_related/opencv_idz/opencv_idz/bin/1_2.jpg");//, 0);

    EDLines lineHandler = EDLines(image);
    Mat outputImage;

    imshow("INPUT IMAGE", imageRGB);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.getSmoothImage();
    imshow("SMOOTHING", outputImage);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.getGradImage();
    imshow("GRADIENT AND THRESHOLDING", outputImage);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.getAnchorImage();
    imshow("ANCHORING AND CONNECTING THEM", outputImage);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.getEdgeImage();
    imshow("EDGES", outputImage);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.getLineImage();
    imshow("ED LINES", outputImage);
    waitKey(WAIT_TIME);
    outputImage = lineHandler.drawOnImage();
    imshow("ED LINES OVER SOURCE IMAGE", outputImage);
    waitKey(0);
    return 0;
}
