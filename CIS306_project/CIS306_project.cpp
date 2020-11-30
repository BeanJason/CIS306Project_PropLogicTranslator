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
	vector<string> statements(1);

	//strings for the parts of our equation
	string p;
	string q;
	string s;
	string r;

	//read in our data from our file and store it in the statements vector
	readfile(statements);
	cout << "statements at 1 " << endl << statements.at(1) << endl << endl;

	convertStatement(statements.at(1), p, q, s, r);


	system("pause");
	return 0;
}

void readfile(vector<string>& statements)
{
	ifstream inputFile;
	string LineOfText;
	string fileName;
	string statement;

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
		//output << "file open" << endl;


		//cout << LineOfText << endl;

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
	vector<string> separatedStatement(1);
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

	//fill a vector with the position of each condition
	for (int i = 0; i < separatedStatement.size(); i++)
	{
		if (separatedStatement.at(i) == "and" || separatedStatement.at(i) == "or" || separatedStatement.at(i) == "then" || separatedStatement.at(i) == "If")
		{
			positionFound.push_back(i);
		}
	}


	//now that we have a value for each position of the conditions we can start adding words to each of our strings
	//start by looping through our entire statement
	//next if we land on one of the poitions of a condition begin another for loop to add the words from our last postion to i
	//keep track of where we left off with the stopPos variable so we know where to begin in the next iteration
	for (int i = 0; i <= separatedStatement.size(); i++)
	{
		if (i == positionFound.at(1))
		{
			for (int j = 0; j < i; j++)
			{
				p += separatedStatement.at(j);
				p += " ";
			}
			stopPos = i + 1;
		}
		else if (i == positionFound.at(2))
		{
			for (int j = stopPos; j < i; j++)
			{
				q += separatedStatement.at(j);
				q += " ";
			}
			stopPos = i + 1;
		}
		else if (i == positionFound.at(3))
		{
			for (int j = stopPos; j < i; j++)
			{
				r += separatedStatement.at(j);
				r += " ";
			}
			stopPos = i + 1;
		}
		else if (i == separatedStatement.size())
		{
			for (int j = stopPos; j < i; j++)
			{
				s += separatedStatement.at(j);
				s += " ";
			}
			stopPos = i + 1;
		}
	}


	cout << "p = " << p << endl;
	cout << " q = " << q << endl;
	cout << "r = " << r << endl;
	cout << " s = " << s << endl;

	return ":p";
}