#include "stdafx.h"
#include "CameraCapture.h"

CameraCapture::CameraCapture()
	:s_mode(none),
	frames(),
	cap(),
	path_save_frames(".\\data\\frames\\"),
	path_video(""),
	stop(true)
{
}

CameraCapture::~CameraCapture()
{
	cap.release();
}

void CameraCapture::set_s_mode(const Mode &mode)
{
	s_mode = mode;
}

void CameraCapture::set_frames()
{
	cap >> frames;
}

void CameraCapture::set_path_video(const std::string &path)
{
	path_video = path;
}

void CameraCapture::set_path_save_frames(const std::string &path)
{
	path_save_frames = path;
}

void CameraCapture::set_stop(const bool &flag)
{
	stop = flag;
}

Mode CameraCapture::get_s_mode() const
{
	return s_mode;
}

cv::Mat CameraCapture::get_frames() const
{
	return frames;
}

std::string CameraCapture::get_path_video() const
{
	return path_video;
}

std::string CameraCapture::get_path_save_frames() const
{
	return path_save_frames;
}

bool CameraCapture::is_stop() const
{
	return stop;
}

bool CameraCapture::is_open() const
{
	return cap.isOpened();
}

void CameraCapture::save_frames() const
{
	save_frames(frames);
}

void CameraCapture::save_frames(const cv::Mat &image) const
{
	std::string path = path_save_frames + "S_record.sak", temp;
	std::ifstream in(path, std::ifstream::in);
	std::stringstream change;
	int numbers = 0;
	if (!in)
	{
		std::ofstream out(path);
		if (out)
			out << numbers;
		out.close();
	}
	else
	{
		std::getline(in, temp);
		change << temp;
		change >> numbers;
		++numbers;
		in.close();
		std::ofstream out(path);
		if (out)
			out << numbers;
		out.close();
	}
	change.clear();
	temp.clear();
	change << numbers;
	change >> temp;
	std::string name = path_save_frames + "frames_" + temp + ".jpg";
	cv::imwrite(name, image);
}

void CameraCapture::show_frames() const
{
	cv::imshow("µ±Ç°Ö¡", frames);
}

void CameraCapture::camera_open(const int &device)
{
	cap.open(0);
	stop = false;
}

void CameraCapture::video_open(const std::string &path)
{
	cap.open(path);
	stop = false;
}


void CameraCapture::cap_begin(const Mode &mode, const std::string &path)
{
	switch (mode)
	{
	case none:
		break;
	case camera:
		camera_open(0);
		break;
	case video:
		video_open(path);
		break;
	case both:
		break;
	default:
		break;
	}
}

void CameraCapture::cap_release()
{
	stop = true;
	cap.release();
}

CameraCapture& CameraCapture::operator>>(cv::Mat &image)
{
	cap >> image;
	return *this;
}