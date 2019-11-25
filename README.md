# Human Obstacle Detector Using OpenCV Haar Cascade

[![Build Status](https://travis-ci.org/varunasthana92/Human_Detection_OpenCV.svg?branch=GMock_Extra_Credit)](https://travis-ci.org/varunasthana92/Human_Detection_OpenCV)
[![Coverage Status](https://coveralls.io/repos/github/varunasthana92/Human_Detection_OpenCV/badge.svg?branch=GMock_Extra_Credit)](https://coveralls.io/github/varunasthana92/Human_Detection_OpenCV?branch=GMock_Extra_Credit)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## Overview
To demonstrate the solitarty testing of a derived class, by mocking the base class via googlemock framework. In this example, the class "Cam" is being inherited by the class "RectPlot". RectPlot uses 2 functions of the Cam class, namely Cam::readVideo and Cam::readFrameImage. In order to do the unit testing of the class RectPlot without having any dependancy on the class Cam, googlemock framework has been utilized to mock the Cam class. 4 test cases in the file test/rectplottest.cpp have been made with a mocked class MockCam and an EXPECT_CALL macro to substitute for the return values of the Cam::readVideo and Cam::readFrameImage methods.

### Dependencies
```
Eigen 3.3.7
OpenCV 4.1.2
```
### Installing OpenCV
```
$ sudo apt-get update
$ sudo apt-get upgrade
$ sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
$ sudo apt-get install python3.5-dev python3-numpy libtbb2 libtbb-dev
$ sudo apt-get install libopencv-dev libjpeg-dev libpng-dev libtiff5-dev libjasper-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev
$ sudo apt-get install git
$ git clone https://github.com/opencv/opencv.git
$ cd opencv
$ mkdir build
$ cd build
$ cmake -D BUILD_TIFF=ON -D WITH_CUDA=OFF -D ENABLE_AVX=OFF -D WITH_OPENGL=OFF -D WITH_OPENCL=OFF -D WITH_IPP=OFF -D WITH_TBB=ON -D BUILD_TBB=ON -D WITH_EIGEN=OFF -D WITH_V4L=OFF -D WITH_VTK=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH= ../ ../opencv_contrib/modules ../
$ make -j4
$ sudo make install
$ sudo ldconfig
$ sudo apt-get install python-opencv
```
Check if everything is done by running below command. A version should be displayed.
```
$ python
>>> import cv2
>>> print(cv2.__version__)
'''after version is printed, exit out of python to commoand line'''
>>> exit()
```

### How to download and build
```
$ git clone -b GMock_Extra_Credit https://github.com/varunasthana92/Human_Detection_OpenCV.git
$ cd Human_Detection_OpenCV
$ mkdir build
$ cd build
$ cmake ..
$ make
```
### How to run rectplottest test
```
$ cd Human_Detection_OpenCV
$ cd build
$ ./test/cpp-test
```

### How to run cpplint and cppcheck
Use the below commands to run cppcheck and cpplint.
```
$ cd Human_Detection_OpenCV
$ cpplint $( find . -name \*.hpp -or -name \*.cpp | grep -vE -e "^./results" -e "^./include/Eigen")
$ cppcheck $( find . -name \*.hpp -or -name \*.cpp | grep -vE -e "^./results" -e "^./include/Eigen")
```
