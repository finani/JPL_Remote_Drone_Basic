# JPL Remote Drone Basic Setup (using PX4, T265)
- DJI F550
- Nvidia Jetson NX
- Intel Realsense T265
 

## Topic Flow
1. Change rostopic from <T265> ```/camera/odom/sample``` to ```/mavros/vision_pose/pose```
    - ```roslaunch tf_rs tf_rs.launch```
3. Estimate precise local position ```/mavros/local_position/pose``` in PX4
    - You can also use ```/mavros/local_position/odom```


## To Do
1. Set symbolic link (optional)
    - It will change the tty name from ```/dev/ttyUSB0``` to ```/dev/ttyPixhawk```
    - https://github.com/finani/WeeBee/tree/master/tty_symlink
        - You can check tty using ```ls /dev/tty*```
        - The tty name depends on the connection order. If you connect an Arduino first and then PX4, the Arduino is set as ttyUSB0 and the PX4 is set as ttyUSB1. The tty name changes frequently because you can not connect the devices sequentially each time. So, you need to set up a symbolic link for a stable system. (Many devices use FTDI chip and they use a serial communication.)
2. Set PX4 Telemetry parameters
    - https://dev.px4.io/master/en/companion_computer/pixhawk_companion.html
    - Set ```MAV_1_CONFIG``` to ```Telem2```, ```MAV_1_MODE``` to ```Onboard``` and ```SER_TEL2_BAUD``` to 921600
    - Reboot PX4
3. Edit mavros px4 launch
    - ```sudo gedit /opt/ros/melodic/share/mavros/launch/px4.launch```
    - Set ```fcu_url``` to ```/dev/ttyPixhawk:921600```
        - ```<arg name="fcu_url" default="/dev/ttyPixhawk:921600"/>```
        - address: /dev/ttyPixhawk (or /dev/ttyUSB0)
        - baudrate: 921600 bps
4. Set PX4 Vision parameters
    - https://docs.px4.io/master/en/computer_vision/visual_inertial_odometry.html
    - Set ```EKF2_AID_MASK``` to ```24``` (vision_position_fusion, vision_yaw_fusion)
    - Set ```EKF2_HGT_MODE``` to ```3: vision```
    - Reboot PX4

## How to Run
1. Run mavros
    - It will connect to PX4
    - ```roslaunch mavros px4.launch```
2. Run T265
    - It will start to estimate local position
    - ```roslaunch realsense2_camera rs_t265.launch```
3. Rename rostopic
    - It will link the T265 topic(data) to mavros(PX4)
    - ```roslaunch tf_rs tf_rs.launch```
4. Send a command (optional)
    - It will send a command to move the drone
    - ```roslaunch offboard_drone offboard.launch```
5. Make a command (optional)
    - It is a mission planner
    - It will make a command to control the drone
    - ```roslaunch ??? ???.launch```


## Preflight Check
1. T265 odometry(```/camera/odom/sample```)
    - Check the value and the direction
    - It is required only once at the first time
2. Mavros local position(```/mavros/local_position/pose``` or ```/mavros/local_position/odom```)
    - Check the value and the direction
    - It is required only once at the first time
3. Mavros state from ```offboard.launch```
    - Check the data (connected, armed, guided, flight_mode, cur_position)
    - It is required every time
4. Command output from ```offboard.launch```
    - Check the command(usually velocity) output
    - It is required when running the new algorithm
5. Fly safely~
