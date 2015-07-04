#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <xutility>
#include <cstdlib>
#include <Windows.h>

#define DISALLOW_COPY_AND_ASSIGN(className)	\
	void operator=(const className &);	\
	className(const className &)

static int photo_numbers = 0;