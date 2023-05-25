#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat wiener_filter(const Mat& src, const Mat& ker, const float k) {
    Mat srcf, kerf;

    dft(src, srcf, DFT_COMPLEX_OUTPUT);
    dft(ker, kerf, DFT_COMPLEX_OUTPUT);

    Mat a;
    Mat ones = Mat::ones(srcf.size(), srcf.type());
    divSpectrums(ones, kerf, a, DFT_ROWS);

    Mat kerfc[2], mag, h2;
    split(kerf, kerfc);
    magnitude(kerfc[0], kerfc[1], mag);
    multiply(mag, mag, h2);

    Mat zeros = Mat::zeros(h2.size(), h2.type());
    std::vector<Mat> h2c = { h2, zeros };
    merge(h2c, h2);

    Mat b;
    divSpectrums(h2, h2 + k, b, DFT_ROWS);

    Mat c, retf;
    mulSpectrums(a, b, c, DFT_ROWS);
    mulSpectrums(c, srcf, retf, DFT_ROWS);

    Mat ret;
    dft(retf, ret, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);

    return ret;
}

int main() {
    Mat input1 = imread("images/input1.png", 0);
    input1.convertTo(input1, CV_32FC1, 1 / 255.f);

    Mat input2 = imread("images/input2.png", 0);
    input2.convertTo(input2, CV_32FC1, 1 / 255.f);

    Mat kernel = imread("images/kernel.png", 0);
    kernel.convertTo(kernel, CV_32FC1, 1 / sum(kernel)[0]);

    Mat filtered1 = wiener_filter(input1, kernel, 0.0005f);
    Mat filtered2 = wiener_filter(input2, kernel, 0.002f);

    imshow("Input 1", input1);
    imshow("Input 2", input2);
    imshow("Filtered 1", filtered1);
    imshow("Filtered 2", filtered2);

    waitKey();
}
