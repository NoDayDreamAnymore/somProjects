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

	//Ĭ�Ϲ���
	Manger();

	//�вι���
	Manger(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();
	
	//�鿴������Ϣ
	void showComputer();
	
	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ�
	bool checkRepeat(int id, int type);
	
	//ѧ������
	vector<Student>vStu;

	//��ʦ����
	vector<Teacher>vTea;

	//��������
	vector<ComputerRoom>vCom;
};
