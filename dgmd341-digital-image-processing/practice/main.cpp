#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat degrade(const Mat& src, const Mat& kernel) {
    Mat sf, kf, rf, ret;

    dft(src, sf, DFT_COMPLEX_OUTPUT);
    dft(kernel, kf, DFT_COMPLEX_OUTPUT);
    mulSpectrums(sf, kf, rf, DFT_ROWS);
    dft(rf, ret, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);

    return ret;
}

Mat deconvolution(const Mat& src, const Mat& kernel) {
    Mat sf, kf, rf, ret;

    dft(src, sf, DFT_COMPLEX_OUTPUT);
    dft(kernel, kf, DFT_COMPLEX_OUTPUT);

    // to divide sf by kf.
    rf.create(sf.size(), sf.type());

    for (Point pt(0, 0); pt.y < rf.rows; pt.y++) {
        for (pt.x = 0; pt.x < rf.cols; pt.x++) {
            // (a + bi) / (c + di) = (a + bi) * (c - di) / (c * c + d * d)
            // {(a * c + b * d) + i(bc - ad)} / (c * c + d * d)
            float a = sf.at<Vec2f>(pt)[0];
            float b = sf.at<Vec2f>(pt)[1];
            float c = kf.at<Vec2f>(pt)[0];
            float d = kf.at<Vec2f>(pt)[1];

            float dx = pt.x > kf.cols / 2 ? kf.cols - pt.x : pt.x;
            float dy = pt.y > kf.rows / 2 ? kf.rows - pt.y : pt.y;
            float D = sqrtf(dx * dx + dy * dy);
            if (D > 20) rf.at<Vec2f>(pt) = Vec2f(0, 0);
            else rf.at<Vec2f>(pt) = Vec2f(a * c + b * d, b * c - a * d) / (c * c + d * d);
        }
    }

    dft(rf, ret, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);

    return ret;
}

int main() {
    Mat img = imread("images/house256.tiff", 0);

    Mat kernel = Mat::zeros(img.size(), CV_32FC1);
    circle(kernel, Point(0, 0), 15, Scalar(1), -1);
    circle(kernel, Point(img.cols, 0), 15, Scalar(1), -1);
    circle(kernel, Point(0, img.rows), 15, Scalar(1), -1);
    circle(kernel, Point(img.cols, img.rows), 15, Scalar(1), -1);
    kernel /= sum(kernel)[0];

    img.convertTo(img, CV_32F, 1 / 255.f);

    Mat deg = degrade(img, kernel);
    deg.convertTo(deg, CV_8U, 255);
    deg.convertTo(deg, CV_32F, 1 / 255.f);

    Mat res = deconvolution(deg, kernel);

    imshow("Image", img);
    imshow("Deg", deg);
    imshow("Res", res);
    // imshow("Kernel", kernel);

    waitKey();
}
