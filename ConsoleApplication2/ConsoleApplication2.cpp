#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Worker
{
	string name;
	string surname;
	string lastname;
	int number;
	string department;
	string position;
	int salary;

public:
	Worker() :name(""), surname(""), lastname(""), number(0), department(""), position(""), salary(0)
	{}
	Worker(string name, string surname, string lastname, int number, string department, string position, int salary)
		: name(name), surname(surname), lastname(lastname), number(number), department(department), position(position), salary(salary)
	{}

	void Show() const
	{
		cout << "Name: " << name << endl;
		cout << "Surname: " << surname << endl;
		cout << "Lastname: " << lastname << endl;
		cout << "Number: " << number << endl;
		cout << "Department: " << department << endl;
		cout << "Position: " << position << endl;
		cout << "Salary: " << salary << endl;
		cout << endl;
	}

	int GetNumber() const
	{
		return number;
	}

	string GetName() const
	{
		return name;
	}

	string GetSurname() const
	{
		return surname;
	}
	string GetLastname() const
	{
		return lastname;
	}
	string GetDepart()const
	{
		return department;
	}
	void SetDepart(string depart)
	{
		if (!depart.empty())
		{
			department = depart;
		}
	}
	string GetPosition() const
	{
		return position;
	}
	int GetSalary() const
	{
		return salary;
	}

	bool operator<(const Worker& other) const //��� ������������� �� ������
	{
		/*if (_stricmp(department.c_str(), other.department.c_str()) < 0)*/
		if (department < other.department)
		{
			return true;
		}
		return false;
	}

};

class ConnectDatabase
{
	string source;
public:
	ConnectDatabase() : source("")
	{}
	ConnectDatabase(string source) : source(source)
	{}

	void Read(vector<Worker>& workers)
	{
		string name;
		string surname;
		string lastname;
		int number;
		string department;
		string position;
		int salary;

		ifstream file(source);
		if (file.is_open())
		{
			int size;
			file >> size;
			for (int i = 0; i < size; i++)
			{
				file >> name >> surname >> lastname >> number >> department >> position >> salary;
				Worker newWorker(name, surname, lastname, number, department, position, salary);
				workers.push_back(newWorker);
			}
		}
		file.close();
	}

	void Write(const vector<Worker>& workers) const
	{
		ofstream of(source);
		if (of.is_open())
		{
			of << workers.size() << endl;
			for (auto& item : workers)
			{
				of << item.GetName() << " ";
				of << item.GetSurname() << " ";
				of << item.GetLastname() << " ";
				of << item.GetNumber() << " ";
				of << item.GetDepart() << " ";
				of << item.GetPosition() << " ";
				of << item.GetSalary() << endl;
			}
			of.close();
		}
	}

	void ChangeSource(string src)
	{
		source = src;
	}
};



class Company
{
	vector<Worker> workers;
	ConnectDatabase* db;
	vector<string> allDepart;

	bool UniquenessCheckNumber(int number)
	{
		for (auto& item : workers)
		{
			if (item.GetNumber() == number)
			{
				return false;
			}
		}
		return true;
	}
	bool FoundDepart(string depart) const
	{
		for (auto& elem : allDepart)
		{
			if (elem == depart)
			{
				return true;
			}
		}
		return false;
	}
	void FoundAllDepart()
	{
		allDepart.clear();
		allDepart.push_back(workers[0].GetDepart());
		for (auto& item : workers)
		{
			if (!FoundDepart(item.GetDepart()))
			{
				allDepart.push_back(item.GetDepart());
			}
		}
	}

	void PrintWorkerFromDepart()
	{
		for (auto& item : allDepart)
		{
			for (auto& elem : workers)
			{
				if (item == elem.GetDepart())
				{
					cout << "²�Ĳ� " << elem.GetDepart() << endl << endl;
					elem.Show();
				}
			}
		}
	}
	void TotalMoneyByCompany()
	{
		int totalMoney = 0;
		for (auto& item : workers)
		{
			totalMoney += item.GetSalary();
		}
		cout << "��������� ���� �� ���� ���������: ";
		cout << totalMoney << endl << endl;
	}

public:
	Company() : db(nullptr)
	{}
	Company(string source) : db(new ConnectDatabase(source))
	{}

