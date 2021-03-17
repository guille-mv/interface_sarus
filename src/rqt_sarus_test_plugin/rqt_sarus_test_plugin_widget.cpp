#include <rqt_sarus_test_plugin/rqt_sarus_test_plugin_widget.h>
#include "ui_rqt_sarus_test_plugin_widget.h"
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <QTimer>
#include <QTime>
#include "geometry_msgs/TwistStamped.h"

TestPluginWidget::TestPluginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPluginWidget)
{
    ui->setupUi(this);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(Update()));
    timer_1s->start(500);
}

TestPluginWidget::~TestPluginWidget()
{
    // Write exit code here

    delete ui;
}

void TestPluginWidget::Update() {
    ui->subText->setText(sub_message.c_str());
    std::string x_speed;
    x_speed = std::to_string(dronSpeed_x);
    ui->speedText->setText(x_speed.c_str());
}

void TestPluginWidget::ros_data_callback(const std_msgs::String::ConstPtr &msg){
    this->sub_message = msg->data.c_str();
}

void TestPluginWidget::ros_speed_callback(const geometry_msgs::TwistStamped::ConstPtr &v){
    this->dronSpeed_x = v->twist.linear.x;
}

void TestPluginWidget::init_ROS_Node()
{
    cont = 0;
    // Write initialization code here (publishers, subscribers)
    buttonPublisher = ros_node_handle.advertise<std_msgs::String>("my_data",1);
    my_subscriber = ros_node_handle.subscribe("my_data", 1, &TestPluginWidget::ros_data_callback, this);
    speed = ros_node_handle.subscribe("/drone107/motion_reference/speed", 1, &TestPluginWidget::ros_speed_callback, this);
}

void TestPluginWidget::on_pushButton_clicked()
{
    // Button clicked callback
    cont++;
    std_msgs::String message;
    message.data = std::to_string(cont);
    buttonPublisher.publish(message);
    ui->pubText->setText(message.data.c_str());
}
