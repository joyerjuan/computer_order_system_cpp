#pragma once
#include <iostream>
using namespace std;
#include <map>
#include <fstream>
#include "globalFile.h"

class OrderFile
{
public:
    OrderFile();

    //更新预约记录
    void updateOrder();
    
    //成员属性
    //记录的容器
    map<int,map<string,string>> m_orderData;
    //容器大小
    int m_Size;
};