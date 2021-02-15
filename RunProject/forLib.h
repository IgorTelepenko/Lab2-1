#pragma once
const int phone_numb_len = 10;

struct field
{
	char surname[20];
	char number[10];
	int len_of_surname;

	field()
	{
		for (int i = 0;i < 20;i++)
			surname[i] = NULL;
		for(int i=0;i<10;i++)
		{
			number[i] = NULL;
		}
	}
};



void add_entry(field book_field);
void find_entry_by_ind(int ind, field &res_field);
int find_by_surn(char search_input[], int n_of_entered_symbols);
void changing_field(int ind_changed, field new_field);
void deleteing_entry(int del_ind);

void start_menu();
