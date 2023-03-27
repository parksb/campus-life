#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main() {
    Mat image = imread("images/house512.tiff", 0);
    Mat equalized;
    cv::equalizeHist(image, equalized);
    imshow("Image", image);
    imshow("Equalized", equalized);
    waitKey();
}
