#include <iostream>
#include<fstream>
#include<cstring>
#include"forLib.h"
#include <stdlib.h>

using namespace std;

const char* access_f = "Access_Data.txt";
const char* f_interm_ = "intermediate.txt";

char password[8];
const int passw_size = 8;

const int not_pressed = -99;
int smth_pressed = not_pressed;


void searching_number();
void admin_log_in();
void add_password_to_file();
void delete_passw_from_file();
void editing_the_contact(int ind_changed);
void deleting_the_contact(int ind_deleted);
void find_by_admin_contact_for_modifying();
void add_new_contact_to_book();
int help_find_contact_display_and_return_ind();
void help_find_passw_by_ind(int ind, char found_passw[]);
int help_finding_passw_file_size();
int help_find_passw_by_entered(char entered_password[]);
bool help_checking_the_access(char entered_passw[]);
void help_renaming_cleaning_passw_f();
void help_return_to_start();
void help_return_to_admin();



void start_menu()
{
	system("CLS");
	cout << "	WELCOME TO THE PHONE BOOK!" << endl;
	cout << "Choose one of the menu options by entering the appropriate number:" << endl;
	cout << "1. Search for the phone number." << endl;
	cout << "2. Log in as Administrator." << endl;
	cout << "3. Exit." << endl;
	cout << "Your choice: ";

	cin >> smth_pressed;

	switch(smth_pressed)
	{
	case 1:
		searching_number();
		break;
	case 2:
		admin_log_in();
		break;
	case 3:
		exit(0);
		break;
	default:
		start_menu();
		break;
	}
	
}

void admin_window()
{
	system("CLS");
	cout << " WELCOME TO ADMIN RIGHTS!" << endl;
	cout << "Choose one of the menu options by entering the appropriate number:" << endl;
	cout << "1. Add new Admin." << endl;
	cout << "2. Delete an Admin." << endl;
	cout << "3. Search for a number and modify it." << endl;
	cout << "4. Add new contact to the book." << endl;
	cout << "5. Exit to main menu." << endl;

	cout << "Your choice: ";
	smth_pressed = not_pressed;
	cin >> smth_pressed;
	switch (smth_pressed)
	{
	case 1:
		add_password_to_file();
		break;
	case 2:
		delete_passw_from_file();
		break;
	case 3:
		find_by_admin_contact_for_modifying();
		break;
	case 4:
		add_new_contact_to_book();
		break;
	case 5:
		start_menu();
		break;


	default:
		admin_window();
		break;
	}

}



void searching_number()
{
	help_find_contact_display_and_return_ind();

	help_return_to_start();
}

void admin_log_in()
{
	system("CLS");
	cout << "(after entering the access password, press 'Enter')" << endl;
	cout << "Enter the password to get admin access: ";
	char passw[passw_size];
	for (int i = 0;i < passw_size;i++)
		passw[i] = NULL;
	cin >> passw;

	if (help_checking_the_access(passw))
	{
		admin_window();
	}
	else
	{
		cout << "Admin access  denied!" << endl;
		help_return_to_start();
	}

}

void add_password_to_file()
{
	system("CLS");
	char the_new_passw[passw_size];
	cout << "Enter the new Admin access password (containing 8 characters) : ";
	//for (int i = 0;i < 8;i++)
		//cin >> new_password[i];
	cin >> the_new_passw;


	ofstream out;
	out.open(access_f, ios::binary | ios::out | ios::app);
	out.seekp(0, ios::end);
	out.write((char*)the_new_passw, sizeof(password));
	out.close();
	cout << endl << "[the new admin password is created]" << endl;

	help_return_to_admin();

}

void delete_passw_from_file()
{
	system("CLS");
	char searched_passw[passw_size];
	cout << "Enter the Admin access password to be deleted (containing 8 characters) : ";
	for (int i = 0;i < 8;i++)
		cin >> searched_passw[i];

	cout << endl << "deleting..." << endl;

	int res_ind = help_find_passw_by_entered(searched_passw);
	int n = help_finding_passw_file_size();

	if (res_ind != -1)
	{
		char carry_mas[passw_size];

		ofstream out;
		out.open(f_interm_, ios::binary | ios::out | ios::app);
		for (int i = 0;i < n;i++)
		{
			if (i != res_ind)
			{
				help_find_passw_by_ind(i, carry_mas);
				out.seekp(0, ios::end);
				out.write((char*)carry_mas, sizeof(password));
			}
		}

		out.close();

		help_renaming_cleaning_passw_f();

		cout << "The chosen Admin was deleted.";
	}
	else
	{
		cout << "Such Admin does not exist!";
	}
	
	help_return_to_admin();
}

void editing_the_contact(int ind_changed)
{
	field new_created_field;
	cout << "Enter the surname of the new contact: ";
	cin >> new_created_field.surname;
	new_created_field.len_of_surname = strlen(new_created_field.surname);
	cout << "Enter the number of the new contact (consisting of 10 digits): ";
	cin >> new_created_field.number;

	changing_field(ind_changed, new_created_field);

	cout << "The cantact was successfully edited." << endl;

	help_return_to_admin();
}

