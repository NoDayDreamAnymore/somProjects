#include"manger.h"

//Ĭ�Ϲ���
Manger::Manger()
{

}

//�вι���
Manger::Manger(string name, string pwd)
{
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();

	//��ȡ������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�δ����" << endl;
	}

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	cout << "��ǰ��������Ϊ:" << vCom.size() << endl;

	ifs.close();

}


//�˵�����
void Manger::operMenu()
{
	cout << "��ӭ����Ա" << this->m_Name << "��¼" << endl;
	cout << "\t\t----------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           1.����˺�           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           2.�鿴�˺�           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           3.�鿴����           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           4.���ԤԼ           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|           0.ע����¼           |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|________________________________|\n";
	cout << "����������ѡ�� " << endl;

}

//����˺�
void Manger::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1.���ѧ��" << endl;
	cout << "2.�����ʦ" << endl;

	string fileName; //�������ļ���
	string tip; //id��
	string errorTip; //������ʾ

	ofstream ofs;
	
	int select = 0;
	cin >> select;
	if (select ==1) //ѧ��
	{
		fileName = STUDENT_FILE;
		tip = "������ѧ��: ";
		errorTip = "ѧ���ظ�����������";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "������ְ�����: ";
		errorTip = "ְ�����ظ�����������";

	}
	
	//����׷�ӷ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);

	int id; //ѧ��orְ����
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
	
	cout << "������������" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");
	
	ofs.close();

	//����������ʼ���ӿ� ʵʱ����
	this->initVector();
}

void myPrintStudent(Student &s)
{
	cout << "ѧ�� " << s.m_Id << " ����" << s.m_Name << " ����" << s.m_Pwd << endl;
}
void myPrintTeacher(Teacher& t)
{
	cout << "ְ���� " << t.m_EmpId << " ����" << t.m_Name << " ����" << t.m_Pwd << endl;
}
void myPrintComputer(ComputerRoom& c)
{
	cout << "������ " << c.m_ComId << "����ʣ��λ��" << c.m_MaxNum << endl; 
}
//�鿴�˺�
void Manger::showPerson()
{
	cout << "��ѡ��鿴������ " << endl;
	cout << "1.�鿴���е�ѧ�� " << endl;
	cout << "2.�鿴���е���ʦ " << endl;

	int select = 0;
	cin >> select;

	if (select==1)
	{
		//�鿴ѧ��
		cout << "����ѧ����Ϣ����:" << endl;
		for_each(vStu.begin(), vStu.end(), myPrintStudent);
	}
	else
	{
		cout << "������ʦ��Ϣ����:" << endl;
		for_each(vTea.begin(), vTea.end(), myPrintTeacher);
	}

	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manger::showComputer()
{
	cout << "���л�����Ϣ����:" << endl;
	for_each(vCom.begin(), vCom.end(), myPrintComputer);
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manger::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();
	cout << "��ճɹ�" << endl;

	system("pause");
	system("cls");

}

//��ʼ������
void Manger::initVector()
{
	vStu.clear();
	vTea.clear();
	//��ȡ��Ϣ  ѧ��
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}

	cout << "��ǰѧ������Ϊ " << vStu.size() << endl;
	ifs.close();

	//��ȡ ��ʦ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}

	cout << "��ǰѧ������Ϊ " << vStu.size() << endl;
	ifs.close();

}

//����ظ�
bool  Manger::checkRepeat(int id, int type)
{
	if (type==1)
	{
		//���ѧ��
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
		//�����ʦ
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