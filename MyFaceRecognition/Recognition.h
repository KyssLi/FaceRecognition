#pragma once

// 人脸识别类
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

	bool read_csv_file;	// 是否读取过csv文件
	bool load_sak_file;	// 是否加载过sak文件

protected:
	void read_csv(const std::string &, const char separator = ';');	// 读取文件数据信息
	void print_error_msg() const;	// 打印错误信息
	int predict_label() const;
	void predict_label(int &, double &) const;

private:
	bool train;	// 标记是否需要重新训练
	std::string path_csv;	//	存放csv文件所在的路径
	std::string path_train_datas;	// 存放训练好的数据文件所在的路径
	std::string username;	//	记录用户名称
	std::vector<cv::Mat> images;	//	存放从csv文件中读取到的路径所在的图片
	std::vector<int> labels;	// 存放图片在csv文件中对应的标号
	cv::Mat current_image;	// 要识别的当前图片
	int current_label;	// 要识别的图片对应的标号
	std::string error_msg;	//	错误信息
	cv::Ptr<cv::FaceRecognizer> model;	// 识别类模型
	DISALLOW_COPY_AND_ASSIGN(Recognition);
};