#include"orderfile.h"

//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string data;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	this->m_Size = 0;

	while (ifs >> data && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		//cout << data << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;
		//cout << endl;


		string key;
		string value;
		map<string, string>m;

		int pos = data.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = data.substr(0, pos);
			value = data.substr(pos + 1, data.size() - pos - 1);

			m.insert(make_pair(key, value));
		}

		pos = interval.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		
		pos = stuId.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);

			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);

			m.insert(make_pair(key, value));
		}		
		
		pos = roomId.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);

			m.insert(make_pair(key, value));
		}		
		
		pos = status.find(":");  //寻找：没找到返回-1
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);

			m.insert(make_pair(key, value));
		}

		this->m_orderData.insert(make_pair(this->m_Size, m));

		//for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
		//{
		//	cout << "条数为" << it->first << "value=" << endl;
		//	for (map<string, string>::iterator mit = (*it).second.begin(); mit != (*it).second.end(); mit++)
		//	{
		//		cout << "key=" << mit->first << " value =" << mit->second << " ";
		//	}
		//	cout << endl;
		//}
		m_Size++;
	}

	ifs.close();
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (size_t i = 0; i < this->m_Size; i++)
	{
		ofs << "data:" << this->m_orderData[i]["data"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << " ";

	}
	ofs.close();
}