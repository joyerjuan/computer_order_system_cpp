#include <iostream>
using namespace std;
#include "identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"

//登录功能,filename 文件名称，type 操作身份类型
void loginIn(string fileName,int type)
{
    //父类指针，用于指向子类对象
    Identity *person=NULL;
    //读文件
    ifstream ifs;
    ifs.open(fileName,ios::in);//ios::in(r),ios::out(w),ios::app(a),ios::binary(b)
    //判断文件是否存在
    if(!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        ifs.close();
        return;
    }

    //准备接受用户的信息
    int id=0;
    string name;
    string pwd;
    //判断身份
    if(type==1)//学生身份
    {
        cout<<"请输入你的学号："<<endl;
        cin>>id;
    }
    else if(type==2)
    {
        cout<<"请输入你的职工编号："<<endl;
        cin>>id;
    }

    cout<<"请输入用户名"<<endl;
    cin>>name;

    cout<<"请输入密码"<<endl;
    cin>>pwd;

    if(type==1)
    {
        //学生身份验证
        int fId;//从文件中读取的id号
        string fName;
        string fPwd;
        while(ifs>>fId && ifs>>fName && ifs>>fPwd)
        {
            //与用户输入的信息进行对比
            if(fId==id && fName==name && fPwd==pwd)
            {
                cout<<"学生验证登录成功！"<<endl;
                person=new Student(id,name,pwd);
                //进入学生身份的子菜单
                Student s;
                s.studentMenu(person);
                return;
                
            }

        }

    }
    else if(type==2)
    {
        //教师身份验证
        int fId;//从文件中读取的id号
        string fName;
        string fPwd;
        while(ifs>>fId && ifs>>fName && ifs>>fPwd)
        {
            //与用户输入的信息进行对比
            if(fId==id && fName==name && fPwd==pwd)
            {
                cout<<"教师验证登录成功！"<<endl;
                person=new Teacher(id,name,pwd);
                //进入教师身份的子菜单
                Teacher t;
                t.teacherMenu(person);
                return;
            }
        }

    }
    else if(type==3)
    {
        //管理员身份验证
        string fName;
        string fPwd;
        while(ifs>>fName && ifs>>fPwd)
        {
            //与用户输入的信息进行对比
            if(fName==name && fPwd==pwd)
            {
                cout<<"管理员验证登录成功！"<<endl;
                person=new Manager(name,pwd);
                //进入管理员身份的子菜单
                Manager m;
                m.managerMenu(person);
                return;
                
            }

        }
    }
    cout<<"验证登录失败"<<endl;
    getchar();
    return;
}

int main()
{
    int select=0;
    while (true)
    {
        cout << "===============欢迎来到机房预约系统=========" << endl;
        cout << endl;
        cout << "请输入您的身份" << endl;
        cout << "------------------------------------------" << endl;
        cout << "-------------  1.学生代表   ---------------" << endl;
        cout << "-------------  2.老师   -------------------" << endl;
        cout << "-------------  3.管理员   -----------------" << endl;
        cout << "-------------  0.退出   ------------------" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "请输入您的选择： ";

        cin >> select;
        switch (select)
        {
            case 1: //学生身份
                loginIn(STUDENT_FILE,1);
                break;
            case 2: //老师身份
                loginIn(TEACHER_FILE,2);
                break;
            case 3: //管理员
                loginIn(ADMIN_FILE,3);
                break;
            case 0: //退出
                cout<<"退出系统，欢迎下次使用"<<endl;
                return 0;
                break;
            default:
                cout << "输入有误，请重新选择！" << endl;
                break;
        }
    }

    getchar();
    return 0;
}