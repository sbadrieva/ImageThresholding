//
//  ThresholdingClass.hpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 5/4/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#ifndef ThresholdingClass_hpp
#define ThresholdingClass_hpp

#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


void globalThresholding(Mat &src, Mat &dst,int T);
void multiLevelThresholding(Mat &src, Mat &dst);
bool niBlacksThreshold(Mat& src, Mat& dst,int kernel,double constant);
bool sauvolaThreshold(Mat& src, Mat& dst,int kernel,double constant);
bool localMeanThreshold(Mat& src, Mat& dst,int kernel);


#endif /* ThresholdingClass_hpp */
