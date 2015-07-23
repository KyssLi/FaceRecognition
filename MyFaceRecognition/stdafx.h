#pragma once

// 预编译头文件
#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <xutility>
#include <cstdlib>
//#include <Windows.h> for "Sleep" function

#define DISALLOW_COPY_AND_ASSIGN(className)	\
	void operator=(const className &);	\
	className(const className &)

static int photo_numbers = 0;	// 用于临时记录用户保存图片的数量