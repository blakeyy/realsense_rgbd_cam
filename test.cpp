#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(){
    rs2::pipeline p;
    p.start();
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    while (1)
    {
        rs2::frameset frames = p.wait_for_frames();
        //rs2::depth_frame depth = frames.get_depth_frame();
        rs2::video_frame frame = frames.get_color_frame();

        // Query frame size (width and height)
        //int w = frame.get_width();
        //int h = frame.get_height();
        //const int w = frame.as<rs2::video_frame>().get_width();
        //const int h = frame.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the colorized depth data (bgr values)
        cv::Mat temp(cv::Size(640, 480), CV_8UC1, (void*)frame.get_data(), cv::Mat::AUTO_STEP);
        //cv::Mat temp(cv::Size(640, 480), CV_16U, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
        
        //std::cout << "The camera is facing an object " << dist_to_center << " meters away \r";
        
        cv::imshow("Display Image", temp);
        cv::waitKey(3);

    }
    return 0;
}
