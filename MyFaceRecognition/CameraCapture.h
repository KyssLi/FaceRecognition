#pragma once

// ����CameraCapture���Ա����mode��ö������
enum Mode
{
	none,
	camera,
	video,
	both
};
// ����ͷ������
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
	Mode s_mode;	//	��ǰ����ģʽ
	cv::Mat frames;	// ��ǰ֡
	cv::VideoCapture cap;	// Opencv�Դ�����Ƶ������
	std::string path_save_frames;	// ֡����·����
	std::string path_video;	// ��Ƶ·��
	bool stop;	// �Ƿ������
	DISALLOW_COPY_AND_ASSIGN(CameraCapture);
};