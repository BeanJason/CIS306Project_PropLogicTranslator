// CIS306_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "string"
#include "fstream"
#include "vector"

using namespace std;

void readfile(vector<string>&);
string convertStatement(string, string&, string&, string&, string&);

int main()
{
	//declare a vector called statements and initialize it with a size of 1
	vector<string> statements;

	//strings for the parts of our equation
	string p;
	string q;
	string s;
	string r;
	

	//read in our data from our file and store it in the statements vector
	readfile(statements);

	for (int i = 0; i < statements.size(); i++)
	{
		p = "";
		q = "";
		s = "";
		r = "";

		cout << endl;
		cout << "statements at " << i << endl << statements.at(i) << endl << endl;

		convertStatement(statements.at(i), p, q, s, r);
	}
	


	system("pause");
	return 0;
}

void readfile(vector<string>& statements)
{
	ifstream inputFile;
	string LineOfText;
	string fileName;
	string statement;

	string temp;

	//int delimPos;
	int numData = 0;
	int lineNum = 0;

	cout << "Please enter the name of input file: " << endl;
	cin >> fileName;



	inputFile.open(fileName);


	//scan through file and store each expression on each line to element in 'Expression' array
	if (inputFile)
	{
		cout << "file open" << endl;
		

		//get data on each line, store LineOfText in element, repeat until last line
		while (getline(inputFile, LineOfText)) {
			//data[lineNum] = LineOfText;
			statements.push_back(LineOfText);
			lineNum++;
			numData++;
		}
		inputFile.close();
	}
	else
	{
		cout << "Error file not found" << endl;
		//output << "Error file not found" << endl;
	}

	if (numData == 0)
	{
		cout << "Error File Empty" << endl;
	}
}

string convertStatement(string statement, string& p, string& q, string& r, string& s)
{
	//store statement as individual words
	vector<string> separatedStatement;
	string word = "";
	int size = 0;
	int lastSpacePosition = 0;
	int counter = 0;
	string convertedStatement;

	bool thenFound = false;
	bool conditionFound = false;
	vector<string> statementPart1;
	vector<string> statementPart2;

	vector<int> positionFound;
	int stopPos;

	bool firstRun = false;
	bool secondRun = false;
	bool thirdRun = false;
	bool fourthRun = false;
	int pos = 0;

	vector<string> operation;
	vector<string> newStatement;
	string temp;

	p = "";
	q = "";
	r = "";
	s = "";

	//code to separate our statement into separate words to make it easier to translate
	//scan through statement, if we find a space push our word to our separatedStatement vector else if the next char is a letter add it to our word
	//Keep track of our last space position so that after the for loop we can add the last word to our vector
	for (int i = 0; i < statement.length(); i++)
	{
		if (statement.at(i) == ' ')
		{
			separatedStatement.push_back(word);
			word = "";
			lastSpacePosition = i;
		}
		else
		{
			word += statement.at(i);
		}
	}

	separatedStatement.push_back(statement.substr(lastSpacePosition, statement.length()));

	if (separatedStatement.at(0) == "If")
	{
		separatedStatement.erase(separatedStatement.begin());

		while (!separatedStatement.empty())
		{
			if (separatedStatement.at(0) == "and" || separatedStatement.at(0) == "or" || separatedStatement.at(0) == "then")
			{
				operation.push_back(separatedStatement.at(0));
				newStatement.push_back(temp);
				temp = "";
			}
			else
			{
				temp += separatedStatement.at(0);
				temp += " ";
			}
			separatedStatement.erase(separatedStatement.begin());
		}
		newStatement.push_back(temp);
		temp = "";
	}
	else
	{
		cout << "Error not an If statement" << endl;
	}

	for (int i = 0; i < operation.size(); i++)
	{
		if (operation.at(i) == "and")
		{
			operation.at(i) = "&";
		}
		else if (operation.at(i) == "or")
		{
			operation.at(i) = "V";
		}
		else if (operation.at(i) == "then")
		{
			operation.at(i) = "->";
		}
	}

	if (newStatement.size() == 1)
	{
		p = newStatement.at(0);

		cout << "p = " << p << endl;

		cout << "converted statement = " << " p " << endl;
	}
	else if (newStatement.size() == 2)
	{
		p = newStatement.at(0);
		q = newStatement.at(1);

		cout << "p = " << p << endl;
		cout << " q = " << q << endl;

		cout << "converted statement = " << " p " << operation.at(0) << " q " << endl;
	}
	else if (newStatement.size() == 3)
	{
		p = newStatement.at(0);
		q = newStatement.at(1);
		r = newStatement.at(2);

		cout << "p = " << p << endl;
		cout << " q = " << q << endl;
		cout << "r = " << r << endl;

		cout << "converted statement = " << " p " << operation.at(0) << " q " << operation.at(1) << " r " << endl;
	}
	else if (newStatement.size() == 4)
	{
		p = newStatement.at(0);
		q = newStatement.at(1);
		r = newStatement.at(2);
		s = newStatement.at(3);

		cout << "p = " << p << endl;
		cout << " q = " << q << endl;
		cout << "r = " << r << endl;
		cout << " s = " << s << endl;

		cout << "converted statement = " << " p " << operation.at(0) << " q " << operation.at(1) << " r " << operation.at(2) << " s " << endl;
	}

	


	return ":p";
}