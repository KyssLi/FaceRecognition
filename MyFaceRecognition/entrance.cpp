#include "stdafx.h"
#include "Component.h"
#include "FaceDetection.h"
#include "CameraCapture.h"

int main(int argc, char **argv)
{
	// ��������ʼ��
	FaceDetection mydetect;
	mydetect.initialization();
	if (mydetect.is_empty())
	{
		std::string error_msg = "���ؼ���������ʧ�ܣ�����ѵ�����Ƿ����°汾��";
		std::cout << error_msg << std::endl;
		system("pause");
		return -1;
	}
	// ʶ���ʼ��
	Recognition myrec;
	myrec.initialization();
	// ����ͷ����
	CameraCapture mycap;
	mycap.set_s_mode(camera);
	if (myrec.need_train())
	{
		std::cout << "��������ͷ�����󣬶�׼����ͷ�������»س���������ͼƬ��Ϣ��" << std::endl;
		mycap.cap_begin();
		Sleep(3000);
		if (!mycap.is_open())
		{
			std::cout << "Sorry, open failure." << std::endl;
			system("pause");
			return -1;
		}
		// ����ÿһ֡
		cv::Mat image;
		while (!mycap.is_stop())
		{
			mycap >> image;
			mydetect.start_work(image);
			if (cv::waitKey(30) == 13)	// ���»س�������ͼƬ
			{
				mydetect.set_save(true);
			}
			else if (cv::waitKey(30) == 27)	//	��Esc���˳�
				mycap.cap_release();
		}
		std::cout << "����������ѵ����" << std::endl;
		myrec.start_work();
	}
	system("cls");

	std::cout << "ʶ��ģʽ��" << std::endl;
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
		if (cv::waitKey(30) == 27)	//	��Esc���˳�
			mycap.cap_release();
	}

	system("pause");
	return 0;
}