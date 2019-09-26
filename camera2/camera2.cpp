// camera2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int camera_size[] = {
	1024,	768,
	600,	480,
};


int main(int argc, const char** argv)
{
	VideoCapture cap1;
	int size_index = 1;

	int img_width = camera_size[size_index * 2];
	int img_height = camera_size[size_index * 2 + 1];

	cap1.open(0);
	cap1.set(CAP_PROP_FRAME_WIDTH, img_width);
	cap1.set(CAP_PROP_FRAME_HEIGHT, img_height);

	if (!cap1.isOpened())
	{
		cout << "摄像头1打开失败!" << endl;
		return -1;
	}

	Rect rect_left(0, 0, img_width / 2, img_height);
	Rect rect_right(img_width / 2, 0, img_width / 2, img_height);
	Mat frame1, frame_L, frame_R;
	while (1)
	{
		cap1 >> frame1;
		frame_L = frame1(rect_left);
		frame_R = frame1(rect_right);

		imshow("Video_all", frame1);
		//imshow("Video_left", frame_L);
		//imshow("Video_right", frame_R);

		char key = waitKey(100);
		if (key == 27)
		{
			//按下ESC退出
			break;
		}
	}

}

