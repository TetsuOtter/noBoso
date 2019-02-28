#include "stdafx.h"
#include <string>
#define DllEx extern "C" __declspec(dllexport)
const char BVELoadingScenarioWinName[29] = "シナリオを読み込んでいます…";
const char BVEWinName[13] = "Bve trainsim";
HWND BVEWindowHandle = NULL;

DllEx bool GetBVEWindowHandle()//BVEのウィンドウハンドルを取得する
{
	HWND detop = GetDesktopWindow();
	HWND hwnd = FindWindowExA(detop, NULL, BVELoadingScenarioWinName, NULL);
	if (hwnd != NULL) BVEWindowHandle = GetParent(hwnd);
	else BVEWindowHandle = FindWindowExA(detop, NULL, BVEWinName, NULL);
	
	if (BVEWindowHandle == NULL) return false;
	return true;
}
DllEx void DisposeHandle() {

}
DllEx void KeyDown(unsigned char KeyCode) {
	PostMessageA(BVEWindowHandle, WM_KEYDOWN, KeyCode, 0);
}
DllEx void KeyUp(unsigned char KeyCode) {
	PostMessageA(BVEWindowHandle, WM_KEYUP, KeyCode, 0);
}
DllEx bool IsKeyDown(unsigned char KeyCode) {
	short key = GetKeyState(KeyCode);
	return GetKeyState(KeyCode) < 0 ? true : false;
}


void DisposeDo()
{
	//Dispose内で実行
	keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	
	keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

int count = 0;
int func7 = 0;

void maindo(int Speedin)
{
	bool bveactive = false;
	char bufs[13];
	char bvets[13] = "Bve trainsim";
	GetWindowText(GetForegroundWindow(), bufs, 13);
	if (memcmp(bufs, bvets, sizeof(bvets)) == 0) {
		bveactive = true;
	}
	else {
		bveactive = false;
		if (bveactive == true) {

			if (Speedin > 5) {
				if (GetKeyState(VK_SHIFT) < 0) {
					keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
				if (GetKeyState(VK_CONTROL) >= 0) {
					keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
				}
				if (GetKeyState(VK_F7) < 0) {
					keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					func7 = 1;
				}
			}
			else if (Speedin < -5) {
				if (GetKeyState(VK_CONTROL) < 0) {
					keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
				if (GetKeyState(VK_SHIFT) >= 0) {
					keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
				}
				if (GetKeyState(VK_F7) < 0) {
					keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
					func7 = 2;
				}
			}
			else {
				if (GetKeyState(VK_SHIFT) < 0) {
					keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}

				if (GetKeyState(VK_F7) < 0) {
					keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
				if (GetKeyState(VK_CONTROL) < 0) {
					keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
				}
			}
		}
		if (bveactive == false) {
			if (GetKeyState(VK_SHIFT) & 0x80) {
				keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			}

			if (GetKeyState(VK_F7) & 0x80) {
				keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			}
			if (GetKeyState(VK_CONTROL) & 0x80) {
				keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			}
		}

		if (GetKeyState(VK_F7) & 0x80 && Speedin != 0) {
			count++;
			std::string showmsg = "F7キー押下を検知 : ";
			showmsg = showmsg + std::to_string(count);
			showmsg = showmsg + " 回目\n";
			if (Speedin > 15 || Speedin < -15) {
				showmsg = showmsg + "F7は車両によって無効化されています。\n";
			}
			showmsg = showmsg + str;
			const char* shmsg = showmsg.c_str();
			MessageBox(NULL, shmsg, "[F7]無効化プログラム", MB_OK | MB_ICONERROR);
		}
		if (count > 10) {
			//exit(0);//最初は10回以上のF7押下で強制終了させようとしていた。
		}
		if (func7 == 1) {
			func7 = 0;
			keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

			keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
		}
		if (func7 == 2) {
			func7 = 0;
			keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
			keybd_event(VK_F7, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			keybd_event(VK_CONTROL, 0x00, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
			keybd_event(VK_SHIFT, 0x00, KEYEVENTF_EXTENDEDKEY | 0, 0);
		}
	}