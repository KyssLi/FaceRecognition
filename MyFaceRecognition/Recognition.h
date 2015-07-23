#pragma once

// ����ʶ����
class Recognition
{
public:
	Recognition();

	~Recognition() {}

	void set_path_csv(const std::string &);
	void set_path_train_datas(const std::string &);
	void set_username(const std::string &);
	void add_images(const cv::Mat &);
	void add_labels(const int &);
	void set_current_image(const cv::Mat &);
	void set_current_image(const std::string &);
	void set_current_label(const int &);

	void delete_image();
	void delete_label();
	void clear_images();
	void clear_labels();

	std::string get_path_csv() const;
	std::string get_path_train_datas() const;
	std::string get_username() const;
	cv::Mat get_current_image() const;
	int get_current_label() const;
	std::string get_error_msg() const;
	bool need_train() const;

	void initialization();
	void start_work();

	bool read_csv_file;	// �Ƿ��ȡ��csv�ļ�
	bool load_sak_file;	// �Ƿ���ع�sak�ļ�

protected:
	void read_csv(const std::string &, const char separator = ';');	// ��ȡ�ļ�������Ϣ
	void print_error_msg() const;	// ��ӡ������Ϣ
	int predict_label() const;
	void predict_label(int &, double &) const;

private:
	bool train;	// ����Ƿ���Ҫ����ѵ��
	std::string path_csv;	//	���csv�ļ����ڵ�·��
	std::string path_train_datas;	// ���ѵ���õ������ļ����ڵ�·��
	std::string username;	//	��¼�û�����
	std::vector<cv::Mat> images;	//	��Ŵ�csv�ļ��ж�ȡ����·�����ڵ�ͼƬ
	std::vector<int> labels;	// ���ͼƬ��csv�ļ��ж�Ӧ�ı��
	cv::Mat current_image;	// Ҫʶ��ĵ�ǰͼƬ
	int current_label;	// Ҫʶ���ͼƬ��Ӧ�ı��
	std::string error_msg;	//	������Ϣ
	cv::Ptr<cv::FaceRecognizer> model;	// ʶ����ģ��
	DISALLOW_COPY_AND_ASSIGN(Recognition);
};