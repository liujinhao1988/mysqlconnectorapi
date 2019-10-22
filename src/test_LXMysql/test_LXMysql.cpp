

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
	if (my.Connect("127.0.0.1", "root", "123456", "laoxiaketang"))//��laoxiaketang
	{
		cout << "my.Connect success" << endl;
	}

	//������
	string sql = "";
	sql = "CREATE TABLE IF NOT EXISTS `t_video` \
			(`id` INT AUTO_INCREMENT, \
			`name` VARCHAR(1024) , \
			`data` BLOB,\
			`size` INT,PRIMARY KEY(`id`))";

	cout << my.Query(sql.c_str()) << endl;
	//�����Զ�����
	/*for (;;)
	{
		cout << my.Query(sql.c_str()) << flush;
	}*/

	//����һ����¼
	//sql = "insert into t_video(name) values('test001')";
	
	//�������
	sql = "truncate t_video";
	my.Query(sql.c_str());


	XDATA data1;

	//data1.insert(make_pair("name", LXData("insertname001")));


	data1["name"] =LXData("insertname001");

	data1["size"] = LXData("1024");




	cout << my.GetInsertSql(data1, "t_video")<<endl;



	//��ȡ�����
	sql = "select * from t_video";
	cout << my.Query(sql.c_str()) << endl;
	
	
	
	my.StoreResult();//���������ȫ���洢
	for (;;)
	{
		//��ȡһ������

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
	my.UseResult();//��ʼ���ս����

	my.FreeResult();



	my.Close();


	cout << "test_LXMysql \n " << endl;
	getchar();
	return 0;
}