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
    ros::Subscriber speed;
    ros::Publisher buttonPublisher;
    void ros_data_callback(const std_msgs::String::ConstPtr &msg);
    void ros_speed_callback(const geometry_msgs::TwistStamped::ConstPtr &v);

    //Variables
    std::string sub_message = "";
    float dronSpeed_x;

    QTimer *timer_1s;

    int cont;

};

#endif // RQT_SARUS_TEST_PLUGIN_WIDGET
