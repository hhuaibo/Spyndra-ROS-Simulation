/* simulator.h */
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <string>

namespace spyndra
{
class Simulator
{
public:
  Simulator(int argc, char **argv, int freq );
  Simulator( const Simulator& rhs ){}
  ~Simulator(){}

  //template <class T>
  //spyndra::GaitGenerator<T> gait_generator(std::string filename);
  GaitGenerator gait_generator(const std::string& method, std::string filename);
  void move( int jt, float angle );
private:
  ros::V_Publisher controllers;
};

Simulator::Simulator(int argc, char **argv, int freq = 10 )
{
  ros::init(argc, argv, "simulator");
  ros::NodeHandle n;
  ros::Publisher j1 = n.advertise<std_msgs::Float64>("/spyndra/joint1_position_controller/command",freq);
  ros::Publisher j2 = n.advertise<std_msgs::Float64>("/spyndra/joint2_position_controller/command",freq);
  ros::Publisher j3 = n.advertise<std_msgs::Float64>("/spyndra/joint3_position_controller/command",freq);
  ros::Publisher j4 = n.advertise<std_msgs::Float64>("/spyndra/joint4_position_controller/command",freq);
  ros::Publisher j5 = n.advertise<std_msgs::Float64>("/spyndra/joint5_position_controller/command",freq);
  ros::Publisher j6 = n.advertise<std_msgs::Float64>("/spyndra/joint6_position_controller/command",freq);
  ros::Publisher j7 = n.advertise<std_msgs::Float64>("/spyndra/joint7_position_controller/command",freq);
  ros::Publisher j8 = n.advertise<std_msgs::Float64>("/spyndra/joint8_position_controller/command",freq);
  controllers = ros::V_Publisher({j1, j2, j3, j4, j5, j6, j7, j8});
}

GaitGenerator Simulator::gait_generator(const std::string& method, std::string filename)
{
  spyndra::GaitGenerator g(method, filename);
  g.set_controllers( controllers );
  return g;
}

void Simulator::move( int jt, float angle )
{
  //ros::Rate loop_rate(1);
  //while (ros::ok() )
  //{
  //for ( int i = 0; i < 5; ++i)
  //{
  //  ROS_INFO_STREAM(" move ");

    std_msgs::Float64 cmd;
    cmd.data = angle;
    controllers[jt-1].publish( cmd );

    ros::spinOnce();
    //loop_rate.sleep();
  //}
}

}
