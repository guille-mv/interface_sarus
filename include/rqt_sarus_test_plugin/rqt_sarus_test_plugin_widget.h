#ifndef RQT_SARUS_TEST_PLUGIN_WIDGET
#define RQT_SARUS_TEST_PLUGIN_WIDGET

#include <QWidget>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include "geometry_msgs/TwistStamped.h"


namespace Ui {
class TestPluginWidget;
}

class TestPluginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestPluginWidget(QWidget *parent = nullptr);
    ~TestPluginWidget();

    void init_ROS_Node();

private slots:
    void on_pushButton_clicked();
    void Update();


private:
    Ui::TestPluginWidget *ui;

    ros::NodeHandle ros_node_handle;
    ros::Subscriber my_subscriber;
    ros::Subscriber speedx;
    ros::Subscriber speedy;
    ros::Publisher buttonPublisher;
    void ros_data_callback(const std_msgs::String::ConstPtr &msg);
    void ros_speedx_callback(const geometry_msgs::TwistStamped::ConstPtr &vx);
    void ros_speedy_callback(const geometry_msgs::TwistStamped::ConstPtr &vy);

    //Variables
    std::string sub_message = "";
    float dronSpeed_x;
    float dronSpeed_y;
    int num_Drones = 2;

    QTimer *timer_1s;

    int cont;

};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
