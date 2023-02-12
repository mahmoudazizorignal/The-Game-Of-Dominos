/*
 * Assignment 1 - OOP - problem 5 in sheet 1 
 * 		Game Idea: The program find if it possible to build a chain consisting of every domino
 *  
 * This code is written by Mahmoud Mamdouh a student at Faculty of Computer Science - Cairo University
 * 		copyright © Mahmoud Mamdouh Abdelaziz
 */




#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct dominoT 
{
	int leftDots;
	int rightDots;
};

ostream& operator<< (ostream& COUT, const dominoT& domino);
bool FormsDominoChain(vector<dominoT>& dominos);
bool FindSolution(vector<dominoT>& Form, vector<dominoT>& rst);

int main()
{
	vector<dominoT> dominos = { dominoT{1, 4}, dominoT{2, 6},
	dominoT{4, 4}, dominoT{6, 1}, dominoT{4, 3} };

	if (FormsDominoChain(dominos)) {
		for (int i = 0; i < dominos.size(); i++)
		{
			cout << dominos[i];
			if(i + 1 < dominos.size()) cout << " - ";
		}
		cout << endl;
	}
	else {
		cout << "NO SOLUTION POSSIBLE!\n";
	}
	return 0;
}


bool FormsDominoChain(vector<dominoT>& dominos)
{
	vector<dominoT> tmp;

	if (FindSolution(tmp, dominos)) {
		dominos = tmp;
		return true;
	}
	return false;
}

bool FindSolution(vector<dominoT>& Form, vector<dominoT>& rst)
{
	if (rst.empty())
	{
		for (int i = 0; i < Form.size() - 1; i++)
		{
			if (Form[i].rightDots != Form[i + 1].leftDots) return false;
		}
		return true;
	}

	for (int i = 0; i < rst.size(); i++)
	{
		dominoT Ttmp = rst[i];
		Form.push_back(Ttmp);
		rst.erase(rst.begin() + i);

		if (FindSolution(Form, rst)) return true;

		Form.pop_back();
		Form.push_back(dominoT{ Ttmp.rightDots, Ttmp.leftDots });

		if (FindSolution(Form, rst)) return true;

		Form.pop_back();
		rst.insert(rst.begin() + i, Ttmp);
	}

	return false;
}

ostream& operator<< (ostream& COUT, const dominoT& domino)
{
	COUT << domino.leftDots << "|" << domino.rightDots;
	return COUT;
}