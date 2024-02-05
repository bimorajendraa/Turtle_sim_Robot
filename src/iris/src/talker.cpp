#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <termios.h>  
#include <unistd.h>  

ros::Publisher pub;
geometry_msgs::Twist twist;

void publishTwist() {
    pub.publish(twist);
}

int getKey() {
    int key = 0;
    struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    key = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return key;
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "talker");
    ros::NodeHandle nh;

    ros::param::set("/turtlesim/window_size_x", 500);
    ros::param::set("/turtlesim/window_size_y", 500);

    pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate rate(10);  

    twist.linear.x = 0.0;
    twist.angular.z = 0.0;

    while (ros::ok()) {
        int key = getKey();

        switch (key) {
            case 'w':
                twist.linear.x = 2.0;
                twist.angular.z = 0.0;
                break;
            case 'a':
                twist.linear.x = 0.0;
                twist.angular.z = 1.55;
                break;
            case 's':
                twist.linear.x = -2.0;
                twist.angular.z = 0.0;
                break;
            case 'd':
                twist.linear.x = 0.0;
                twist.angular.z = -1.55;
                break;
            default:
                twist.linear.x = 0.0;
                twist.angular.z = 0.0;
        }

        publishTwist();
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}