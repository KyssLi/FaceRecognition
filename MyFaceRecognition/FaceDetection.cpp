#include "stdafx.h"
#include "FaceDetection.h"

FaceDetection::FaceDetection()
	:save(false),
	recognize(false),
	have_image(false),
	faces(),
	path_images(".\\data\\at\\s41\\"),
	path_classifier(".\\resource\\haarcascade_frontalface_alt.xml"),
	cascade_classifier(),
	in_image(),
	out_image()
{
}

void FaceDetection::set_save(const bool &s)
{
	save = s;
}

void FaceDetection::set_recognize(const bool &rec)
{
	recognize = rec;
}

void FaceDetection::set_have_image(const bool &have)
{
	have_image = have;
}

void FaceDetection::set_in_image(const cv::Mat &in)
{
	in_image = in.clone();
}

void FaceDetection::set_out_image(const cv::Mat &out)
{
	out_image = out.clone();
}

cv::Mat FaceDetection::get_in_image() const
{
	return in_image;
}

cv::Mat FaceDetection::get_out_image() const
{
	return out_image;
}

bool FaceDetection::empty_image() const
{
	return !have_image;
}

void FaceDetection::save_faces(const cv::Mat &image) const
{
	std::stringstream temp;
	std::string name = path_images, temp_string;
	temp << ++photo_numbers;
	temp >> temp_string;
	name += temp_string;
	name += ".pgm";
	cv::imwrite(name, image);
	std::ofstream out(".\\data\\at.csv", std::ofstream::app);
	out << name << ";" << 41 << "\n";
	out.close();
}

bool FaceDetection::is_empty() const
{
	return cascade_classifier.empty();
}

void FaceDetection::initialization()
{
	cascade_classifier.load(path_classifier);
}

void FaceDetection::start_work(const cv::Mat &image)
{
	in_image = image.clone();
	out_image = image.clone();
	cv::cvtColor(in_image, in_image, cv::COLOR_BGR2GRAY);	// 转为灰度图
	cv::equalizeHist(in_image, in_image);	// 直方图均衡化
	faces.clear();
	cascade_classifier.detectMultiScale(in_image, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
	if (!faces.empty())
	{
		for (int i = 0; i != faces.size(); ++i)
			cv::rectangle(out_image, faces[i], cv::Scalar(0, 0, 255), 1, 8, 0);	//	画出人脸部分的矩形框
		if (save)
		{
			faces[0].y -= static_cast<int>(0.1 * faces[0].height);
			faces[0].height += static_cast<int>(0.1 * faces[0].height);
			cv::resize(in_image(faces[0]), in_image, cv::Size(92, 112));	// 可自己定义图片大小
			save_faces(in_image);
			system("cls");
			std::cout << "OK，您已经保存了" << photo_numbers << "张图片了" << std::endl;
			save = false;
		}
		if (recognize)
		{
			faces[0].y -= static_cast<int>(0.1 * faces[0].height);
			faces[0].height += static_cast<int>(0.1 * faces[0].height);
			cv::resize(in_image(faces[0]), in_image, cv::Size(92, 112));
			cv::imwrite(".\\data\\me.pgm", in_image);
			set_have_image(true);
		}
	}
	cv::imshow("当前帧", out_image);
}
