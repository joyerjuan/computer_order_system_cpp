#include "teacher.h"

Teacher::Teacher()
{
}

//有参构造
Teacher::Teacher(int id, string name, string pwd)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
}

//纯虚函数，显示教师操作的子菜单界面
void Teacher::operMenu()
{
    cout << "===============欢迎教师" << this->m_Name << "登录=========" << endl;
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "-------------  1.查看所有预约   ---------------" << endl;
    cout << "-------------  2.审核预约   -------------------" << endl;
    cout << "-------------  0.注销登录   ------------------" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "请输入您的选择： " << endl;
}

//查看所有预约
void Teacher::showAllOrder()
{

    OrderFile od;
    if (od.m_Size == 0)
    {
        cout << "无预约信息" << endl;
        return;
    }
    int index = 1;
    for (int i = 0; i < od.m_Size; i++)
    {
        cout << "index" << index++ << "、";
        cout << "预约日期 周" << od.m_orderData[i]["date"];
        cout << " 时段： " << (od.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 学号： " << od.m_orderData[i]["stuId"];
        cout << " 姓名： " << od.m_orderData[i]["stuName"];
        cout << " 机房： " << od.m_orderData[i]["roomId"];
        string status = " 状态： ";
        if (od.m_orderData[i]["status"] == "1")
            status += "审核中";
        else if (od.m_orderData[i]["status"] == "2")
            status += "预约成功";
        else if (od.m_orderData[i]["status"] == "3")
            status += "预约失败";
        else if (od.m_orderData[i]["status"] == "0")
            status += "取消成功";
        cout << status << endl;
    }
}

//审核预约
void Teacher::checkOrder()
{
    OrderFile od;
    if (od.m_Size == 0)
    {
        cout << "无预约信息" << endl;
        return;
    }
    cout << "待审核的预约记录如下" << endl;

    int index = 1;
    vector<int> v;

    for (int i = 0; i < od.m_Size; i++)
    {
        if (od.m_orderData[i]["status"] == "1")
        {
            v.push_back(i);
            cout << "index" << index++ << "、";
            cout << "预约日期 周" << od.m_orderData[i]["date"];
            cout << " 时段： " << (od.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 学号： " << od.m_orderData[i]["stuId"];
            cout << " 姓名： " << od.m_orderData[i]["stuName"];
            cout << " 机房： " << od.m_orderData[i]["roomId"];
            string status = " 状态： ";
            status += "审核中";
            cout << status << endl;
        }
    }

    cout << "请输入审核预约的index，0代表返回" << endl;

    int select = 0;
    while (true)
    {
        cin >> select;
        if (select > 0 && select <= v.size())
        {
            od.m_orderData[v[select - 1]]["status"] = "2";
            od.updateOrder(); //在文件中更新
            cout<<"审核成功"<<endl;
            break;
        }
        else if (select == 0)
        {
            cout << "退出审核操作成功" << endl;
            break;
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }
}

//析构函数
Teacher::~Teacher()
{
}

//进入管理员子菜单控制逻辑
void Teacher::teacherMenu(Identity *teach)
{
    while (true)
    {
        //调用管理员子菜单
        teach->operMenu();
        Teacher *tea = (Teacher *)teach;
        int select = 0;

        //接收用户的选择
        cin >> select;

        if (select == 1)
        {
            //查看所有预约
            tea->showAllOrder();
        }
        else if (select == 2)
        {
            //审核预约
            tea->checkOrder();
        }
        else
        {
            delete teach;
            cout << "注销成功！" << endl;
            return;
        }
    }
}