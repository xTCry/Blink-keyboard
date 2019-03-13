#include <stdlib.h>
#include <Windows.h>
#include <iostream>

int rand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void ToggleKeyState(BYTE keyCode) {
	keybd_event(keyCode, 0x45,
		KEYEVENTF_EXTENDEDKEY | 0, 0);

	keybd_event(keyCode, 0x45,
		KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void BlinkKeyboard() {
	int i = 0;
	
	while (true) {
		int r = rand(0, 2);
		byte key = (i % 40 == 0)? VK_SNAPSHOT:
					(r == 0)? VK_CAPITAL:
					(r == 1)? VK_SCROLL:
							VK_NUMLOCK;
		
		ToggleKeyState(key);
		Sleep(80);
		i++;
	}
}

int main(int argc, char** argv) {
	
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);
	
	BlinkKeyboard();
	
	return 0;
}
