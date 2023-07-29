#include <iostream>

#include <opencv2/highgui.hpp>

#include <iostream>
using namespace cv;

using namespace std;

Mat applyLaplacian(Mat image);

int main(int argc, char** argv)
{
	// read 16bit depth image
	cv::Mat input = cv::imread("img_signed_16bpp.png", IMREAD_ANYDEPTH);
	cv::Mat output = applyLaplacian(input);
	// write the laplacian filter result
	imwrite("img_unsigned_16bpp.png", output);
	std::cout << "0xE0F8E1EC" << std::endl;
	getchar();
}

Mat applyLaplacian(Mat image) {
	cv::Mat output = image.clone();
	// run on evrey pixel in the image and apply laplacian mask on it
	for (int y = 1; y < image.rows - 1; y++) {
		for (int x = 1; x < image.cols - 1; x++) {
			ushort z = image.at<ushort>(y, x);
			int sum = 
				4 * image.at<ushort>(y, x) -
				image.at<ushort>(y - 1, x) -
				image.at<ushort>(y + 1, x) -
				image.at<ushort>(y, x - 1) -
				image.at<ushort>(y, x + 1);
			output.at<ushort>(y, x) = sum;
		}
	}
	return output;
}