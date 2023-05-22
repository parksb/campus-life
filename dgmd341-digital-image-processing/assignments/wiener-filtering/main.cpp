#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat wiener_filter_manual(const Mat& src, const Mat& ker, const int k) {
    Mat srcf, kerf, retf, ret;

    dft(src, srcf, DFT_COMPLEX_OUTPUT);
    dft(ker, kerf, DFT_COMPLEX_OUTPUT);

    retf.create(srcf.size(), srcf.type());

    for (Point p(0, 0); p.y < retf.rows; p.y++) {
        for (p.x = 0; p.x < retf.cols; p.x++) {
            float srcr = srcf.at<Vec2f>(p)[0];
            float srci = srcf.at<Vec2f>(p)[1];
            float kerr = kerf.at<Vec2f>(p)[0];
            float keri = kerf.at<Vec2f>(p)[1];

            float g = srcr + srci;
            float h = kerr + keri;
            float m = kerr * kerr + keri * keri;

            retf.at<Vec2f>(p) = Vec2f(
                kerr * srcr + keri * srci,
                ((kerr - keri) / m) * (m / (m + k)) * g
            ) / m;
        }
    }

    dft(retf, ret, DFT_INVERSE | DFT_SCALE | DFT_REAL_OUTPUT);

    return ret;
}

Mat wiener_filter_auto(const Mat& src, const Mat& ker, const int k) {
    Mat srcf, kerf;

    dft(src, srcf, DFT_COMPLEX_OUTPUT);
    dft(ker, kerf, DFT_COMPLEX_OUTPUT);

    Mat a;
    Mat ones = Mat::ones(srcf.size(), srcf.type());
    divSpectrums(ones, kerf, a, DFT_ROWS);

    Mat mag;
    magnitude(kerf, kerf, mag);

    Mat b;
    Mat h2 = mag * mag;
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
    input1.convertTo(input1, CV_32F, 1 / 255.f);

    Mat input2 = imread("images/input2.png", 0);
    input2.convertTo(input2, CV_32F, 1 / 255.f);

    Mat kernel = imread("images/kernel.png", 0);
    kernel.convertTo(kernel, CV_32F, 1 / sum(kernel)[0]);

    Mat filtered1 = wiener_filter_auto(input1, kernel, 2);
    Mat filtered2 = wiener_filter_auto(input2, kernel, 7);

    imshow("Input 1", input1);
    imshow("Input 2", input2);
    imshow("Filtered 1", filtered1);
    imshow("Filtered 2", filtered2);

    waitKey();
}
