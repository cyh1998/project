// Student-System.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
//1.1版本说明
//实现判断用户输入的内容是否正确(存在正则表达式无法使用的问题)
//实现判断是否有同名,同学号学生
//实现可按照学生学号查询学生信息
//
//更改并添加了项目整体功能
//细化已实现的功能


#include <bits/stdc++.h>
//#include <regex>   //正则表达式头文件
#define NUM 30     //定义学生上限

//添加功能：
//批量数据录入
//实现多门成绩管理
//将数据写入文件，实现数据保存


using namespace std;

void display_menu();//显示系统界面

int num = 0;//全局变量num，记录学生个数

struct stu {
	string name;
	int id;
	int age;
	double score;
};

class student {
public:
	stu students[NUM];
public:
	void input_student_info();    //录入学生信息1
	void display_student_info();  //显示学生信息2
	void find_student_info();     //查找学生信息3
	void change_student_info();   //修改学生信息4
	void delect_student_info();   //删除学生信息5
	void sort_info();             //学生信息排序6
};

void student::input_student_info() {
	//int i = 0;
	//添加功能：判断用户输入的内容是否正确(实现) 正则表达式无法使用
	//细化功能：判断用户输入出错的具体内容
	//添加功能：判断是否有同名,同学号学生(实现)
	int if_stu;
	if (num == NUM) {
		cout << "学生人数已达上限\n";
	}
	else {
		cout << "请输入学生姓名、学号、年龄、成绩:" << endl;
		string _name;
		int _id;
		int _age;
		double _score;

		string reg_1("^[a-zA-Z]{1,3}$");  //匹配学生名称(正则表达式)
		int times = 3;  //设置输入错误次数
		while (times--) {
			if_stu = 0;
			cin >> _name >> _id >> _age >> _score;
			//regex_match(_name,reg_1)
			for (int i = 0; i < num; i++) {
				if (students[i].id == _id) {
					cout << "已有此学生。请重新输入\n";
					if_stu = 1;
					break;
				}
			}
			if (if_stu == 0) {
				if (((0 < _id) && (_id <= NUM)) && ((18 < _age) && (_age < 25)) && ((1 <= _score) && (_score <= 100))) {
					students[num].name = _name;
					students[num].id = _id;
					students[num].age = _age;
					students[num].score = _score;
					num++;
					cout << "录入成功\n";
					break;
				}
				else {
					if (times == 0) cout << "错误次数已达上限！\n";
					else cout << "输入数据有误，请重新输入\n";
				}
			}
		}
	}
}

void student::display_student_info() {
	if (num == 0) {
		cout << "暂无数据，请先录入" << endl;
	}
	else {
		cout << "现有" << num << "条学生信息\n";
		for (int i = 0; i < num; i++) {
			cout << i + 1 << ".学生姓名:" << students[i].name << " 学号:" << students[i].id << " 年龄:" << students[i].age << " 成绩:" << students[i].score << endl;
		}
	}

}

void student::find_student_info() {
	if (num == 0) {
		cout << "暂无数据，请先录入" << endl;
	}
	else {
		//添加功能：还可按照学生学号查询(实现)
		cout << "1.按照姓名查找  2.按照学号查找  0.取消\n";
		int find_num;
		cin >> find_num;
		switch (find_num) {
		case 1: {
			int stu_if = 0;
			string find_name;
			cout << "请输入查找的学生姓名\n";

			cin >> find_name;
			int i;
			for (i = 0; i < num; i++) {
				if (students[i].name == find_name) {
					cout << "学生姓名:" << students[i].name << " 学号:" << students[i].id << " 年龄:" << students[i].age << " 成绩:" << students[i].score << endl;
					stu_if = 1;
					//break;  //查询所有name的数据
				}
			}
			if (stu_if == 0) cout << "无此学生" << endl;
			break;
		}
		case 2: {
			int find_id;
			cout << "请输入查找的学生学号\n";
			cin >> find_id;
			int i;
			for (i = 0; i < num;) {
				if (students[i].id == find_id) {
					cout << "学生姓名:" << students[i].name << " 学号:" << students[i].id << " 年龄:" << students[i].age << " 成绩:" << students[i].score << endl;
					break;
				}
				else i++;
			}
			if (i == num) cout << "无此学生" << endl;
			break;
		}
		case 0: break;
		default:cout << "选择错误！重新选择" << endl;
		}

	}
}

