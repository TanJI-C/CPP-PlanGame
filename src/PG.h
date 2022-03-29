#pragma once
#include<stdio.h>
#include<graphics.h>
struct Bullet								//����һ���ӵ��ṹ��
{											//ʹ�ýṹ�����ǿ����һ������
public:
	Bullet() :x(0), y(-6), atk(15), hit_dist(15), HZ(10), image_x(0), image_y(0)
	{ }
	int x, y;								//�ӵ�����
	int atk;								//�ӵ�����
	int hit_dist;							//���������ж�
	int HZ;									//�ӵ����Ƶ��
	int image_x, image_y;					//ͼƬ����λ��
	static const int SPEED = 10;			//�ӵ��ٶȣ�����Ϊ��̬������Ա
	void InitMPlaneBullet(int type);		//�ɻ��ӵ���ʼ��
	void InitLPlaneBullet(int type);		//�Ż��ӵ���ʼ��
	void InitEnemyBullet(int type);			//�л��ӵ���ʼ��
};
class Plane									//����һ���ɻ����࣬�������ɻ���л�
{
public:
	Plane():x(0), y(0), speed(5), life(3), image_x(0), image_y(0),
		bullet(NULL), bullet_num(20), bullet_HZ(16), bullet_times(0), bullet_index(0),
		dist_x(0), dist_y(0)
	{}
	Bullet* bullet;							//�ӵ�ָ��
	int bullet_num;							//�ӵ��������޶�ѭ������
	bool IfBehitted(Bullet& bull);			//�ж��Ƿ񱻻���
protected:								//����Ϊ������Ա���������������п��Է���
	int x, y;								//�ɻ�����
	int speed;								//�ɻ��ٶ�
	int life;								//�ɻ�Ѫ��
	int image_x, image_y;					//��ͼλ��
	int bullet_HZ;							//�ӵ�����
	int bullet_times;						//������ı������ʹ�ã������ӵ�����
	int bullet_index;						//�����ӵ�������±�
	int dist_x, dist_y;						//�ӵ���ɻ�����������룬���ڻ����ж�
	IMAGE planeY_ima, plane_ima;			//�ɻ�����ͼ��ͼƬ
	IMAGE bulletY_ima, bullet_ima;			//�ӵ�����ͼ��ͼƬ
	virtual void Death();
};
class Enemy :public Plane					//�������л���
{
public:
	void Init(int type);					//�л���ʼ��
	void PlaneMove();						//�л��Զ��ƶ�
	void PlaneP();							//�л���ӡ
	void BulletCreate();					//�ӵ�����
	void BulletP_Move();					//�ӵ���ӡ�Զ��ƶ�
private:
	virtual void Death();							//��������������µķɻ�
	int life_ = 1;							//�ɻ�Ѫ�������ڸ�ֵ������ı�
};
class MPlane :public Plane					//�������ķɻ���
{
public:
	void Init(int type);					//��ʼ��
	void Operator();						//��ȡ�ɻ�����
	void PlaneP();							//�ɻ���ӡ
	void LBulletCreate();					//�Ż��ӵ�����
	void L_BulletP_Move();					//�Ż��ɻ��ӵ���ӡ�ƶ�
	void StatusP();							//�ɻ�״̬����ӡ��Ŀǰ����Ѫ��
	int lbullet_num = 0;					//�Ż��ӵ�����
	Bullet* lbullet = NULL;					//�Ż��ӵ�����
	int killenemy_num = 0;
private:
	int lbullet_HZ = 0;						//�Ż��ӵ�����
	int lbullet_times = 0;					//�������ı���ʹ��
	int lbullet_index = 0;					//�����Ż��ӵ������±�
	IMAGE statusY_ima, status_ima;			//״̬������ͼ��ͼƬ
	virtual void Death();							//���������GameOver
};
class BackGround												//PG������
{
public:
	BackGround()												//Ĭ�ϳ�ʼ��
	{
		PG_background_move = 5349;							//���Ʊ����ƶ��ı���
		loadimage(&PG_background, "PG_background.jpg");			
	}
	void BackGroundP_Move();											//������ӡ
private:
	int PG_background_move;								//�����ƶ��ٶ�
	IMAGE PG_background;										//����ͼƬ
};


