#include <iostream>
#include <fstream>
#include <io.h>
#include <string>

using namespace std;

typedef struct modsList
{
	string mod_name;
	string mod_path;
	modsList* next = nullptr;
};

int updateLocal();

int main()
{
	int choose = 0;
	//printf("1.Update the local inf\t 2.Update the server inf\n");
	//printf("Please enter the number:");
	updateLocal();

	getchar();
	return 0;
}

int updateLocal()
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

int updateFile()
{

}
