#include"manger.h"

//默认构造
Manger::Manger()
{

}

//有参构造
Manger::Manger(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();

	//获取机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件未创建" << endl;
	}

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "当前机房数量为:" << vCom.size() << endl;

	ifs.close();

}


//菜单界面
void Manger::operMenu()
{
	cout << "欢迎管理员" << this->m_Name << "登录" << endl;
	cout << "\t\t----------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           1.添加账号           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           2.查看账号           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           3.查看机房           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           4.清空预约           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           0.注销登录           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|________________________________|\n";
	cout << "请输入您的选择 " << endl;

}

//添加账号
void Manger::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;

	string fileName; //操作的文件名
	string tip; //id号
	string errorTip; //错误提示

	ofstream ofs;
	
	int select = 0;
	cin >> select;
	if (select ==1) //学生
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号: ";
		errorTip = "学号重复请重新输入";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号: ";
		errorTip = "职工号重复请重新输入";

	}
	
	//利用追加方式写文件
	ofs.open(fileName, ios::out | ios::app);

	int id; //学号or职工号
	string name;
	string pwd;

	cout << tip << endl;
	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	
	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//像文件中添加数组
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");
	
	ofs.close();

	//调用容器初始化接口 实时更新
	this->initVector();
}

void myPrintStudent(Student &s)
{
	cout << "学号 " << s.m_Id << " 姓名" << s.m_Name << " 密码" << s.m_Pwd << endl;
}
void myPrintTeacher(Teacher& t)
{
	cout << "职工号 " << t.m_EmpId << " 姓名" << t.m_Name << " 密码" << t.m_Pwd << endl;
}
void myPrintComputer(ComputerRoom& c)
{
	cout << "机房号 " << c.m_ComId << "机房剩余位置" << c.m_MaxNum << endl; 
}
//查看账号
void Manger::showPerson()
{
	cout << "请选择查看的内容 " << endl;
	cout << "1.查看所有的学生 " << endl;
	cout << "2.查看所有的老师 " << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		//查看学生
		cout << "所有学生信息如下:" << endl;
		for_each(vStu.begin(), vStu.end(), myPrintStudent);
	}
	else
	{
		cout << "所有老师信息如下:" << endl;
		for_each(vTea.begin(), vTea.end(), myPrintTeacher);
	}

	system("pause");
	system("cls");
}

//查看机房信息
void Manger::showComputer()
{
	cout << "所有机房信息如下:" << endl;
	for_each(vCom.begin(), vCom.end(), myPrintComputer);
	system("pause");
	system("cls");
}

//清空预约记录
void Manger::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "清空成功" << endl;

	system("pause");
	system("cls");

}

//初始化容器
void Manger::initVector()
{
	vStu.clear();
	vTea.clear();
	//读取信息  学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	cout << "当前学生数量为 " << vStu.size() << endl;
	ifs.close();

	//读取 老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "当前学生数量为 " << vStu.size() << endl;
	ifs.close();

}

//检测重复
bool  Manger::checkRepeat(int id, int type)
{
	if (type==1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	
		return false;
}