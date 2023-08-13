#include<time.h>

#include<Windows.h>

#include<graphics.h>
#include<conio.h>
#include<mmsystem.h>

#pragma comment( lib, "MSIMG32.LIB")
#pragma comment(lib,"winmm.lib")


//”Œœ∑ΩÁ√Êµƒ≥§∫ÕøÌ
#define WEDTH  1000
#define HEIGHT 500

IMAGE gamebegin;//”Œœ∑ø™ ºΩÁ√Ê
IMAGE gamebackground;//”Œœ∑±≥æ∞±‰¡ø
IMAGE rolerun[9];//Ω«…´±º≈‹±‰¡ø
IMAGE rolejump[12];//Ω«…´Ã¯‘æ±‰¡ø
IMAGE rolecrouch[12];//Ω«…´œ¬∂◊±‰¡ø
IMAGE roleblood[10];//Ω«…´—™¡ø±‰¡ø
IMAGE gameover;//”Œœ∑Ω· ¯ª≠√Ê
IMAGE win;//”Œœ∑ §¿˚ª≠√Ê
typedef struct barrier
{
	IMAGE bluecar;
	IMAGE thunder;
	IMAGE gun;
}barrier;

barrier gamebarrier;

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //–¬∞Êpng»•≥˝±≥æ∞
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}


