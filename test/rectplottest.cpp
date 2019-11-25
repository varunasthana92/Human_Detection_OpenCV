/**
 * @file rectplottest.cpp
 * @brief unit testing of RectPlot class
 * @author Varun Asthana
 * @author Pruthvikumar Sanghavi
 *
 * Copyright [2019] Group14
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "rectplot.hpp"
#include "cam.hpp"

using ::testing::Return;
using ::testing::_;

class MockCam : public Cam {
 public:MOCK_METHOD1(readVideo,int(std::string dPath))
  ;MOCK_METHOD1(readFrameImage,int(cv::Mat &img))
  ;
};

TEST(RectPlotTest, mockCamFeed) {
  MockCam mockCam; /**< Declare mock class object */
  RectPlot a; /**< Declare RectPlot class object */
  /**
   * @brief Set the return value of readVideo method of mocked
   * class to 1 such that the return of method feed is 2
   */
  EXPECT_CALL(mockCam,readVideo("xyz")).Times(1).WillOnce(Return(1));
  EXPECT_EQ(2, a.feed(mockCam, "xyz"));
}

TEST(RectPlotTest, mockCamFeed1) {
  MockCam mockCam; /**< Declare mock class object */
  RectPlot a; /**< Declare RectPlot class object */
  /**
   * @brief Set the return value of readVideo method of mocked
   * class to 0 such that the return of method feed is 3
   */
  EXPECT_CALL(mockCam,readVideo(_)).Times(1).WillOnce(Return(0));
  EXPECT_EQ(3, a.feed(mockCam, "xyz"));
}

TEST(RectPlotTest, mockCamImg) {
  MockCam mockCam; /**< Declare mock class object */
  cv::Mat img; /**< Declare img variable of type cv::Mat */
  RectPlot a; /**< Declare RectPlot class object */
  /**
   * @brief Set the return value of readFrameImage method of mocked
   * class to 1 such that the return of method imgRead is 1
   */
  EXPECT_CALL(mockCam,readFrameImage(_)).Times(1).WillOnce(Return(1));
  EXPECT_EQ(1, a.imgRead(mockCam, img));
}

TEST(RectPlotTest, mockCamImg1) {
  MockCam mockCam; /**< Declare mock class object */
  cv::Mat img; /**< Declare img variable of type cv::Mat */
  RectPlot a; /**< Declare RectPlot class object */
  /**
   * @brief Set the return value of readFrameImage method of mocked
   * class to 0 such that the return of method imgRead is 0
   */
  EXPECT_CALL(mockCam,readFrameImage(_)).Times(1).WillOnce(Return(0));
  EXPECT_EQ(0, a.imgRead(mockCam, img));
}

TEST(RectPlotTest, testiplot) {
  RectPlot a;
  cv::Mat refImg1, refImg2, refImg3;
  refImg1 = cv::imread("../test/human01-01.png");
  /**
   * @brief Dummy data to check return value of plot method
   * by passing an actual image
   */
  EXPECT_DOUBLE_EQ(1, a.plot(refImg1, 10, 10, 10, 10));
  /**
   * @brief Dummy data to check return value of plot method
   * by not passing any actual image
   */
  EXPECT_DOUBLE_EQ(0, a.plot(refImg2, 10, 10, 10, 10));
}

TEST(RectPlotTest, testiworldCord) {
  RectPlot a;
  cv::Mat refImg1, refImg2, refImg3;
  refImg1 = cv::imread("../test/human01-01.png");
  /**
   * @brief Dummy data to assert correct operation of the plot method
   * by passing an actual image
   */
  ASSERT_TRUE(a.plot(refImg1, 0, 0, 10, 10));
  /**
   * @brief Dummy data to check return value of worldCord method
   * by passing an actual image
   */
  EXPECT_DOUBLE_EQ(1, a.worldCord(refImg1));
  /**
   * @brief Dummy data to check return value of worldCord method
   * by not passing any actual image
   */
  EXPECT_DOUBLE_EQ(0, a.worldCord(refImg2));
}
