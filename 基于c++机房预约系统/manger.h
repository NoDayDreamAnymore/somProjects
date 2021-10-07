#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include"teacher.h"
#include"student.h"
#include<vector>
#include<algorithm>
#include"computerroom.h"


class Manger :public Identity
{
public:

	//默认构造
	Manger();

	//有参构造
	Manger(string name, string pwd);

	//菜单界面
	virtual void operMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();
	
	//查看机房信息
	void showComputer();
	
	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复
	bool checkRepeat(int id, int type);
	
	//学生容器
	vector<Student>vStu;

	//老师容器
	vector<Teacher>vTea;

	//机房容器
	vector<ComputerRoom>vCom;
};
