#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include "orderFile.h"
#include <vector>

class Teacher:public Identity
{
public:
    //默认构造
    Teacher();

    //有参构造
    Teacher(int id,string name,string pwd);

    //纯虚函数，显示教师操作的子菜单界面
    virtual void operMenu();

    //查看所有预约
    void showAllOrder();

    //审核预约
    void checkOrder();

    //析构函数
    ~Teacher();


    //成员属性
    int m_Id;

    void teacherMenu(Identity *teach);
};