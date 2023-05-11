#include <opencv2/highgui.hpp>

using namespace cv;

Mat preprocess(const Mat& img) {
    Mat ret;

    log(img + 1, ret);
    dft(ret, ret, DFT_COMPLEX_OUTPUT);

    return ret;
}

Mat postprocess(const Mat& img) {
    Mat ret;

    dft(img, ret, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
    exp(ret, ret);

    return ret - 1;
}

Mat homomorphic_filter(const Mat& img) {
    Mat ret = preprocess(img);

    const float d0 = 20.f;
    const float gamma_h = 3.5f;
    const float gamma_l = 0.7f;
    const float c = 1.f;

    for (Point p(0, 0); p.y < img.rows; p.y++) {
        for (p.x = 0; p.x < img.cols; p.x++) {
            float dx = p.x < img.cols / 2 ? p.x : img.cols - p.x;
            float dy = p.y < img.rows / 2 ? p.y : img.rows - p.y;
            float d = sqrtf(dx * dx + dy * dy);

            float gaussian = 1 - expf(-c * ((d * d) / (d0 * d0)));
            float h = (gamma_h - gamma_l) * gaussian + gamma_l;

            ret.at<Vec2f>(p) = ret.at<Vec2f>(p) * h;
        }
    }

    return postprocess(ret);
}

int main() {
    Mat img = imread("images/input.jpeg", 0);
    img.convertTo(img, CV_32FC1, 1 / 255.f);

    Mat filtered = homomorphic_filter(img);

    imshow("Original image", img);
    imshow("Filtered image", filtered);

    waitKey();
}
