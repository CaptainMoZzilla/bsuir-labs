// Dll1.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>

#include "Dll1.h"



namespace MyLibrary {

	char _stdcall getKey() {
		return _getch();
	}

	void _cdecl PrintWithCesarsCode() {
		printf("%c", _getch() + 1);
	}
	
}
