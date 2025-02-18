#ifndef CHASSIS_H
#define CHASSIS_H

#include "system_config.h"

#include "struct_typedef.h"
#include "First_order_filter.h"
#include "Remote_control.h"
#include "Motor.h"
#include "Pid.h"
#include "Super_cap.h"
#include "Config.h"

#define rc_deadband_limit(input, output, dealine)        \
    {                                                    \
        if ((input) > (dealine) || (input) < -(dealine)) \
        {                                                \
            (output) = (input);                          \
        }                                                \
        else                                             \
        {                                                \
            (output) = 0;                                \
        }                                                \
    }

// 任务开始空闲一段时间
#define CHASSIS_TASK_INIT_TIME 357

// 前后的遥控器通道号码
#define CHASSIS_X_CHANNEL 3

// 左右的遥控器通道号码
#define CHASSIS_Y_CHANNEL 2

// 在特殊模式下，可以通过遥控器控制旋转
#define CHASSIS_WZ_CHANNEL 0

// 初始yaw轴角度
#define INIT_YAW_SET 0.0f

// 选择底盘状态 开关通道号
#define CHASSIS_LEFT_CHANNEL 0  // 左拨杆
#define CHASSIS_RIGHT_CHANNEL 1 // 右拨杆

// 遥控器前进摇杆（max 660）转化成车体前进速度（m/s）的比例
#define CHASSIS_VX_RC_SEN 0.005f

// 遥控器左右摇杆（max 660）转化成车体左右速度（m/s）的比例
#define CHASSIS_VY_RC_SEN -0.003f

// 跟随底盘yaw模式下，遥控器的yaw遥杆（max 660）增加到车体角度的比例
#define CHASSIS_ANGLE_Z_RC_SEN 0.000002f

// 不跟随云台的时候 遥控器的yaw遥杆（max 660）转化成车体旋转速度的比例
#define CHASSIS_WZ_RC_SEN 0.01f

#define CHASSIS_ACCEL_X_NUM 0.1666666667f
#define CHASSIS_ACCEL_Y_NUM 0.3333333333f

// 摇杆死区
#define CHASSIS_RC_DEADLINE 10

#define MOTOR_SPEED_TO_CHASSIS_SPEED_VX 0.25f
#define MOTOR_SPEED_TO_CHASSIS_SPEED_VY 0.25f
#define MOTOR_SPEED_TO_CHASSIS_SPEED_WZ 0.25f

#define MOTOR_DISTANCE_TO_CENTER 0.2f // 英雄为0.22+0.24=0.46  官方步兵为0.2

// 底盘任务控制间隔 2ms
#define CHASSIS_CONTROL_TIME_MS 2
// 底盘任务控制间隔 0.002s
#define CHASSIS_CONTROL_TIME 0.002f
// 底盘任务控制频率，尚未使用这个宏
#define CHASSIS_CONTROL_FREQUENCE 500.0f
// 底盘3508最大can发送电流值
#define MAX_MOTOR_CAN_CURRENT 16000.0f

/*----------------按键-------------------------*/

// 底盘前后左右控制按键WASD
#define KEY_CHASSIS_FRONT if_key_pessed(chassis_RC, KEY_PRESSED_CHASSIS_FRONT)
#define KEY_CHASSIS_BACK if_key_pessed(chassis_RC, KEY_PRESSED_CHASSIS_BACK)
#define KEY_CHASSIS_LEFT if_key_pessed(chassis_RC, KEY_PRESSED_CHASSIS_LEFT)
#define KEY_CHASSIS_RIGHT if_key_pessed(chassis_RC, KEY_PRESSED_CHASSIS_RIGHT)