void student::change_student_info() {
	if (num == 0) {
		cout << "暂无数据，请先录入" << endl;
	}
	else {
		string change_name;
		cout << "请输入修改的学生姓名\n";
		//添加功能：还可按照学生学号查询修改
		cin >> change_name;
		int i;
		int k = 1;
		for (i = 0; i < num; i++) {
			if (k == 0) break;

			if (students[i].name == change_name) {
				cout << "请重新输入学生姓名、学号、年龄、成绩:\n";
				//添加功能：判断用户输入的内容是否正确(实现)
				int times = 3;  //设置输入错误次数
				while (times--) {
					string _name;
					int _id;
					int _age;
					double _score;
					cin >> _name >> _id >> _age >> _score;
					//regex_match(_name,reg_1)
					if (((0 < _id) && (_id <= NUM)) && ((18 < _age) && (_age < 25)) && ((1 <= _score) && (_score <= 100))) {
						students[i].name = _name;
						students[i].id = _id;
						students[i].age = _age;
						students[i].score = _score;
						//num++;
						cout << "修改成功\n";
						k = 0;
						break;
					}
					else {
						if (times == 0) cout << "错误次数已达上限，修改失败\n";
						else cout << "输入数据有误，请重新输入\n";
					}
				}
			}
			if (i == num) cout << "无此学生" << endl;
		}
	}
}

void student::delect_student_info() {
	if (num == 0) {
		cout << "暂无数据，无法删除" << endl;
	}
	else {
		cout << "现有" << num << "条学生信息，选择需要删除的学生姓名\n";
		for (int i = 0; i < num; i++) {
			cout << i + 1 << ".学生姓名:" << students[i].name << " 学号:" << students[i].id << " 年龄:" << students[i].age << " 成绩:" << students[i].score << endl;
		}
		string delect_name;
		cin >> delect_name;
		int i;
		for (i = 0; i < num; i++) {
			if (students[i].name == delect_name) {
				for (int j = i; j < num - 1; j++) {
					students[j].name = students[j + 1].name;
					students[j].id = students[j + 1].id;
					students[j].age = students[j + 1].age;
					students[j].score = students[j + 1].score;
				}
				num--;
				cout << "删除成功" << endl;
				break;
			}
		}
		if (i == num && num != 0) cout << "无此学生" << endl;
	}
}

void student::sort_info() {
	if (num == 0) {
		cout << "暂无数据，请先录入" << endl;
	}
	else {
		cout << "请输入需要排序的依据值\n";
		cout << "学号：1 成绩：2\n";
		int sort_num;
		cin >> sort_num;
		switch (sort_num) {
		case 1: {
			for (int j = 0; j < num; j++) {
				for (int k = 0; k < num - j - 1; k++) {
					if (students[k].id > students[k + 1].id) {
						stu temp = students[k];
						students[k] = students[k + 1];
						students[k + 1] = temp;
					}
				}
			}
			cout << "排序成功\n";
			break;
		}
		case 2: {
			for (int j = 0; j < num; j++) {
				for (int k = 0; k < num - j - 1; k++) {
					if (students[k].score > students[k + 1].score) {
						stu temp = students[k];
						students[k] = students[k + 1];
						students[k + 1] = temp;
					}
				}
			}
			cout << "排序成功\n";
			break;
		}
		default:cout << "选择错误！重新选择" << endl;
		}
	}

}

int main()
{
	student root;
	int key = 1;
	while (key) {
		display_menu();
		int test_num;
		cin >> test_num;
		switch (test_num) {
		case 1: root.input_student_info(); break;
		case 2: root.display_student_info(); break;
		case 3: root.find_student_info(); break;
		case 4: root.change_student_info(); break;
		case 5: root.delect_student_info(); break;
		case 6: root.sort_info(); break;
		case 0: {
			cout << "退出系统。" << endl;
			key = 0;
			break;
		}
		default:cout << "选择错误！重新选择" << endl;
		}
	}
	return 0;
}

void display_menu() {
	cout << "=================================================\n";
	cout << "=              欢迎使用学生管理系统             =\n";
	cout << "=           1=录入学生     2=显示信息           =\n";
	cout << "=           3=查找学生     4=修改信息           =\n";
	cout << "=           5=删除学生     6=信息排序           =\n";
	cout << "=                    0=退出                     =\n";
	cout << "=================================================\n";
	cout << "请选择:";
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
