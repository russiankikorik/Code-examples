


/* МАТРИЦЫ 3Х3
Ввод через консоль комплексных чисел осуществляется в форме a+bi. Однако можно просто написать 18 чисел с типа double. Прикладываю файлы с матрицами mtrx_1.txt (нулевой детерминант),
    mtrx_2.txt, комплексные: mtrx_3.txt, mtrx_4.
    Работа Артёма Кирика.*/


using namespace std;

#include <fstream>
#include <iostream>
#include <cmath>

class cmplx
{
public:
	double re;
	double im;
	cmplx operator+(cmplx b);
	cmplx operator+(double b);
	cmplx operator-(cmplx b);
	cmplx operator-(double b);
	cmplx interf();
	double abs();
	cmplx operator*(cmplx b);
	cmplx operator*(double b);
	cmplx operator/(cmplx b);
	cmplx operator/(double b);
	bool operator==(cmplx b);
	bool operator==(double b);
	bool operator!=(cmplx b);
	bool operator!=(double b);
	double arg();
	cmplx()
	{
		re = 0;
		im = 0;
	}
	explicit cmplx(double a)
	{
		re = a;
		im = 0;
	}
	cmplx(double a, double b)
	{
		re = a;
		im = b;
	}
};

bool cmplx::operator==(cmplx b)
{
	if ((re == b.re) && (im == b.im)) return true;
	else return false;
}

bool cmplx::operator==(double b)
{
	if (re == b) return true;
	else return false;
}

bool cmplx::operator!=(cmplx b)
{
	if ((re != b.re) || (im != b.im)) return true;
	else return false;
}

bool cmplx::operator!=(double b)
{
	if ((re != b)||(im!=0)) return true;
	else return false;
}

bool operator==(double b, cmplx a)
{
	if ((a.re == b)&&(a.im==0)) return true;
	else return false;
}

bool operator!=(double b, cmplx a)
{
	if ((a.re != b)||(a.im!=0)) return true;
	else return false;
}

cmplx cmplx::interf()
{
	cmplx res;
	res.re = re;
	res.im = -im;
	return res;
}

double cmplx::abs()
{
	return sqrt(re*re + im*im);
}

double cmplx::arg()
{
	double res = atan(im / re);
	return res;
}

istream& operator >> (istream& str, cmplx& A)
{
	int k;
	do
	{
		k = 0;
		str >> A.re;
		if (str.fail())
		{
			k = 1;
			str.clear();
			str.ignore();
		}
	} while (k == 1);
	do
	{
		str >> A.im;
		if (str.fail())
		{
			k = 1;
			str.clear();
			str.ignore();
		}
	} while (k == 1);
	return str;
}

ostream& operator << (ostream& str, cmplx A)
{
	if (A.im >= 0)
	{
		str << A.re << "+" << A.im << "i";
	}
	if (A.im < 0)
	{
		str << A.re << A.im << "i";
	}
	return str;
}

cmplx cmplx::operator+(double b)
{
	cmplx res;
	res.re = re + b;
	res.im = im;
	return res;
}

cmplx cmplx::operator+(cmplx b)
{
	cmplx res;
	res.re = re + b.re;
	res.im = im + b.im;
	return res;
}

cmplx operator+(double a, cmplx b)
{
	cmplx res;
	res.re = a + b.re;
	res.im = b.im;
	return res;
}

cmplx operator-(double a, cmplx b)
{
	cmplx res;
	res.re = a - b.re;
	res.im = -b.im;
	return res;
}

cmplx cmplx::operator-(cmplx b)
{
	cmplx res;
	res.re = re - b.re;
	res.im = im - b.im;
	return res;
}

cmplx cmplx::operator-(double b)
{
	cmplx res;
	res.re = re - b;
	res.im = im;
	return res;
}

cmplx cmplx::operator*(cmplx b)
{
	cmplx res;
	res.re = re*b.re - im*b.im;
	res.im = re*b.im + b.re*im;
	return res;
}

