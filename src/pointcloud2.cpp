#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <random>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>

class DummyPointCloud2Publication{
	private:
		/*node handle*/
		ros::NodeHandle nh_;
		ros::NodeHandle nh_private_;
		/*publisher*/
		ros::Publisher pub_;
        /*buffer*/
        pcl::PointCloud<pcl::PointXYZI>::Ptr pc_ {new pcl::PointCloud<pcl::PointXYZI>};
		/*tool*/
		std::random_device rd_;
		std::mt19937 mt_{rd_()};
		std::uniform_real_distribution<> urd_;
		std::uniform_int_distribution<> uid_0_255_{0, 255};
		/*parameter*/
		double hz_;
		std::string frame_;
		double rand_range_;
		int num_points_;

	public:
		DummyPointCloud2Publication();
		void loop(void);
        void inputRandomValue(void);
		void publication(void);
};

DummyPointCloud2Publication::DummyPointCloud2Publication()
	: nh_private_("~")
{
	std::cout << "----- dummy_pointcloud2_publication -----" << std::endl;
	/*parameter*/
	nh_private_.param("hz", hz_, 10.0);
	std::cout << "hz_ = " << hz_ << std::endl;
	nh_private_.param("frame", frame_, std::string("frame"));
	std::cout << "frame_ = " << frame_ << std::endl;
	nh_private_.param("rand_range", rand_range_, 100.0);
	std::cout << "rand_range_ = " << rand_range_ << std::endl;
	nh_private_.param("num_points", num_points_, 1000);
	std::cout << "num_points_ = " << num_points_ << std::endl;
	/*publisher*/
	pub_ = nh_.advertise<sensor_msgs::PointCloud2>("/dummy/pointcloud2", 1);
	/*setting*/
	urd_ = std::uniform_real_distribution<>(-rand_range_, rand_range_);
	pc_->points.resize(num_points_);
}

void DummyPointCloud2Publication::loop(void)
{
	ros::Rate loop_rate(hz_);
	while(ros::ok()){
		inputRandomValue();
		publication();
		loop_rate.sleep();
	}
}

void DummyPointCloud2Publication::inputRandomValue(void)
{
	for(int i = 0; i < num_points_; i++){
		pc_->points[i].x = urd_(mt_);
		pc_->points[i].y = urd_(mt_);
		pc_->points[i].z = urd_(mt_);
		pc_->points[i].intensity = uid_0_255_(mt_);
	}
}

void DummyPointCloud2Publication::publication(void)
{
    if(!pc_->points.empty()){
		sensor_msgs::PointCloud2 ros_pc;
        pcl::toROSMsg(*pc_, ros_pc);
        ros_pc.header.frame_id = frame_;
        ros_pc.header.stamp = ros::Time::now();
        pub_.publish(ros_pc);
    }
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "dummy_pointcloud2_publication");
	
	DummyPointCloud2Publication dummy_pointcloud2_publication;
	dummy_pointcloud2_publication.loop();
}