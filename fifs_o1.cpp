#include <iostream>
#include <string>
using namespace std;
typedef struct Process_Control_Block
{
	int num;
	float enter_Tim;//���̽���ʱ��
	float start_Tim;//���̿�ʼʱ��
	float sev_Tim;//����ʱ��
	float save_Sev_Tim;
	float over_Tim;
	int priority_Rank;		// ���ȼ�
	bool finish_Flag;		// �Ƿ��Է�����ı�־
}PCB;
void FCFS_Algorithm();		// �����ȷ����㷨 FCFS (First Come First Service)
/*��ʼ�����̿��ƿ�PCB��Ϣ*/
void Init(int* n, PCB*& Pro_Array)
{
	cout << "�������ڵ��������£�����ȵ���ҵ���� n Ϊ��";
	cin >> *n;
	Pro_Array = new PCB[*n];

	cout << "��ֱ������� " << *n << " �����̵Ľ��̺ţ����ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].num;
		Pro_Array[i].finish_Flag = false;
	}
	cout << "��ֱ������� " << *n << " �����̴ﵽϵͳ��ʱ�̣����ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].enter_Tim;//��ʼ������ʱ�䣬���ҽ���ʼʱ����Ϊ���-1
		Pro_Array[i].start_Tim = -1;
	}

	cout << "��ֱ������� " << *n << " ��������Ҫ�ķ���ʱ�䣺���ո����֣�";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].sev_Tim;
		Pro_Array[i].save_Sev_Tim = Pro_Array[i].sev_Tim;
	}
}

/************************************************************
* Print_Res�������
**************************************************************/
void Print_Res(int* m, PCB*& Pro_Array)
{
	/* ���ģ��*/
	int n = *m;

	/* ���ģ��һ���� */
	cout << endl << "| ���̺�\t| ����ʱ��\t| ����ʱ��\t| ��ʼʱ��\t| ����ʱ��\t| ��תʱ��\t| ��Ȩ��תʱ��\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;	// ��תʱ��
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / Pro_Array[i].save_Sev_Tim;	// ��Ȩ��תʱ��
		cout.precision(4);
		cout << "| ����\t" << Pro_Array[i].num << "\t| " << Pro_Array[i].enter_Tim << "\t\t| " << Pro_Array[i].save_Sev_Tim\
			<< "\t\t| " << Pro_Array[i].start_Tim << "\t\t| " << Pro_Array[i].over_Tim << "\t\t| " << cicle_Time << "\t\t| "\
			<< carry_Weight_Cicle_Time << "\t\t|" << endl;
	}
	cout << endl;

	/* ���ģ������������� */
	/* [1]�����ÿ�����̵���תʱ�� */
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		cout << Pro_Array[i].num << "���̵���תʱ��Ϊ��" << cicle_Time << endl;
	}
	cout << endl;

	/* [2]�����ÿ�����̵Ĵ�Ȩ��תʱ�� */
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		float actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		cout << Pro_Array[i].num << "���̵Ĵ�Ȩ��תʱ��Ϊ��" << 1.0 * cicle_Time / actual_execution_Time << endl;
	}
	cout << endl;

	/* [3]��������н��̵�ƽ����תʱ�� */
	float tol_Tim_1 = 0;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		tol_Tim_1 += cicle_Time;
	}
	cout << "���н��̵�ƽ����תʱ��Ϊ��" << 1.0 / n * tol_Tim_1 << endl;
	cout << endl;

	/* [4]��������н��̵Ĵ�Ȩƽ����תʱ�� */
	double tol_Tim_2 = 0;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		float actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		tol_Tim_2 += 1.0 * cicle_Time / actual_execution_Time;
	}
	cout << "���н��̵Ĵ�Ȩƽ����תʱ��Ϊ��" << 1.0 / n * tol_Tim_2 << endl;
	cout << endl;
}

void FCFS_Algorithm()		// �����ȷ����㷨 FCFS (First Come First Service)
{
	/* ����ģ�� */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array);

	/* FCFS�㷨���ģ�� */
	int over_Job_Num = 0;
	int i = 0;	// ��ǰ���������±�
	float cur_Time = Pro_Array[i].enter_Tim;	// ��ǰʱ��, ��ʼ��Ϊ��һ�����̵Ŀ�ʼʱ��
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// ��ǰ���̻�δ������
		{
			Pro_Array[i].start_Tim = cur_Time;	// ��ʼʱ��
			Pro_Array[i].finish_Flag = true;	// �ȵ��ȷ���
			over_Job_Num++;
			Pro_Array[i].sev_Tim = 0;			// �ý�����Ҫ��ķ���ʱ������
			cur_Time += Pro_Array[i].save_Sev_Tim;	// ��ǰʱ������ƽ�
			Pro_Array[i].over_Tim = cur_Time;	// ��¼�ý��̵Ľ���ʱ��
		}
		i++;
	}

	/* ���ģ��*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return ;
}

int main()
{
	FCFS_Algorithm();
	return 0;
}
