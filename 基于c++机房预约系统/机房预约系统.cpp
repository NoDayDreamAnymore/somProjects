#include<iostream>
using namespace std;
#include"Identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"student.h"
#include"manger.h"
#include"teacher.h"


//�������Ա�Ӳ˵�
void mangerMenu(Identity*& manger)
{
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manger->operMenu();

		//������ָ��תΪ����ָ�룬���Ե����������нӿ�
		Manger* man = (Manger*)manger;

		int select = 0;
		cin >> select;
		
		if (select ==1) //����˺�
		{
			cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) //�鿴�˺�
		{
			cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3) //�鿴����
		{
			cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if(select ==4) //���ԤԼ
		{
			cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else
		{
			delete manger; //���ٶ�������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		
	}
}

//����ѧ���Ӳ˵�
void studentMenu(Identity*& student)
{
	while (true)
	{
		//����ѧ���Ӳ˵�����
		student->operMenu();

		Student *stu = (Student *)student;

		int select = 0;
		cin >> select;
		 
		if (select ==1) //����ԤԼ
		{
			stu->applyOrder();
		}
		else if (select ==2) //�鿴����ԤԼ
		{
			stu->showMyOrder();
		}
		else if (select ==3) //�鿴������ԤԼ
		{
			stu->showAllOrder();
		}
		else if (select ==4) //ȡ��ԤԼ
		{
			stu->cancelOrder();
		}
		else
		{
			//ע����¼
			delete student;
			cout << "ע���ɹ�" << endl;
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
		//������ʦ�Ӳ˵�����
		tea->operMenu();

		Teacher *t = (Teacher*)tea;

		int select = 0;
		cin >> select;

		if (select == 1) //�鿴����ԤԼ
		{
			t->showAllOrder();
			
		}
		else if (select == 2) //���ԤԼ
		{
			t->validOrder();
		}

		else
		{
			//ע����¼
			delete tea;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��¼����
void LoginIn(string fileName, int type)
{
	//����ָ������ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(fileName, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼�������û���Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type ==1)  
	{
		cout << "���������ѧ�� " << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "���������ְ����" << endl;
		cin >> id;
	}

	cout << "�������û���:" << endl;
	cin >> name;

	cout << "����������:" << endl;
	cin >> pwd;

	if (type ==1)
	{
		//ѧ�������֤
		int fId; //���ļ��л�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd; //���ļ��л�ȡ����
		while (ifs >> fId &&ifs >> fName&& ifs>> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Student(id,name,pwd);
				studentMenu(person);

				return;

				//����ѧ���Ӳ˵�
			}
		}
	
	}
	else if (type == 2)
	{
		//��ʦ�����֤
		int fId; //���ļ��л�ȡ��id��
		string fName; //���ļ��л�ȡ������
		string fPwd; //���ļ��л�ȡ����
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//�����ʦ�Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա�����֤
		string fName; //���ļ��л�ȡ������
		string fPwd; //���ļ��л�ȡ����
		while (ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ���Ա�
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤��¼�ɹ���" << endl;
				system("pause");
				system("cls");
				person = new Manger(name, pwd);

				//�������Ա�˵�
				mangerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��½ʧ��!" << endl;
	system("pause");
	system("cls");
	return;
}

int main()
{
	int select = 0; //���ڽ����û���ѡ��
	while (true)
	{
		cout << "====================��ӭʹ�û���ԤԼϵͳ====================" << endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t----------------------------------\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           1.ѧ������           |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           2.��ʦ               |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           3.����Ա             |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|           0.�˳�               |\n";
		cout << "\t\t|                                |\n";
		cout << "\t\t|________________________________|\n";
		cout << "����������ѡ�� " << endl;

		cin >> select;
		
		switch (select)
		{
		case 1:	//ѧ��
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:	//��ʦ
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:	//����Ա
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:	//�˳�ϵͳ
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}




	system("pause");
	return 0;

}