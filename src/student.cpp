#include "student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
    //初始化学生属性
    this->m_Id = id;
    this->m_Name = name;
    this->m_Pwd = pwd;
    this->initVector();
}

//子菜单操作界面
void Student::operMenu()
{
    cout << "===============欢迎学生" << this->m_Name << "登录=========" << endl;
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "-------------  1.申请预约   ---------------" << endl;
    cout << "-------------  2.查看我的预约   -------------------" << endl;
    cout << "-------------  3.查看所有预约  -----------------" << endl;
    cout << "-------------  4.取消预约  -----------------" << endl;
    cout << "-------------  0.注销登录   ------------------" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "请输入您的选择： " << endl;
}

//申请预约
void Student::applyOrder()
{
    cout << "请选择申请日期:" << endl;
    cout << "1 周一" << endl;
    cout << "2 周二" << endl;
    cout << "3 周三" << endl;
    cout << "4 周四" << endl;
    cout << "5 周五" << endl;
    int date = 0;

    while (true)
    {
        cin >> date;
        if (date < 1 || date > 5)
        {
            cout << "输入错误，请重新选择" << endl;
        }
        else
        {
            break;
        }
    }

    cout << "请选择时间段:" << endl;
    cout << "1 上午" << endl;
    cout << "2 下午" << endl;

    int interval = 0;
    while (true)
    {
        cin >> interval;
        if (interval < 1 || interval > 2)
        {
            cout << "输入错误，请重新选择" << endl;
        }
        else
        {
            break;
        }
    }
    cout << "请选择机房:" << endl;
    //显示机房信息
    cout << "1 机房1---"
         << " 机房容量: " << vCom[0].m_MaxNum << endl;
    cout << "2 机房2---"
         << " 机房容量: " << vCom[1].m_MaxNum << endl;
    cout << "3 机房3---"
         << " 机房容量: " << vCom[2].m_MaxNum << endl;
    int roomId = 0;
    while (true)
    {
        cin >> roomId;
        if (roomId < 1 || roomId > 3)
        {
            cout << "输入错误，请重新选择" << endl;
        }
        else
        {
            break;
        }
    }

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::out | ios::app);
    ofs << "date:" << date << " "
        << "interval:" << interval << " "
        << "stuId:" << this->m_Id << " "
        << "stuName:" << this->m_Name << " "
        << "roomId:" << roomId << " "
        << "status:"
        << "1" << endl;
    ofs.close();
    // OrderFile odd;
    // odd.updateOrder();
    cout << "预约成功，审核中！" << endl;
}

//map<string,string>
// map<int,map<string,string>>
//vector v1;
//v1.push_back(make_pair(string,string))
//vector.push_back(v)
//vector<make_pair(string,string)>

//查看我的预约
void Student::showMyOrder()
{
    OrderFile od;
    if (od.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    cout << "orderNum:" << od.m_Size << endl;
    cout << "od.m_orderData:" << od.m_orderData.size() << endl;

    for (int i = 0; i < od.m_Size; i++)
    {
        if (atoi(od.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            cout << "预约日期 周" << od.m_orderData[i]["date"];
            cout << " 时段： " << (od.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 机房： " << od.m_orderData[i]["roomId"];
            string status = " 状态： "; //取消的预约（0），审核中(1)，预约成功（2),预约失败（3）
            if (od.m_orderData[i]["status"] == "1")
                status += "审核中";
            else if (od.m_orderData[i]["status"] == "2")
                status += "预约成功";
            else if (od.m_orderData[i]["status"] == "3")
                status += "预约失败";
            else if (od.m_orderData[i]["status"] == "0")
                status += "取消的预约";
            cout << status << endl;
        }
    }
}

//查看所有预约
void Student::showAllOrder()
{
    OrderFile od;
    if (od.m_Size == 0)
    {
        cout << "无预约记录" << endl;
        return;
    }
    cout << "orderNum:" << od.m_Size << endl;
    cout << "od.m_orderData:" << od.m_orderData.size() << endl;

    for (int i = 0; i < od.m_Size; i++)
    {

        cout << "预约日期 周" << od.m_orderData[i]["date"];
        cout << " 时段： " << (od.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 学号： " << od.m_orderData[i]["stuId"];
        cout << " 姓名： " << od.m_orderData[i]["stuName"];
        cout << " 机房： " << od.m_orderData[i]["roomId"];
        string status = " 状态： "; //取消的预约（0），审核中(1)，预约成功（2),预约失败（3）
        if (od.m_orderData[i]["status"] == "1")
            status += "审核中";
        else if (od.m_orderData[i]["status"] == "2")
            status += "预约成功";
        else if (od.m_orderData[i]["status"] == "3")
            status += "预约失败";
        else if (od.m_orderData[i]["status"] == "0")
            status += "取消的预约";
        cout << status << endl;
    }
}

//取消预约
void Student::cancelOrder()
{

    OrderFile od;
    if (od.m_Size == 0)
    {
        cout << "无预约信息" << endl;
        return;
    }
    cout << "审核中和预约成功的记录可以取消，请输入取消的记录" << endl;

    int index = 1;
    vector<int> v;

    for (int i = 0; i < od.m_Size; i++)
    {
        if (atoi(od.m_orderData[i]["stuId"].c_str()) == this->m_Id)
        {
            if (od.m_orderData[i]["status"] == "1" || od.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
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
                cout << status << endl;
            }
        }
    }
    cout << "请输入取消预约的index，0代表返回" << endl;

    int select = 0;
    while (true)
    {
        cin >> select;
        if (select > 0 && select <= v.size())
        {
            od.m_orderData[v[select - 1]]["status"] = "0";
            od.updateOrder(); //在文件中更新
            cout<<"取消预约成功"<<endl;
            break;
        }
        else if (select == 0)
        {
            cout << "取消预约操作成功" << endl;
            break;
        }
        else
        {
            cout << "输入有误，请重新输入" << endl;
        }
    }
}

//析构函数
Student::~Student()
{
}

//进入管理员子菜单控制逻辑
void Student::studentMenu(Identity *studen)
{
    while (true)
    {
        //调用管理员子菜单
        studen->operMenu();
        Student *stu = (Student *)studen;
        int select = 0;

        //接收用户的选择
        cin >> select;

        if (select == 1)
        {
            //申请预约
            stu->applyOrder();
        }
        else if (select == 2)
        {
            //查看我的预约
            stu->showMyOrder();
        }
        else if (select == 3)
        {
            //查看所有预约
            stu->showAllOrder();
        }
        else if (select == 4)
        {
            //取消预约
            stu->cancelOrder();
        }
        else
        {
            delete studen;
            cout << "注销成功！" << endl;
            return;
        }
    }
}

void Student::initVector()
{
    ifstream ifs;
    vCom.clear();
    ifs.open(CPROOM_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "打开失败" << endl;
        return;
    }

    Computer com;
    while (ifs >> com.m_RoomId && ifs >> com.m_MaxNum)
    {
        vCom.push_back(com);
    }
    cout << "当前机房数量为：" << vCom.size() << endl;
    ifs.close();
}