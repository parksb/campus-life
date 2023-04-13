#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

using namespace cv;

Mat box(const Mat& img, const Size& sz) {
    assert(sz.width % 2 == 1); // only odd

    Mat ret(img.size(), img.type());
    int wx = (sz.width - 1) / 2;
    int wy = (sz.height - 1) / 2;

    for (int y = 0; y < ret.rows; y++) {
        for (int x = 0; x < ret.cols; x++) {
            int sum = 0;
            for (int dy = -wy; dy <= wy; dy++) {
                for (int dx = -wx; dx <= wx; dx++) {
                    int xx = x + dx;
                    int yy = y + dy;

                    // replicate padding
                    // if (x < 0) xx = 0;
                    // else if (xx > img.cols - 1) xx = img.cols - 1;
                    // if (yy < 0) yy = 0;
                    // else if (yy > img.rows - 1) yy = img.rows - 1;

                    // reflect 101 padding
                    // if (x < 0) xx = -xx;
                    // else if (xx > img.cols - 1) xx = img.cols * 2 - 2 - xx;
                    // if (y < 0) yy = -yy;
                    // else if (yy > img.rows - 1) yy = img.rows * 2 - 2 - yy;

                    // constant(zero) padding
                    // if (xx >= 0 && yy >= 0 && xx < img.cols && yy < img.rows) {
                    //   sum += img.at<uchar>(yy, xx);
                    // } else {
                    //   sum += 0;
                    // }


                    // WARP padding
                    sum += img.at<uchar>((yy + img.rows) % img.rows, (xx + img.cols) % img.cols);
                }
            }
            ret.at<uchar>(y, x) = sum / ((wx * 2 + 1) * (wy * 2 + 1));
        }
    }

    return ret;
}

Mat boxSep(const Mat& img, bool vert, int sz) {
    assert(sz % 2 == 1); // only odd

    Mat ret(img.size(), img.type());
    int w = (sz - 1) / 2;

    for (int y = 0; y < ret.rows; y++) {
        for (int x = 0; x < ret.cols; x++) {
            int sum = 0;
            if (!vert) {
                for (int dx = -x; dx <= w; dx++) {
                    int xx = x + dx;
                    sum += img.at<uchar>(y, (xx + img.cols) % img.cols);
                }
            } else {
                for (int dy = -y; dy <= w; dy++) {
                    int yy = y + dy;
                    sum += img.at<uchar>((yy + img.rows) % img.rows, x);
                }
            }
            ret.at<uchar>(y, x) = sum / (w * 2 + 1);
        }
    }

    return ret;
}

Mat gaussian(const Mat& img, const Size& sz) {
    assert(sz.width % 2 == 1); // only odd

    Mat ret(img.size(), img.type());
    int wx = (sz.width - 1) / 2;
    int wy = (sz.height - 1) / 2;

    for (int y = 0; y < ret.rows; y++) {
        for (int x = 0; x < ret.cols; x++) {
            int sum = 0;
            int wsum = 0;

            for (int dy = -wy; dy <= wy; dy++) {
                for (int dx = -wx; dx <= wx; dx++) {
                    int xx = x + dx;
                    int yy = y + dy;

                    // replicate padding
                    if (x < 0) xx = 0;
                    else if (xx > img.cols - 1) xx = img.cols - 1;
                    if (yy < 0) yy = 0;
                    else if (yy > img.rows - 1) yy = img.rows - 1;

                    float w = exp(-(dx * dx + dy * dy) / (wx * wx));
                    wsum += w;
                    sum += w * img.at<uchar>(yy, xx);
                }
            }

            ret.at<uchar>(y, x) = sum / wsum;
        }
    }

    return ret;
}

void visFreq(const Mat& image, Mat& output) {
    std::vector<Mat> ch;
    split(image, ch);
    magnitude(ch[0], ch[1], output);
    output += 1;
    log(output, output);
    output *= 0.1;
}

int main() {
    Mat img = imread("images/house256.tiff", 0);
    img.convertTo(img, CV_32FC1, 1 / 255.f);

    const float PI = 3.14159265358979323846;
    // Mat img(256, 256, CV_32FC1);
    Mat out;

    Mat F, out2, img2;
    dft(img, F, DFT_COMPLEX_OUTPUT);

    Mat ch[2];

    const float D0 = 2;
    for (Point pt(0, 0); pt.y < F.rows; pt.y++) {
        for (pt.x = 0; pt.x < F.cols; pt.x++) {
            Vec2f v = F.at<Vec2f>(pt.y, pt.x);
            float dx = pt.x < F.cols / 2 ? pt.x : F.cols - pt.x;
            float dy = pt.y < F.rows / 2 ? pt.y : F.rows - pt.y;
            float D = sqrtf(dx * dx + dy * dy);
            int H = 1 + 4 * PI * PI * D * D / (F.rows * F.cols);

            F.at<Vec2f>(pt.y, pt.x) = v * H;
        }
    }

    dft(F, img2, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
    imshow("Image2", img2);

    dft(img, out, DFT_COMPLEX_OUTPUT);
    imshow("Image", img);

    waitKey();
}
