#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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

int main() {
    Mat image = imread("images/house256.tiff", 0);

    Mat image2 = box(image, Size(15, 15));
    Mat image3 = boxSep(image, false, 15);
    Mat image4 = boxSep(image, true, 15);

    Mat image5;
    boxFilter(image, image5, CV_8U, Size(15, 15));

    Mat image6 = gaussian(image, Size(15, 15));

    imshow("Image", image);
    imshow("Image2", image2);
    imshow("Image3", image3);
    imshow("Image4", image4);
    imshow("Image5", image5);
    imshow("Image6", image6);

    waitKey();
}
