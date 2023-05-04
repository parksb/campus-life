#include <opencv2/highgui.hpp>

using namespace cv;

Mat gaussian_highpass_filter(const Mat& img) {
    Mat ret(img.size(), img.type());
    const float D0 = 2.f;

    for (Point p(0, 0); p.y < img.rows; p.y++) {
        for (p.x = 0; p.x < img.cols; p.x++) {
            float dx = p.x - img.cols / 2.f;
            float dy = p.y - img.rows / 2.f;
            float d = 1 - exp(-(dx * dx + dy * dy) / (2 * D0 * D0));

            ret.at<Vec2f>(p.y, p.x) = img.at<Vec2f>(p.y, p.x) * d;
        }
    }

    return ret;
}

Mat preprocess(const Mat& img) {
    Mat ret = img;

    ret += 1;
    log(ret, ret);
    dft(ret, ret, DFT_COMPLEX_OUTPUT);

    return ret;
}

Mat postprocess(const Mat& img) {
    Mat ret = img;

    dft(ret, ret, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
    exp(ret, ret);
    ret -= 1;

    return ret;
}

int main() {
    Mat img = imread("images/input.jpeg", 0);
    img.convertTo(img, CV_32FC1, 1 / 255.f);

    Mat preprocessed = preprocess(img);
    Mat filtered = gaussian_highpass_filter(preprocessed);
    Mat postprocessed = postprocess(filtered);

    imshow("Original image", img);
    imshow("Filtered image", postprocessed);

    waitKey();
}
