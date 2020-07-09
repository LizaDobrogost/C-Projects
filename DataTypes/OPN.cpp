#include <iostream> 
#include <string.h>
using namespace std;
struct tstk
{
	char inf;
	tstk *a;
};

struct tstkd
{
	double inf;
	tstkd *a;
};
struct Num
{
	char per = '\0';
	double znach = NULL;
};
tstk *AddStack(tstk *sp, char inf)
{
	tstk *spt = new tstk;
	spt->inf = inf;
	spt->a = sp;
	return spt;
}

tstkd *AddStack1(tstkd *sp, double inf)
{
	tstkd *spt = new tstkd;
	spt->inf = inf;
	spt->a = sp;
	return spt;
}
tstk *ReadStackD(tstk *sp, char &inf)
{
	tstk *spt = sp;
	inf = sp->inf;
	sp = sp->a;
	delete spt;
	return sp;
}
tstkd *ReadStackD1(tstkd *sp, double &inf)
{
	tstkd *spt = sp;
	inf = sp->inf;
	sp = sp->a;
	delete spt;
	return sp;
}
int priority(char ch)  // Вычисление 
{
	switch (ch)
	{
	case '^': return 4;
	case '*': 	case '/':   return 3;
	case '-': 	case '+':   return 2;
	case '(': 	return 1;
	}
	return 0;
}
int Balans(char *strin, int len)
{
	int balans = 0;
	if (strin[1] == ')' || strin[len] == '(') {
		cout << "Wrong input\n";
		system("pause");
		return -1;
	}
	for (int i = 0; i < strlen(strin); i++) {
		if (strin[0] == '-' && (strin[1] >= 'a' && strin[1] <= 'z')
			|| (strin[i] == '-' && (strin[i + 1] >= 'a' && strin[2] <= 'z') && strin[i - 1] == '(' && strin[i + 2] == ')')) {
			cout << "- perem\n";
			system("pause");
			return -1;
		}
		if ((strin[i] >= 'a' && strin[i] <= 'z') && (strin[i + 1] == '(')) {
			cout << "Missing operation sign\n";
			system("pause");
			return -1;
		}
		else {
			if (strin[i] == '(')
				balans++;
			if (strin[i] == ')')
				balans--;
		}
		if ((strin[i] == '(') && (strin[i + 1] == ')')) {
			cout << "Ermpty ()\n";
			system("pause");
			return -1;
		}
		if (strin[i] == ' ')
			continue;
	}
	if (balans <= -1) {
		cout << "extra )\n";
		system("pause");
		return -1;
	}
	if (balans > 0) {
		cout << "Extra (\n";
		system("pause");
		return -1;
	}
	
}
void AddPostFix(char *strin, char *strout)
{

	tstk *sp = NULL;
	int n = 0;
	char ch, inf;
	int balans = 0;
	if (Balans(strin, strlen(strin)) != -1) {
		for (int i = 0; i < strlen(strin); i++)
		{
			ch = strin[i];
			// Если это операнд
			if (ch >= 'A') { strout[n++] = ch; continue; }
			// Если стек пуст или открыв.скобка  
			if (sp == NULL || ch == '(')
			{
				sp = AddStack(sp, ch); continue;
			}
			if (ch == ')')
			{
				while (sp->inf != '(')
				{
					sp = ReadStackD(sp, inf);
					strout[n++] = inf;
				}
				// Удаление открывающей скобки
				sp = ReadStackD(sp, inf); continue;
			}
			int pr = priority(ch);
			while (sp != NULL && priority(sp->inf) >= pr)
			{
				sp = ReadStackD(sp, inf);
				strout[n++] = inf;
			}
			sp = AddStack(sp, ch);
		}  // end for
		while (sp != NULL)
		{
			sp = ReadStackD(sp, inf);
			strout[n++] = inf;
		}
		strout[n++] = '\0';
		if(sp==NULL)
		{
			cout << "Enter expresion first\n";
		}else
		cout << endl << "OPN:" << strout << "\n";
	}
	else
		cout << "Error";

}
double rasAV(char *str, double *mz)
{
	tstkd *sp = NULL;
	char ch;
	double	inf, inf1, inf2;
	for (int i = 0; i < strlen(str); i++)
	{
		ch = str[i];


		if (ch >= 'A')
		{
			sp = AddStack1(sp, mz[int(ch)]);
			continue;
		}
		sp = ReadStackD1(sp, inf2); // Если знак операции
		sp = ReadStackD1(sp, inf1);
		switch (ch)
		{
		case '+': sp = AddStack1(sp, inf1 + inf2); break;
		case '-': sp = AddStack1(sp, inf1 - inf2); break;
		case '*': sp = AddStack1(sp, inf1 * inf2); break;
		case '/':
			if (inf2 != 0)
			{
				sp = AddStack1(sp, inf1 / inf2);
				break;
			}
			else
				cout << "Error of /0\n";
			system("pause");
			return 0;
		}
	}
	sp = ReadStackD1(sp, inf);
	return inf;
}
double input() {
	double q;
	while (!(cin >> q))

	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error,put numbers\n" << "=";
	}
	return q;
}
int main()
{
	int j,kod;
	double masz[122];
	bool k = true;
	char str[100], strp[100];
	while (true) {
		cout << "\n\tInput expression - 1\n\tTranslate and show OPN- 2\n\tInput values and Calculate - 3\n\tEXIT - 4 :\n  ";
		cin >> kod;
		switch (kod) {
		case 1:
			cout << "Enter expression : " << endl;
	        cin >>str;
			break;
		case 2:
			if(str==NULL)
			{
				cout << "Еnter OPN first\n";
			}else
			AddPostFix(str, strp);
			/*cout << endl << "OPN:" << strp << "\n";*/
			break;
		case 3:
			if(str==NULL)
			{
				cout << "Enter expresion first\n";
			}else{
			if (Balans(str, 100) != -1) {
		for (int i = 0; str[i] != '\0'; i++, k = true)
		{
			if (str[i] >= 'A')
			{
				for (j = i + 1; str[j] != '\0'; j++)
				{

					if (str[i] == str[j]) {
						k = false;
						break;
					}


				}if (k) {
					cout << "Enter " << str[i] << "\n";
					masz[str[i]] = input();
				}
			}
		}
	} 
    cout << endl << "Rezult = " << rasAV(strp, masz) << "\n";
			}
	break;

		case 4:
			return 0;
		}

	}
	system("pause");
	return 0;
}


