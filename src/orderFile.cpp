#include "orderFile.h"

OrderFile::OrderFile()
{
    ifstream ifs;
    ifs.open(ORDER_FILE, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }
    //date:2 interval:2 stuId:1 stuName:张三 roomId:3 status:1
    string date;
    string interval;
    string stuId;
    string stuName;
    string roomId;
    string status;

    this->m_Size = 0; //初始化记录条数为0
    this->m_orderData.clear();

    while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
    {
        map<string, string> tmp;
        int pos;
        //1
        pos = date.find(":");
        if (pos!=-1)
        {
            string date_key = date.substr(0, pos);
            // cout << "date_key:" << date_key << endl;
            string date_value = date.substr(pos + 1, date.size() - pos - 1);
            // cout << "date_value:" << date_value << endl;
            tmp.insert(make_pair(date_key, date_value));
        }

        //2
        pos = interval.find(":");
        if (pos!=-1)
        {
            string interval_key = interval.substr(0, pos);
            string interval_value = interval.substr(pos + 1, interval.size() - pos - 1);
            tmp.insert(make_pair(interval_key, interval_value));
        }

        //3
        int pos_stuId = -1;
        pos_stuId = stuId.find(":");
        if (pos_stuId)
        {
            string stuId_key = stuId.substr(0, pos_stuId);
            string stuId_value = stuId.substr(pos_stuId + 1, stuId.size() - pos_stuId - 1);
            tmp.insert(make_pair(stuId_key, stuId_value));
        }

        //4
        int pos_stuName = -1;
        pos_stuName = stuName.find(":");
        if (pos_stuName)
        {
            string stuName_key = stuName.substr(0, pos_stuName);
            string stuName_value = stuName.substr(pos_stuName + 1, stuName.size() - pos_stuName - 1);
            tmp.insert(make_pair(stuName_key, stuName_value));
        }

        //5
        int pos_roomId = -1;
        pos_roomId = roomId.find(":");
        if (pos_roomId)
        {
            string roomId_key = roomId.substr(0, pos_roomId);
            string roomId_value = roomId.substr(pos_roomId + 1, roomId.size() - pos_roomId - 1);
            tmp.insert(make_pair(roomId_key, roomId_value));
        }

        //6
        int pos_status = -1;
        pos_status = status.find(":");
        if (pos_status)
        {
            string status_key = status.substr(0, pos_status);
            string status_value = status.substr(pos_status + 1, status.size() - pos_status - 1);
            tmp.insert(make_pair(status_key, status_value));
        }
        this->m_orderData.insert(make_pair(this->m_Size,tmp));
        this->m_Size++;
    }
    ifs.close();
    
}

void OrderFile::updateOrder()
{
    if(this->m_Size==0)
    {
        return;
    }
    ofstream ofs;
    ofs.open(ORDER_FILE,ios::out |ios::trunc);
    for(int i=0;i<this->m_Size;i++)
    {
        // cout<<"更新预约文件"<<endl;
        ofs<<"date:"<<this->m_orderData[i]["date"]<<" "
        <<"interval:"<<this->m_orderData[i]["interval"]<<" "
        <<"stuId:"<<this->m_orderData[i]["stuId"]<<" "
        <<"stuName:"<<this->m_orderData[i]["stuName"]<<" "
        <<"roomId:"<<this->m_orderData[i]["roomId"]<<" "
        <<"status:"<<this->m_orderData[i]["status"]<<endl;
    }

    ofs.close();
}