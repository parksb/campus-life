#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

Mat connected_component(const Mat& img, const Mat& input) {
    Mat ret(img.size(), img.type());
    Mat se = getStructuringElement(MORPH_RECT, Size(5, 5));

    dilate(img, ret, se);
    bitwise_and(ret, input, ret);

    Mat diff;
    compare(ret, img, diff, CMP_NE);
    if (countNonZero(diff) > 0) {
        return connected_component(ret, input);
    }

    return ret;
}

void on_click(int event, int x, int y, int flag, void* param) {
    if (event != EVENT_LBUTTONDOWN) return;

    Mat* input = (Mat*) param;
    Mat seed = Mat::zeros(input->size(), input->type());
    seed.at<uchar>(y, x) = input->at<uchar>(y, x);

    Mat found = connected_component(seed, *input);
    imshow("Found", found);
}

int main() {
    Mat input = imread("images/input.png", 0);
    input.convertTo(input, CV_8UC1);

    imshow("Input", input);
    setMouseCallback("Input", on_click, &input);

    waitKey();
}
