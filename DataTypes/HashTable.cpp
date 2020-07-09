#include <iostream>
#include <clocale>
#include <conio.h>
#include <string>
#include <io.h>
#include <fstream>
using namespace std;

struct Struct
{
	int Key;
	string Info;
	Struct* next;
};

struct Hash
{
	Struct* begin;
};

int h(int key, int n);
Hash* Add(Hash* hash, int n, int key, string info);
Struct* Add_to_Struct(Struct* begin, int key, string info);
void View(Hash* hash, int n);
void DellAll(Struct*& begin);
void Find(Hash* hash, int key, int n);
Hash* Delete(Hash* hash, int key, int n);
void Save(ofstream fourt, Hash* hash, int n);

int main()
{
	setlocale(LC_ALL, "Russian");
	int number, kol, i, n, key, kod, kluch,kod1;
	string Str;
	string info;
	Hash* hash;
	ofstream fout;
	ifstream fin;
	Struct S, *t;
	ifstream file("result.txt");
	ofstream file2("result1.txt");
	cout << "\n������� ������ ���-�������: ";
	cin >> number;
	hash = new Hash[number];
	for (i = 0; i < number; ++i)
		hash[i].begin = NULL;
	while (true)
	{
		cout <<
			"\n1 - �������� ��������;\n2 - ��������;\n3- ����� ��������;\n4 - �������� ������;\n5-��������� ��������� ������� � ����\n0-�����\n";
		cin >> n;
		switch (n)
		{
		case 1:
			cout << "1-�� �����\n����� �������� ������� ����(� ��)��������� ����� �����\n2-� ����������\n";
			cin >> kod;
			switch (kod)
			{
			case 1:
				while (file >> kluch >> Str)
					hash = Add(hash, number, kluch, Str);
				file.close();
				break;
			case 2:
				cout << "\n������� ���������� ���������: ";
				cin >> kol;
				for (i = 0; i < kol; ++i)
				{
					cout << "������� ����: ";
					cin >> key;

					cout << "������� ������: ";
					cin >> info;
					hash = Add(hash, number, key, info);
				}
				break;
			}
			View(hash, number);
			break;
		case 2:
			View(hash, number);
			break;
		case 3:
			cout << "\n������� ���� �������� ��������: ";
			cin >> key;
			Find(hash, key, number);
			break;
		case 4:
			for (i = 0; i < number; ++i)
				DellAll(hash[i].begin);
			cout << "\n������ �������" << endl;
			break;
		case 5:
			cout << "���� ���������?\n1-� ����� ����\n2-� �������� ����\n";
			cin >> kod1;
			switch (kod1)
			{
			default:case 1:
				fout.open("result1.txt");
				for (int i = 0; i < number; ++i)
				{
					fout << "\n������ " << i + 1 << endl;
					t = hash[i].begin;
						while (t)
						{
							fout << t->Key << " - " << t->Info << endl;
							t = t->next;
						}
				}
			fout.close();
			fin.open("result1.txt");
				cout << "���������� ������ �����:\n";
				for (int i = 0; i < number; ++i)
				{
					cout << "\n������ " << i + 1 << endl;
					t = hash[i].begin;
					while (t)
					{
						cout << t->Key << " - " << t->Info << endl;
						t = t->next;
					}
				}
				fin.close();
				break;
			case 2:
				fout.open("result.txt");
				for (int i = 0; i < number; ++i)
				{
					//fout << "\n������ " << i + 1 << endl;
					t = hash[i].begin;
					while (t)
					{
						fout << t->Key <<t->Info << endl;
						t = t->next;
					}
				}
				fout.close();
				fin.open("result.txt");
				cout << "���������� ������ ��������� �����:\n";
				for (int i = 0; i < number; ++i)
				{
					cout << "\n������ " << i + 1 << endl;
					t = hash[i].begin;
					while (t)
					{
						cout << t->Key << " - " << t->Info << endl;
						t = t->next;
					}
				}
				fin.close();
				break;
			}
			break;
		default: case 0:
			for (i = 0; i < number; ++i)
				DellAll(hash[i].begin);
			delete[] hash;
			return 0;
		}
	}
}


int h(int key, int n)
{
	return key % n;
}

Hash* Add(Hash* hash, int n, int key, string info)
{
	Struct* t = nullptr;
	for (int i = 0; i < n; i++)
	{
		t = hash[i].begin;
		if (t != NULL)
		{
			while (t != NULL)
			{
				if (t->Key == key)
				{
					cout << "������� � �������� ������ ��� ����������\n";
					return hash;
				}
				t = t->next;
			}
		}
	}
	hash[h(key, n)].begin = Add_to_Struct(hash[h(key, n)].begin, key, info);
	return hash;
}

Struct* Add_to_Struct(Struct* begin, int key, string info)
{
	Struct* t = new Struct;
	t->Key = key;
	t->Info = info;
	t->next = begin;
	return t;
}

void View(Hash* hash, int n)
{
	Struct* t;
	//cout � "\n ���� ���� ������ \n";
	for (int i = 0; i < n; ++i)
	{
		cout << "\n������ " << i + 1 << endl;
		t = hash[i].begin;
		if (t != NULL)
		{
			while (t != NULL)
			{
				cout << t->Key << " - " << t->Info << endl;
				t = t->next;
			}
		}
	}
}

void DellAll(Struct*& begin)
{
	Struct* t;
	while (begin != NULL)
	{
		t = begin;
		begin = begin->next;
		delete t;
	}
}

void Find(Hash* hash, int key, int n)
{
	Struct* t = hash[h(key, n)].begin;
	int i;
	while (t != NULL)
	{
		if (t->Key == key)
		{
			cout << "������� � �������� ������: " << t->Info << endl;
			cout << "\n������� ��������� �������?\n1 - ��,\n����� - ���.";
			cin >> i;
			if (i == 1)
				hash = Delete(hash, key, n);
			return;
		}
		t = t->next;
	}
	cout << "������� �� ������\n" << endl;
}

Hash* Delete(Hash* hash, int key, int n)
{
	Struct *t = hash[h(key, n)].begin, *t1 = NULL;
	while (t && t->Key != key)
	{
		t1 = t;
		t = t->next;
	}
	if (!t)
	{
		cout << "�������� � �������� ������ �� ����������\n" << endl;
		return hash;
	}
	if (t1)
		t1->next = t->next;
	else hash[h(key, n)].begin = t->next;
	cout << "������ �������: " << t->Info << endl;
	delete t;
	return hash;
}