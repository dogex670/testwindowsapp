#include "stdafx.h"
#include "capture.hpp"
#include <iostream>


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char buffer[128];
	memset(buffer, 0, sizeof(buffer));

	GetWindowTextA(hwnd, buffer, sizeof(buffer));
	if (IsWindowVisible(hwnd))
	{
		std::cout << buffer << std::endl;
	}

	return TRUE;
}
/*
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char buffer[256];
	GetWindowTextA(hwnd, buffer, sizeof(buffer));

	if (strcmp(buffer, "OBS") == 0)
	{
		// OBS is running
		*(bool*)lParam = true;
		return FALSE;
	}

	return TRUE;
}
*/
bool IsObsRunning()
{
	bool isRunning = false;
	EnumWindows(EnumWindowsProc, (LPARAM)&isRunning);
	return isRunning;
}




void CaptureScreen()
{
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND hDesktopWnd = GetDesktopWindow();
	HDC hDesktopDC = GetDC(hDesktopWnd);
	HDC hCaptureDC = CreateCompatibleDC(hDesktopDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hDesktopDC, nScreenWidth, nScreenHeight);
	SelectObject(hCaptureDC, hCaptureBitmap);
	BitBlt(hCaptureDC, 0, 0, nScreenWidth, nScreenHeight, hDesktopDC, 0, 0, SRCCOPY | CAPTUREBLT);
	//SaveCapture(hCaptureBitmap);
	ReleaseDC(hDesktopWnd, hDesktopDC);
	DeleteDC(hCaptureDC);
	DeleteObject(hCaptureBitmap);
}


int wmain()
{
	/*
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	MFStartup(MF_VERSION);
	std::cout << "Capturing screen for 10 seconds...";
	DESKTOPCAPTUREPARAMS dp;

	// To Video
	dp.VIDEO_ENCODING_FORMAT = MFVideoFormat_H265;
	dp.f = L"capture.mp4";

	// To Stream
	dp.f = L"";
	dp.PrepareAttributes = [](IMFAttributes* attrs)
	{
		attrs->SetGUID(MF_TRANSCODE_CONTAINERTYPE, MFTranscodeContainerType_ASF);
	};
	dp.Streamer = [](const BYTE* b,size_t sz,void* cb)
	{
		FILE* fp = 0;
		_wfopen_s(&fp, L"capture.asf", L"a+b");
		fwrite(b, 1, sz, fp);
		fclose(fp);
		return S_OK;
	};



	// To callback frame
	dp.f = L"";
	dp.HasAudio = 0;
	dp.HasVideo = 1;
	dp.Framer = [](const BYTE* b, size_t sz,void* cb)
	{
		if (sz)
			return S_OK;
		return S_FALSE;
	};


	dp.EndMS = 10000;
	DesktopCapture(dp);
	std::cout << "Done.\r\n";
	return 0;
	*/


	//new
	CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	MFStartup(MF_VERSION);
	std::cout << "Capturing screen for 10 seconds...";
	DESKTOPCAPTUREPARAMS dp;

	dp.f = L"capture.mp4";
	dp.EndMS = 10000;
	DesktopCapture(dp);
	std::cout << "Done.\r\n";


	EnumWindows(EnumWindowsProc, 0);

	if (IsObsRunning())
	{
		CaptureScreen();
	}

	return 0;


}
