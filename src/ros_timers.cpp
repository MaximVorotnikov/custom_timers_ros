#include "custom_timers_ros/ros_timers.hpp"


// class RosStopwatch

RosStopwatch::RosStopwatch()
{
    running = false;
}


/**
 * @brief This function starts the timer
 * 
 */
void RosStopwatch::start_sw()
{
    start_time = rclcpp::Clock(RCL_ROS_TIME).now();
    running = true;
}


/**
 * @brief This function stops the timer
 * 
 */
void RosStopwatch::stop_timer()
{
    stop_time = rclcpp::Clock(RCL_ROS_TIME).now();
    running = false;
}


/**
 * @brief Get the timer duration object
 * 
 * @return ros::Duration 
 */
rclcpp::Duration RosStopwatch::get_timer_duration()
{
    if (running) return rclcpp::Clock(RCL_ROS_TIME).now() - start_time;
    return start_time - stop_time;
}


/**
 * @brief Get the timer duration object
 * 
 * @return ros::Duration 
 */
double RosStopwatch::get_sec_timer_duration()
{
    if (running) return (rclcpp::Clock(RCL_ROS_TIME).now() - start_time).seconds();
    return (start_time - stop_time).seconds();
}


/**
 * @brief Get the start ros time 
 * 
 * @return ros::Time 
 */
rclcpp::Time RosStopwatch::get_start_ros_time()
{
    return start_time;
}


/**
 * @brief Get the stop ros time object
 * 
 * @return ros::Time 
 */
rclcpp::Time RosStopwatch::get_stop_ros_time()
{
    return stop_time;
}

// class 

RosTimer::RosTimer()
{
    is_finished = false;
    is_started = false;
    dur_set = false;
}


void RosTimer::set_duration(float duration)
{
    dur = duration;
    dur_set = true;
}


void RosTimer::start_timer()
{
    if (dur_set)
    {
        is_started = true;
        is_finished = false;
        stopwatch.start_sw();
        return;
    }
    
    std::cerr << "RosTimer in start_timer(): timer duration not set! Can't start timer\n";
}


void RosTimer::set_off()
{
    is_started = false;
    is_finished = true;
}


bool RosTimer::started()
{
    return is_started;
}


bool RosTimer::finished()
{
    return is_finished;
}


void RosTimer::timer_tick()
{
    if (is_started)
    {
        if (stopwatch.get_sec_timer_duration() >= dur)
        {
            // is_started = false;
            is_finished = true;
            dur_set = false;
            return;
        }
        return;
    }
}


double RosTimer::remaining_time()
{
    return dur - (rclcpp::Clock(RCL_ROS_TIME).now() - stopwatch.get_start_ros_time()).seconds();
}


