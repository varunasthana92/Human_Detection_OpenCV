# Human Obstacle Detector Using OpenCV Haar Cascade

[![Build Status](https://travis-ci.org/varunasthana92/Human_Detection_OpenCV.svg?branch=master)](https://travis-ci.org/varunasthana92/Human_Detection_OpenCV)
[![Coverage Status](https://coveralls.io/repos/github/varunasthana92/Human_Detection_OpenCV/badge.svg?branch=master)](https://coveralls.io/github/varunasthana92/Human_Detection_OpenCV?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

---

## Overview

Project was part of the academic coursework ENPM808X Software Development for Robotics at the Univeristy of Maryland-College Park.
<p align="center">
<img src="https://github.com/varunasthana92/Human_Detection_OpenCV/blob/master/additional_files/sampleOutput.gif" height = 400><br>
Sample output
</p>

Acme Robotics is developing a new series of robots to add to its portfolio– warehouse management robots (WMR). WMR's main function would be to carry goods from one place to another in a warehouse. One of the issue with such a market is: not all warehouses work on 100% automation, this means that WMRs would often be working in a workspace shared by humans. This raises the issue of safety for the humans working in the warehouse. As a safety counter-measure it is desired that WMRs should not collide with any human.

To achieve the goal of coallision avoidance of WMRs with humans, Acme Robotics reached out to our team to provide a ready to install solution. Our team is developing a Human Detector (HD) module which will identenfy the presence of any human in the vicinity of the robot (in its field of view) and provide the coordinates of the detected human in the robot's coordinate system. These coordinates can then be used by other modules of the WMR developed by Acme Robotics, like-real time path planning module, to modify the travel path of the WMR to avoid any possibility of a collision.

Our HD module works on the principles of supervised learning by utilizing Haar Cascade Classifier for object detection (humans in our case) from the OpenCV library. OpenCV library is covered under the 3-clause BSD License. HD module will use an on-board camera provided in the WMR to capture videos. But for our testing purposes, we will make use of a demo video. HD module will process the captured images (frame by frame) to detect the presence of any human, and then return their coordinates in the 2D-coordinate frame corresponding to the field of view of the robot. This data will contain bottom left (x,y) and top right (x,y) world coordinates of the enveloping rectangular box around the detected humans.

<p align="center">
<img src="https://github.com/varunasthana92/Human_Detection_OpenCV/blob/master/additional_files/expected_behaviour.png"><br>
Expected behavior of the HD Module (Images from: Machine Learning by Andrew Ng, Coursera)
</p>

## Approach
The presence of humans in a video feed is detected by the use of Haar Cascade Classifier from the OpenCV library. Cascade functionality can be used to detect objects by importing a trained model XML file. These XML files can be of a pre-trained model or can be generated using command prompt utility of the OpenCV. For this project our team created a new model from scratch using pre-acquired training dataset. We will thus first higlight the steps to generate a new cascade model. Before we can proceed with the model generation, we first need to install OpenCV and related dependancies.

### Dependencies
```
Eigen 3.3.7
OpenCV 4.1.2
```
Eigen has been provided in the repository. And install instructions for OpenCV are provided below.

#### Installing OpenCV
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

### How to create and train a Haar Cascade model
For any deep learning based training and model generation the most important thing is to have a dataset of POSITIVE and NEGATIVE instances. In this case the postive instances refer to a set of images which contain human object(s) and negative instances refer to a set of images which do not contain humans. Positive dataset is taken from [Horses or Humans](https://www.kaggle.com/sanikamal/horses-or-humans-dataset) and negative dataset is taken from [INRIA Person Dataset](http://pascal.inrialpes.fr/data/human/).

Follow the below steps-
1) Create a directory <_model_> and cd into it.
2) Download the images in two different folders namely, pos and neg.
3) Label the positive images and create a info.lst file in the <pos> directory with entiries for each image to specify the object position: <_filename_> <no_of_instances> <left_top_x_coordinate> <left_top_y_coordinate> <_width_> <_height_>
<p align="center">
<img src="https://github.com/varunasthana92/Human_Detection_OpenCV/blob/master/additional_files/info_list.png">
</p>

4) In the <_model_> directory create a background text file "bgNeg.txt" with information of path of each negatives instances <filepath_filename>
<p align="center">
<img src="https://github.com/varunasthana92/Human_Detection_OpenCV/blob/master/additional_files/bgNeg.png">
</p>


5) From the <_model_> run the below command in terminal to generate a vector file. Lets name that file as "positives.vec". Here -w and -h are the training model parameters (ensure that the object in positive instances have similar width/height ratio for better performance)

```
opencv_createsamples -info pos/info.lst -num 527 -w 36 -h 110 -vec positives.vec
```

6) mkdir data in <_model_>

7) Lastly, tain your Haar Cascade Model from the <_model_> directory.
```
opencv_traincascade -data data -vec positives.vec -bg bgNeg.txt -numPos 500-numNeg 800 -numStages 10 -w 36 -h 110
```
8) Cascade.xml file will be generated in the "data" folder. You may now use this file with our repository by renaming it to "humanDetectCascade.xml" and place it in "app" folder (replacing the exsting one, provided by our team).

Training is a time demanding and computationally expensive process. Larger the number of instances, traininig stages, -w and -h parametrs, the more time it takes. We used 527 positive instances with w=36 and h=110 over 10 stages, and it took 16hrs (approx.) for one model to train.

# How to build
```
$ cd Human_Detection_OpenCV
$ mkdir build
$ cd build
$ cmake ..
$ make
```
# How to run demo
```
$ cd Human_Detection_OpenCV
$ cd build
$ ./app/humanDetect
```
# How to run tests
```
$ cd Human_Detection_OpenCV
$ cd build
$ ./test/cpp-test
```
# Known issues/bugs

1) With small set of training data, the quality of output is not good. Many false positives are captured.

# Installing Doxygen and generating doxygen documentation
```
$ git clone https://github.com/doxygen/doxygen.git
$ cd doxygen
$ mkdir build
$ cd build
$ cmake -G "Unix Makefiles" ..
$ make
$ sudo make install
$ cd Human_Detection_OpenCV
$ doxygen -g DoxyConfig
```
The above commands are used to install doxygen and generate doxygen configuration file. This file has been provided in the repository as DoxyConfig with the required flags.
To generate doxygen documentaion-
```
$ cd Human_Detection_OpenCV
$ doxygen DoxyConfig
```
We have already provided the generated documents in the "docs" directory in the repository.

# Function that gives the world coordinates
```
A homogeneous matrix trasformation and lens formula are used to convert from the image cordinate
to the world cordinate.
The image origin is at the top left corner with positive x axis pointing towards right, and positive
y axis pointing towards bottom. While the world coordinate (view point of robot) is set with origin
at the center of view and positive x axis towards right and positive y axis pointing upwards.

This give the roational matrix as
R= [ 1  0  0
     0 -1  0
     0  0 -1]

Translation from world origin to image origin
T = [ -Image width /2
      Image height /2
	    0 	     ]

Homogenenous matrix from image to world frame is :

H= [ R T
     0 1]

World Cordinate = H* Image Cordinate (in pixel)
(with depth z of detected object is assumed to be 8ft inside the image plane) 

Units considered by us gives the world coordinates in feets.
```