cmplx cmplx::operator*(double b)
{
	cmplx res;
	res.re = re*b;
	res.im = im*b;
	return res;
}

cmplx operator*(double a, cmplx b)
{
	cmplx res;
	res.re = a*b.re;
	res.im = a*b.im;
	return res;
}

cmplx cmplx::operator/(double b)
{
	cmplx res;
	res.re = re / b;
	res.im = im / b;
	return res;
}

cmplx cmplx::operator/(cmplx b)
{
	cmplx buf;
	buf.re = re;
	buf.im = im;
	buf = (buf*b.interf()) / (b.abs()*b.abs());
	return buf;
}

cmplx operator/(double a, cmplx b)
{
	cmplx res;
	res.re = a;
	res.im = 0;
	res = res / b;
	return res;
}



template <class type>
class mtrx
{
public:
	type m[3][3];
	mtrx<type> operator=(mtrx<type> b);
	mtrx<type> operator+(mtrx<type> b);
	mtrx<type> operator-(mtrx<type> b);
	mtrx<type> operator*(type b);
	mtrx<type> operator/(type b);
	mtrx<type> operator*(mtrx<type> b);
	mtrx<type> tr();
	type adj(int i, int j);
	type det();
	mtrx<type> inv();
	mtrx<type>()
	{
		int i;
		i = 0;
		while (i < 3)
		{
			int j = 0;
			while (j < 3)
			{
				m[i][j] = (type)0;
				j++;
			}
			i++;
		}
	}
};

template <class type>
mtrx<type> mtrx<type>::operator=(mtrx<type> b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[i][j] = b.m[i][j];
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::operator+(mtrx<type> b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[i][j] + b.m[i][j];
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::operator-(mtrx<type> b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[i][j] - b.m[i][j];
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::operator*(type b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[i][j] * b;
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> operator*(type b, mtrx<type> a)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = a.m[i][j] * b;
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::operator/(type b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[i][j] / b;
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::operator*(mtrx<type> b)
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = (type)0;
			int k = 0;
			while (k < 3)
			{
				res.m[i][j] = res.m[i][j] + m[i][k] * b.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
mtrx<type> mtrx<type>::tr()
{
	mtrx<type> res;
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			res.m[i][j] = m[j][i];
			j++;
		}
		i++;
	}
	return res;
}

template <class type>
type mtrx<type>::adj(int i, int j)
{
	type buf[4];
	int v = 0;
	int k = 0;
	while (k < 3)
	{
		int l = 0;
		while (l < 3)
		{
			if (k != i&&l != j) { buf[v] = m[k][l]; v++; }
			l++;
		}
		k++;
	}
	type d = (buf[0] * buf[3] - buf[1] * buf[2])*pow(-1, i + j);
	return d;
}

template <class type>
type mtrx<type>::det()
{
	type d = (type)0;
	int j = 0;
	int i = 0;
	while (j < 3)
	{
		d = d + m[i][j] * (this->adj(i, j));
		j++;
	}
	return d;
}

template <class type>
mtrx<type> mtrx<type>::inv()
{
	mtrx buf;
	int i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			buf.m[i][j] = this->adj(i, j);
			j++;
		}
		i++;
	}
	buf = (buf.tr()) / (this->det());
	return buf;
}

template <class type>
mtrx<type> operator/(mtrx<type> a, mtrx<type> b)
{
	return a*b.inv();
}

template <class type>
mtrx<type> operator/(type b, mtrx<type> a)
{
	return b*a.inv();
}

template <class type>
istream& operator >> (istream& str, mtrx<type>& A)
{
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			str >> A.m[i][j];
			if (str.fail())
			{
				str.clear();
				str.ignore();
			}
			j++;
		}
		i++;
	}
	return str;
}

template <class type>
ostream& operator << (ostream& str, mtrx<type> A)
{
	int i;
	i = 0;
	while (i < 3)
	{
		int j = 0;
		while (j < 3)
		{
			cout.precision(5);
			str << fixed << A.m[i][j] << " ";
			j++;
		}
		i++;
		str << endl;
	}
	return str;
}

