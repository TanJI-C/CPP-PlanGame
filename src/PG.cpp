#include"PG.h"
#include"Update.h"
#include<graphics.h>
#include<cmath>
#include<Windows.h>

void Bullet::InitMPlaneBullet(int type)								//初始胡攻击力，攻击距离，射速，图片
{
	atk = type + 1;
	hit_dist = 13 + type * 6;
	HZ = 8 + type * 8;
	image_x = type * 12;
	image_y = 0;
}
void Bullet::InitLPlaneBullet(int type)								//初始胡攻击力，攻击距离，射速，图片
{
	atk = 1;
	hit_dist = 14 - type * 5;
	HZ = 24 + type * 4;
	image_x = type * 12;
	image_y = 12;
}
void Bullet::InitEnemyBullet(int type)								//初始胡攻击力，攻击距离，射速
{
	atk = (type + 2) / 2;
	hit_dist = 15 + type * 5;
	HZ = 60 + type * 15 - (int)diff * 8;
	image_x = 12 * type;
}

bool Plane::IfBehitted(Bullet& bull)						//判定是否被击中
{
	if (dist_y = fabs(bull.y - y) > 10)return false;
	if (dist_x = fabs(bull.x - x) > 10)return false;
	if (dist_x + dist_y * dist_y < bull.hit_dist)
	{
		//音效
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
	for (int i = 0; i < bullet_num; i++)				//子弹初始化
	{
		bullet[i].InitEnemyBullet(type);
	}
	bullet_HZ = bullet[0].HZ;
	loadimage(&planeY_ima	, "PG_enemyY.jpg");			//敌机掩码图
	loadimage(&plane_ima	, "PG_enemy.jpg");				//敌机
	loadimage(&bulletY_ima	, "PG_ebulletY.jpg");			//飞机子弹掩码图
	loadimage(&bullet_ima	, "PG_ebullet.jpg");			//飞机子弹
}
void Enemy::PlaneMove()
{
	if (y < 618)								//敌机的坐标变化	
		y += speed;								//如果在屏幕内则移动
	else
	{
		//音效
		Death();								//如果在屏幕外则重新生成
	}
}
void Enemy::PlaneP() {
	putimage(x - 18, y - 18, 36, 36, &planeY_ima, image_x, 0, SRCAND);
	putimage(x - 18, y - 18, 36, 36, &plane_ima, image_x, 0, SRCPAINT);
}
void Enemy::BulletCreate()
{
	if (bullet_times++ % bullet_HZ == 0)			//敌机子弹自动生成
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
	x = WIDTH / 2, y = HEIGHT / 2;//初始化飞机位置
	life = (int)lif * 2 + 1;
	speed = 5;										//飞机速度
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
	loadimage(&planeY_ima, "PG_planeY.jpg");			//飞机掩码图
	loadimage(&plane_ima, "PG_plane.jpg");				//飞机
	loadimage(&bulletY_ima, "PG_pbulletY.jpg");			//飞机子弹掩码图
	loadimage(&bullet_ima, "PG_pbullet.jpg");			//飞机子弹
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
		//注意子弹的下标增加了
	}
	//光翼展开
}
void MPlane::PlaneP()
{
	putimage(x - 40, y - 18, 80, 36, &planeY_ima,		//飞机掩码图片
		image_x, (KEYGET(VK_LEFT) ? 0 : (KEYGET(VK_RIGHT) ? 72 : 36)),
		SRCAND);
	putimage(x - 40, y - 18, 80, 36, &plane_ima,		//飞机掩码图片
		image_x, (KEYGET(VK_LEFT) ? 0 : (KEYGET(VK_RIGHT) ? 72 : 36)),
		SRCPAINT);
}
void MPlane::LBulletCreate()
{
	if (lbullet_times++ % lbullet_HZ == 0)			//子弹自动生成
	{
		lbullet[lbullet_times % lbullet_num].x = x - 34;
		lbullet[lbullet_times++ % lbullet_num].y = y;
		lbullet[lbullet_times % lbullet_num].x = x + 34;
		lbullet[lbullet_times++ % lbullet_num].y = y;
	}
}
void MPlane::L_BulletP_Move()
{
	for (int i = 0; i < lbullet_num; i++)				//僚机子弹图片
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
	putimage(0, 0, WIDTH, HEIGHT, &PG_background, 0,		//背景图片 //5400 = 6000(图片长度) - HEIGHT
		PG_background_move = (5350 + PG_background_move--) % 5350);
}

