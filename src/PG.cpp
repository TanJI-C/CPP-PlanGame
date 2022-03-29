#include"PG.h"
#include"Update.h"
#include<graphics.h>
#include<cmath>
#include<Windows.h>

void Bullet::InitMPlaneBullet(int type)								//��ʼ�����������������룬���٣�ͼƬ
{
	atk = type + 1;
	hit_dist = 13 + type * 6;
	HZ = 8 + type * 8;
	image_x = type * 12;
	image_y = 0;
}
void Bullet::InitLPlaneBullet(int type)								//��ʼ�����������������룬���٣�ͼƬ
{
	atk = 1;
	hit_dist = 14 - type * 5;
	HZ = 24 + type * 4;
	image_x = type * 12;
	image_y = 12;
}
void Bullet::InitEnemyBullet(int type)								//��ʼ�����������������룬����
{
	atk = (type + 2) / 2;
	hit_dist = 15 + type * 5;
	HZ = 60 + type * 15 - (int)diff * 8;
	image_x = 12 * type;
}

bool Plane::IfBehitted(Bullet& bull)						//�ж��Ƿ񱻻���
{
	if (dist_y = fabs(bull.y - y) > 10)return false;
	if (dist_x = fabs(bull.x - x) > 10)return false;
	if (dist_x + dist_y * dist_y < bull.hit_dist)
	{
		//��Ч
		life -= bull.atk;
		bull.y = -5;
		if (life <= 0)
		{
			Death();
			return true;
		}
	}
	return false;
}
void Plane::Death()
{}

void Enemy::Init(int type)
{
	x = rand() % WIDTH;
	y = -18;
	life_ = life = (int)diff + type * 2 + 1;
	speed = type + 1 + (int)diff / 2;
	image_x = type * 36;
	image_y = 0;
	bullet_num = 6;
	bullet = new Bullet[bullet_num];
	for (int i = 0; i < bullet_num; i++)				//�ӵ���ʼ��
	{
		bullet[i].InitEnemyBullet(type);
	}
	bullet_HZ = bullet[0].HZ;
	loadimage(&planeY_ima	, "PG_enemyY.jpg");			//�л�����ͼ
	loadimage(&plane_ima	, "PG_enemy.jpg");				//�л�
	loadimage(&bulletY_ima	, "PG_ebulletY.jpg");			//�ɻ��ӵ�����ͼ
	loadimage(&bullet_ima	, "PG_ebullet.jpg");			//�ɻ��ӵ�
}
void Enemy::PlaneMove()
{
	if (y < 618)								//�л�������仯	
		y += speed;								//�������Ļ�����ƶ�
	else
	{
		//��Ч
		Death();								//�������Ļ������������
	}
}
void Enemy::PlaneP() {
	putimage(x - 18, y - 18, 36, 36, &planeY_ima, image_x, 0, SRCAND);
	putimage(x - 18, y - 18, 36, 36, &plane_ima, image_x, 0, SRCPAINT);
}
void Enemy::BulletCreate()
{
	if (bullet_times++ % bullet_HZ == 0)			//�л��ӵ��Զ�����
	{
		bullet[bullet_index % bullet_num].x = x;
		bullet[bullet_index++ % bullet_num].y = y + 18;
	}
}
void Enemy::BulletP_Move()
{
	for (int i = 0; i < bullet_num; i++)
	{
		putimage(bullet[i].x - 6, bullet[i].y - 6, 12, 12, 
			&bulletY_ima, bullet[i].image_x, 0, SRCAND);
		putimage(bullet[i].x - 6, bullet[i].y - 6, 12, 12,
			&bullet_ima, bullet[i].image_x, 0, SRCPAINT);
		if (bullet[i].y > -5)
		{
			bullet[i].y += Bullet::SPEED;
		}
	}
}
void Enemy::Death()
{
	life = life_;
	x = rand() % WIDTH;
	y = -18;
}

