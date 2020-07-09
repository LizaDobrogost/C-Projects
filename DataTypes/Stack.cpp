 #include<iostream>
#include<ctime>
#include<stack>
using namespace std;
struct Stack {
	int info;
	Stack *next;
};
void View(Stack *p);
Stack* OutStack(Stack* p, int *out);
void Del_All(Stack *&p);
Stack* InStack(Stack *p, int in);
Stack* Del_5(Stack *b);
int input();
void main()
{
	int i, in, n, kod, kod1;
	Stack *Begin = NULL;
	while (true) {
		cout << "\n\tCreate - 1.\n\tAdd - 2.\n\tView - 3.\n\tDel - 4.\n\tTask - 5\n\tEXIT - 0 :  ";
		kod=input();
		switch (kod) {
		case 1: case 2:
			if (kod == 1 && Begin != NULL) {
				cout << "Clear Memory!" << endl;
				break;
			}
			cout << "Input kol = ";
			 n=input();
	       	for (i = 1; i <= n; i++) {
				in=input();
				Begin = InStack(Begin, in);
				
			}
			if (kod == 1) cout << "Created " << n << "- elements "<< endl;
			else cout << "Add " << n << endl;
			break;
		case 3:         if (!Begin) {
			cout << "Stack is empty!" << endl;
			break;
		}
						cout << "--- Stack ---" << endl;
						View(Begin);
						break;
		case 4:
			Del_All(Begin);
			cout << "Memory Free!" << endl;
			break;
		case 5:
			Begin = Del_5(Begin);
			break;
		case 0:
			if (Begin != NULL)
				Del_All(Begin);
			return;
		}
	}
}
Stack* InStack(Stack *p, int in) {
	Stack *t = new Stack;			
	t->info = in;			
	t->next = p;			
	return t;
}
void View(Stack *p) {
	Stack *t = p;
	while (t != NULL) {
		cout <<"  " << t->info; 
		t = t->next;
	}
}
Stack* OutStack(Stack* p, int *out) {
	Stack *t = p;			
	*out = p->info;
	p = p->next; 		
	delete t; 			
	return p; 			
}
void Del_All(Stack *&p) {
	Stack *t;
	while (p != NULL) {
		t = p;
		p = p->next;
		delete t;
	}
}
Stack* Del_5(Stack *b)
{
	
	b = InStack(b, 21);	    
	Stack *p = b,*t;
	t = p->next;	          
	while (t != NULL) {
		if (t->info % 5 == 0) {
			p->next = t->next;
			delete t;
			t = p->next;
		}
		else {
			p = t;
			t = t->next;
		}
	}
	t = b;			
	b = b->next;
	delete t;
	return b;

}

int input() {
	int q;
	while (!(cin >> q))

	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error,put numbers\n" << "=";
	}
	return q;
}