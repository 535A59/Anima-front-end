#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <io.h>
#include <iomanip>
using namespace std;

#pragma once
class PathHandle
{
public:
	CString static FilePath();
	void static getFileNames(string path, vector<string>& files);
};

