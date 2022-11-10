#include <librealsense2/rs.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

void getImage(rs2::pipeline &pipe, cv::Mat &grayImg, cv::Mat &image_next){
    rs2::frameset frames = pipe.wait_for_frames();
    rs2::video_frame color_frame = frames.get_color_frame();

    image_next = cv::Mat(cv::Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
    cv::cvtColor(image_next, grayImg, cv::COLOR_BGR2GRAY);
}

int main(){
    //Contruct a pipeline which abstracts the device
    rs2::pipeline pipe;

    //Create a configuration for configuring the pipeline with a non default profile
    rs2::config cfg;

    //Add desired streams to configuration
    cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);

    //Instruct pipeline to start streaming with the requested configuration
    pipe.start(cfg);

    // Camera warmup - dropping several first frames to let auto-exposure stabilize
    rs2::frameset frames;

    cv::namedWindow("Display image", cv::WINDOW_AUTOSIZE );
    
    // Obtain first image and set up two feature vectors
    cv::Mat image_prev, image_next, color;
    std::vector<cv::Point2f> features_prev, features_next, optical_flow;
    
    getImage(pipe, image_next, color);
    
    // Obtain initial set of features
    cv::goodFeaturesToTrack(image_next, // the image 
                            features_next,   // the output detected features
                            23,  // the maximum number of features 
                            0.01,     // quality level
                            10     // min distance between two features
    );
    optical_flow = features_next;
    while (1)
    {
        image_prev = image_next.clone();
        features_prev = features_next;
        getImage(pipe, image_next, color);  // Get next image
        
        // Find position of feature in new image
        cv::Mat status, err;
        cv::calcOpticalFlowPyrLK(
            image_prev, image_next, // 2 consecutive images
            features_prev, // input point positions in first im
            features_next, // output point positions in the 2nd
            status,    // tracking success
            err      // tracking error
        );
        optical_flow.insert(optical_flow.end(), features_next.begin(), features_next.end());

        for (size_t i = 0; i < optical_flow.size(); i++)
        {
            cv::circle(color, optical_flow[i], 1, cv::Scalar(0,0,255), 2);
        }
        cv::imshow("Display image",  color);
        
        cv::waitKey(1);
    }
    return 0;
}
