// opencv4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

//int main()
//{
//    std::cout << "Hello World!\n"; 
//}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


#if 0
#include <opencv2/opencv.hpp>
//#include <opencv2/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	//if (argc != 2)
	//{
	//	cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
	//	return -1;
	//}
	Mat image;
	//String path_pic = "D:\\uidb1247\\Desktop\\la-ji\\4.jpg";
	String path_pic = "D:\\uidb1247\\Desktop\\la-ji\\can-id.png"; 
	//string path_pic = argv[1];

	image = imread(path_pic, IMREAD_COLOR); // Read the file
	if (image.empty()) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", image); // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window
	return 0;
}
#endif


#include <iostream> // for standard I/O
#include <string>   // for strings
#include <iomanip>  // for controlling float print precision
#include <sstream>  // string to number conversion
#include <opencv2/opencv.hpp>
//#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
//#include <opencv2/imgproc.hpp>  // Gaussian Blur
//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>  // OpenCV window I/O
using namespace std;
using namespace cv;

#define CV_COLOR_RED Scalar(0, 0, 255)
#define CV_COLOR_GREEN Scalar(0, 255, 0)

int main(int argc, char**argv)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}

	namedWindow("MyVideo", WINDOW_AUTOSIZE);
	CascadeClassifier faceDetector;
	CascadeClassifier eyeDetector;
	//if (!faceDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml"))

	bool flag_face =
		//faceDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt_tree.xml");
		//faceDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml");
		faceDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");

	bool flag_eye =
		//eyeDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml");
		eyeDetector.load("D:\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml");

	if (!flag_face || !flag_eye)
	{
		cout << "不能打开xml文件" << endl;
		return -1;
	}

	Size max = Size(60, 60);
	Size min = Size(10, 10);

	Mat srcImage, grayImage;
	Mat s1, s2;
	vector<Rect> objects;
	int div = 1;
	while (true)
	{
		if (cap.read(srcImage))
		{
			//grayImage.create(srcImage.size(), srcImage.type());
			cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
			//pyrDown(image, s1, Size(image.cols / div, image.rows / div));

			equalizeHist(grayImage, grayImage);
			//s2 = grayImage;
			
			//faceDetector.detectMultiScale(grayImage, objects, 1.1, 2, 0, min, max);
			faceDetector.detectMultiScale(grayImage, objects);
			//eyeDetector.detectMultiScale(grayImage, objects);
			for (int i = 0; i < objects.size(); i++)
			{
				Rect tmp = objects[i];
				tmp.x *= div;
				tmp.y *= div;
				tmp.width *= div;
				tmp.height *= div;
				rectangle(srcImage, tmp, CV_COLOR_RED);
			}

			//Rect rect(100, 100, 100, 100);
			//rectangle(srcImage, rect, CV_COLOR_GREEN);

			imshow("MyVideo", srcImage);
			if (objects.size() > 0)
			{
				cout << "找到目标" << endl;
				waitKey();
				break;
			}

			char key = waitKey(100);
			if (key == 13)
			{
				cout << "按下ENTER键" << endl;
				break;
			}
			if (key == 27)
			{
				//按下ESC退出
				break;
			}
		}
		else
		{
			cout << "不能从视频文件读取帧" << endl;
			return -1;
		}
	}
}




//----------------------------------------------------------------
void pic_compare(Mat m1, Mat m2);
void tmp_compare(Mat src, Mat tmp);

int main_compare(int argc, char**argv)
{
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cout << "不能打开视频文件" << endl;
		return -1;
	}

	//从3000ms开始播放视频
	//cap.set(CV_CAP_PROP_POS_MSEC, 3000);

	//获取视频的帧速率
	//double fps = cap.get(CAP_PROP_FPS);
	//cout << "帧/秒：" << fps << endl;

	namedWindow("MyVideo", WINDOW_AUTOSIZE);
	Mat frame_tg;
	cout << "请选择目标图像" << endl;
	Rect rect(100, 100, 300, 300);
	while (true)
	{
		if (cap.read(frame_tg))
		{
			rectangle(frame_tg, rect, Scalar(0, 0, 255), 2, LINE_8, 0);
			imshow("MyVideo", frame_tg);
			if (waitKey(50) == 13)
			{
				cout << "按下ENTER键" << endl;
				break;
			}
		}
		else
		{
			cout << "不能从视频文件读取帧" << endl;
			return -1;
		}
	}

	Mat frame_temp = Mat(frame_tg, rect);

	namedWindow("MyCap", WINDOW_AUTOSIZE);
	Mat frame_cap;
	while (true)
	{
		if (cap.read(frame_cap))
		{
			//pic_compare(frame_tg, frame_cap);
			tmp_compare(frame_cap, frame_temp);
			imshow("MyCap", frame_cap);
			if (waitKey(1000) == 13)
			{
				cout << "按下ENTER键" << endl;
				break;
			}
		}
		else
		{
			cout << "不能从视频文件读取帧" << endl;
			return -1;
		}
	}
	return 0;
}


double getPSNR(const Mat& I1, const Mat& I2);
Scalar getMSSIM(const Mat& I1, const Mat& I2);
void pic_compare(Mat m1, Mat m2)
{
	double psnrV = getPSNR(m1, m2);
	cout << setiosflags(ios::fixed) << setprecision(3) << psnrV << "dB";

	Scalar mssimV = getMSSIM(m1, m2);
	cout << " MSSIM: "
		<< " R " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[2] * 100 << "%"
		<< " G " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[1] * 100 << "%"
		<< " B " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[0] * 100 << "%"
		<< endl;
}

