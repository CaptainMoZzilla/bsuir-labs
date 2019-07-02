#pragma once


namespace MyLibrary {
	extern "C" { __declspec(dllexport) char _stdcall getKey(); }

	extern "C" { __declspec(dllexport) void _cdecl PrintWithCesarsCode(); }
}