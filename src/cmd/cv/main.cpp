#include <iostream>
#include <opencv2/opencv.hpp>  // OpenCV主头文件


int main() {
  cv::Mat image = cv::imread("scatter.jpg");

  if (image.empty()) {
    std::cout << "Could not open or find the image!" << std::endl;
    return -1;
  }

  cv::imshow("Display Window", image);

  // 等待按键操作（0表示无限等待）
  std::cout << "Press any key on the image window to exit..." << std::endl;
  cv::waitKey(0);
  cv::destroyAllWindows();

  return 0;
}