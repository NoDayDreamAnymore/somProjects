#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"student.h"
#include"manger.h"
#include"teacher.h"


//进入管理员子菜单
void mangerMenu(Identity*& manger)
{
	while (true)
	{
		//调用管理员子菜单
		manger->operMenu();

		//将父类指针转为子类指针，可以调用子类特有接口
		Manger* man = (Manger*)manger;

		int select = 0;
		cin >> select;
		
		if (select ==1) //添加账号
		{
			cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			cout << "查看机房" << endl;
			man->showComputer();
		}
		else if(select ==4) //清空预约
		{
			cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{
			delete manger; //销毁堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		
	}
}

//进入学生子菜单
void studentMenu(Identity*& student)
{
	while (true)
	{
		//调用学生子菜单界面
		student->operMenu();

		Student *stu = (Student *)student;

		int select = 0;
		cin >> select;
		 
		if (select ==1) //申请预约
		{
			stu->applyOrder();
		}
		else if (select ==2) //查看自身预约
		{
			stu->showMyOrder();
		}
		else if (select ==3) //查看所有人预约
		{
			stu->showAllOrder();
		}
		else if (select ==4) //取消预约
		{
			stu->cancelOrder();
		}
		else
		{
			//注销登录
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void teacherMenu(Identity*& tea)
{
	while (true)
	{
		//调用老师子菜单界面
		tea->operMenu();

		Teacher *t = (Teacher*)tea;

		int select = 0;
		cin >> select;

		if (select == 1) //查看所有预约
		{
			t->showAllOrder();
			
		}
		else if (select == 2) //审核预约
		{
			t->validOrder();
		}

		else
		{
			//注销登录
			delete tea;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录功能
void LoginIn(string fileName, int type)
{
	//父类指针用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备接收用户信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type ==1)  
	{
		cout << "请输入你的学号 " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}

	cout << "请输入用户名:" << endl;
	cin >> name;

	cout << "请输入密码:" << endl;
	cin >> pwd;

	if (type ==1)
	{
		//学生身份验证
		int fId; //从文件中获取的id号
		string fName; //从文件中获取的名字
		string fPwd; //从文件中获取密码
		while (ifs >> fId &&ifs >> fName&& ifs>> fPwd)
		{
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,pwd);
				studentMenu(person);

				return;

				//进入学生子菜单
			}
		}
	
	}
	else if (type == 2)
	{
		//教师身份验证
		int fId; //从文件中获取的id号
		string fName; //从文件中获取的名字
		string fPwd; //从文件中获取密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "教师验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//进入教师子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份验证
		string fName; //从文件中获取的名字
		string fPwd; //从文件中获取密码
		while (ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息做对比
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证登录成功！" << endl;
				system("pause");
				system("cls");
				person = new Manger(name, pwd);

				//进入管理员菜单
				mangerMenu(person);
				return;
			}
		}
	}

	cout << "验证登陆失败!" << endl;
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0; //用于接收用户的选择
	while (true)
	{
		cout << "====================欢迎使用机房预约系统====================" << endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t----------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           1.学生代表           |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           2.老师               |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           3.管理员             |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           0.退出               |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|________________________________|\n";
		cout << "请输入您的选择 " << endl;

		cin >> select;
		
		switch (select)
		{
		case 1:	//学生
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:	//老师
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:	//管理员
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:	//退出系统
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}




	system("pause");
	return 0;

}