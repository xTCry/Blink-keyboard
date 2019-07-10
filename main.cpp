#include <stdlib.h>
#include <Windows.h>
#include <iostream>

int rand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void SetKeyState(bool state, BYTE keyCode) {
	byte keyState[256];

	GetKeyboardState((PBYTE)&keyState);
	if ((state && !(keyState[keyCode] & 1)) || (!state && (keyState[keyCode] & 1))) {
		
		keybd_event(keyCode, 0x45,
			KEYEVENTF_EXTENDEDKEY | 0, 0);

		keybd_event(keyCode, 0x45,
			KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}
}

void ToggleKeyState(BYTE keyCode) {
	keybd_event(keyCode, 0x45,
		KEYEVENTF_EXTENDEDKEY | 0, 0);

	keybd_event(keyCode, 0x45,
		KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
}

void BlinkKeyboard() {
	int i = 0;
	bool bBlink = false;
	
	while (true) {
		int r = rand(0, 2);
		byte key = (i % 40 == 0)? VK_SNAPSHOT:
					(r == 0)? VK_CAPITAL:
					(r == 1)? VK_SCROLL:
							VK_NUMLOCK;
		
		// SetKeyState(bBlink, key);
		ToggleKeyState(key);
		bBlink = !bBlink;
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
