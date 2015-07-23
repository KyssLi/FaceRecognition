#include "stdafx.h"
#include "Recognition.h"
#include "FaceDetection.h"
#include "CameraCapture.h"

const std::string img_path(".\\data\\me.pgm");

int main(int argc, char **argv)
{
	// �������ʼ��
	FaceDetection mydetect;
	mydetect.initialization();	// �����Ѿ�����õķ�����
	if (mydetect.is_empty())
	{
		std::string error_msg = "���ؼ���������ʧ�ܣ�����ѵ�����Ƿ����°汾��";
		std::cout << error_msg << std::endl;
		return -1;
	}
	// ʶ������ʼ��
	Recognition myrec;
	myrec.initialization();
	// ����ͷ����
	CameraCapture mycap;
	mycap.set_s_mode(camera);	// ָ��Ϊ������ͷ����ͼƬ
	if (myrec.need_train())
	{
		std::cout << "��������ͷ�����󣬶�׼����ͷ�������»س���������ͼƬ��Ϣ��" << std::endl;
		mycap.cap_begin();
		//Sleep(3000);	// Ϊ�˱�֤����ɿ���ִ��
		if (!mycap.is_open())
		{
			std::cout << "������ͷʧ�ܣ������ԣ�" << std::endl;
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
	//Sleep(2000);
	mydetect.set_recognize(true);
	myrec.initialization();	// �ٴγ�ʼ��
	if (!mycap.is_open())
	{
		std::cout << "������ͷʧ�ܣ������ԣ�" << std::endl;
		return -1;
	}
	cv::Mat image;
	while (!mycap.is_stop())
	{
		system("cls");
		mycap >> image;
		mydetect.start_work(image);	// �������
		if (!mydetect.empty_image())	//	���û�м�⵽�������ͼ������
		{
			myrec.set_current_image(img_path);
			myrec.start_work();	// ʶ������
			mydetect.set_have_image(false);
		}
		if (cv::waitKey(30) == 27)	//	��Esc���˳�
			mycap.cap_release();
	}

	system("pause");
	return 0;
}