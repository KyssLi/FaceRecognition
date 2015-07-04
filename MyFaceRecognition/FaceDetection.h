#pragma once

// 人脸检测类
class FaceDetection
{
public:
	FaceDetection();

	~FaceDetection() {}

	void set_save(const bool &);
	void set_recognize(const bool &);
	void set_in_image(const cv::Mat &);
	void set_out_image(const cv::Mat &);

	cv::Mat get_in_image() const;
	cv::Mat get_out_image() const;

	void save_faces(const cv::Mat &) const;
	bool is_empty() const;
	void initialization();
	void start_work(const cv::Mat &);	// 主要处理

private:
	bool save;	// 是否保存脸部图像
	bool recognize;	// 是否识别
	std::vector<cv::Rect> faces;	// 用来保存检测到的人脸
	std::string path_images;	// 头像图片保存路径
	std::string path_classifier;	//	Haar特征检测分类器所在的路径
	cv::CascadeClassifier cascade_classifier;	//	级联分类器
	cv::Mat in_image;	// 用来保存即将进行处理的图片
	cv::Mat out_image;	// 用来输出结果的图片
	DISALLOW_COPY_AND_ASSIGN(FaceDetection);
};