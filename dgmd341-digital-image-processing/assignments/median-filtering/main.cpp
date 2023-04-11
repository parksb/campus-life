#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

std::tuple<int, int> replicate_padding(const Mat& img, const int x, const int y) {
    int ret_x = x;
    int ret_y = y;

    if (x < 0) {
        ret_x = 0;
    } else if (x > img.cols - 1) {
        ret_x = img.cols - 1;
    }

    if (y < 0) {
        ret_y = 0;
    } else if (y > img.rows - 1) {
        ret_y = img.rows - 1;
    }

    return std::make_tuple(ret_x, ret_y);
}

Mat median_filter(const Mat& img, const Size& sz) {
    assert(sz.width % 2 == 1);
    assert(sz.height % 2 == 1);

    Mat ret(img.size(), img.type());

    const int wx = (sz.width - 1) / 2;
    const int wy = (sz.height - 1) / 2;

    for (int y = 0; y < ret.rows; y++) {
        for (int x = 0; x < ret.cols; x++) {
            std::vector<uchar> values;

            for (int dy = -wy; dy <= wy; dy++) {
                for (int dx = -wx; dx <= wx; dx++) {
                    const auto [kernel_x, kernel_y] = replicate_padding(img, x + dx, y + dy);
                    values.push_back(img.at<uchar>(kernel_y, kernel_x));
                }
            }

            std::sort(values.begin(), values.end());
            ret.at<uchar>(y, x) = values[values.size() / 2];
        }
    }

    return ret;
}

int main() {
    Mat img = imread("images/salt-pepper.png", 0);
    img.convertTo(img, CV_8UC1);

    Mat filtered = median_filter(img, Size(5, 5));

    imshow("Image", img);
    imshow("Filtered Image", filtered);

    waitKey();
}
