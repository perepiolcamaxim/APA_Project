#include <iostream>
#include <vector>
using namespace std;

int N;
int*  Zecimal_Binar(int n);
void pregat_nr_binar(int *t1, int *t2, int a, int b, int n1, int n2);
vector <int> CD(vector <int> &X, int a);
vector<int> CI(vector <int> &A, int n);
vector <int> CC(vector <int> X, int n1);
vector<int> adunare(vector <int> &a, vector <int> &b, int n);
vector <int> scadere(vector <int> &A, vector <int> &B, int n);

int main()
{
        int n, *t1, *t2, n1, n2, a, b;

        cout<<"Dati 2 numere zecimale:\n";
        cin>>a>>b;

        t1 = Zecimal_Binar(a);
        t2 = Zecimal_Binar(b);
        
        for(n1 = 0; t1[n1] != 4; n1++);   //lungimile la fiecare numar
        for(n2 = 0; t2[n2] != 4; n2++);
        
        pregat_nr_binar(t1, t2, a, b, n1, n2);
        delete t1, t2;
        return 0;
}

int* Zecimal_Binar(int n)
{
        int *t1, m, rest, i = 1, l, *temp, j, flag = 0;
        if(n < 0)
                n = n * (-1);
        t1 = new int[20];
        for (m = 0; n != 0; m++)
        {
                rest = n % 2;
                t1[m] = rest;
                n = n / 2;
        }
        temp = new int[m + 1];
        for(j = 0, l = m - 1 ; j < m; j++, l--)
                temp[j] = t1[l];                   //inverseaza tabloul deoarece  numarul binar este invers cum l-am obtinut
        temp[j] = 4;                            //conditia de stopare a numarului binar
        delete t1;
        return temp;
}

void pregat_nr_binar(int *t1, int *t2, int a, int b, int n1, int n2)  // pregateste numarul binar pentru operatiile ulterioare(adunare, scadere)
{
        int i;
        vector <int> A(n1);
        vector <int> B(n2);
        vector <int> Suma;
        vector <int> C(n1 + 1);
        for(i = 0; i < n1; i++)
                A[i] = t1[i]; // atribuirea numerelor binare in vector
        for(i = 0; i < n2; i++)
                B[i] = t2[i];

        if(n1 != n2)    // daca numarul de biti nu coincide , facem asa ca sa coincida
        {
                while(n1 != n2)
                {
                        if(n1 > n2)
                        {
                                B.insert(B.begin(), 0);    // se insereaza la inceput zerouri in numarul mai mic de biti
                                n2++;
                        }
                        else
                        {
                                A.insert(A.begin(), 0);
                                n1++;
                        }
                }
        }
        if(a < 0)
        {
                A = CD(A, a);
                A = CI(A, n1 + 1);
                A = CC(A, n1);
        }
        else
                A = CD(A, a);
        if(b > 0)
                B = CD(B, b);
        else
        {
				B = C = CD(B, b);
                B = CI(B, n2 + 1);
                B = CC(B, n2);
        }
        n1++;          //lungimile se incrementeaza, deoarece am pus bitul semnului
        n2++;

        cout<<"\nPrimul numar binar:\n";
        for(i = 0; i < n1; i++)
                cout<<A[i]<<" ";
        cout<<endl<<"Al doilea numar binar\n";

        for(i = 0; i < n2; i++)
                cout<<B[i]<<" ";

        cout<<endl<<"\n\nSuma numerelor binare:\n";
        Suma = adunare(A, B, n1);
        cout<<endl;
        for(i = 0; i < N; i++)
                cout<<Suma[i]<<" ";
        cout<<endl;

        if(b > 0)
                Suma = scadere(A, B, n1);
        else
                Suma = scadere(A, C, n1);
        cout<<endl<<"Scaderea numerelor binare:\n";
        for(i = 0; i < N; i++)
                cout<<Suma[i]<<" ";
        cout<<"\n\n";
}

vector <int> CD(vector <int> &X, int a)
{
        if(a > 0)
                X.insert(X.begin(), 0);
        else if(a < 0)
                X.insert(X.begin(), 1);
        return X;
}

vector <int> CI(vector <int> &A, int n)
{
        for(int i = 1; i < n; i++)
        {
                if(A[i] == 1)
                {
                        A[i] = 0;
                        goto c;
                }
                if(A[i] == 0)
                        A[i] = 1;
				c:
                	cout<<"";
        }
        return A;
}

vector <int> CC(vector <int> X, int n1)
{
        int e;
        vector<int> D(n1 + 1);
        for(e = 0; e < n1; e++)
                D[e] = 0;        // facem un vector cu valoarea "1" ca sa adunam cuCI si sa obtinem CC
        D[e] = 1;
        X = adunare(X, D, n1 + 1);
        return X;
}

vector <int> adunare(vector <int> &a, vector <int> &b, int n)
{
        int tr0, tr = 0, j = n, u;

        vector <int> result(n + 1);
        for(int i = n - 1; i >= 0; i--, j--)
        {
                tr0 = tr;
                if((a[i] + b[i] + tr) == 3)
                {
                        result[j] = 1;
                        tr = 1;
                }
                else if((a[i] + b[i] + tr) == 2)
                {
                        result[j] = 0;
                        tr = 1;
                }
                else if((a[i] + b[i] + tr) ==1 )
                {
                        result[j] = 1;
                        tr = 0;
                }
                else if ((a[i] + b[i] + tr) == 0)
                {
                        result[j] = 0;
                        tr = 0;
                }
        }
        if(tr != tr0)
        {
                result[0] = a[0];
                N = ++n;
        }
        else
        {
                for(u = 0; u < n; u++)
					result[u] = result[u + 1];
                N = n;
        }

        while(result[0]  == 0 && result[1] == 0)
        {
                result.erase(result.begin());
                N--;
        }
        return result;
}

vector <int> scadere(vector <int> &A, vector <int> &B, int n)
{
        vector <int> D;int i;
        if(B[0] == 0)
        {
                B[0] = 1;
                B = CI(B, n);
                B = CC(B, n - 1);
        }
        else
                B[0] = 0;
        D = adunare(A, B, n);
        return D;
}