#define KEY_CHASSIS_TOP if_key_singal_pessed(chassis_RC, last_chassis_RC, KEY_PRESSED_CHASSIS_TOP)
#define KEY_CHASSIS_SWING if_key_singal_pessed(chassis_RC, last_chassis_RC, KEY_PRESSED_CHASSIS_SWING)
#define KEY_CHASSIS_PISA if_key_singal_pessed(chassis_RC, last_chassis_RC, KEY_PRESSED_CHASSIS_PISA)
#define KEY_CHASSIS_SUPER_CAP if_key_singal_pessed(chassis_RC, last_chassis_RC, KEY_PRESSED_CHASSIS_SUPER_CAP)
#define KEY_UI_UPDATE if_key_singal_pessed(chassis_RC, last_chassis_RC, KEY_PRESSED_UI_UPDATE)

/*----------------自动控制-------------------------*/
// 输入为上位机所给信号，目前未知
#define AUTO_FORWARD 1
#define AUTO_BACK 1
#define AUTO_LEFT 1
#define AUTO_RIGHT 1

// slam相关控制
#define IF_SLAM_OPEN 1

// 是否开启小陀螺
#define IF_SPIN_OPEN 1

// 解算方式是否为全向轮解算，如果为哨兵(全向轮)则置1，(麦轮)置0
#define IF_SEMTRY_SOLVE 1

// m3508转化成底盘速度(m/s)的比例，
#define M3508_MOTOR_RPM_TO_VECTOR 0.000415809748903494517209f
#define CHASSIS_MOTOR_RPM_TO_VECTOR_SEN M3508_MOTOR_RPM_TO_VECTOR
#define CHASSIS_MOTOR_RPM_TO_VECTOR_SEN M3508_MOTOR_RPM_TO_VECTOR

// 单个底盘电机最大速度
#define MAX_WHEEL_SPEED 5.0f // 4
// 底盘运动过程最大前进速度
#define NORMAL_MAX_CHASSIS_SPEED_X 4.0f // 2.0
// 底盘运动过程最大平移速度
#define NORMAL_MAX_CHASSIS_SPEED_Y 4.0f // 1.5
// 底盘运动过程最大旋转速度
#define NORMAL_MAX_CHASSIS_SPEED_Z 20.0f

#define CHASSIS_WZ_SET_SCALE 0.1f

// 摇摆原地不动摇摆最大角度(rad)
#define SWING_NO_MOVE_ANGLE 0.7f // 0.7
// 摇摆过程底盘运动最大角度(rad)
#define SWING_MOVE_ANGLE 0.31415926535897932384626433832795f

// 电机反馈码盘值范围
#define HALF_ECD_RANGE 4096
#define ECD_RANGE 8191

// 电机编码值转化成角度值
#define MOTOR_ECD_TO_RAD 0.000766990394f //      2*  PI  /8192

#define MISS_CLOSE 0
#define MISS_BEGIN 1
#define MISS_OVER 2

#define PISA_DELAY_TIME 500
#define CHASSIS_OPEN_RC_SCALE 10 // in CHASSIS_OPEN mode, multiply the value. 在chassis_open 模型下，遥控器乘以该比例发送到can上

#define SPIN_BEGIN_TIME 1000 // 小陀螺启动时间
#define SPIN_CHANGE_V 1000   // 小陀螺变速比例

#define SPIN_PROPORTION 10000000 // 对小陀螺旋转进行等比缩放

// chassis motor speed PID
// 底盘电机速度环PID
#define MOTIVE_MOTOR_SPEED_PID_KP 6000.0f
#define MOTIVE_MOTOR_SPEED_PID_KI 0.0f
#define MOTIVE_MOTOR_SPEED_PID_KD 2.0f
#define MOTIVE_MOTOR_SPEED_PID_MAX_IOUT 2000.0f
#define MOTIVE_MOTOR_SPEED_PID_MAX_OUT 6000.0f

// chassis follow angle PID
// 底盘旋转跟随PID
#define CHASSIS_FOLLOW_GIMBAL_PID_KP 8.0f // 8.0f
#define CHASSIS_FOLLOW_GIMBAL_PID_KI 0.0f
#define CHASSIS_FOLLOW_GIMBAL_PID_KD 0.0f
#define CHASSIS_FOLLOW_GIMBAL_PID_MAX_IOUT 2.0f
#define CHASSIS_FOLLOW_GIMBAL_PID_MAX_OUT 10.0f

