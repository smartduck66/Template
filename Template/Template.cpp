//
// Book : Version du chapitre 19 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 30/06/2018 
// Commit en cours : Exos page 708 à 710 - 03/07/2018
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"

#include<iostream>
#include<vector>
#include<string>
#include<typeinfo>
//#include<utility>

using namespace std;

inline void keep_window_open() // From "std_lib_facilities.h" of BS
{
	cin.clear();
	cout << "Please enter a character to exit\n";
	char ch;
	cin >> ch;
	return;
}

inline void keep_window_open(string s)
{
	if (s == "") return;
	cin.clear();
	cin.ignore(120, '\n');
	for (;;) {
		cout << "Please enter " << s << " to exit\n";
		string ss;
		while (cin >> ss && ss != s)
			cout << "Please enter " << s << " to exit\n";
		return;
	}
}


template<typename T> 
struct S { 

	S() = default;					// Constructeur par défaut
	
	S(T v) noexcept :val(v) {  }	// Constructeur générique

	T& get() { return val; }
	const T& get() const { return val; }

	void set(T v) { val = v; }
	S& operator=(const T& a) { val = a; return *this; }			// Copy Assignment
	//S& operator=(const T&);
		
	

private:
	T val;
};


// Ne fonctionne pas
/*
template<typename T>S& S<T>::operator=(const S& a)
{  
	if (this == &a) return *this;

	val = a;
	return *this;

}
*/

template<typename T>
void read_val(T& v)
{
	// Routine test non exhaustive : le cas string et vector ne sont pas gérés / De même, le test sur le typeid est laid
	cout << "Saisir quelque chose puis Entrée (typeid :"<<typeid(v).name()<<"): ";
	string s{};
	cin >> s;
	
	string ss = typeid(v).name();
	if (ss == "struct S<int>")
		v = stoi(s);
	else if (ss == "struct S<char>")
		v = s[0];
	else if (ss == "struct S<double>")
		v = stod(s);
	
}

template<typename T>
void f(vector<T>& d1, const vector<T>& d2)
{
	// Exo 1 page 708 : T& d1 sera modifié en sortie de fonction ; par contre, ce n'est pas le cas de d2 donc on le préfixe const
	// Pas de test sur la taille de d2<d1 => Contrat en C++20 : [[assert: size(d1) >= size(d2)]]
	for (unsigned int i=0; i < size(d1);i++) {
		d1[i] += d2[i];
		cout << d1[i] << ' ';
	}
	cout << endl;
}

template<typename T, typename U>
double fx(const vector<T>& vt, const vector<U>& vu)
{
	// Exo 2 page 708 : pas de modification des vecteurs, donc argument const - Passage par référence pour éviter la copie
	// Pas de test sur la taille de d2<d1 => Contrat en C++20 : [[assert: size(d1) >= size(d2)]]
	double sum = 0;
	for (unsigned int i = 0; i < size(vt); i++) {
		sum += vt[i] * vu[i];
	}
	return sum;
}

template<typename T, typename U>
struct Pair {
	// Exo 3 page 709
	
	Pair() = default;								// Constructeur par défaut

	Pair(T a, U b) noexcept :v1(a), v2(b) {  }		// Constructeur générique

	const T& get_v1() const { return v1; }			// Getters
	const U& get_v2() const { return v2; }

	// ostream& operator<<(ostream& os, const Pair& p) { return os << '(' << p.get_v1() << ',' << p.get_v2() << ')'; } // Ne fonctionne pas

private:
	T v1;
	U v2;
		
};

template<typename T>
class Number {
public:
	Number() = default;					// Constructeur par défaut

	Number(T v) noexcept :nb(v) {  }	// Constructeur générique

	T& get() { return nb; }
	const T& get() const { return nb; }

	void set(T v) { nb = v; }


private:
	T nb;

};

template<typename T>
double operator+(const Number<T>& a, const Number<T>& b)
{

	return a.get() + b.get();

}

