#include "stdafx.h"
#include "Component.h"
#include "FaceDetection.h"
#include "CameraCapture.h"

int main(int argc, char **argv)
{
	// 分类器初始化
	FaceDetection mydetect;
	mydetect.initialization();
	if (mydetect.is_empty())
	{
		std::string error_msg = "加载级联分类器失败，请检查训练器是否是新版本的";
		std::cout << error_msg << std::endl;
		system("pause");
		return -1;
	}
	// 识别初始化
	Recognition myrec;
	myrec.initialization();
	// 摄像头调用
	CameraCapture mycap;
	mycap.set_s_mode(camera);
	if (myrec.need_train())
	{
		std::cout << "请在摄像头开启后，对准摄像头，并按下回车键来保存图片信息：" << std::endl;
		mycap.cap_begin();
		Sleep(3000);
		if (!mycap.is_open())
		{
			std::cout << "Sorry, open failure." << std::endl;
			system("pause");
			return -1;
		}
		// 处理每一帧
		cv::Mat image;
		while (!mycap.is_stop())
		{
			mycap >> image;
			mydetect.start_work(image);
			if (cv::waitKey(30) == 13)	// 按下回车键保存图片
			{
				mydetect.set_save(true);
			}
			else if (cv::waitKey(30) == 27)	//	按Esc键退出
				mycap.cap_release();
		}
		std::cout << "接下来进行训练：" << std::endl;
		myrec.start_work();
	}
	system("cls");

	std::cout << "识别模式：" << std::endl;
	mycap.cap_begin();
	Sleep(3000);
	mydetect.set_recognize(true);
	if (!mycap.is_open())
	{
		std::cout << "Sorry, open failure." << std::endl;
		system("pause");
		return -1;
	}
	cv::Mat image;
	while (!mycap.is_stop())
	{
		mycap >> image;
		mydetect.start_work(image);
		myrec.set_current_image(std::string(".\\data\\me.pgm"));
		myrec.start_work();
		if (cv::waitKey(30) == 27)	//	按Esc键退出
			mycap.cap_release();
	}

	system("pause");
	return 0;
}