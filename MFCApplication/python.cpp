#include"pch.h"
#include<iostream>
#include<Python.h>
#include <afxwin.h>

void main() {
    Py_Initialize(); /*��ʼ��python������,���߱�����Ҫ�õ�python������*/
    PyRun_SimpleString("import helloworld"); /*����python�ļ�*/
    PyRun_SimpleString("helloworld.printHello()");/*����python�ļ��еĺ���*/
    Py_Finalize(); /*����python���������ͷ���Դ*/
    system("pause");
}