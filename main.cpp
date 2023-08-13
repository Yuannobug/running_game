#include<time.h>

#include<Windows.h>

#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>

#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")


//��Ϸ����ĳ��Ϳ�
#define WEDTH  1000
#define HEIGHT 500

IMAGE gamebegin;//��Ϸ��ʼ����
IMAGE gamebackground;//��Ϸ��������
IMAGE rolerun[9];//��ɫ���ܱ���
IMAGE rolejump[12];//��ɫ��Ծ����
IMAGE rolecrouch[12];//��ɫ�¶ױ���
IMAGE roleblood[10];//��ɫѪ������
IMAGE gameover;//��Ϸ��������
IMAGE win;//��Ϸʤ������
typedef struct barrier
{
	IMAGE bluecar;
	IMAGE thunder;
	IMAGE gun;
}barrier;

barrier gamebarrier;

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //�°�pngȥ������
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}


void init()//��ʼ��
{
	int i = 0;
	initgraph(WEDTH, HEIGHT);
	loadimage(&gamebegin, L"E:\\C++\\���\\DIY�ܿ�\\picture\\begin.jpg",  WEDTH, HEIGHT);
	loadimage(&win, L"E:\\C++\\���\\DIY�ܿ�\\picture\\win.jpg", WEDTH, HEIGHT);
	loadimage(&gamebackground, L"E:\\C++\\���\\DIY�ܿ�\\picture\\background.jpg", 3 * WEDTH, HEIGHT);
	loadimage(&gameover, L"E:\\C++\\���\\DIY�ܿ�\\picture\\gameover.jpg", WEDTH, HEIGHT);
	//run
	loadimage(&rolerun[0], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run2.png", 350,350);
	loadimage(&rolerun[1], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run3.png", 350, 350);
	loadimage(&rolerun[2], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run4.png", 350, 350);
	loadimage(&rolerun[3], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run8.png", 350, 350);
	loadimage(&rolerun[4], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run9.png", 350, 350);
	loadimage(&rolerun[5], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run10.png", 350, 350);
	loadimage(&rolerun[6], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run12.png", 350, 350);
	loadimage(&rolerun[7], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run13.png", 350, 350);
	loadimage(&rolerun[8], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run14.png", 350, 350);
	//jump
	loadimage(&rolejump[0], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run10.png", 350, 350);
	loadimage(&rolejump[1], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run15.png", 350, 350);
	loadimage(&rolejump[2], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run15.png", 350, 350);
	loadimage(&rolejump[3], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[4], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[5], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[6], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[7], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[8], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[9], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[10], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run1.png", 350, 350);
	loadimage(&rolejump[11], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run1.png", 350, 350);
	//crouch
	for ( i = 0; i < 12; i++)
	{
		loadimage(&rolecrouch[i], L"E:\\C++\\���\\DIY�ܿ�\\picture\\run17.png", 350, 350);
	}
	loadimage(&gamebarrier.bluecar, L"E:\\C++\\���\\DIY�ܿ�\\picture\\bluecar.png", 450, 450);
	loadimage(&gamebarrier.thunder, L"E:\\C++\\���\\DIY�ܿ�\\picture\\thunder.png", 800, 800);
	loadimage(&gamebarrier.gun, L"E:\\C++\\���\\DIY�ܿ�\\picture\\gun.png", 600, 600);
	//Ѫ��
	for (i = 0; i < 10; i++)
	{
		loadimage(&roleblood[i], L"E:\\C++\\���\\DIY�ܿ�\\picture\\blood.png", 300, 300);

	}
}

void showbackground(int x)//��ʾ����
{
	putimage(x, 0, &gamebackground);
}

void musicinit()//��������
{
	mciSendString(L"open E:\\C++\\���\\DIY�ܿ�\\picture\\music.mp3 alias m", 0, 0, 0);
	mciSendString(L"play m repeat", 0, 0, 0);
}

void showrun(int x,int status)//��ɫ����
{
	transparentimage3(NULL, x, 140, &rolerun[status]);//��ת��ȥ����ɫ
}

void showjump(int x,int y, int status)//��ɫ��Ծ
{
	transparentimage3(NULL, x, y, &rolejump[status]);
}

void showcrouch(int x, int y, int status)//��ɫ�¶�
{
	transparentimage3(NULL, x, y, &rolecrouch[status]);
}

void showbluecar(int x, int y)
{
	transparentimage3(NULL, x, y, &gamebarrier.bluecar);
}

void showgun(int x, int y)
{
	transparentimage3(NULL, x, y, &gamebarrier.gun);
}

void showthunder(int x, int y)
{
	transparentimage3(NULL, x, y, &gamebarrier.thunder);
}

void showblood(int bloodnum)
{
	int i = 0;
	int blood_x[10] = {-125,-75,-25,25,75,125,175,225,275,325};
	int blood_y = -100;
	for (i = 0; i < bloodnum; i++)
	{
		transparentimage3(NULL, blood_x[i], blood_y, &roleblood[i]);
	}
}

int operate()
{
	char ch;
	if (_kbhit())
	{
		ch=_getch();
		if (ch == 'w' || ch == 'W')
		{
			return 1;
		}
		if (ch == 'S' || ch == 's')
		{
			return 2;
		}
		if (ch == ' ')
		{
			return 3;
		}
	}
	return 0;
}

void judgeblood(int &bloodnum,int&score, int jumping, int crouching, int bluecar_x, int thunder_x, int gun_x)
{
	if (bluecar_x >= 50 && bluecar_x < 68)
	{
		if (jumping == 0)
		{
			bloodnum--;
		}
		else
		{
			score++;
		}
	}
	if (thunder_x >= 5 && thunder_x < 23)
	{
		if (crouching == 0)
		{
			bloodnum--;
		}
		else
		{
			score++;
		}
	}
	if (gun_x >= 30 && gun_x < 58)
	{
		if (jumping == 0)
		{
			bloodnum--;
		}
		else
		{
			score++;
		}
	}
}



int main()
{
	srand((unsigned int)time(NULL));
	int time = 0;//ʵ��֡�ȴ�
	int i = 0;
	int background_x = 0;//����������x
	int runstatus = 0;//���ܵ�֡
	int jumpstatus = 0;//��Ծ��֡
	int jumping = 0;//�����Ծ����
	int jumpheight[12] = {150,100,80,50,40,25,25,40,50,80,100,150};
	int crouchheight = 180;
	int crouching = 0;
	int crouchstatus = 0;
	int choice = 0;//����ѡ��
	int bluecar_x = 1000;
	int bluecar_y = 125;//��ɫС������
	int bluecar_num = 0;
	int thunder_x = 1000;
	int thunder_y = -170;
	int thunder_num = 0;//��������
	int gun_x = 1000;
	int gun_y = 50;
	int gun_num = 0;
	int random = 0;
	int bloodnum = 10;
	int score = 0;
	init();
	musicinit();
	while (1)//��ʼ����
	{
		putimage(0, 0, &gamebegin);
		if (operate() == 3)
		{
			break;
		}
	}
	while (1)
	{
		time++;//ʵ��֡�ȴ��Ҳ�Ӱ�찴����ȡ
		choice = operate();
		if (time > 1100 || choice)
		{
			time = 0;
			random = rand() % 20 + 1;//�����ȡ�ϰ���
			if (random % 13 == 0)//���������ɫС��
			{
				bluecar_num = 1;
			}
			if (random % 15 == 0)
			{
				thunder_num = 1;
			}
			if (random % 11 == 0)
			{
				gun_num = 1;
			}
			if (background_x == -1750)//����ѭ��
			{
				background_x = 0;
			}
			showbackground(background_x);
			showblood(bloodnum);
			if (choice == 0 && jumping == 0 && crouching == 0)//����
			{
				if (runstatus == 9)//����ѭ��
				{
					runstatus = 0;
				}
				showrun(150, runstatus);
				runstatus++;//����֡�仯 
			}
			if ((choice == 1 && jumping == 0) || (jumping == 1))//��Ծ�ұ����ظ���Ծ
			{
				jumping = 1;
				if (jumpstatus == 12)//��ֹ��Ծ
				{
					jumpstatus = 0;
					jumping = 0;
					i = 0;
				}
				showjump(150, jumpheight[i++], jumpstatus);
				jumpstatus++;
			}
			if (choice == 2 || crouching == 1)//�¶�
			{
				crouching = 1;
				if (crouchstatus == 12)
				{
					crouching = 0;
					crouchstatus = 0;
				}
				showcrouch(150, crouchheight, crouchstatus);
				crouchstatus++;

			}
			if (bluecar_num == 1)//����ɫС��
			{
				if (bluecar_x < gun_x)//�������
				{
					if (gun_x - bluecar_x < 300)
					{
						gun_x = bluecar_x + 500;
					}
				}
				else
				{
					if (bluecar_x - gun_x < 300)
					{
						bluecar_x = gun_x + 500;
					}
				}
				if (bluecar_x < -100)
				{
					bluecar_x = 1000;
					bluecar_num = 0;
				}
				showbluecar(bluecar_x, bluecar_y);
				bluecar_x -= 18;
			}	
			if (thunder_num == 1)//������
			{
				if (thunder_x < bluecar_x)//�������
				{
					if (bluecar_x-thunder_x < 300)
					{
						bluecar_x = thunder_x + 500;
					}
				}
				else
				{
					if (thunder_x - bluecar_x < 300)
					{
						thunder_x = bluecar_x + 500;
					}
				}
				showthunder(thunder_x, thunder_y);
				if (thunder_x < -500)
				{
					thunder_x = 1300;
					thunder_num = 0;
				}
				thunder_x -= 18;
			}
			if (gun_num == 1)
			{
				if (thunder_x < gun_x)//�������
				{
					if (gun_x - thunder_x < 300)
					{
						gun_x = thunder_x + 500;
					}
				}
				else
				{
					if (thunder_x - gun_x < 300)
					{
						thunder_x = gun_x + 500;
					}
				}
				showgun(gun_x, gun_y);
				if (gun_x < -500)
				{
					gun_x = 1600;
					gun_num = 0;
				}
				gun_x -= 18;
			}
			judgeblood(bloodnum,score,jumping,crouching,bluecar_x,thunder_x,gun_x);
			outtextxy(870, 10, 's');
			outtextxy(880, 10, 'c');
			outtextxy(890, 10, 'o');
			outtextxy(900, 10, 'r');
			outtextxy(910, 10, 'e');
			outtextxy(920, 10, ':');
			outtextxy(930, 10, '0'+score/100);
			outtextxy(940, 10, '0'+score/10);
			outtextxy(950, 10, '0'+score%10);
			background_x -= 5;//��������
		}
		//Sleep(30);//֡�ȴ�30ms(���ܵ��°���©��ȡ)
		if (bloodnum == 0)//ʧ��
		{
			break;
		}
		if (score == 50)//�ɹ�
		{
			break;
		}
	}
	mciSendString(L"close m", 0, 0, 0);
	if (bloodnum == 0)
	{
		while (1)//ʧ�ܴ���
		{
			putimage(0, 0, &gameover);
			mciSendString(L"open E:\\C++\\���\\DIY�ܿ�\\picture\\gameover.mp3 alias m1", 0, 0, 0);
			mciSendString(L"play m1 repeat", 0, 0, 0);
			if (_kbhit())
			{
				break;
			}
		}
		mciSendString(L"close m1", 0, 0, 0);
	}
	else
	{
		while (1)//�ɹ�����
		{
			putimage(0, 0, &win);
			mciSendString(L"open E:\\C++\\���\\DIY�ܿ�\\picture\\win.mp3 alias m2", 0, 0, 0);
			mciSendString(L"play m2 repeat", 0, 0, 0);
			if (_kbhit())
			{
				break;
			}
		}
		mciSendString(L"close m2", 0, 0, 0);
	}
	closegraph();
	return 0;
}