#include <ros/node.h>
#include <rostime/clock.h>
#include <std_msgs/MsgPointCloudFloat32.h>
#include <std_msgs/MsgEmpty.h>

#include <math.h>

class cloudGenerator : public ros::node
{
public:
  static const unsigned int num_points = 10000;
  
  
  cloudGenerator(): ros::node("CloudGenerator")
  { 
    advertise<MsgPointCloudFloat32>("cloud");
    advertise<MsgEmpty>("shutter");
  };
  //  ~cloudGenerator(){return;};
  
  
  void sendCloud()
  {
    MsgPointCloudFloat32 cloud;
    cloud.set_pts_size(num_points);
    cloud.set_chan_size(1);
    cloud.chan[0].name = "intensities";
    cloud.chan[0].set_vals_size(num_points);
    double seconds = (double)(myClock.ulltime())/1000000000.0;
    for (unsigned int i = 0; i < num_points ; i++)
      {
	cloud.pts[i].x = cos((double)i/100.0 +seconds);
	cloud.pts[i].y = i * 0.01 + cos(seconds);
	cloud.pts[i].z = 10*sin((double)i/100.0+seconds);
	cloud.chan[0].vals[i] = cos(i);
      }
    
    publish("cloud",cloud);
  };

  void sendShutter()
  {
    MsgEmpty shutter;
    publish("shutter",shutter);
  };
  

  
private:
  MsgPointCloudFloat32 cloud;
  MsgEmpty shutter;
  
  ros::time::clock myClock;
  
};


int main(int argc, char ** argv)
{
  ros::init(argc, argv);

  cloudGenerator myClouder;

for (unsigned int i = 0; i < 1000000; i++)
  {
    myClouder.sendCloud();
    if (i % 100)
      myClouder.sendShutter();
    usleep(10000);
    
  }
 
 ros::fini();
};
