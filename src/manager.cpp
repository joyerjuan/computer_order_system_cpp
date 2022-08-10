#include "manager.h"

//构造函数
Manager::Manager()
{

}
//有参构造
Manager::Manager(string name,string pwd)
{
    //初始化管理员信息
    this->m_Name=name;
    this->m_Pwd=pwd;
    this->initVector();
}
//纯虚函数，显示管理员操作的子菜单界面
void Manager::operMenu()
{
    cout << "===============欢迎管理员"<<this->m_Name<<"登录=========" << endl;
    cout << endl;
    cout << "------------------------------------------" << endl;
    cout << "-------------  1.添加账号   ---------------" << endl;
    cout << "-------------  2.查看账号   -------------------" << endl;
    cout << "-------------  3.查看机房  -----------------" << endl;
    cout << "-------------  4.清空预约  -----------------" << endl;
    cout << "-------------  0.注销登录   ------------------" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "请输入您的选择： "<<endl;
}
//添加账号
void Manager::addPerson()
{
    cout<<"请输入添加账号的类型"<<endl;
    cout<<"1 添加学生"<<endl;
    cout<<"2 添加老师"<<endl;
    int select=0;
    
    string filename;
    while(true){
        cin >>select;
        if(select==1)
        {
            cout<<"请输入学号:"<<endl;
            filename=STUDENT_FILE;
            break;
        }
        else if(select==2)
        {
            cout<<"请输入职工编号:"<<endl;
            filename=TEACHER_FILE;
            break;
        }
        else
        {
            cout<<"输入有误，请重新输入"<<endl;
        }
    }
    int id;
    string name;
    string pwd;
    while (true)
    {
        cin>>id;
        if(this->checkRepeat(id,select))
        {
            cout<<"id重复，请重新输入"<<endl;
        }  
        else
        {
            break;
        }
    }


    cout<<"请输入姓名"<<endl;
    cin>>name;
    cout<<"请输入密码"<<endl;
    cin>>pwd;

    ofstream ofs;

    ofs.open(filename,ios::out|ios::app);
    ofs<<id<<" "<<name<<" "<<pwd<<endl;
    ofs.close();
    this->initVector();
    cout<<"账户添加成功"<<endl;


}

void printStu(Student s)
{
    cout<<"学号: "<<s.m_Id<<" 姓名： "<<s.m_Name<<" 密码： "<<s.m_Pwd<<endl;
}

void printTea(Teacher t)
{
    cout<<"职工号: "<<t.m_Id<<" 姓名： "<<t.m_Name<<" 密码： "<<t.m_Pwd<<endl;
}

//查看账号
void Manager::showPerson()
{
    cout<<"请选择查看内容"<<endl;
    cout<<"1 查看所有学生"<<endl;
    cout<<"2 查看所有老师"<<endl;
    int select=0;
    cin>>select;
    if(select==1)
    {
        for_each(vStu.begin(),vStu.end(),printStu);
    }
    else
    {
        for_each(vTea.begin(),vTea.end(),printTea);
    }
}
//查看机房信息
void Manager::showCpRoom()
{
    ifstream ifs;
    ifs.open(CPROOM_FILE,ios::in);
    if(!ifs.is_open()){
        cout<<"打开失败"<<endl;
        return;
    }
    int roomId;
    int num;
    while(ifs>>roomId && ifs>>num){
        cout<<"机房： "<<roomId<<" 容量： "<<num<<"人"<<endl;
    }
}
//清空预约记录
void Manager::clearOdFile()
{
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::trunc);
    ofs.close();
    cout<<"清空成功"<<endl;

}
//析构函数
Manager::~Manager()
{

}

//初始化容器
void Manager::initVector()
{
    ifstream ifs;

    vStu.clear();
    ifs.open(STUDENT_FILE,ios::in);
    if(!ifs.is_open()){
        cout<<"打开失败"<<endl;
        return;
    }

    Student std;
    while(ifs>>std.m_Id&&ifs>>std.m_Name&&ifs>>std.m_Pwd)
    {
        vStu.push_back(std);
    }
    ifs.close();
    cout<<"当前学生数量为："<<vStu.size()<<endl;


    vTea.clear();
    ifs.open(TEACHER_FILE,ios::in);
    if(!ifs.is_open()){
        cout<<"打开失败"<<endl;
        return;
    }
    Teacher tea;
    while(ifs>>tea.m_Id&&ifs>>tea.m_Name&&ifs>>tea.m_Pwd)
    {
        vTea.push_back(tea);
    }
    cout<<"当前老师数量为："<<vTea.size()<<endl;
    ifs.close();


    vComp.clear();
    ifs.open(CPROOM_FILE,ios::in);
    if(!ifs.is_open()){
        cout<<"打开失败"<<endl;
        return;
    }

    Computer com;
    while(ifs>>com.m_RoomId&&ifs>>com.m_RoomId)
    {
        vComp.push_back(com);
    }
    cout<<"当前机房数量为："<<vComp.size()<<endl;
    ifs.close();

}

//进入管理员子菜单控制逻辑
void Manager::managerMenu(Identity* manag)
{
    while(true)
    {
        //调用管理员子菜单
        manag->operMenu();
        Manager* man=(Manager*)manag;
        int select=0;

        //接收用户的选择
        cin>>select;

        if(select==1)
        {
            //添加账号
            man->addPerson();
        }
        else if(select==2)
        {
            //查看账号
            man->showPerson();

        }
        else if(select==3)
        {
            //查看机房信息
            man->showCpRoom();

        }
        else if(select==4)
        {
            //清空预约
            man->clearOdFile();

        }
        else
        {
            delete manag;
            cout<<"注销成功！"<<endl;
            return;
        }
    }

}

bool Manager::checkRepeat(int id,int type)
{
    if(type==1)
    {
        for(vector<Student>::iterator it=vStu.begin();it!=vStu.end();it++)
        {
            if(id==it->m_Id){
                return true;
            }
        }
    }
    else
    {
        for(vector<Teacher>::iterator it=vTea.begin();it!=vTea.end();it++)
        {
            if(id==it->m_Id){
                return true;
            }
        }
    }
    return false;
}