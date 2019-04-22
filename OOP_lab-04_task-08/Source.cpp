#include <iostream> 
using namespace std;
#define len 20

class game {
private:
	char game_name[20];
protected: 
	char* strcpy(char* destination, const char* source);
public:
	void SetName(char* game_name);
	const char* GetName() const;
};

class checkers : public game {
private:
	char imit_game_name[20];
	double figure_weight;
	double board_weight;
public:
	void SetImitName(char* local_name);
	void ShowAllImit();
	void SetFigureWeight(double figure_weight);
	void SetBoardWeight(double board_weight);
	double GetFigureWeight(checkers &obj);
	double GetBoardWeight(checkers &obj);
	friend void quick_object(checkers items[], int count);
	friend void qs_obj(checkers items[], int left, int right);
	friend double WeightSum(checkers items[], int count);
};

int main()
{
	const int arr_size = 4;
	checkers arr[arr_size];
	char temp_name[20];
	double temp_board_weight;
	double temp_figure_weight;
	register int i = 0;
	for (i = 0; i < arr_size; i++)
	{
		cout << "Input name of game" << endl;
		cin >> temp_name;
		arr[i].SetImitName(temp_name);
		cout << "input board weight" << endl;
		cin >> temp_board_weight;
		arr[i].SetBoardWeight(temp_board_weight);
		cout << "input figure weight" << endl;
		cin >> temp_figure_weight;
		arr[i].SetFigureWeight(temp_figure_weight);
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	qs_obj(arr, 0, arr_size);
	for (i = 0; i < arr_size; i++)
	{
		cout << "Name of game is " << arr[i].GetName() << endl;
		cout << "Board weight is " << arr[i].GetBoardWeight(arr[i]) << endl;
		cout << "Figure weight is " << arr[i].GetFigureWeight(arr[i]) << endl;
		cout << "------------------" << endl;
	}
	cout << " Sum of all weights = " << WeightSum(arr, arr_size) << endl;
	system("pause");
	return 0;
}

void game::SetName(char* game_name)
{
	strcpy(this->game_name, game_name);
}

const char* game::GetName() const {
	//cout << this->game_name << endl;
	return this->game_name;
}

char* game::strcpy(char* destination, const char* source)
{
	if (destination == NULL)
		return NULL;
	char *ptr = destination;
	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return ptr;
}

void checkers::SetImitName(char* local_name)
{
	SetName(local_name);
	strcpy(imit_game_name, this->GetName());
}

void checkers::ShowAllImit() {
	GetName();
}

void checkers::SetFigureWeight(double figure_weight)
{
	this->figure_weight = figure_weight;
}

void checkers::SetBoardWeight(double board_weight)
{
	this->board_weight = board_weight;
}

double checkers::GetFigureWeight(checkers &obj)
{
	return this->figure_weight;
}

double checkers::GetBoardWeight(checkers &obj)
{
	return this->board_weight;
}

void quick_object(checkers items[], int count)
{
	qs_obj(items, 0, count - 1);
}

void qs_obj(checkers items[], int left, int right)
{
	register int i, j;
	double x;
	checkers temp;
	i = left; j = right + 1;
	x = items[(left + right) / 2].GetFigureWeight(items[(left + right) / 2]);
	do {
		while ((items[i].GetFigureWeight(items[i]) > x) && (i < right)) i++;
		while ((x > items[j].GetFigureWeight(items[i])) && (j > left)) j--;
		if (i <= j) {
			temp = items[i];
			items[i] = items[j];
			items[j] = temp;
			i++; j--;
		}
	} while (i <= j);
	if (left < j) qs_obj(items, left, j);
	if (i < right) qs_obj(items, i, right);
}

double WeightSum(checkers items[], int count)
{
	register int i = 0;
	double sum = 0;
	for (; i < count; i++)
	{
		sum += items[i].GetFigureWeight(items[i]);
	}
	return sum;
}
