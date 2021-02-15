#include <iostream>
#include <cstdio>
#include<fstream>
#include"forLib.h"

using namespace std;

const char* f_name = "PhoneBook_data.txt";
const char* f_interm = "intermediate.txt";

//"field" is "entry"

void add_entry(field book_field)
{
	ofstream out;
	out.open(f_name, ios::binary | ios::out | ios::app);
	out.seekp(0, ios::end);
	out.write((char*)&book_field, sizeof(field));
	out.close();
}

//void read_entry(field &res_field)
//{
//	ifstream in(f_name,ios::binary|ios::in); 
//	in.read((char*)&res_field, sizeof(field));
//	in.close(); 
//}

void find_entry_by_ind(int ind, field &res_field)
{
	ifstream fs;
	fs.open(f_name, ios::binary | ios::in);
	
	fs.seekg((ind * sizeof(field)), ios::beg);
	fs.read((char*)&res_field, sizeof(field));
	
	fs.close();
}

int get_number_of_fields()
{
	ifstream fs;
	fs.open(f_name, ios::binary | ios::in);
	fs.seekg(0, ios::end);
	int f_size = fs.tellg() / sizeof(field);
	fs.close();

	return f_size;
}

int find_by_surn(char search_input[], int n_of_entered_symbols)
{

	field checked_field;
	int checked_ind = 0;
	bool flag_if_fit = false;

	int n = get_number_of_fields();

	//cout << " size = " << n << endl;

	for(checked_ind=0;checked_ind<n;checked_ind++)
	{
		find_entry_by_ind(checked_ind, checked_field);
		flag_if_fit = true;
		for(int i=0;i<n_of_entered_symbols;i++)
		{
			if (search_input[i] != checked_field.surname[i])
			{
				flag_if_fit = false;
				break;
			}
		}
		if(flag_if_fit)
		{
			return checked_ind;
		}
		//checked_ind++;
	}

	return -1;
}

void renaming_cleaning_f()
{
	const char* f_interm_midddle = "intermediate_name.txt";

	rename(f_name, f_interm_midddle);
	rename(f_interm, f_name);
	rename(f_interm_midddle, f_interm);

	ofstream ofs_for_cleaning;
	ofs_for_cleaning.open(f_interm, std::ofstream::out | std::ofstream::trunc);
	ofs_for_cleaning.close();
}

void changing_field(int ind_changed, field new_field)
{
	int n = get_number_of_fields();
	field carry_field;

	ofstream out;
	out.open(f_interm, ios::binary | ios::out | ios::app);
	for(int i = 0;i<n;i++)
	{
		if (i != ind_changed)
			find_entry_by_ind(i, carry_field);
		else
			carry_field = new_field;
		out.seekp(0, ios::end);
		out.write((char*)&carry_field, sizeof(field));
		
	}

	out.close();

	renaming_cleaning_f();
}

void deleteing_entry(int del_ind)
{
	int n = get_number_of_fields();
	field carry_field;

	ofstream out;
	out.open(f_interm, ios::binary | ios::out | ios::app);
	for (int i = 0;i < n;i++)
	{
		if (i != del_ind)
		{
			find_entry_by_ind(i, carry_field);
			out.seekp(0, ios::end);
			out.write((char*)&carry_field, sizeof(field));
		}
	}

	out.close();

	renaming_cleaning_f();
}