void deleting_the_contact(int ind_deleted)
{
	deleteing_entry(ind_deleted);

	cout << "The contact was deleted successfully." << endl;

	help_return_to_admin();
}

void find_by_admin_contact_for_modifying()
{
	system("CLS");
	int ind_cont_to_be_changed = help_find_contact_display_and_return_ind();

	cout << endl;
	if (ind_cont_to_be_changed != -1)
	{
		cout << "Choose the action what to do with the chosen contact:" << endl;
		cout << "1. Edit it." << endl;
		cout << "2. Delete it." << endl;
		cout << "3. Nothing." << endl;

		cout << "Your choice: ";
		smth_pressed = not_pressed;
		cin >> smth_pressed;

		switch (smth_pressed)
		{
		case 1:
			editing_the_contact(ind_cont_to_be_changed);
			break;
		case 2:
			deleting_the_contact(ind_cont_to_be_changed);
			break;
		case 3:
			break;
		default:
			cout << "[There was chosen an unexisting option.]" << endl;
			break;
		}

	}

	help_return_to_admin();

}

void add_new_contact_to_book()
{
	system("CLS");
	field new_added_field;
	cout << "Enter the surname of the new contact: ";
	cin >> new_added_field.surname;
	new_added_field.len_of_surname = strlen(new_added_field.surname);

	cout << "Enter the number of the new contact (consisting of 10 digits): ";
	cin >> new_added_field.number;

	add_entry(new_added_field);
	cout << "It was successfully added." << endl;

	help_return_to_admin();
}



int help_find_contact_display_and_return_ind()
{
	system("CLS"); //cleaning the console
	cout << "Enter the surname: ";

	char searched_surn[20];
	cin >> searched_surn;
	cout << endl;

	field res_field;
	int res_ind = find_by_surn(searched_surn, strlen(searched_surn));

	cout << "RESULT: " << endl;
	if (res_ind == -1)
		cout << "Not found." << endl;
	else
	{
		find_entry_by_ind(res_ind, res_field);
		cout << "Phone number: ";
		for (int i = 0;i < 10;i++)
			cout << res_field.number[i];
		cout << endl;
		cout << "Surname: ";
		for (int i = 0;i < res_field.len_of_surname;i++)
		{
			cout << res_field.surname[i];
		}
	}

	cout << endl;
	return res_ind;
}

void help_find_passw_by_ind(int ind, char found_passw[])
{
	ifstream fs;
	fs.open(access_f, ios::binary | ios::in);

	fs.seekg((ind * sizeof(password)), ios::beg);
	fs.read((char*)found_passw, sizeof(password));

	fs.close();
}

int help_finding_passw_file_size()
{
	ifstream fs;
	fs.open(access_f, ios::binary | ios::in);
	fs.seekg(0, ios::end);
	int f_size = fs.tellg() / sizeof(password);
	fs.close();
	return f_size;
}

int help_find_passw_by_entered (char entered_password[])
{
	int f_size = help_finding_passw_file_size();
	char checked_passw_in_file[passw_size];
	int checked_ind = 0;
	bool flag_if_fit = false;

	for (checked_ind = 0;checked_ind < f_size;checked_ind++)
	{
		help_find_passw_by_ind(checked_ind, checked_passw_in_file);
		flag_if_fit = true;
		for (int i = 0;i < passw_size;i++)
		{
			if (entered_password[i] != checked_passw_in_file[i])
			{
				flag_if_fit = false;
				//cout << "cought 'false' with checked symbol: " << checked_passw_in_file[i] << endl;
				break;
			}
		}
		if (flag_if_fit)
		{
			return checked_ind;
		}
		//checked_ind++;
	}

	return -1;	
}

bool help_checking_the_access(char entered_passw[])
{
	if (help_find_passw_by_entered(entered_passw) != -1)
		return true;
	else return false;
}

void help_renaming_cleaning_passw_f()
{
	const char* f_interm_midddle = "intermediate_name.txt";

	rename(access_f, f_interm_midddle);
	rename(f_interm_, access_f);
	rename(f_interm_midddle, f_interm_);

	ofstream ofs_for_cleaning;
	ofs_for_cleaning.open(f_interm_, std::ofstream::out | std::ofstream::trunc);
	ofs_for_cleaning.close();
}

void help_return_to_start()
{
	cout << endl;
	cout << "To return to the main menu, press 0: ";
	smth_pressed = not_pressed;
	cin >> smth_pressed;
	if (smth_pressed == 0)
	{
		start_menu();
	}
}

void help_return_to_admin()
{
	cout << endl;
	cout << "To return to the admin menu, press 0: ";
	smth_pressed = not_pressed;
	cin >> smth_pressed;
	if (smth_pressed == 0)
	{
		admin_window();
	}
}
