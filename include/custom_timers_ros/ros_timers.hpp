#pragma once
#include <rclcpp/rclcpp.hpp>


class RosStopwatch
{
    public:
    RosStopwatch();


    /**
     * @brief This function starts the timer
     * 
     */
    void start_sw();


    /**
     * @brief This function stops the timer
     * 
     */
    void stop_timer();


    /**
     * @brief Get the timer duration object
     * 
     * @return ros::Duration 
     */
    rclcpp::Duration get_timer_duration();


    /**
     * @brief Get the timer duration object
     * 
     * @return ros::Duration 
     */
    double get_sec_timer_duration();


    /**
     * @brief Get the start ros time 
     * 
     * @return ros::Time 
     */
    rclcpp::Time get_start_ros_time();


    /**
     * @brief Get the stop ros time object
     * 
     * @return ros::Time 
     */
    rclcpp::Time get_stop_ros_time();


    private:
    bool running; 
    rclcpp::Time start_time;
    rclcpp::Time stop_time;
};





class RosTimer
{
    public:
    RosTimer();


    void set_duration(float duration);


    void start_timer();


    void set_off();


    bool started();


    bool finished();


    void timer_tick();


    double remaining_time();


    private:
    RosStopwatch stopwatch;
    bool is_finished;
    bool is_started;
    bool dur_set;
    double dur;
};
