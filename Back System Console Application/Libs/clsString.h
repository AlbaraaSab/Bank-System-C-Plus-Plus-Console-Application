#pragma once
#include <iostream>
#include <vector>

using namespace std;

enum enWhatToCount { SmallLetters = 0, CapitalLetters = 1, All = 2 };

class clsString
{
private:
	string _Value;

public:

	clsString()
	{
		_Value = "";
	}

	clsString(string value)
	{
		_Value = value;
	}

	void setValue(string value)
	{
		_Value = value;
	}

	string getValue()
	{
		return _Value;
	}

	__declspec(property(get = getValue, put = setValue)) string Value;


	static short CountWords(string st)
	{
		short counter = 0;
		string delmi = " ";
		short pos = 0;
		string sWord;

		while ((pos = st.find(delmi)) != std::string::npos)
		{
			sWord = st.substr(0, pos);

			if (sWord != "")
			{
				counter++;
			}
			st.erase(0, pos + delmi.length());
		}

		if (st != "")
		{
			counter++;
		}

		return counter;
	}

	short CountWords()
	{
		return CountWords(_Value);
	}

	static string ConvertStringCharactersCase(string st)
	{
		for (int i = 0; i < st.length(); i++)
		{
			isupper(st[i]) ? st[i] = tolower(st[i]) : st[i] = toupper(st[i]);
		}
		return st;
	}

	void ConvertStringCharactersCase()
	{
		_Value = ConvertStringCharactersCase(_Value);
	}

	static string CovertStringToUpperCase(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			str[i] = toupper(str[i]);
		}
		return str;
	}

	static string ConvertFirstLetterOfStringCapital(string str)
	{
		for (int i = 0; i < str.length(); i++)
		{
			if (i == 0)
			{
				str[i] = toupper(str[i]);
				break;
			}
		}
		return str;
	}

	static short CountLetters(string st, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		short counter = 0;

		if (WhatToCount == enWhatToCount::All)
		{
			return st.length();
		}


		for (short i = 0; i < st.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(st[i]))
			{
				counter++;
			}
			if (WhatToCount == enWhatToCount::SmallLetters && islower(st[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_Value, WhatToCount);
	}

	static short CountSpecificLetterInString(string st, char c, bool MatchCase = true)
	{
		short counter = 0;

		if (MatchCase)
		{
			for (short i = 0; i < st.length(); i++)
			{
				if (st[i] == c)
					counter++;
			}
		}
		else
		{
			for (short i = 0; i < st.length(); i++)
			{
				if (tolower(st[i]) == tolower(c))
				{
					counter++;
				}
			}
		}

		return counter;
	}

	short CountSpecificLetterInString(char c , bool MatchCase = true)
	{
		return CountSpecificLetterInString(_Value, c, MatchCase);
	}

	static bool IsVowel(char c)
	{
		char ch = tolower(c);
		return (ch == 'a' || ch == 'e' || ch == 'u' || ch == 'i' || ch == 'o');
	}

	static short CountVowels(string st)
	{
		short counter = 0;
		for (short i = 0; i < st.length(); i++)
		{
			if (IsVowel(st[i]))
			{
				counter++;
			}
		}
		return counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	void PrintVowels(string st)
	{
		short counter = 0;
		for (short i = 0; i < st.length(); i++)
		{
			if (IsVowel(st[i]))
			{
				cout << st[i] << "\t";
			}
		}
	}

	void PrintVowels()
	{
		short counter = 0;
		for (short i = 0; i < _Value.length(); i++)
		{
			if (IsVowel(_Value[i]))
			{
				cout << _Value[i] << "\t";
			}
		}
	}

	static vector<string> Split(string st, string Delmi)
	{
		vector<string> vWord;
		short pos = 0;
		string sWord;

		while ((pos = st.find(Delmi)) != std::string::npos)
		{
			sWord = st.substr(0, pos);

			if (sWord != "")
			{
				vWord.push_back(sWord);
			}
			st.erase(0, pos + Delmi.length());
		}

		if (st != "")
		{
			vWord.push_back(st);
		}
		return vWord;
	}

	vector<string> Split(string Delmi)
	{
		return Split(_Value, Delmi);
	}

	static void PrintSplitedString(vector<string> words)
	{
		for (string& word : words)
		{
			cout << word << endl;
		}
	}

	static string TrimLeft(string st)
	{
		for (int i = 0; i < st.length(); i++)
		{
			if (st[i] != '-')
			{
				return st.substr(i, st.length() - 1);
			}
		}
		return "";
	}

	string TrimLeft()
	{
		return TrimLeft(_Value);
	}

	static string TrimRight(string st)
	{
		for (int i = st.length() - 1; i >= 0; i--)
		{
			if (st[i] != '-')
			{
				return st.substr(0, i + 1);
			}
		}
		return "";
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string st)
	{
		return TrimLeft(TrimRight(st));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	static string JoinString(vector<string> Words, string Delmi)
	{
		string sentence = "";

		for (string& word : Words)
		{
			sentence += word + Delmi;
		}

		return sentence.substr(0, sentence.length() - Delmi.length());

	}

	static string JoinString(string Words[], short l, string Delmi)
	{
		string sentence = "";

		for (short i = 0; i < l; i++)
		{
			sentence += Words[i] + Delmi;
		}

		return sentence.substr(0, sentence.length() - Delmi.length());

	}

	static string ReverseWordsInString(string st)
	{
		vector<string> vString;
		string S1;

		vString = Split(st, " ");

		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;
			S1 += *iter + " ";
		}

		S1 = S1.substr(0, S1.length() - 1);
		return S1;
	}

	string ReverseWordsInString()
	{
		return ReverseWordsInString(_Value);
	}

	static string ReplaceWordInString(string st, string searchedWord, string replaceWord)
	{
		vector<string> vString = Split(st, " ");

		string newString = "";

		vector<string>::iterator iter = vString.begin();

		while (iter != vString.end())
		{
			if (*iter != searchedWord)
				newString += *iter + " ";
			else
				newString += replaceWord + " ";
			iter++;
		}

		return newString.substr(0, newString.length() - 1);
	}

	string ReplaceWordInString(string searchedWord, string replaceWord)
	{
		return ReplaceWordInString(_Value, searchedWord, replaceWord);
	}

	static string RemoveAllPunctuation(string st)
	{
		string str = "";

		for (int i = 0; i < st.length(); i++)
		{
			if (!ispunct(st[i]))
			{
				str += st[i];
			}
		}
		return str;
	}

	string RemoveAllPunctuation()
	{
		return RemoveAllPunctuation(_Value);
	}

};