void tmp_compare(Mat src, Mat tmp)
{
	Mat s1, t1;
	int div = 2;
	//pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	pyrDown(src, s1, Size(src.cols / div, src.rows / div));
	pyrDown(tmp, t1, Size(tmp.cols / div, tmp.rows / div));

	//int match_method = TM_SQDIFF_NORMED; 
	//int match_method = TM_CCOEFF;
	int match_method = TM_CCOEFF_NORMED;
	int result_cols = s1.cols - t1.cols + 1;
	int result_rows = s1.rows - t1.rows + 1;
	Mat result;
	result.create(result_cols, result_rows, CV_32FC1);

	matchTemplate(s1, t1, result, match_method);
	//normalize(result, result, 0, 1, NORM_MINMAX, match_method, Mat());

	double minVal; double maxVal; 
	Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	cout << " minVal: " << minVal << " maxVal: " << maxVal << endl;
	cout << "x=" << matchLoc.x << " y=" << matchLoc.y << endl;

	Rect rect_tmp(matchLoc.x * div, matchLoc.y * div, tmp.cols, tmp.rows);
	rectangle(src, rect_tmp, Scalar(0, 0, 255), 2, LINE_8, 0);
}



//----------------------------------------------------------------
int main_back(int argc, char *argv[])
{
	if (argc != 5)
	{
		cout << "Not enough parameters" << endl;
		return -1;
	}
	stringstream conv;
	const string sourceReference = argv[1], sourceCompareWith = argv[2];
	int psnrTriggerValue, delay;
	conv << argv[3] << endl << argv[4];       // put in the strings
	conv >> psnrTriggerValue >> delay;        // take out the numbers
	int frameNum = -1;          // Frame counter
	VideoCapture captRefrnc(sourceReference), captUndTst(sourceCompareWith);
	if (!captRefrnc.isOpened())
	{
		cout << "Could not open reference " << sourceReference << endl;
		return -1;
	}
	if (!captUndTst.isOpened())
	{
		cout << "Could not open case test " << sourceCompareWith << endl;
		return -1;
	}
	Size refS = Size((int)captRefrnc.get(CAP_PROP_FRAME_WIDTH),
		(int)captRefrnc.get(CAP_PROP_FRAME_HEIGHT)),
		uTSi = Size((int)captUndTst.get(CAP_PROP_FRAME_WIDTH),
		(int)captUndTst.get(CAP_PROP_FRAME_HEIGHT));
	if (refS != uTSi)
	{
		cout << "Inputs have different size!!! Closing." << endl;
		return -1;
	}
	const char* WIN_UT = "Under Test";
	const char* WIN_RF = "Reference";
	// Windows
	namedWindow(WIN_RF, WINDOW_AUTOSIZE);
	namedWindow(WIN_UT, WINDOW_AUTOSIZE);
	moveWindow(WIN_RF, 400, 0);         //750,  2 (bernat =0)
	moveWindow(WIN_UT, refS.width, 0);         //1500, 2
	cout << "Reference frame resolution: Width=" << refS.width << "  Height=" << refS.height
		<< " of nr#: " << captRefrnc.get(CAP_PROP_FRAME_COUNT) << endl;
	cout << "PSNR trigger value " << setiosflags(ios::fixed) << setprecision(3)
		<< psnrTriggerValue << endl;
	Mat frameReference, frameUnderTest;
	double psnrV;
	Scalar mssimV;
	for (;;) //Show the image captured in the window and repeat
	{
		captRefrnc >> frameReference;
		captUndTst >> frameUnderTest;
		if (frameReference.empty() || frameUnderTest.empty())
		{
			cout << " < < <  Game over!  > > > ";
			break;
		}
		++frameNum;
		cout << "Frame: " << frameNum << "# ";
		psnrV = getPSNR(frameReference, frameUnderTest);
		cout << setiosflags(ios::fixed) << setprecision(3) << psnrV << "dB";
		if (psnrV < psnrTriggerValue && psnrV)
		{
			mssimV = getMSSIM(frameReference, frameUnderTest);
			cout << " MSSIM: "
				<< " R " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[2] * 100 << "%"
				<< " G " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[1] * 100 << "%"
				<< " B " << setiosflags(ios::fixed) << setprecision(2) << mssimV.val[0] * 100 << "%";
		}
		cout << endl;
		imshow(WIN_RF, frameReference);
		imshow(WIN_UT, frameUnderTest);
		char c = (char)waitKey(delay);
		if (c == 27) break;
	}
	return 0;
}
double getPSNR(const Mat& I1, const Mat& I2)
{
	Mat s1;
	absdiff(I1, I2, s1);       // |I1 - I2|
	s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
	s1 = s1.mul(s1);           // |I1 - I2|^2
	Scalar s = sum(s1);        // sum elements per channel
	double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
	if (sse <= 1e-10) // for small values return zero
		return 0;
	else
	{
		double mse = sse / (double)(I1.channels() * I1.total());
		double psnr = 10.0 * log10((255 * 255) / mse);
		return psnr;
	}
}
Scalar getMSSIM(const Mat& i1, const Mat& i2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	/***************************** INITS **********************************/
	int d = CV_32F;
	Mat I1, I2;
	i1.convertTo(I1, d);            // cannot calculate on one byte large values
	i2.convertTo(I2, d);
	Mat I2_2 = I2.mul(I2);        // I2^2
	Mat I1_2 = I1.mul(I1);        // I1^2
	Mat I1_I2 = I1.mul(I2);        // I1 * I2
	/*************************** END INITS **********************************/
	Mat mu1, mu2;                   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);
	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);
	Mat sigma1_2, sigma2_2, sigma12;
	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;
	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;
	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;
	Mat t1, t2, t3;
	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);                 // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);                 // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))
	Mat ssim_map;
	divide(t3, t1, ssim_map);        // ssim_map =  t3./t1;
	Scalar mssim = mean(ssim_map);   // mssim = average of ssim map
	return mssim;
}
