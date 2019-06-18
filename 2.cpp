#pragma once
#include <string>
#include <stdexcept>
using namespace std;
class Cipher
{
	int n;
	string getValidText(const string& s);
public:
	Cipher() = delete;
	Cipher(int key);
	string encrypt(const string& open_text);
//зашифрование
	string decrypt(const string&
	               cipher_text);//расшифрование
};
class Error: public invalid_argument
{
public:
	explicit Error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit Error (const char* what_arg):
		invalid_argument(what_arg) {}
};
#include "Cipher.h"
Cipher::Cipher(int key)
{
	if (key < 2)
		throw Error(string("Invalid key"));
	n = key;
}
string Cipher::encrypt(const string& open_text)
{
	int m = ((getValidText(open_text).size() - 1)/n + 1);
	char ** value = new char * [m];
	for (int i = 0; i < m; i++) {
		value[i] = new char [n];
	}
	//заполнение таблицы " "
	for (int i=0; i < m; i++)
		for (int j=0; j < n; j++)
			value[i][j] = '*';
//заполнение таблицы текстом
	for (int i = 0; i < getValidText(open_text).size(); i
	     ++)
		value[i/n][i%n] = getValidText(open_text)[i];
//вывод таблицы в строку
	string cipher_text;
	for (int i = n - 1; i >= 0; i --)
		for (int j = 0; j < m; j++)
			cipher_text = cipher_text + value[j][i];
	for (int i = 0; i < m; i++) {
		delete [] value[i];
	}
	delete [] value;
	return cipher_text;
}
string Cipher::decrypt(const string& cipher_text)
{
	int m = ((getValidText(cipher_text).size() - 1)/n +
	         1);
	char ** value = new char * [m];
	for (int i = 0; i < m; i++) {
		value[i] = new char [n];
	}
//заполнение таблицы " "
	for (int i=0; i < m; i++)
		for (int j=0; j < n; j++)
			value[i][j] = '*';
//заполнение таблицы текстом
	for (int i = 0; i < getValidText(cipher_text).size();
	     i ++)
		value[i%m][i/m] = getValidText(cipher_text)[i];
//вывод таблицы в строку
	string open_text;
	for (int i = 0; i < m; i ++)
		for (int j = n - 1; j >= 0; j--)
			open_text = open_text + value[i][j];
	for (int i = 0; i < m; i++) {
		delete [] value[i];
	}
	delete [] value;
	return open_text;
}
string Cipher::getValidText(const string& s)
{
	string tmp(s);
	if (s.empty())
		throw Error("Empty text");
	if (n >= s.size()) {
		throw Error(string("Too short string"));
	}
	for (auto c:tmp)
		if (!isalpha(c)) {
			throw Error(string("Invalid text"));
		}
	return tmp;
}
