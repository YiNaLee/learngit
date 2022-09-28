#include <iostream>
#include <string>
using namespace std;
typedef struct Process_Control_Block
{
	int num;
	float enter_Tim;//进程进入时间
	float start_Tim;//进程开始时间
	float sev_Tim;//服务时间
	float save_Sev_Tim;
	float over_Tim;
	int priority_Rank;		// 优先级
	bool finish_Flag;		// 是否以服务完的标志
}PCB;
void FCFS_Algorithm();		// 先来先服务算法 FCFS (First Come First Service)
/*初始化进程控制块PCB信息*/
void Init(int* n, PCB*& Pro_Array)
{
	cout << "请输入在单道环境下，需调度的作业个数 n 为：";
	cin >> *n;
	Pro_Array = new PCB[*n];

	cout << "请分别输入这 " << *n << " 个进程的进程号：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].num;
		Pro_Array[i].finish_Flag = false;
	}
	cout << "请分别输入这 " << *n << " 个进程达到系统的时刻：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].enter_Tim;//初始化进入时间，并且将开始时间置为标记-1
		Pro_Array[i].start_Tim = -1;
	}

	cout << "请分别输入这 " << *n << " 个进程需要的服务时间：（空格区分）";
	for (int i = 0; i < *n; i++)
	{
		cin >> Pro_Array[i].sev_Tim;
		Pro_Array[i].save_Sev_Tim = Pro_Array[i].sev_Tim;
	}
}

/************************************************************
* Print_Res负责输出
**************************************************************/
void Print_Res(int* m, PCB*& Pro_Array)
{
	/* 输出模块*/
	int n = *m;

	/* 输出模块一：表 */
	cout << endl << "| 进程号\t| 进入时间\t| 服务时间\t| 开始时间\t| 结束时间\t| 周转时间\t| 带权周转时间\t|" << endl;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;	// 周转时间
		double carry_Weight_Cicle_Time = 1.0 * cicle_Time / Pro_Array[i].save_Sev_Tim;	// 带权周转时间
		cout.precision(4);
		cout << "| 进程\t" << Pro_Array[i].num << "\t| " << Pro_Array[i].enter_Tim << "\t\t| " << Pro_Array[i].save_Sev_Tim\
			<< "\t\t| " << Pro_Array[i].start_Tim << "\t\t| " << Pro_Array[i].over_Tim << "\t\t| " << cicle_Time << "\t\t| "\
			<< carry_Weight_Cicle_Time << "\t\t|" << endl;
	}
	cout << endl;

	/* 输出模块二：其他内容 */
	/* [1]输出：每个进程的周转时间 */
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		cout << Pro_Array[i].num << "进程的周转时间为：" << cicle_Time << endl;
	}
	cout << endl;

	/* [2]输出：每个进程的带权周转时间 */
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		float actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		cout << Pro_Array[i].num << "进程的带权周转时间为：" << 1.0 * cicle_Time / actual_execution_Time << endl;
	}
	cout << endl;

	/* [3]输出：所有进程的平均周转时间 */
	float tol_Tim_1 = 0;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		tol_Tim_1 += cicle_Time;
	}
	cout << "所有进程的平均周转时间为：" << 1.0 / n * tol_Tim_1 << endl;
	cout << endl;

	/* [4]输出：所有进程的带权平均周转时间 */
	double tol_Tim_2 = 0;
	for (int i = 0; i < n; i++)
	{
		float cicle_Time = Pro_Array[i].over_Tim - Pro_Array[i].enter_Tim;
		float actual_execution_Time = Pro_Array[i].save_Sev_Tim;
		tol_Tim_2 += 1.0 * cicle_Time / actual_execution_Time;
	}
	cout << "所有进程的带权平均周转时间为：" << 1.0 / n * tol_Tim_2 << endl;
	cout << endl;
}

void FCFS_Algorithm()		// 先来先服务算法 FCFS (First Come First Service)
{
	/* 输入模块 */
	int n;
	PCB* Pro_Array = NULL;
	Init(&n, Pro_Array);

	/* FCFS算法设计模块 */
	int over_Job_Num = 0;
	int i = 0;	// 当前服务对象的下标
	float cur_Time = Pro_Array[i].enter_Tim;	// 当前时刻, 初始化为第一个进程的开始时刻
	while (over_Job_Num < n)
	{
		if (Pro_Array[i].finish_Flag == false)	// 当前进程还未服务完
		{
			Pro_Array[i].start_Tim = cur_Time;	// 开始时间
			Pro_Array[i].finish_Flag = true;	// 先到先服务
			over_Job_Num++;
			Pro_Array[i].sev_Tim = 0;			// 该进程所要求的服务时间清零
			cur_Time += Pro_Array[i].save_Sev_Tim;	// 当前时间向后推进
			Pro_Array[i].over_Tim = cur_Time;	// 记录该进程的结束时间
		}
		i++;
	}

	/* 输出模块*/
	Print_Res(&n, Pro_Array);

	delete[] Pro_Array;
	return ;
}

int main()
{
	FCFS_Algorithm();
	return 0;
}
