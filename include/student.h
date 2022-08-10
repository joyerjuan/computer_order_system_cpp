#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include <fstream>
#include <vector>
#include "computer.h"
#include "globalFile.h"
#include "orderFile.h"

class Student:public Identity
{
public:
    Student();
    //有参构造
    Student(int id,string name,string pwd);//学号，姓名，密码
    //子菜单操作界面
    virtual void operMenu();
    //申请预约
    void applyOrder();
    //查看我的预约
    void showMyOrder();
    //查看所有预约
    void showAllOrder();
    //取消预约
    void cancelOrder();
    //析构函数
    ~Student();

    //成员属性
    int m_Id;//学生学号
    vector<Computer> vCom;

    void studentMenu(Identity* manag);
    void initVector();

};