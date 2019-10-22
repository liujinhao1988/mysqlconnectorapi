

#include <iostream>
#include "LXMysql.h"


using namespace std;
using namespace LX;
int main()
{
	LXMysql my;
	cout <<"my.Init()= "<< my.Init() << endl;
	my.SetConnectTimeout(3);
	my.SetReconnect(true);
	if (my.Connect("127.0.0.1", "root", "123456", "laoxiaketang"))//改laoxiaketang
	{
		cout << "my.Connect success" << endl;
	}

	//创建表
	string sql = "";
	sql = "CREATE TABLE IF NOT EXISTS `t_video` \
			(`id` INT AUTO_INCREMENT, \
			`name` VARCHAR(1024) , \
			`data` BLOB,\
			`size` INT,PRIMARY KEY(`id`))";

	cout << my.Query(sql.c_str()) << endl;
	//测试自动重连
	/*for (;;)
	{
		cout << my.Query(sql.c_str()) << flush;
	}*/

	//插入一条记录
	//sql = "insert into t_video(name) values('test001')";
	
	//清空数据
	sql = "truncate t_video";
	my.Query(sql.c_str());


	XDATA data1;

	//data1.insert(make_pair("name", LXData("insertname001")));


	data1["name"] =LXData("insertname001");

	data1["size"] = LXData("1024");




	cout << my.GetInsertSql(data1, "t_video")<<endl;



	//获取结果集
	sql = "select * from t_video";
	cout << my.Query(sql.c_str()) << endl;
	
	
	
	my.StoreResult();//结果集本地全部存储
	for (;;)
	{
		//获取一行数据

		auto row=my.FetchRow();
		if (row.size() == 0)
			break;

		for (int i = 0; i < row.size(); i++)
		{
			if (row[i].data)
				cout << row[i].data << " ";
		}
		cout << endl;
	}






	my.FreeResult();
	cout << my.Query(sql.c_str()) << endl;
	my.UseResult();//开始接收结果集

	my.FreeResult();



	my.Close();


	cout << "test_LXMysql \n " << endl;
	getchar();
	return 0;
}