template<typename T>
double operator-(const Number<T>& a, const Number<T>& b)
{

	return a.get() - b.get();

}

template<typename T>
double operator*(const Number<T>& a, const Number<T>& b)
{

	return a.get() * b.get();

}

template<typename T>
double operator/(const Number<T>& a, const Number<T>& b)
{
	// Attention : le retour perd la décimale si les deux opérandes sont integer
	return a.get() / b.get();

}

template<typename T>
double operator%(const Number<T>& a, const Number<T>& b)
{
	// Attention : compile seulement si les deux nombres son entiers
	return a.get() % b.get();

}

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// Drill page 707
		S<int> s1 = 1;
		S<char> s2 = 'a';
		S<double> s3 = 1.1;
		S<string> s4 { "andré" };
		S<vector<int>> s5 {};

		s4.set("Bertrand");
		string s = s4.get();
		cout << s << endl;
		s4 = "Jean";
		s = s4.get();
		cout << s << endl;
		string ss = "Jules";
		s4 = ss;
		s = s4.get();
		cout << s << endl;
		s2 = 'c';
		char si = s2.get();
		cout << si << endl;

		// Lecture d'un char à partir de cin
		//read_val(s2);
		//cout << s2.get() << endl;
						
		// Exo n°1 page 708 *******************************
		vector <int> v1{ 1,2,3,4,5 };
		vector <int> v2{ 1,2,3,4,5 };
		f(v1, v2);
		
		vector <double> v1bis{ 1.5,2.5,3.5,4.5,5.5 };
		vector <double> v2bis{ 1.5,2.5,3.5,4.5,5.5 };
		f(v1bis, v2bis);

		vector <string> v1ter{ "a","b","c","d","e","f","g" };
		vector <string> v2ter{ "h","i","j","k","l","m","n" };
		f(v1ter, v2ter);

		// Exo n°2 page 708 *******************************
		vector <int> vt{ 1,2,3,4,5 };
		vector <int> vu{ 1,2,3,4,5 };
		cout << "La somme de vt * vu (int) est égale à "<<fx(vt, vu)<<endl;

		vector <double> vtbis{ 1.5,2.5,3.5,4.5,5.5 };
		vector <double> vubis{ 1.5,2.5,3.5,4.5,5.5 };
		cout << "La somme de vt * vu (double) est égale à " << fx(vtbis, vubis) << endl;

		vector <int> vtter{ 1,2,3,4,5 };
		vector <double> vuter{ 1.5,2.5,3.5,4.5,5.5 };
		cout << "La somme de vt * vu (int*double) est égale à " << fx(vtter, vuter) << endl;

		// Exo n°3 page 708 *******************************
		Pair p1{ 1,2 };
		Pair p2{ 1.5,2 };
		Pair p3{ 'a',3 };
		Pair p4{ "coco",'z' };

		cout << p1.get_v1() << ',' << p1.get_v2() << ','<<p2.get_v1() << ',' << p2.get_v2()<< ',' << p3.get_v1() << ',' << p3.get_v2()<< ',' 
			<< p4.get_v1() << ',' << p4.get_v2() << endl;

		
		// Exos n°5&6&7 page 709
		Number xx { 3.5 };
		Number yy { 2.5 };
		cout << xx + yy << endl;
		cout << xx - yy << endl;
		cout << xx * yy << endl;
		cout << xx / yy << endl;
		//cout << xx % yy << endl;
		vector <Number<double>> vtN{ 1,2,3,4,5 };
		vector <Number<double>> vuN{ 1.1,2.2,3.3,4.4,5.5 };
		cout << "La somme de vt * vu (Number) est égale à " << fx(vtN, vuN) << endl; // Attention : si les deux types précédents ne sont pas identiques, la compilation échoue !


		keep_window_open();

		return 0;
	}
	/*
	catch (XXXXXXX::Invalid&)
	{
	cerr << "error: ???????????????????? ! \n";
	keep_window_open("q");	// For some Windows(tm) setup
	return 1;
	}
	*/

	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}

