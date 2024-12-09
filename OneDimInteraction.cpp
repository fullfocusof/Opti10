#include "OneDimInteraction.h"

void printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

float OneDimInteraction::getFuncValue(float x)
{
	return x * exp(-(pow(x, 2) / 2));
}

void OneDimInteraction::ScanMethod()
{
	vector<pair<float, float>> table;
	float a, b, eps, h;
	cout << "Введите границы отрезка и точность через пробел: ";
	cin >> a >> b >> eps;

	h = eps / 10;
	for (float x = a; x <= b; x += h)
	{
		float y = getFuncValue(x);
		table.push_back(make_pair(x, y));
	}

	auto max_it = max_element(table.begin(), table.end(),
		[](const pair<float, float>& a, const pair<float, float>& b) 
		{
			return a.second < b.second;
		});

	auto min_it = min_element(table.begin(), table.end(),
		[](const pair<float, float>& a, const pair<float, float>& b) 
		{
			return a.second < b.second;
		});

	system("cls");
	cout << "Значение x\tЗначение y\tТочность = " << eps << endl;

	int size = table.size();
	for (int i = 0; i < size; i++)
	{
		if (table[i] == *max_it) cout << setprecision(3) << table[i].first << "\t" << setw(15) << table[i].second << setw(10) << "\t<-max" << endl;
		else if (table[i] == *min_it) cout << setprecision(3) << table[i].first << "\t" << setw(15) << table[i].second << setw(10) << "\t<-min" << endl;
		else cout << setprecision(3) << table[i].first << "\t" << setw(15) << table[i].second << endl;
	}

	cout << endl << "Количество подсчетов = " << size;
}

void OneDimInteraction::ScanMethodVar()
{
	vector<pair<float, float>> table;
	float a, b, eps, h, maxValue;
	int n;
	cout << "Введите границы отрезка, точность и количество разрезов через пробел: ";
	cin >> a >> b >> eps >> n;

	h = eps / 10;
	maxValue = getFuncValue(a);
	for (float x = a; x < b; x += h)
	{
		float y = getFuncValue(x);
		table.push_back(make_pair(x, y));

		if (y > maxValue)
		{
			maxValue = y;
			h /= 2;
		}
		else h = eps / 10;
	}

	auto max_it = max_element(table.begin(), table.end(),
		[](const pair<float, float>& a, const pair<float, float>& b)
		{
			return a.second < b.second;
		});

	auto min_it = min_element(table.begin(), table.end(),
		[](const pair<float, float>& a, const pair<float, float>& b)
		{
			return a.second < b.second;
		});

	system("cls");
	cout << "Значение x\tЗначение y\tТочность = " << eps << endl;

	int size = table.size();
	for (int i = 0; i < size; i++)
	{
		if (table[i] == *max_it) cout << table[i].first << "\t" << setw(20) << table[i].second << setw(10) << "\t<-max" << endl;
		else if (table[i] == *min_it) cout << table[i].first << "\t" << setw(20) << table[i].second << setw(10) << "\t<-min" << endl;
		else cout << table[i].first << "\t" << setw(20) << table[i].second << endl;
	}

	cout << endl << "Количество подсчетов = " << size;
}

void OneDimInteraction::DichotomyMethod()
{
	vector<vector<float>> table;
	float a, b, eps, d;
	cout << "Введите границы отрезка, точность и параметр метода: ";
	cin >> a >> b >> eps >> d;

	while (b - a > eps)
	{
		vector<float> temp;
		float x1 = (a + b - d) / 2, x2 = (a + b + d) / 2;
		float fx1 = getFuncValue(x1), fx2 = getFuncValue(x2);

		if (fx1 <= fx2) a = x1;
		else b = x2;

		temp.push_back(x1);
		temp.push_back(x2);
		temp.push_back(fx1);
		temp.push_back(fx2);
		table.push_back(temp);
	}

	float xTarget = (a + b) / 2;
	float yTarget = getFuncValue(xTarget);

	system("cls");
	cout << "Значение x1\tЗначение x2\tЗначение f(x1)\tЗначение f(x2)\tТочность = " << eps << endl;

	int size = table.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			cout << setw(10) << table[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl << "Количество подсчетов = " << size << endl;
	cout << "Абсцисса точки максимума = " << xTarget << endl;
	cout << "Значение функции в точке максимума = " << yTarget;
}

void OneDimInteraction::GoldenRatioMethod()
{
	vector<vector<float>> table;
	float a, b, eps, k1 = (3-sqrt(5)) / 2, k2 = (sqrt(5) - 1) / 2;
	cout << "Введите границы отрезка и точность: ";
	cin >> a >> b >> eps;

	float x1 = a + k1 * (b - a), x2 = a + k2 * (b - a);
	float fx1 = getFuncValue(x1), fx2 = getFuncValue(x2);

	vector<float> temp = { x1, x2, fx1, fx2 };
	table.push_back(temp);

	while (b - a >= eps)
	{
		if (fx1 > fx2)
		{
			b = x2;
			x2 = x1;
			x1 = a + k1 * (b - a);
			fx2 = fx1;
			fx1 = getFuncValue(x1);
			temp = { x1, x2, fx1, fx2 };
			table.push_back(temp);
		}
		else
		{
			a = x1;
			x1 = x2;
			x2 = a + k2 * (b - a);
			fx1 = fx2;
			fx2 = getFuncValue(x2);
			temp = { x1, x2, fx1, fx2 };
			table.push_back(temp);
		}
	}

	float xTarget = (a + b) / 2;
	float yTarget = getFuncValue(xTarget);

	system("cls");
	cout << "Значение x1\tЗначение x2\tЗначение f(x1)\tЗначение f(x2)\tТочность = " << eps << endl;

	int size = table.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < table[i].size(); j++)
		{
			cout << setw(10) << table[i][j] << "\t";
		}
		cout << endl;
	}

	cout << endl << "Количество подсчетов = " << size << endl;
	cout << "Абсцисса точки максимума = " << xTarget << endl;
	cout << "Значение функции в точке максимума = " << yTarget;
}