template <class type>
void body()
{
	mtrx<type> a, b;
	int l;
	char fa[15];
	do
    {
	cout << "Choose source for the first matrix:\n1. .txt file\n2. console" << endl;
	l=0;
	cin >> l;
	cin.clear();
	cin.ignore();
        if (l == 1)
        {
            cout << "Print *name of file.txt" << endl;
            cin >> fa;
            ifstream fin(fa);
            if (fin)
                fin >> a;
            fin.close();
        }
        if (l == 2) cin >> a;
        if (l != 1 && l != 2) cout << "misclick" << endl;
    } while (!((l==1)||(l==2)));
	char fb[15];
	do
    {
	cout << "Choose source for second matrix:\n1. .txt file\n2. console" << endl;
	l=0;
	cin >> l;
	cin.clear();
	cin.ignore();
        if (l == 1)
        {
            cout << "Print *name of file.txt" << endl;
            cin >> fb;
            ifstream fin(fb);
            if (fin)
                fin >> b;
            fin.close();
        }
        if (l == 2) cin >> b;
        if (l != 1 && l != 2) cout << "misclick" << endl;
    } while (!((l==1)||(l==2)));
	int p = 1;
	while (p == 1)
	{
	    l=0;
		cout << "Choose option:\n1. a+b\n2. a-b\n3. a*b\n4. transp. b\n5. inverse b\n6. a/b\n7. det b\n8. show\save mtrx " << endl;
		cin >> l;
		mtrx <type>res;
		switch (l)
		{
		case 1:
			res = a + b;
			break;
		case 2:
			res = a - b;
			break;
		case 3:
			res = a*b;
			break;
		case 4:
			res = b.tr();
			break;
		case 5:
			if (b.det() != (type)0)
				res = b.inv();
			else cout << "zero det" << endl;
			break;
		case 6:
			if (b.det() != (type)0)
				res = a / b;
			else cout << "zero det" << endl;
			break;
		case 7:
			cout << b.det() << endl;
			break;
		case 8:
			cout << "choose path:\n1. file\n2. Console" << endl;
			int p;
			cin >> p;
			char fo[15];
			if (p == 1)
			{
				cout << "Print file name" << endl;
				cin >> fo;
				ofstream fin(fo);
				cout << "choose mtrx:\n1. a\n2. b" << endl;
				cin >> p;
				if (p == 1)
					fin << a;
				else fin << b;
				fin.close();
			}
			else
			{
				cout << "choose mtrx:\n1. a\n2. b" << endl;
				cin >> p;
				if (p == 1)
					cout << a;
				else cout << b;
			}
			break;
		default:
			cout << "misclick" << endl;
			break;
		}
		if (l != 7)
		{
			if (l != 8)
			{
				cout << "choose path:\n1. file\n2. Console" << endl;
				cin >> l;
				char fo[15];
				if (l == 1)
				{
					cout << "Print file name" << endl;
					cin >> fo;
					ofstream fin(fo);
					fin << res;
					fin.close();
				}
				else cout << res;
			}
		}
		if (b.det() != (type)0)
			cout << endl << "matrix B multiplied by inverted B"<<endl<< b*b.inv() << endl;
		cout << "print 1 to continue with the same matrix else print any sym." << endl;
		cin.clear();
		cin.ignore();
		cin >> p;
		if (p != 1) break;
	}
}

int main()
{
	int k;
	do
	{
		k = 0;
		int l;
		cout << "choose type:\n1. int\n2. double\n3. complex" << endl;
		cin >> l;
		cin.clear();
		cin.ignore();
		switch (l)
		{
		case 1:
			body<int>();
			break;
		case 2:
			body<double>();
			break;
		case 3:
			body<cmplx>();
			break;
		default: break;
		}
		cout << "print 1 to continue else print any sym." << endl;
		cin.clear();
        cin.ignore();
		cin >> k;
	} while (k == 1);
	return 0;
}
