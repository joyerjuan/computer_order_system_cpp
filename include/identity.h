#pragma once
#include <iostream>
using namespace std;

//身份抽象基类
class Identity
{
public:
    //操作子菜单，纯虚函数,抽象类，无法实例化，子类必须重写纯虚函数
    virtual void operMenu()=0;
    //用户名
    string m_Name;
    //密码
    string m_Pwd;
};
