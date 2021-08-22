#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget drive_command;
    drive_command.request.linear_x = lin_x;
    drive_command.request.angular_z = ang_z;

    client.call(drive_command);
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    int split_section = img.step / 3;
    int fall_section = -1; // 0 = Left, 1 = Middle, 2 = Right

    float linear_x = 0.0;
    float angular_z = 0.0;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.step - 2; j ++) {
            // Check 3 color channels (R, G, B)
            if (img.data[i * img.step + j] == white_pixel &&
                img.data[i * img.step + j + 1] == white_pixel &&
                img.data[i * img.step + j + 2] == white_pixel) {
                fall_section = (int)(j / split_section);
                break;
            }
        }
    }

    if (fall_section == 0) { // left section
        // Rotate left
        linear_x = 0.1;
        angular_z = 0.2;
        ROS_INFO_STREAM("Found ball in left section");
    } else if (fall_section == 1) { // middle section
        // Move Forward
        linear_x = 0.1;
        angular_z = 0.0;
        ROS_INFO_STREAM("Found ball in middle section");
    } else if (fall_section == 2) { // right section
        // Rotate Right
        linear_x = 0.1;
        angular_z = -0.2;
        ROS_INFO_STREAM("Found ball in right section");
    } else { // Rotate left when not found
        linear_x = 0.0;
        angular_z = 0.2;
        ROS_INFO_STREAM("Rotate left for seeking ball");
    }

    drive_robot(linear_x, angular_z);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