	void FillDatabase(int size)
	{
		workers.clear();
		allDepart.clear();
		for (size_t i = 0; i < size; i++)
		{
			AddWorker();
		}
	}

	void AddWorker()
	{
		bool check = true;
		string name;
		string surname;
		string lastname;
		int number;
		string department;
		string position;
		int salary;

		while (check)
		{
			check = false;
			cout << "������ ϲ� (����� �����):" << endl;
			cin >> name;
			cin >> surname;
			cin >> lastname;
			if (name.empty() || surname.empty() || lastname.empty())
			{
				cout << "������ �������� ���!" << endl;
				check = true;
			}
			int num;
			while (true)
			{
				cout << "������ ��������� �����: ";
				cin >> num;
				if (UniquenessCheckNumber(num))
				{
					number = num;
					break;
				}
				else
				{
					cout << "��� ��������� ����� �� � ���������!\a" << endl;
				}
			}
			cout << "������ ����: ";
			cin >> department;
			cout << "������ ������: ";
			cin >> position;
			cout << "������ ��������: ";
			cin >> salary;
			Worker newWorker(name, surname, lastname, number, department, position, salary);
			workers.push_back(newWorker);
		}
	}

	void ShowAll() const
	{
		for (auto& item : workers)
		{
			item.Show();
		}
	}

	void DeleteWorker()
	{
		cout << "������ ��������� ����� ����������: ";
		int num;
		cin >> num;
		for (size_t i = 0; i < workers.size(); i++)
		{
			if (workers[i].GetNumber() == num)
			{
				workers.erase(workers.begin() + i); // workers.begin() + i
				break;
			}
		}
	}

	void SortByDepart()
	{
		sort(workers.begin(), workers.end());
	}

	void FoundWorkerByNSL() const
	{
		cout << "������ ϲ� ����������� ������: ";
		string name;
		string surname;
		string lastname;
		cin >> name >> surname >> lastname;
		for (auto& item : workers)
		{
			/*if (_stricmp(name, item.) == 0 && _stricmp(surname, mySurname) == 0 && _stricmp(lastname, myLastname) == 0)*/
			if (name == item.GetName() && surname == item.GetSurname() && lastname == item.GetLastname())
			{
				item.Show();
				return;
			}
		}
		cout << "�� ��������!" << endl;
		cout << endl << endl;
	}

	void FoundWorkedByDepart() const
	{
		bool flag = false;
		cout << "������ ���� ��� ��������� ���������� ��� �����������: ";
		string depart;
		cin >> depart;
		for (auto& item : workers)
		{
			if (depart == item.GetDepart())
			{
				item.Show();
				flag = true;
			}
		}
		if (!flag)
		{
			cout << "�� ��������!" << endl;
			cout << endl << endl;
		}
	}

	void AmountWorkerInDepart() const
	{
		cout << "������ ���� ��� ���������� ������� �����������: ";
		string depart;
		cin >> depart;
		int count = 0;
		for (auto& item : workers)
		{
			if (depart == item.GetDepart())
			{
				count++;
			}
		}
		if (count == 0)
		{
			cout << "�� ��������!" << endl;
		}
		else
		{
			cout << "� ���� " << depart << " " << count << " ����������" << endl;
		}
		cout << endl << endl;
	}

	void TotalMoneyByDepart()
	{
		struct TotalMoney
		{
			string depart;
			int money;
			TotalMoney(string depart) : depart(depart)
			{
				money = 0;
			}
			void Show()
			{
				cout << "³��� " << depart << endl;
				cout << "���� �/�: " << money << endl;
				cout << endl;
			}
		};
		vector<TotalMoney> money;
		FoundAllDepart();
		for (auto& item : allDepart)
		{
			money.push_back(TotalMoney(item));
		}
		for (auto& item : money)
		{
			for (auto& elem : workers)
			{
				if (item.depart == elem.GetDepart())
				{
					item.money += elem.GetSalary();
				}
			}
			item.Show();
		}
	}

