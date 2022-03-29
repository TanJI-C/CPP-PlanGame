#pragma once
#include<stdio.h>
#include<graphics.h>
struct Bullet								//声明一个子弹结构体
{											//使用结构体更加强调是一个变量
public:
	Bullet() :x(0), y(-6), atk(15), hit_dist(15), HZ(10), image_x(0), image_y(0)
	{ }
	int x, y;								//子弹坐标
	int atk;								//子弹攻击
	int hit_dist;							//攻击距离判定
	int HZ;									//子弹射出频率
	int image_x, image_y;					//图片放置位置
	static const int SPEED = 10;			//子弹速度，声明为静态常量成员
	void InitMPlaneBullet(int type);		//飞机子弹初始化
	void InitLPlaneBullet(int type);		//僚机子弹初始化
	void InitEnemyBullet(int type);			//敌机子弹初始化
};
class Plane									//声明一个飞机基类，派生出飞机与敌机
{
public:
	Plane():x(0), y(0), speed(5), life(3), image_x(0), image_y(0),
		bullet(NULL), bullet_num(20), bullet_HZ(16), bullet_times(0), bullet_index(0),
		dist_x(0), dist_y(0)
	{}
	Bullet* bullet;							//子弹指针
	int bullet_num;							//子弹数量，限定循环次数
	bool IfBehitted(Bullet& bull);			//判定是否被击中
protected:								//声明为保护成员，便于在派生类中可以访问
	int x, y;								//飞机坐标
	int speed;								//飞机速度
	int life;								//飞机血量
	int image_x, image_y;					//贴图位置
	int bullet_HZ;							//子弹射速
	int bullet_times;						//与上面的变量配合使用，决定子弹射速
	int bullet_index;						//访问子弹数组的下标
	int dist_x, dist_y;						//子弹与飞机横纵坐标距离，用于击中判定
	IMAGE planeY_ima, plane_ima;			//飞机掩码图和图片
	IMAGE bulletY_ima, bullet_ima;			//子弹掩码图和图片
	virtual void Death();
};
class Enemy :public Plane					//派生出敌机类
{
public:
	void Init(int type);					//敌机初始化
	void PlaneMove();						//敌机自动移动
	void PlaneP();							//敌机打印
	void BulletCreate();					//子弹产生
	void BulletP_Move();					//子弹打印自动移动
private:
	virtual void Death();							//死亡处理→产生新的飞机
	int life_ = 1;							//飞机血量，用于赋值，不会改变
};
class MPlane :public Plane					//派生出的飞机类
{
public:
	void Init(int type);					//初始化
	void Operator();						//读取飞机操作
	void PlaneP();							//飞机打印
	void LBulletCreate();					//僚机子弹产生
	void L_BulletP_Move();					//僚机飞机子弹打印移动
	void StatusP();							//飞机状态栏打印，目前仅有血量
	int lbullet_num = 0;					//僚机子弹数量
	Bullet* lbullet = NULL;					//僚机子弹数组
	int killenemy_num = 0;
private:
	int lbullet_HZ = 0;						//僚机子弹射速
	int lbullet_times = 0;					//配合上面的变量使用
	int lbullet_index = 0;					//访问僚机子弹数组下标
	IMAGE statusY_ima, status_ima;			//状态栏掩码图和图片
	virtual void Death();							//死亡处理→GameOver
};
class BackGround												//PG背景类
{
public:
	BackGround()												//默认初始化
	{
		PG_background_move = 5349;							//控制背景移动的变量
		loadimage(&PG_background, "PG_background.jpg");			
	}
	void BackGroundP_Move();											//背景打印
private:
	int PG_background_move;								//背景移动速度
	IMAGE PG_background;										//背景图片
};


