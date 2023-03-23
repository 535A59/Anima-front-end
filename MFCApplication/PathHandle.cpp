#include "pch.h"
#include "PathHandle.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <io.h>
#include <iomanip>

using namespace std;

CString PathHandle::FilePath()
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString PathName(szPath);
	//get exe list
	CString PROGRAM_PATH = PathName.Left(PathName.ReverseFind(_T('\\')) + 1);
	return PROGRAM_PATH;
}

void PathHandle::getFileNames(string path, vector<string>& files)
{
	intptr_t hFile = 0;
	//file information
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//if it is directory,find it recursively
			//if not, store the absolute path into vector
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}