#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <opencv2/opencv.hpp>

double prev_x = 0.0;
double prev_y = 0.0;

cv::Mat image;

void Line(const turtlesim::Pose::ConstPtr& msg) {
    ROS_INFO("Received Turtle Pose - x: %.2f, y: %.2f, theta: %.2f", msg->x, msg->y, msg->theta);

    cv::line(image, cv::Point(prev_x * 50, 500 - prev_y * 50), cv::Point(msg->x * 50, 500 - msg->y * 50), cv::Scalar(0, 0, 255), 2);

    prev_x = msg->x;
    prev_y = msg->y;


    cv::imshow("Turtle Track", image);
    cv::waitKey(10); 
}



int main(int argc, char **argv) {
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;

    std::string image_path = "/home/bimo/code/kurakura/src/iris/src/img/arena_robot.png";  

    image = cv::imread(image_path, cv::IMREAD_COLOR);
    if (image.empty()) {
        ROS_ERROR("Image eeror or empty");
        return -1;
    }

    ros::Subscriber sub = nh.subscribe("/turtle1/pose", 10, Line);

    cv::namedWindow("Turtle Track", cv::WINDOW_AUTOSIZE);

    ros::spin();

    return 0;
}