// 功率控制参数
#define POWER_DEFAULT_LIMIT 50.0f    // 默认功率限制
#define WARNING_POWER_DISTANCE 10.0f // 距离超过率的距离
#define WARNING_POWER_BUFF 30.0f
// 警告能量缓冲  通过计算超级电容 电压低于12v得到的值

#define NO_JUDGE_TOTAL_CURRENT_LIMIT 48000.0f // 16000 * 4,
#define BUFFER_TOTAL_CURRENT_LIMIT 12000.0f   // 16000
#define POWER_TOTAL_CURRENT_LIMIT 16000.0f    // 20000

typedef enum
{
    CHASSIS_VECTOR_ZERO_FORCE, // 无力模式

    CHASSIS_VECTOR_REMOTE, // 遥控器控制

    CHASSIS_VECTOR_SLAM, // 跟随slam模式

    CHASSIS_VECTOR_SPIN, // 自主模式下的旋转

} chassis_mode_e; // 控制模式

struct speed_t
{
    fp32 speed;
    fp32 speed_set;

    fp32 max_speed;
    fp32 min_speed;
};

class Chassis
{
public:
    const RC_ctrl_t *chassis_RC; // 底盘使用的遥控器指针
    RC_ctrl_t *last_chassis_RC;  // 底盘使用的遥控器指针

    uint16_t chassis_last_key_v; // 遥控器上次按键

    chassis_mode_e chassis_mode;      // 底盘控制状态机
    chassis_mode_e last_chassis_mode; // 底盘上次控制状态机

    M3508_motor chassis_motive_motor[4]; // 底盘动力电机数据

    First_order_filter chassis_cmd_slow_set_vx; // 使用一阶低通滤波减缓设定值
    First_order_filter chassis_cmd_slow_set_vy; // 使用一阶低通滤波减缓设定值
    First_order_filter chassis_cmd_slow_set_vz; // 使用一阶低通滤波减缓设定值

    Pid chassis_wz_angle_pid; // 底盘角度pid

    speed_t x;
    speed_t y;
    speed_t z;

    fp32 chassis_relative_angle;     // 底盘与云台的相对角度，单位 rad
    fp32 chassis_relative_angle_set; // 设置相对云台控制角度
    fp32 chassis_yaw_set;

    fp32 chassis_yaw;   // 底盘的yaw角度
    fp32 chassis_pitch; // 底盘的pitch角度
    fp32 chassis_roll;  // 底盘的roll角度

    // 任务流程
    void init();

    void set_mode();

    void feedback_update();

    void set_contorl();

    void solve();

    void power_ctrl();

    void output();

    // 行为控制

    void chassis_behaviour_mode_set();

    void chassis_behaviour_control_set(fp32 *vx_set_, fp32 *vy_set_, fp32 *angle_set);

    void chassis_zero_force_control(fp32 *vx_can_set, fp32 *vy_can_set, fp32 *wz_can_set);

    void chassis_infantry_follow_gimbal_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set);

    void chassis_engineer_follow_chassis_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set);

    void chassis_no_follow_yaw_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set);

    void chassis_slam_control(fp32 *vx_set, fp32 *vy_set, fp32 *wz_set);

    void chassis_spin_control(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set);

    // 功能性函数
    void chassis_rc_to_control_vector(fp32 *vx_set, fp32 *vy_set, fp32 *angle_set); // 使用遥控器控制速度

    void chassis_control_vector(fp32 *vx_set, fp32 *vy_set); // 自动控制速度

    void chassis_vector_to_omni_wheel_speed(fp32 wheel_speed[4]);
};

extern Chassis chassis;

// 超电模块
extern Super_Cap cap;
#endif
