/* Напишите программу, которая вычисляет среднее арифметическое вводимой пользователем с клавиатуры 
последовательности дробных чисел. */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>  // для превращения строки в число

using std::cout; using std::cin; using std::endl;
using std::vector; using std::string;

// пытается превратить строку в число, выдаёт false, если не получилось
inline bool is_number(const string& str, double& number)
{
	std::istringstream istream(str);
	return (istream >> number) ? true : false;
}

// создаёт вектор дробных чисел из строки, введённой пользователем
vector<double> create_array_from_string(const string& users_input)
{
	vector<double> array{};
	string future_number{}; // будущее число в виде строки
	unsigned short points_in_number{ 0 }; // количество точек в будущем числе

	// будем собирать каждое число по символам-цифрам, каждый пробел добавляем число в массив и начинаем заново
	for (unsigned int i = 0; i < users_input.length(); i++)
	{
		// если после пробела знак минус или просто число или первая точка
		if (((future_number == "") && (users_input[i] == '-')) 
			  || (isdigit(users_input[i])) 
			  || ((users_input[i] == '.') && (points_in_number == 0)))
		{ 
			future_number.push_back(users_input[i]);
			if (users_input[i] == '.') 
				points_in_number++;
		}
		// если пробел или конец строки
		if ((users_input[i] == ' ') || (i == (users_input.length() - 1)))
		{
			double one_more_number{ 0 };
			if (is_number(future_number, one_more_number))
				array.push_back(one_more_number);
			future_number = "";
			points_in_number = 0;
		}
	}
	return array;
}

// получаем от пользователя последовательность чисел и, возможно, не только числа в виде строки
string get_users_input()
{
	cout << "Вводите последовательность  дробных чисел через пробел\n"
		 << "для разделения целой и дробной части используйте точку, прочие знаки и лишние точки будут проигнорированы\n"
		 << "для окончания ввода нажмите enter: ";
	string input;
	getline(cin, input);
	return input;
}

// вывод на экран среднего арифметического для последовательности
void print_average(const vector<double>& array)
{
	if (array.size() == 0)
		cout << "В последовательности нет чисел" << endl;
	else
	{
		double summ{ 0 };
		for (const auto& one_number : array)
			summ += one_number;
		cout << "Среднее арифметическое введённой последовательности: " << summ / array.size() << endl;
	}
}

int main()
{
	setlocale(LC_CTYPE, "rus"); // подключаем кириллицу:

	vector<double> array = create_array_from_string(get_users_input());
	print_average(array);

	return 0;
}
