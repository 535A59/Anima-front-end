#include"pch.h"
#include<iostream>
#include<Python.h>
#include <afxwin.h>

void main() {
    Py_Initialize(); /*初始化python解释器,告诉编译器要用的python编译器*/
    PyRun_SimpleString("import helloworld"); /*调用python文件*/
    PyRun_SimpleString("helloworld.printHello()");/*调用python文件中的函数*/
    Py_Finalize(); /*结束python解释器，释放资源*/
    system("pause");
}