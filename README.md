# PROJECT: GO CHASE IT

![GoChaseIt](https://user-images.githubusercontent.com/53105229/130345694-cf0ff903-9a2f-44d2-8701-9fd9780c7b18.png)

## OBJECTIVE
Create two ROS packages inside your `catkin_ws/src`: the `drive_bot` and the `ball_chaser` to chase white-colored balls

## PROJECT STEP OF WROKS
1. Complete learning Introduction to ROS, Package & Catkin Workspaces and Write ROS Node.
2. Create the my_robot ROS package. Create and Store an Empty Gazebo World File and Create a Launch File.
3. Robot Basic Setup and Enchanment by creating a URDF file and then add two sensrs (camera and lidar).
![RobotEnchancement](https://user-images.githubusercontent.com/53105229/130346352-f2b44e9a-5501-48e0-a02f-0ade8a8455e0.JPG)
![RobotSensor](https://user-images.githubusercontent.com/53105229/130346375-d4d2f5fc-9743-48e4-b798-20293a72fc18.JPG)
4. Add Gazebo Plugins; camera, Hokuyo lidar, wheel joints (https://s3-us-west-1.amazonaws.com/udacity-robotics/my_robot.gazebo).
5. Intregrate RViz to visualize data from the camera and lidar sensors.
6. Replace empty world with existing world (from project build my world) and let robot inside the house.
![House your Robot](https://user-images.githubusercontent.com/53105229/130346841-dc7518c7-0b94-431b-bdf8-2c1632859e83.png)
7. Crete white ball and insert into the wolrd.
![Model with white ball](https://user-images.githubusercontent.com/53105229/130346877-076653ac-0eb9-4b3b-9881-4c08fdced52d.png)
8. Process image node. This client node will subscribe to the robot’s camera images and analyze them to determine the position of the white ball. Once the ball position is determined, the client node will request a service from the drive_bot server node to drive the robot toward the ball. The robot can drive either left, right or forward, depending on the robot position inside the image.
![GoChaseIt _result](https://user-images.githubusercontent.com/53105229/130346862-7de6f117-4677-467f-b375-ada93416a2ff.png)

## FILE DIRECTORY STRUCTURE
```
.GoChaseIt                             # Go Chase It Project
    ├── my_robot                       # my_robot package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── meshes                     # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                       # urdf folder for xarco files
    │   │   ├── my_robot.gazebo
    │   │   ├── my_robot.xacro
    │   ├── world                      # world folder for world files
    │   │   ├── myWorld.world
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    ├── ball_chaser                    # ball_chaser package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── ball_chaser.launch
    │   ├── src                        # source folder for C++ scripts
    │   │   ├── drive_bot.cpp
    │   │   ├── process_images.cpp
    │   ├── srv                        # service folder for ROS services
    │   │   ├── DriveToTarget.srv
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info                  
    └──                              
```

## PROJECT SUBMISSION CHECKLIST
- [x] I am confident all rubric items have been met and my project will pass as submitted.
- [x] Project builds correctly without errors and runs.
- [x] All required functionality exists and my project behaves as expected per the project's specifications.

## TIPS
* ROS supports many different types of sensors (more info. http://wiki.ros.org/Sensors#A2D_range_finders)
* Fix RViz's Global status errorr by select `odom` in Global Options's Fix Frame.
* Setting `GAZEBO_MODEL_PATH` to let GAZEBO know you white ball save path.
* An algorithm for image process is important (img.step, img.data)
