#include<iostream>
#include<string>
using namespace std;
struct tree
{
	int inf;
	char hight;
	string str;
	tree *left,*right;
};

tree *list(int inf)
{
	tree *t = new tree;
	t->inf = inf;
	t->left = t->right = NULL;
	return t;
}
int input() {
	int q;
	while (!(cin >> q))

	{
		cin.clear();
		while (cin.get() != '\n');
		cout << "Error,put numbers" << "=";
	}
	return q;
}
void addlist(tree *root, int key) {//����������
	tree *pr=NULL, *t;
	bool find1 = true;
	t = root;
	while (t && find1) {
		pr = t;
		if (key == t->inf) {
			find1 = false;
			cout << "Dublucate Key!";
		}
		else
			if (key < t->inf)
				t = t->left;
			else
				t = t->right;
	}
	if (find1) {
		t = list(key);
		if (key < pr->inf){
			pr->left = t;
			cout << "Enter string=";
		cin >> pr->left->str;
		}
		else{
			pr->right = t;
			cout << "Enter string= ";
			cin >> pr->right->str;
		}

	}
}
void Viewtree(tree *p, int level) {//��������
	if (p) {
		Viewtree(p->right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "   ";
		cout << p->inf << endl;
		Viewtree(p->left, level + 1);
	}
}
void Sort_Bubble(tree **roots, int n)
{
	tree *r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (roots[i]->inf < roots[j]->inf){
				r = roots[i];
			roots[i] = roots[j];
			roots[j] = r;
			}
		}
	}
}
tree* Del_inf(tree *&root, int key) {//�������� ���� �� ������
	tree *del, *Prev_Del, *R, *Prev_R;
	del= root;
	Prev_Del = NULL;

	while (del != NULL && del->inf!= key) {
		Prev_Del = del;
		if (del->inf > key)
			del = del->left;
		else
			del = del->right;
	}
	if (del == NULL) {
		cout << "\n No Key!" << endl;
		return root;
	}
	if (del->right == NULL)
		R = del->left;
	else
	if (del->left == NULL)
		R = del->right;
	else {
		Prev_R = del;
		R = del->left;
		while (R->right != NULL) {
			Prev_R = R;
			R = R->right;
		}
		if (Prev_R == del)
			R->right = del->right;
		else {
			R->right = del->right;
			Prev_R->right = R->left;
			R->left = Prev_R;
		}
	}
	if (del == root)
		root = R;
	else
		if (del->inf < Prev_Del->inf)
			Prev_Del->left = R;
		else{
			cout << "Delete" << del->inf << endl;
			Prev_Del->right = R;
			delete del;
			return root;
		}
}
tree* find1(tree *&root, int key) {
	tree *Del;
	Del = root;
	while (Del != NULL && Del->inf!= key) {
		if (Del->inf > key)
			Del = Del->left;
		else
			Del = Del->right;
	}
	if (Del == NULL) {
		cout << "No key\n";
		return 0;
	}
	return Del;
}


int Max_Key(tree *p) {
	if (p->right != NULL) {
		return Max_Key(p->right);
	}
	else
		return p->inf;
}
int Min_Key(tree *p) {
	if (p->left != NULL) {
		return Min_Key(p->left);
	}
	else
	{
		return p->inf;
	}
}
double Sred(tree* p) {
	double sum=0,n=0,sr;
	while(p!=NULL){
	if (p->right != NULL) {
			sum = sum + p->inf;
			p = p->right;
			n++;
	}
		else {
			
			sum = sum + p->inf;
			p = p->left;
			n++;
		}
	}
	sr = sum / n;
	return sr;
}
void Balans(tree **p, int n, int k, tree *&a) {
	if (n == k) {
		*p = NULL;
		return;
	}
	if(n!=k) {
		int m = (n + k) / 2;
		a=p[m];
		Balans(p, n, m, a->left);
		Balans(p, m+1 , k, a->right);
	}
}
void sozdmasiva(tree **roots, tree *root, int &k) {
	if (root) {
		sozdmasiva(roots, root->right, k);
		sozdmasiva(roots, root->left, k);
		root->left = NULL;
		root->right = NULL;
		roots[k++] = root;
	}
}
void schetchikuslov(tree *root, int &k) {
	if (root) {
		schetchikuslov(root->left, k);
		schetchikuslov(root->right, k);
		
	}
}
void Del(tree *&t) {
	if (t != NULL) {
		Del(t->left);
		Del(t->right);
		t = NULL;
		delete t;
	}
}


void main(void) {
	int kod, c, el,k,m;
	tree  *root = NULL,**roots;
	int mas[120];
	while (true) {
		cout << "\n\tCreate tree- 1\n\tVeiw- 2\n\tAdd - 3\n\tDelete the whole tree-4 \n\tBalans-5\n\tMax and min elements-6\n\tDel element-7\n\tFind string by key-8\n\tEXIT - 0 :\n  ";
		kod=input();
		switch (kod)
		{
		default:case 1:
			if (root != NULL)
				Del(root);
			cout << "Input root=  ";
			m=input();
			root = list(m);
			cout << "Enter string= ";
			cin >> root->str;
			break;

		case 2:if (root == NULL)
			cout << "Create tree!";
			   else
		{
			cout << "------Veiw------\n";
			Viewtree(root, 0);
		}
			   break;
		case 3:
			if (root == NULL) {
				cout << "Input key=";
				m=input();
				root = list(m);
				cout << "Enter string  ";
				cin >> root->str;
			}
			else {
				cout << "Input col= ";
				c=input();
				for (int i = 0; i <c; ++i) {
					cout << "Input key= ";
					m=input();
					addlist(root, m);
				}
			}
			break;
		case 4:
			Del(root);
			cout << "Tree deleted!";
		//	root = NULL;
			break;
		case 5:	if (root == NULL) {
			cout << "Create tree";
			break;
		}
				cout << "---Balans---\n";
				k = 0;
				schetchikuslov(root, k);
				roots = new tree*[k]; 
				k = 0;
				sozdmasiva(roots, root, k);
				Sort_Bubble(roots, k);
				Balans(roots, 0, k, root);
				Viewtree(root, 0);
				break;
		case 6:
			if (root == NULL || root->right == NULL|| root->left == NULL) {
				cout << "Create tree!";
				break;
			}else
			{
				cout << "Max element-" << Max_Key(root) << "\n";
				cout << "Min element-" << Min_Key(root) << "\n";
				break;
			}
		case 7:
			if (root == NULL) {
				cout << "Create tree!";
				break;
			}else{
				cout << "Input key,that you want to delete\nkey= ";
				el=input();
				Del_inf(root, el);
				break;
			}
		case 8:if (root == NULL) {
			cout << "Create tree!";
			break;
		}
			   else {
			cout << "Input key of the information that you want to see\nkey= ";
			el=input();
			if (find1(root, el) == 0) {
				cout << "No string!";
			}else{
			cout << " info= " << find1(root, el)->str;
			}
			break;
		       }
		case 9:
			cout <<"Sred znach="<<Sred(root);
			break;
		case 0:
			if (root != NULL) {
				Del(root);
				cout << "Tree Delete!";
			}
			return;
		}
	}
}

