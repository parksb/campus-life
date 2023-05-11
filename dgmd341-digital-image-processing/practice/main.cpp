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

    // implementation for divSpectrums
    std::vector<Mat> kfc;
    split(kf, kfc);

    Mat denom, mags, h_inv;
    magnitude(kfc[0], kfc[1], mags); // ||H||^2 = (\sqrt{h_i^2 + h_r^2})^2
    multiply(mags, mags, denom);
    denom = 1 / denom; // make to 1

    for (Point pt(0, 0); pt.y < denom.rows; pt.y++) {
        for (pt.x = 0; pt.x < denom.cols; pt.x++) {
            float dx = pt.x > denom.cols / 2 ? denom.cols - pt.x : pt.x;
            float dy = pt.y > denom.rows / 2 ? denom.rows - pt.y : pt.y;
            float d = sqrtf(dx * dx + dy * dy);
            if (d > 20) denom.at<float>(pt) *= 0;
        }
    }

    Mat zz = Mat::zeros(denom.size(), denom.type());
    std::vector<Mat> dfc = { denom, zz };
    merge(dfc, h_inv);

    kfc[1] *= -1;
    merge(kfc, kf);
    mulSpectrums(sf, kf, ret, DFT_ROWS);
    mulSpectrums(ret, h_inv, ret, DFT_ROWS);

    dft(ret, ret, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);

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
