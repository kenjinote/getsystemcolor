#pragma comment(linker, "/opt:nowin98")
#include <windows.h>

CHAR szClassName[]="window";
HWND hEdit;

VOID AddLine(LPSTR str)
{
	DWORD len = SendMessage(hEdit,WM_GETTEXTLENGTH,0,0);
	SendMessage(hEdit,EM_SETSEL,(WPARAM)len,(LPARAM)len);
	SendMessage(hEdit,EM_REPLACESEL,(WPARAM)false,(LPARAM)str);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static const int syscolor[] = {
		COLOR_3DDKSHADOW ,		
		COLOR_3DFACE ,
		COLOR_3DHILIGHT ,
		COLOR_3DLIGHT ,
		COLOR_3DSHADOW ,
		COLOR_ACTIVEBORDER ,
		COLOR_ACTIVECAPTION ,
		COLOR_APPWORKSPACE ,
		COLOR_BACKGROUND ,
		COLOR_BTNTEXT ,
		COLOR_CAPTIONTEXT ,
		COLOR_GRAYTEXT ,
		COLOR_HIGHLIGHT ,
		COLOR_HIGHLIGHTTEXT ,
		COLOR_INACTIVEBORDER ,
		COLOR_INACTIVECAPTION ,
		COLOR_INFOBK ,
		COLOR_INFOTEXT ,
		COLOR_MENU ,
		COLOR_MENUTEXT ,
		COLOR_SCROLLBAR ,
		COLOR_WINDOW ,
		COLOR_WINDOWFRAME ,
		COLOR_WINDOWTEXT,
		NULL
	};
	int i;

	switch (msg){
	case WM_CREATE:
		hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|ES_MULTILINE|ES_AUTOVSCROLL,0,0,0,0,
			hWnd,NULL,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
		for(i=0;syscolor[i];i++){
			TCHAR szTemp[1024];
			DWORD rgb = GetSysColor(syscolor[i]);
			wsprintf(szTemp,TEXT("RGB = %d, %d, %d\r\n"),GetRValue(rgb),GetGValue(rgb),GetBValue(rgb));
			AddLine(szTemp);
		}

		break;
	case WM_SIZE:
		MoveWindow(hEdit,0,0,LOWORD(lParam),HIWORD(lParam),TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return(DefWindowProc(hWnd,msg,wParam,lParam));
	}
	return (0L);
}

int WINAPI WinMain(HINSTANCE hinst,HINSTANCE hPreInst,
				   LPSTR pCmdLine,int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	if(!hPreInst){
		wndclass.style=CS_HREDRAW|CS_VREDRAW;
		wndclass.lpfnWndProc=WndProc;
		wndclass.cbClsExtra=0;
		wndclass.cbWndExtra=0;
		wndclass.hInstance =hinst;
		wndclass.hIcon=NULL;
		wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
		wndclass.lpszMenuName=NULL;
		wndclass.lpszClassName=szClassName;
		if(!RegisterClass(&wndclass))
			return FALSE;
	}
	hWnd=CreateWindow(szClassName,
		"ƒ^ƒCƒgƒ‹",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hinst,
		NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg,NULL,0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (msg.wParam);
}