void init()//≥ı ºªØ
{
	int i = 0;
	initgraph(WEDTH, HEIGHT);
	loadimage(&gamebegin, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\begin.jpg",  WEDTH, HEIGHT);
	loadimage(&win, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\win.jpg", WEDTH, HEIGHT);
	loadimage(&gamebackground, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\background.jpg", 3 * WEDTH, HEIGHT);
	loadimage(&gameover, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\gameover.jpg", WEDTH, HEIGHT);
	//run
	loadimage(&rolerun[0], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run2.png", 350,350);
	loadimage(&rolerun[1], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run3.png", 350, 350);
	loadimage(&rolerun[2], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run4.png", 350, 350);
	loadimage(&rolerun[3], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run8.png", 350, 350);
	loadimage(&rolerun[4], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run9.png", 350, 350);
	loadimage(&rolerun[5], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run10.png", 350, 350);
	loadimage(&rolerun[6], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run12.png", 350, 350);
	loadimage(&rolerun[7], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run13.png", 350, 350);
	loadimage(&rolerun[8], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run14.png", 350, 350);
	//jump
	loadimage(&rolejump[0], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run10.png", 350, 350);
	loadimage(&rolejump[1], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run15.png", 350, 350);
	loadimage(&rolejump[2], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run15.png", 350, 350);
	loadimage(&rolejump[3], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[4], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[5], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[6], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[7], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run16.png", 350, 350);
	loadimage(&rolejump[8], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[9], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run11.png", 350, 350);
	loadimage(&rolejump[10], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run1.png", 350, 350);
	loadimage(&rolejump[11], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run1.png", 350, 350);
	//crouch
	for ( i = 0; i < 12; i++)
	{
		loadimage(&rolecrouch[i], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\run17.png", 350, 350);
	}
	loadimage(&gamebarrier.bluecar, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\bluecar.png", 450, 450);
	loadimage(&gamebarrier.thunder, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\thunder.png", 800, 800);
	loadimage(&gamebarrier.gun, L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\gun.png", 600, 600);
	//—™¡ø
	for (i = 0; i < 10; i++)
	{
		loadimage(&roleblood[i], L"E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\blood.png", 300, 300);

	}
}

void showbackground(int x)//œ‘ æ±≥æ∞
{
	putimage(x, 0, &gamebackground);
}

void musicinit()//º”‘ÿ“Ù¿÷
{
	mciSendString(L"open E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\music.mp3 alias m", 0, 0, 0);
	mciSendString(L"play m repeat", 0, 0, 0);
}

void showrun(int x,int status)//Ω«…´±º≈‹
{
	transparentimage3(NULL, x, 140, &rolerun[status]);//æ≠◊™ªª»•≥˝µ◊…´
}

void showjump(int x,int y, int status)//Ω«…´Ã¯‘æ
{
	transparentimage3(NULL, x, y, &rolejump[status]);
}

void showcrouch(int x, int y, int status)//Ω«…´œ¬∂◊
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
	int time = 0;// µœ÷÷°µ»¥˝
	int i = 0;
	int background_x = 0;//±≥æ∞µƒ◊¯±Íx
	int runstatus = 0;//±º≈‹µƒ÷°
	int jumpstatus = 0;//Ã¯‘æµƒ÷°
	int jumping = 0;//ÕÍ≥…Ã¯‘æ∂Ø◊˜
	int jumpheight[12] = {150,100,80,50,40,25,25,40,50,80,100,150};
	int crouchheight = 180;
	int crouching = 0;
	int crouchstatus = 0;
	int choice = 0;//∂Ø◊˜—°œÓ
	int bluecar_x = 1000;
	int bluecar_y = 125;//¿∂…´–°≥µ◊¯±Í
	int bluecar_num = 0;
	int thunder_x = 1000;
	int thunder_y = -170;
	int thunder_num = 0;//Œ⁄‘∆ ˝¡ø
	int gun_x = 1000;
	int gun_y = 50;
	int gun_num = 0;
	int random = 0;
	int bloodnum = 10;
	int score = 0;
	init();
	musicinit();
	while (1)//ø™ º¥∞ø⁄
	{
		putimage(0, 0, &gamebegin);
		if (operate() == 3)
		{
			break;
		}
	}
	while (1)
	{
		time++;// µœ÷÷°µ»¥˝«“≤ª”∞œÏ∞¥º¸ªÒ»°
		choice = operate();
		if (time > 1100 || choice)
		{
			time = 0;
			random = rand() % 20 + 1;//ÀÊª˙ªÒ»°’œ∞≠ŒÔ
			if (random % 13 == 0)//ÀÊª˙…˙≥…¿∂…´–°≥µ
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
			if (background_x == -1750)//±≥æ∞—≠ª∑
			{
				background_x = 0;
			}
			showbackground(background_x);
			showblood(bloodnum);
			if (choice == 0 && jumping == 0 && crouching == 0)//±º≈‹
			{
				if (runstatus == 9)//±º≈‹—≠ª∑
				{
					runstatus = 0;
				}
				showrun(150, runstatus);
				runstatus++;//±º≈‹÷°±‰ªØ 
			}
			if ((choice == 1 && jumping == 0) || (jumping == 1))//Ã¯‘æ«“±‹√‚÷ÿ∏¥Ã¯‘æ
			{
				jumping = 1;
				if (jumpstatus == 12)//÷’÷πÃ¯‘æ
				{
					jumpstatus = 0;
					jumping = 0;
					i = 0;
				}
				showjump(150, jumpheight[i++], jumpstatus);
				jumpstatus++;
			}
			if (choice == 2 || crouching == 1)//œ¬∂◊
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
			if (bluecar_num == 1)//”–¿∂…´–°≥µ
			{
				if (bluecar_x < gun_x)//µ˜’˚º‰æ‡
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
			if (thunder_num == 1)//”–Œ⁄‘∆
			{
				if (thunder_x < bluecar_x)//µ˜’˚º‰æ‡
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
				if (thunder_x < gun_x)//µ˜’˚º‰æ‡
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
			background_x -= 5;//±≥æ∞¡˜∂Ø
		}
		//Sleep(30);//÷°µ»¥˝30ms(ø…ƒ‹µº÷¬∞¥º¸¬©∂¡»°)
		if (bloodnum == 0)// ß∞‹
		{
			break;
		}
		if (score == 50)//≥…π¶
		{
			break;
		}
	}
	mciSendString(L"close m", 0, 0, 0);
	if (bloodnum == 0)
	{
		while (1)// ß∞‹¥∞ø⁄
		{
			putimage(0, 0, &gameover);
			mciSendString(L"open E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\gameover.mp3 alias m1", 0, 0, 0);
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
		while (1)//≥…π¶¥∞ø⁄
		{
			putimage(0, 0, &win);
			mciSendString(L"open E:\\C++\\ ÓºŸ\\DIY≈‹ø·\\picture\\win.mp3 alias m2", 0, 0, 0);
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