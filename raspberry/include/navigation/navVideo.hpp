#include <opencv2/opencv.hpp>
class vidGuidance{
    public:
        vidGuidance(cv::VideoCapture cam);
    private:
        cv::VideoCapture camera;
};