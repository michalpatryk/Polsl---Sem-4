#include <string>
#include <Windows.h>

void getFullPath(const std::string& str)
{
	char filename[100];
	strcpy_s(filename, str.c_str());
	char fullFilename[MAX_PATH];
	GetFullPathName(filename, MAX_PATH, fullFilename, nullptr);
	MessageBox(NULL, fullFilename, "DEBUG", MB_OK);
	return;
}
