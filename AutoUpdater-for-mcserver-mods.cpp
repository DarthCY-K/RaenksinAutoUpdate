#include <iostream>
#include <fstream>
#include <io.h>
#include <cstdio>
#include <string>

using namespace std;

typedef struct modsList
{
	string mod_name;
	string mod_path;
	modsList* next = nullptr;
};

typedef struct modSolutionList
{
	string mod_name;
	int solution = 0;	//0为不存在 1为增加 2为删除
	modSolutionList* next = nullptr;
};

int updateLocalInf();
int checkVersion();
int updateLocalMods();
int updateLocalVersion(string new_version);

int main()
{
	updateLocalInf();
	checkVersion();

	getchar();
	return 0;
}

int updateLocalInf()
{
	string path = "C:\\Users\\45271\\Desktop\\TestProject\\AutoUpdater-for-mcserver-mods\\.minecraft\\mods\\";		//使用相对路径进行检索
	string search_path = path + "*.jar";
	modsList* head = new modsList;	//为头申请指针空间
	modsList* node_temp = new modsList;		//用于移动的指针
	node_temp = head;

	long handle;
	int mod_count = 0;

	_finddata_t fileinfo;
	handle = _findfirst(search_path.c_str(), &fileinfo);

	if (handle == -1)
		return -1;
	do
	{
		//cout << fileinfo.name << endl;

		node_temp->mod_name = fileinfo.name;
		node_temp->mod_path = path + fileinfo.name;

		node_temp->next = new modsList;

		if (mod_count == 0)		//保存头指针
			head = node_temp;

		node_temp = node_temp->next;
		mod_count++;

	} while (_findnext(handle, &fileinfo) == 0);
	_findclose(handle);

	node_temp = head;

	while (node_temp->next != nullptr)
	{
		cout << "======================================" << endl;
		cout << node_temp->mod_name << endl;
		cout << node_temp->mod_path << endl;
		node_temp = node_temp->next;
	}
	cout << "\n\n------------------------------------------------------------------------" << endl;
	cout << "总mod数：" << mod_count << endl;
	return 0;

}

int updateLocalVersion(string new_version)
{
	string path = "C:\\Users\\45271\\Desktop\\TestProject\\AutoUpdater-for-mcserver-mods\\.minecraft\\AutoUpdater\\version_client.xml";

	ofstream file(path, ifstream::out);	//以清除并增加的方式打开文件
	if (file.is_open())
	{
		file << new_version;
		file.close();
	}
	return 0;
}

int checkVersion()	//用于比对文件版本号
{
	string server_version = "2.0";
	string client_version;
	char rua[100];
	string path = "C:\\Users\\45271\\Desktop\\TestProject\\AutoUpdater-for-mcserver-mods\\.minecraft\\AutoUpdater\\version_client.xml";
	
	ifstream in(path, ifstream::in);	//以只读方式打开文件
	if (in.is_open())
	{
		while (!in.eof())
		{
			//in >> client_version;
			getline(in, client_version);
		}
		in.close();
	}
	cout << "client_version：V" << client_version << endl;
	cout << "server_version：V" << server_version << endl;

	if (client_version != server_version)
	{
		//ask for update
		if (updateLocalMods() == 0)
		{
			if (updateLocalVersion(server_version) == 0)
			{
				client_version = server_version;
				cout << "更新成功！新的本地版本号为V" + client_version << endl;
			}

		}
	}
	else
		cout << "客户端已经是最新版本，无需更新" << endl;

	return 0;
}

int updateLocalMods()
{
	//download solution_list from server
	modSolutionList* head = new modSolutionList;
	modSolutionList* temp_solution = new modSolutionList;
	temp_solution = head;
	string solution_path = "C:\\Users\\45271\\Desktop\\TestProject\\AutoUpdater-for-mcserver-mods\\.minecraft\\AutoUpdater\\Temp\\solution_list.xml";
	string mods_path = "C:\\Users\\45271\\Desktop\\TestProject\\AutoUpdater-for-mcserver-mods\\.minecraft\\mods\\";
	ifstream in(solution_path, ifstream::in);
	if (in.is_open())
	{
		while (!in.eof())
		{
			in >> temp_solution->mod_name;
			in >> temp_solution->solution;

			temp_solution->next = new modSolutionList;
			temp_solution = temp_solution->next;
		}
		in.close();
	}

	cout << "==================================================" << endl;
	cout << "Mods Need To Be Modify" << endl;
	cout << "Mod Name\t\t\tSolution" << endl;
	temp_solution = head;
	while ((temp_solution->next != nullptr) && (temp_solution->solution != 0))
	{
		cout << temp_solution->mod_name << "\t\t\t\t" << temp_solution->solution << endl;
		temp_solution = temp_solution->next;
	}

	temp_solution = head;
	while ((temp_solution->next != nullptr) && (temp_solution->solution != 0))
	{
		if (temp_solution->solution == 2)		//2为删除方案
		{
			if (remove((mods_path + temp_solution->mod_name).c_str()) == 0)
				cout << "文件名：" << temp_solution->mod_name << "已删除" << endl;
			else
			{
				cout << "文件名：" << temp_solution->mod_name << "删除失败，不存在" << endl;
			}
			temp_solution = temp_solution->next;
		}
		else
		{
			//get file from server
		}
	}

	return 0;
}


