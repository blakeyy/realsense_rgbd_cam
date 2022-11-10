#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(){
    rs2::pipeline pipe;
    pipe.start();
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    while (1)
    {
        rs2::frameset frames = pipe.wait_for_frames();
        rs2::depth_frame depth = frames.get_depth_frame();
        
        // CAPTURE A FRAME
        // Query frame size (width and height)
        const int width = depth.as<rs2::video_frame>().get_width();
        const int height = depth.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the colorized depth data
        cv::Mat depth_img(cv::Size(width, height), CV_16UC1, (void*)depth.get_data(), cv::Mat::AUTO_STEP);
        
        // Convert 16bit image to 8bit image
        depth_img.convertTo(color_img, CV_8UC1, 15 / 256.0);
        cv::imshow("Display Image",  depth_img);
        
        cv::waitKey(3);

    }
    return 0;
}
