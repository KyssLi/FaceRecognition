#pragma once

// 定义CameraCapture类成员变量mode的枚举类型
enum Mode
{
	none,
	camera,
	video,
	both
};
// 摄像头捕获类
class CameraCapture
{
public:
	CameraCapture();

	~CameraCapture();

	void set_s_mode(const Mode &);
	void set_frames();
	void set_path_video(const std::string &);
	void set_path_save_frames(const std::string &);
	void set_stop(const bool &);

	Mode get_s_mode() const;
	cv::Mat get_frames() const;
	std::string get_path_video() const;
	std::string get_path_save_frames() const;
	bool is_stop() const;

	bool is_open() const;
	void save_frames() const;
	void save_frames(const cv::Mat &image) const;
	void show_frames() const;
	void cap_begin(const Mode &mode = camera, const std::string &path = "");
	void cap_release();

	CameraCapture& operator >>(cv::Mat &image);

protected:
	void camera_open(const int &device = 0);
	void video_open(const std::string &path);

private:
	Mode s_mode;	//	当前处理模式
	cv::Mat frames;	// 当前帧
	cv::VideoCapture cap;	// Opencv自带的视频捕获类
	std::string path_save_frames;	// 帧保存路径名
	std::string path_video;	// 视频路径
	bool stop;	// 是否进行中
	DISALLOW_COPY_AND_ASSIGN(CameraCapture);
};