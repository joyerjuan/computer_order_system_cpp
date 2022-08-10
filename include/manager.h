#pragma once
#include <iostream>
using namespace std;
#include "identity.h"
#include <string>
#include <fstream>
#include "globalFile.h"
#include <vector>
#include "student.h"
#include "teacher.h"
#include "computer.h"
#include <algorithm>


class Manager:public Identity
{
public:
    //构造函数
    Manager();
    //有参构造
    Manager(string name,string pwd);
    //纯虚函数，显示管理员操作的子菜单界面
    virtual void operMenu();
    //添加账号
    void addPerson();
    //查看账号
    void showPerson();
    //查看机房信息
    void showCpRoom();
    //清空预约记录
    void clearOdFile();
    //析构函数
    ~Manager();

    //学生容器
    vector<Student> vStu;
    //老师容器
    vector<Teacher> vTea;
    //机房容器
    vector<Computer> vComp;
    //容器初始化
    void initVector();
    //检查重复
    bool checkRepeat(int id,int type);
    void managerMenu(Identity* manager);

};

