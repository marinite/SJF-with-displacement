#include <iostream>
#include <list>
using namespace std;

class Process
{
private:
	int st_position; //���.������� ��������
	int position; //����� � ������
	int duration; //������������
public:
	Process();
	Process(int st_position, int duration, int position);
	Process(const Process& Proc);
	~Process(); //����������� �������� ������ ��� ������������ ��������
	int getSt_pos(); //�������� ��������� �������
	int getDur(); //�������� ������������
	int getPos(); //�������� ����� � ������
	int DurMinus(); //���������� ������������
	void setDur(int duration);
};

Process::Process()
{
	st_position = 0;
	duration = 0;
	position = 0;
}

Process::Process(int st_position, int duration, int position)
{
	this->st_position = st_position;
	this->duration = duration;
	this->position = position;
}

Process::Process(const Process& Proc)
{
	st_position = Proc.st_position;
	duration = Proc.duration;
	position = Proc.position;
}

Process::~Process()
{}

int Process::getSt_pos()
{
	return st_position;
}

int Process::getDur()
{
	return duration;
}

int Process::getPos()
{
	return position;
}

int Process::DurMinus()
{
	int i = this->duration;
	i--;
	this->duration = i;
	return i;
}

void Process::setDur(int duration)
{
	this->duration = duration;
}

int Min(list<Process> spisok, int cur)
{
	auto min=spisok.begin(); //�������� ����������� ����������� �������, ������� �������: ����� ��� ������������ �� ���� ����� 0 ->
	int position;            //������ ��� ����� �� �� ������ ����� ������������ ����������� �������
	for (auto it = spisok.begin(); it != spisok.end(); it++)
	{
		if ((*it).getDur() != 0)
		{
			min = it;
			position = min->getPos();
			break;
		}
	}
	for (auto it = spisok.begin(); it != spisok.end(); it++)
	{
		if (((*it).getDur() <= min->getDur()) && ((*it).getSt_pos() <= cur) && ((*it).getDur() != 0))
		{
			min = it;
			position = (*it).getPos();
		}
	}
	return position;
}

int main()
{
	int const N = 4;
	int ar_st_pos[N] = {1,3,7,10};
	int ar_dur[N] = {4,10,7,2};
	int alltime = 0;
	bool openchoice = true;

	list<Process> spisok; //������ ���������

	//������������ �� ����� ��������� � �������
	for (int i = 0; i < N; i++)
	{
		alltime += ar_dur[i];
	}

	//��������� ������ ����������
	for (int i = 0; i < N; i++)
	{
		spisok.push_back(Process(ar_st_pos[i], ar_dur[i], i));
	}


	for (int cur = 1; cur <= alltime; cur++)
	{
		cout << "takt " << cur << ":" << endl;
		for (auto it = spisok.begin(); it != spisok.end(); it++)
		{
			cout << "Process " << (*it).getPos()+1 << ":";
			if ((openchoice)&&(Min(spisok, cur) == (*it).getPos())) //openchoice ��� ���������� �����
			{
				int duration = (*it).getDur() - 1;
				(*it).setDur(duration);
				cout << "+" << endl;
				openchoice = false;
			}
			else if (((*it).getSt_pos() <= cur) && ((*it).getDur() > 0)) cout << "-" << endl;
			else if(((*it).getSt_pos()>cur) || ((*it).getDur()==0))cout << "0" << endl;
		}
		openchoice = true;
	}

	spisok.clear();

	return 0;
}