void MPlane::Init(int type)
{
	x = WIDTH / 2, y = HEIGHT / 2;//��ʼ���ɻ�λ��
	life = (int)lif * 2 + 1;
	speed = 5;										//�ɻ��ٶ�
	image_x = 80 * type;
	bullet_num = 40 - type * 4;
	bullet = new Bullet[bullet_num];
	for (int i = 0; i < bullet_num; i++)
	{
		bullet[i].InitMPlaneBullet(type);
	}
	bullet_HZ = bullet[0].HZ;

	lbullet_num = 10;
	lbullet = new Bullet[lbullet_num];
	for (int i = 0; i < lbullet_num; i++)
	{
		lbullet[i].InitLPlaneBullet(type);
	}
	lbullet_HZ = lbullet[0].HZ;
	killenemy_num = 0;
	loadimage(&planeY_ima, "PG_planeY.jpg");			//�ɻ�����ͼ
	loadimage(&plane_ima, "PG_plane.jpg");				//�ɻ�
	loadimage(&bulletY_ima, "PG_pbulletY.jpg");			//�ɻ��ӵ�����ͼ
	loadimage(&bullet_ima, "PG_pbullet.jpg");			//�ɻ��ӵ�
	loadimage(&statusY_ima, "PG_statusY.jpg");
	loadimage(&status_ima, "PG_status.jpg");
}
void MPlane::Operator()
{
	if (KEYGET(VK_UP))
		y -= speed;
	if (KEYGET(VK_LEFT))
		x -= speed;
	if (KEYGET(VK_DOWN))
		y += speed;
	if (KEYGET(VK_RIGHT))
		x += speed;
	if (KEYGET(VK_SPACE) && bullet_times++ % bullet_HZ == 0)
	{
		switch(killenemy_num / 10 )
		{
		case 0:
			bullet[bullet_index % bullet_num].x = x;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			break;
		case 1:
		case 2:
		case 3:
			bullet[bullet_index % bullet_num].x = x - 10;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x + 10;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			bullet[bullet_index % bullet_num].x = x;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x - 16;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x + 16;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			break;
		default:
			bullet[bullet_index % bullet_num].x = x-10;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x - 30;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x + 10;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			bullet[bullet_index % bullet_num].x = x + 30;
			bullet[bullet_index++ % bullet_num].y = y - 17;
			bullet_index %= bullet_num;
			break;
		}
		//ע���ӵ����±�������
	}
	//����չ��
}
void MPlane::PlaneP()
{
	putimage(x - 40, y - 18, 80, 36, &planeY_ima,		//�ɻ�����ͼƬ
		image_x, (KEYGET(VK_LEFT) ? 0 : (KEYGET(VK_RIGHT) ? 72 : 36)),
		SRCAND);
	putimage(x - 40, y - 18, 80, 36, &plane_ima,		//�ɻ�����ͼƬ
		image_x, (KEYGET(VK_LEFT) ? 0 : (KEYGET(VK_RIGHT) ? 72 : 36)),
		SRCPAINT);
}
void MPlane::LBulletCreate()
{
	if (lbullet_times++ % lbullet_HZ == 0)			//�ӵ��Զ�����
	{
		lbullet[lbullet_times % lbullet_num].x = x - 34;
		lbullet[lbullet_times++ % lbullet_num].y = y;
		lbullet[lbullet_times % lbullet_num].x = x + 34;
		lbullet[lbullet_times++ % lbullet_num].y = y;
	}
}
void MPlane::L_BulletP_Move()
{
	for (int i = 0; i < lbullet_num; i++)				//�Ż��ӵ�ͼƬ
	{
		putimage(lbullet[i].x - 6, lbullet[i].y - 6, 12, 12,
			&bulletY_ima, lbullet->image_x, 12, SRCAND);
		putimage(lbullet[i].x - 6, lbullet[i].y - 6, 12, 12,
			&bullet_ima, lbullet->image_x, 12, SRCPAINT);
		if (lbullet[i].y > -5)
		{
			lbullet[i].y -= Bullet::SPEED;
		}
	}
	for (int i = 0; i < bullet_num; i++)
	{
		putimage(bullet[i].x - 6, bullet[i].y - 6, 12, 12,
			&bulletY_ima, bullet[i].image_x, 0, SRCAND);
		putimage(bullet[i].x - 6, bullet[i].y - 6, 12, 12,
			&bullet_ima, bullet[i].image_x, 0, SRCPAINT);
		if (bullet[i].y > -5)
		{
			bullet[i].y -= Bullet::SPEED;
		}
	}
}
void MPlane::StatusP()
{
	putimage(0, 0, 450, 70, &statusY_ima, 0, life * 70, SRCAND);
	putimage(0, 0, 450, 70, &status_ima, 0, life * 70, SRCPAINT);
}
void MPlane::Death()
{
	ifnext = NextKW::NEXT;
}

void BackGround::BackGroundP_Move()
{
	putimage(0, 0, WIDTH, HEIGHT, &PG_background, 0,		//����ͼƬ //5400 = 6000(ͼƬ����) - HEIGHT
		PG_background_move = (5350 + PG_background_move--) % 5350);
}

