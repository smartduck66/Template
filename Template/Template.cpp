//
// Book : Version du chapitre 19 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 30/06/2018 
// Commit en cours : Drill page 707
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"

#include<iostream>
#include<vector>
#include<string>
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

/*
template<typename T>		// Ne fonctionne pas
S& S<T>::operator=(const T& a)
{  
	if (this == &a) return *this;

	val = a;
	return *this;

}
*/

template<typename T>
void read_val(T& v)
{
	cout << "Saisir quelque chose puis Entrée : ";
	char s{};
	cin >> s;
	v = static_cast<T>(s);
	//cin >> v;
}

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

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
		read_val(s2);
		cout << s2.get() << endl;
						
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

