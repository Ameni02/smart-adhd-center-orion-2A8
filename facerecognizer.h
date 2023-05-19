
#ifndef FACERECOGNIZER_H
#define FACERECOGNIZER_H



#pragma once
#include <string>
#include <vector>
#include <opencv2/core.hpp>

class FaceRecognizer
{
public:
    FaceRecognizer();
    void load(const std::string& modelPath);
    std::string recognize(const cv::Mat& face);

private:
    struct RecognizerData;
    std::unique_ptr<RecognizerData> m_data;
};


#endif // FACERECOGNIZER_H
