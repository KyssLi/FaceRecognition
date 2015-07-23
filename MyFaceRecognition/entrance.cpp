#include "stdafx.h"
#include "Recognition.h"
#include "FaceDetection.h"
#include "CameraCapture.h"

const std::string img_path(".\\data\\me.pgm");

int main(int argc, char **argv)
{
	// 检测器初始化
	FaceDetection mydetect;
	mydetect.initialization();	// 加载已经分类好的分类器
	if (mydetect.is_empty())
	{
		std::string error_msg = "加载级联分类器失败，请检查训练器是否是新版本的";
		std::cout << error_msg << std::endl;
		return -1;
	}
	// 识别器初始化
	Recognition myrec;
	myrec.initialization();
	// 摄像头调用
	CameraCapture mycap;
	mycap.set_s_mode(camera);	// 指定为从摄像头调入图片
	if (myrec.need_train())
	{
		std::cout << "请在摄像头开启后，对准摄像头，并按下回车键来保存图片信息。" << std::endl;
		mycap.cap_begin();
		//Sleep(3000);	// 为了保证代码可靠的执行
		if (!mycap.is_open())
		{
			std::cout << "打开摄像头失败，请重试！" << std::endl;
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
	//Sleep(2000);
	mydetect.set_recognize(true);
	myrec.initialization();	// 再次初始化
	if (!mycap.is_open())
	{
		std::cout << "打开摄像头失败，请重试！" << std::endl;
		return -1;
	}
	cv::Mat image;
	while (!mycap.is_stop())
	{
		system("cls");
		mycap >> image;
		mydetect.start_work(image);	// 检测人脸
		if (!mydetect.empty_image())	//	如果没有检测到人脸，就继续检测
		{
			myrec.set_current_image(img_path);
			myrec.start_work();	// 识别人脸
			mydetect.set_have_image(false);
		}
		if (cv::waitKey(30) == 27)	//	按Esc键退出
			mycap.cap_release();
	}

	system("pause");
	return 0;
}