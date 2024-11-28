#pragma once

#include <iostream>
#include <vector>
#include "queue.h"
#include <random>
#include <ctime>

using ui = unsigned;
using namespace std;

const double ACCURACY = 0.000001;

struct Task {
	ui ID; //ID
	ui t_appear; //tact of appear
	ui p_num; // process num
	ui time; // number of tacts needed to work
};

inline void printTask(Task t) {
	cout << "ID: " << t.ID << endl << "APPEAR: " << t.t_appear << endl << "PROC: " << t.p_num << endl << "TIME: " << t.time << endl;
};

struct Statistic {
	ui program_num;
	ui done_prog_num;
	ui running_num; 
	double average_workload; 
};

inline void printStatistic(const Statistic& st) {
	cout << st.program_num << endl << st.done_prog_num << endl << st.running_num << endl << st.average_workload << endl;
};

inline bool operator==(const Statistic& lst, const Statistic& rst) {
	return (abs(lst.average_workload - rst.average_workload) < ACCURACY) && (lst.done_prog_num == rst.done_prog_num)
		&& (lst.program_num == lst.program_num) && (lst.running_num == rst.running_num);
}




class CL {
	//arguements
	ui processes_num;
	ui chance;
	ui Tmax;

	// cur
	vector<pair<ui, ui>> task_running; 
	// will be sorted by ennd-time; pair<end_tact, proc_num>
	TStackQueue<Task> queue; 

public:
	CL(ui p_n, ui T_m, ui ch) : Tmax(T_m), processes_num(p_n), chance(ch) { 
		if (p_n == 0 || ch > 100 || T_m == 0 || p_n > 64) throw "Invalid arguement";
	}

	CL() : Tmax(1), processes_num(1), chance(0) {}

	CL(const CL& c) {
		processes_num = c.processes_num;
		Tmax = c.Tmax;
		chance = c.chance;
	}
	
	CL& operator=(const CL& c) {
		processes_num = c.processes_num;
		Tmax = c.Tmax;
		chance = c.chance;
		return *this;
	}
	
	Statistic Simulation(ui k = 1, vector <Task>*  tsks = NULL) {
		Statistic stat{ 0, 0, 0, 0.0 };
		srand(time(0));
		//inside usage
		ui tact_ended_prog_num = 0,
			ID_flow = 1,
			free_proc_num = processes_num;
		vector <Task> tmp; 
		tmp.resize(0);

		//for tests
		bool import_user_queue = true;

		//main cycle
		for (ui T = 0; T <= Tmax; T++) {
			//ending programs
			tact_ended_prog_num = 0;
			for (; (tact_ended_prog_num < task_running.size()) && (task_running[tact_ended_prog_num].first == T); tact_ended_prog_num++) {
				free_proc_num += task_running[tact_ended_prog_num].second;
			}
			if (tact_ended_prog_num) {
				task_running.erase(task_running.begin(), task_running.begin() + tact_ended_prog_num); //O(n)
				stat.done_prog_num += tact_ended_prog_num;
			}
			//exit if T == Tmax
			if (T == Tmax) { 
				stat.running_num = task_running.size(); 
				continue; 
			}

			//getting new programs & adding in queue
			if (tsks) {
				if (import_user_queue) {
					tmp = GetTasks(tsks);
					for (auto task : tmp) {
						if (task.p_num > processes_num) { throw "Error: Task required too many processors. Buy some more processors"; }
					}
					AddTasksToQueue(tmp);
					stat.program_num += tmp.size();
					import_user_queue = false;
				}
			}
			else {
				tmp = GetTasks(k, T, ID_flow); 
				AddTasksToQueue(tmp);
				stat.program_num += tmp.size();
			}


			// trying to start new programs
			while ((!queue.IsEmpty()) && (queue.Top().p_num <= free_proc_num)) {
				task_running.push_back(make_pair(T + queue.Top().time, queue.Top().p_num));
				free_proc_num -= queue.Top().p_num;
				queue.Pop();
			}
			RunningTaskSort();
			stat.running_num = task_running.size();
			stat.average_workload += processes_num - free_proc_num;
		}

		stat.average_workload = (stat.average_workload / Tmax) / processes_num;
		return stat;
	};

private:
	vector<Task> GetTasks(vector <Task>* tasks) {
		return *tasks;
	}

	vector<Task> GetTasks(ui task_num, ui cur_T, ui& ID_flow) {
		vector<Task> tasks;
		for (ui i = 0; i < task_num; i++) {
			if (Random(0, 100) > chance) continue;
			Task t{ ID_flow++, cur_T, Random(0, processes_num), Random(1, Tmax) };
			tasks.push_back(t);
			//cout << "---------------------------------------------------\n";
			//printTask(t);
		}
		//cout << endl << endl;
		return tasks;
	}
	
	ui Random(ui lb, ui rb) {
		//srand(time(0)); 
		return (rand() % (rb - lb + 1)) + lb;
	}

	void RunningTaskSort() {
		int n = task_running.size();

		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - i - 1; j++)
				if (task_running[j].first > task_running[j + 1].first) { 
					auto tmp = task_running[j + 1];
					task_running[j + 1] = task_running[j];
					task_running[j] = tmp;
				}
	}

	void AddTasksToQueue(const vector<Task>& v_ts) {
		for (ui i = 0; i < v_ts.size(); i++)
			queue.Push(v_ts[i]);
	};

};

