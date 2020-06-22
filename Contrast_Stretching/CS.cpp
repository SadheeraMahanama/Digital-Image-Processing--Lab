#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], IMREAD_COLOR); // Read the file
	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	Mat gr;
	cv::cvtColor(image, gr, cv::COLOR_BGR2GRAY); //create a gray image

	int h = gr.rows;
	int w = gr.cols;

	Mat CSt = gr.clone();
	int x = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			x = (int)gr.at<uchar>(i, j);

			if (x < 100) {
				CSt.at<uchar>(i, j) = (uchar)(cvRound((double)(5 / 148) * double(x)));
			}
			else if (x < 240) {
				CSt.at<uchar>(i, j) = (uchar)(cvRound((double)(245 / 72) * double(x - 148) + 5));
			}
			else {
				CSt.at<uchar>(i, j) = (uchar)(cvRound((double)(5 / 35) * double(x - 220) + 250));
			}
		}
	}

	cout << "Width and Height : " << w << ", " << h << endl;

	imwrite("cst.jpg", CSt);
	namedWindow("input image(LOW CONTRAST)", WINDOW_NORMAL);
	imshow("input image(LOW CONTRAST)", gr);
	namedWindow("output image(HIGH CONTRAST)", WINDOW_NORMAL);
	imshow("output image(HIGH CONTRAST)", CSt);
	waitKey(0);
	image.release();
	gr.release();

	return 0;

}