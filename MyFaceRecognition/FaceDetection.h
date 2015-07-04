#pragma once

// ���������
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
	void start_work(const cv::Mat &);	// ��Ҫ����

private:
	bool save;	// �Ƿ񱣴�����ͼ��
	bool recognize;	// �Ƿ�ʶ��
	std::vector<cv::Rect> faces;	// ���������⵽������
	std::string path_images;	// ͷ��ͼƬ����·��
	std::string path_classifier;	//	Haar���������������ڵ�·��
	cv::CascadeClassifier cascade_classifier;	//	����������
	cv::Mat in_image;	// �������漴�����д����ͼƬ
	cv::Mat out_image;	// ������������ͼƬ
	DISALLOW_COPY_AND_ASSIGN(FaceDetection);
};