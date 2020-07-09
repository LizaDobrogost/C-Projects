#include<iostream>
using namespace std;
struct Spis2 {
	int info;
	Spis2 *next, *prev;
};
void Create(Spis2 **b, Spis2 **e, int in) {
	Spis2 *t = new Spis2;
	t->info = in;
	t->next = NULL;
	if (*b == NULL) {
		t->next = t->prev = NULL;
		*b = *e = t;
	}
	else
	{
		t->next = NULL;
		t->prev = (*e);
		(*e)->next = t;
		(*e) = t;
	}
}
void View_Spis2_Beg(Spis2 *b) {
	
	while (b != NULL) {
		cout << b->info<<"\t";
		b = b->next;
	}

}
void View_Spis2_End(Spis2 *e) {
	
	while (e != NULL) {
		cout << e->info << "\t";
		e = e->prev;
	}
}
void Del_All(Spis2 **p) {
	Spis2 *t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}
void Add_Spis2(int kod, Spis2 **b, Spis2 **e, int in) {
	Spis2 *t;
	t = new Spis2;
	t->info = in;
	if (kod == 0) {
		t->prev = NULL;
		t->next = *b;
		if(b!=NULL)
		(*b)->prev = t;
		*b = t;
	}
	else {
		t->next = NULL;
		t->prev = *e;
		if(e!=NULL)
		(*e)->next = t;
		*e = t;
	}
}
Spis2* Del_5(Spis2 *&b, Spis2 *&end) {
	Spis2 *p = b, *e = b;
	Spis2 *t = p->next;
	while (t != NULL)
	{
		if (t->info % 5 == 0) {
			if (t->prev != NULL && t->next != NULL)
			{
				t->prev->next = t->next;
				t->next->prev = t->prev;
			}
			else if (t->prev == NULL && t->next != NULL) {
				t->next->prev = NULL;
				b = t->next;
			}
			else if (t->prev != NULL && t->next == NULL)
			{
				t->prev->next = NULL;
				end = t->prev;

			}
			delete t;
			t = p->next;
		}
		else {
			e = t;
			t->prev = p;
			p = t;
			t = t->next;
		}

	}
	if (b->info % 5 == 0) {
		if (e == b)
			e = t = NULL;
		else
		{
			t = b->next;
			t->prev = NULL;
		}
		delete b;
		b = t;
	}
	return e;
}
void main()
{
	int i, in, in1, n, n1, kod, kod1;
	Spis2 *Begin = NULL, *End = NULL, *t;
	char Str[2][10] = { "Begin ", "End " };
	while (true) {
		cout << "\n\tCreate - 1\n\tAdd - 2\n\tView - 3\n\tDel - 4\n\tTask-5\n\tEXIT - 0  :  ";
		cin >> kod;
		switch (kod) {
		case 1:        if (Begin != NULL) {
			cout << "Clear Memory!" << endl;
			break;
		}

					   cout << "Input kol = ";
					   cin >> n;
					   cout << "Begin Info = ";
					   for (i = 1; i <= n; i++) {
						   cin >> in;
						   Create(&Begin, &End, in);
					   }
					   cout << "Creat Begin = " << Begin->info << endl;
					   break;
		case 2:
			if(Begin!=NULL && End!=NULL){
			cout << "Input kol = ";
			cin >> n1;
			cout << "Add Begin - 0, Add End - 1 :  ";
			cin >> kod1;
			if (kod1 == 0)
				t = Begin;
			else t = End;
			for (i = 1; i <= n1; i++) {
				cin >> in1;
				Add_Spis2(kod1, &Begin, &End, in1);
			}
			cout << "Add to " << Str[kod1] << "  " << t->info << endl;
			break;}
			else
			{
				cout << "Ermpty,new created\n";
				cout << "Input kol = ";
				cin >> n;
				cout << "Begin Info = ";
				for (i = 1; i <= n; i++) {
					cin >> in;
					Create(&Begin, &End, in);
				}
				cout << "Creat Begin = " << Begin->info << endl;
				break;
			}
		case 3: {
			if (!Begin) {
				cout << "Empty!" << endl;
				break;
			}
			else {
				cout << "-- Begin --\n";
				View_Spis2_Beg(Begin);
				cout << "\n--- End --\n";
				View_Spis2_End(End);
				break;

			}

		}
		case 4:
			Del_All(&Begin);
			cout << "Memory Free!" << endl;
			break;
		case 5:
			Del_5(Begin,End);
			break;

		case 0:  if (Begin != NULL)
			Del_All(&Begin);
			return;
		}
	}
}