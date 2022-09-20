//
//  ThresholdingClass.cpp
//  OpenCv
//
//  Created by Shokhina Badrieva on 5/4/21.
//  Copyright © 2021 Shokhina Badrieva. All rights reserved.
//

#include "ThresholdingClass.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;


void globalThresholding(Mat &src, Mat &dst,int T){
    
    int imgRows = src.size().height;
    int imgCols = src.size().width;
    dst=Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    for(int i=0;i<imgRows;i++){
        for( int j=0;j<imgCols;j++){
            int val=src.at<uchar>(i,j);
            if(val<=T){
                dst.at<uchar>(i,j)=0;
            }
            else{
                dst.at<uchar>(i,j)=255;
            }
            
            
        }
    }
    
}

void multiLevelThresholding(Mat &src, Mat &dst){
    
    int imgRows = src.size().height;
    int imgCols = src.size().width;
    dst=Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    for(int i=0;i<imgRows;i++){
        for( int j=0;j<imgCols;j++){
            int val=src.at<uchar>(i,j);
            if(val>=55&&val<=70){
                dst.at<uchar>(i,j)=0;
            }
            
            else if(val>=182&&val<=205){
                dst.at<uchar>(i,j)=0;
            }
            
            else if(val>=225&&val<=246){
                dst.at<uchar>(i,j)=0;
            }
            
            else{
                dst.at<uchar>(i,j)=255;
            }
            
            
        }
    }
    
}



bool niBlacksThreshold(Mat& src, Mat& dst,int kernel,double constant){
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    float mean = 0.0;
    int imgRows, imgCols;
    Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 1);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            int count=0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    
                    mean += img_temp.at<uchar>(i + x, j + y);
                    count++;
                }
            }
            mean=mean/count;
            
            int sum=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    int sub=0;
                    sub=mean-img_temp.at<uchar>(i + x, j + y);
                    sub=sub*sub;
                    sum+=sub;
                }
            }
            double var=sum/(kernel*kernel-1);
            double std=sqrt(var);
            
            double T=mean+constant*std;
            if(img_temp.at<uchar>(i,j)>T){
                dst.at<uchar>(i - padding, j - padding)=255;
            }
            else{
                dst.at<uchar>(i - padding, j - padding)=0;
            }
            
            
        }
    }
    
    return true;
}

bool sauvolaThreshold(Mat& src, Mat& dst,int kernel,double constant){
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    float mean = 0.0;
    int imgRows, imgCols;
    Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 1);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            int count=0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    
                    mean += img_temp.at<uchar>(i + x, j + y);
                    count++;
                }
            }
            mean=mean/count;
            
            int sum=0;
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    int sub=0;
                    sub=mean-img_temp.at<uchar>(i + x, j + y);
                    sub=sub*sub;
                    sum+=sub;
                }
            }
            double var=sum/(kernel*kernel-1);
            double std=sqrt(var);
            double stdDividedByR=std/128;
            double T=mean*(1+constant*((stdDividedByR-1)));
            
            if(img_temp.at<uchar>(i,j)>T){
                dst.at<uchar>(i - padding, j - padding)=255;
            }
            else{
                dst.at<uchar>(i - padding, j - padding)=0;
            }
            
            
        }
    }
    
    return true;
}

bool localMeanThreshold(Mat& src, Mat& dst,int kernel){
    if(src.type()!=CV_8UC1){
        cout<<"Image is not grayscale!"<<endl;
        return false;
    }
    else if(kernel%2!=1){
        cout<<"Kernel is not uneven!"<<endl;
        return false;
    }
    else if(kernel<1){
        cout<<"Kernel must be of size greater than 1!"<<endl;
        return false;
    }
    
    //border size
    int padding = (kernel - 1) / 2;
    
    float mean = 0.0;
    int imgRows, imgCols;
    Mat img_temp;
    
    imgRows = src.size().height;
    imgCols = src.size().width;
    
    //make a border around image with border size
    copyMakeBorder(src, img_temp, padding, padding, padding, padding, BORDER_CONSTANT, 1);
    
    //output image will be grayscale
    dst = Mat::zeros(imgRows, imgCols, CV_8UC1);
    
    
    // loop over whole image and find mean of neighborhood of pixel
    for (unsigned int i = padding; i<imgRows + padding; i++){
        for (unsigned int j = padding; j<imgCols + padding; j++){
            mean = 0.0;
            int count=0;
            // loop over neighborhood
            for (int x = -padding; x <= padding; x++){
                for (int y = -padding; y <= padding; y++){
                    
                    mean += img_temp.at<uchar>(i + x, j + y);
                    count++;
                }
            }
            mean=mean/count;
            if(img_temp.at<uchar>(i,j)>mean){
                dst.at<uchar>(i - padding, j - padding)=255;
            }
            else{
                dst.at<uchar>(i - padding, j - padding)=0;
            }
            
            
        }
    }
    
    return true;
}