	void ReplaceDepart()
	{
		cout << "������ ��������� ����� ����������� ��� ����������� � ����� ����: ";
		int num;
		int index = -1;
		cin >> num;
		for (size_t i = 0; i < workers.size(); i++)
		{
			if (workers[i].GetNumber() == num)
			{
				index = i;
				break;
			}
		}
		if (index >= 0)
		{
			cout << "������ ����� ����� � ���� ������ ��������� ����������:" << endl;
			string depart;
			cin >> depart;
			workers[index].SetDepart(depart);
		}
		else
		{
			cout << "�� ��������!" << endl;
		}
	}
	void PrintTable()
	{
		FoundAllDepart();
		PrintWorkerFromDepart();
		TotalMoneyByDepart();
		TotalMoneyByCompany();
	}
	void Read()
	{
		db->Read(workers);
	}
	void Write() const
	{
		db->Write(workers);
	}

	~Company()
	{
		workers.clear();
		delete db;
	}
};

class Menu
{
	void PrintMenu()
	{
		int g = 0;
		cout << ++g << " - ���������� ���� �����" << endl;
		cout << ++g << " - �������� ����� ��� ��� �����������" << endl; //done(�������), ��� ���������� ��� ����������(�� ���)
		cout << ++g << " - ���������� ���� ����� ����� ������������" << endl; //done
		cout << ++g << " - ��������� �� ���� ����� ��������� �����������" << endl; //done
		cout << ++g << " - ������������ ����������� �� ������" << endl; //done
		cout << ++g << " - ����� ����������� � ������ ϲ�" << endl; //done
		cout << ++g << " - ������ ����������� ��������� �����" << endl; //done
		cout << ++g << " - ��������� ������� ����������� � ��������� ����" << endl; //done
		cout << ++g << " - ��������� ���� �������� ����� �� ������" << endl; //done
		cout << ++g << " - ��������� ������� ��� ���������� �����������" << endl; //done
		cout << ++g << " - ����������� ����������� � ����� �� � ���� ��" << endl; //done
		cout << ++g << " - ��������� ���: ������ ����������� �� ������," <<
			"\n������� - ���� �������� ������� ����� � ��������� ���� �� ����" << endl;

		cout << ++g << " - ��������" << endl;
		cout << ++g << " - �����" << endl;
	}

	int CheckMenu(Company& company)
	{
		PrintMenu();
		int number = 0;
		cin >> number;
		int g = 0;
		if (++g == number)//1
		{
			int size = -1;
			while (size < 0)
			{
				cout << "������ ������� ����������: ";
				cin >> size;
			}
			company.FillDatabase(size);
		}
		else if (++g == number)//2
		{
			company.ShowAll();
		}
		else if (++g == number)//3
		{
			company.AddWorker();
		}
		else if (++g == number)//4
		{
			company.DeleteWorker();
		}
		else if (++g == number)//5
		{
			company.SortByDepart();
		}
		else if (++g == number)//6
		{
			company.FoundWorkerByNSL();
		}
		else if (++g == number)//7
		{
			company.FoundWorkedByDepart();
		}
		else if (++g == number)//8
		{
			company.AmountWorkerInDepart();
		}
		else if (++g == number)//9
		{
			company.TotalMoneyByDepart();
		}
		else if (++g == number)//10
		{
			company.DeleteWorker();
		}
		else if (++g == number)//11
		{
			company.ReplaceDepart();
		}
		else if (++g == number)//12
		{
			//�������

			company.PrintTable();
		}
		else if (++g == number)//13
		{
			company.Write();
			system("cls");
			cout << "���������!" << endl;
		}
		else if (++g == number)//14
		{
			system("cls");
			cout << "�����" << endl;
			company.Write();
		}
		else
		{
			system("cls");
			cout << "Error\a\a" << endl;
			system("pause");
			return 0;
		}
		system("pause");
		return number;
	}
public:
	void DoWork(Company& company)
	{
		company.Read();
		int number = 0;
		while (number != 14)
		{
			system("cls");
			number = CheckMenu(company);
		}
	}
};



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Company company("text.txt");
	Menu menu;
	menu.DoWork(company);


	system("pause");
	return 0;
}