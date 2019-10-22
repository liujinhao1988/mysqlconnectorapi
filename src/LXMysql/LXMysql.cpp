



#include"LXMysql.h"

#include<iostream>

#include<mysql.h>



using namespace std;




namespace LX {


	//typedef std::map<std::string, LXData> XDATA;

	bool LXMysql::Init()
	{
		Close();
		cout << "LXMysql::Init()" << endl;
		//新创建一个MySQL 对象
		mysql = mysql_init(0);
		if (!mysql)
		{
			cerr << "mysql_init failed\n" << endl;
			return false;
		}

		return true;
	}

	//清理
	void LXMysql::Close()
	{
		FreeResult();
		if (mysql)
		{
			mysql_close(mysql);
			mysql = NULL;

		}
		cout << "LXMysql::Close()\n" << endl;
	}


	//数据库连接 flag 设置多条语句
	bool LXMysql::Connect(const char* host, const char* user, const char* pass, const char*db, unsigned short port, unsigned short flag)
	{
		if (!mysql && !Init())
		{
			cerr << "mysql Connect fail! mysql is not init!" << endl;
			return false;
		}
		if (!mysql_real_connect(mysql, host, user, pass, db, port, 0, flag))
		{
			cerr << "mysql Connect fail!" << mysql_error(mysql) << endl;
		}
		cout << "mysql connect successs" << endl;

		return true;
	}

	//执行sql语句
	bool LXMysql::Query(const char* sql, unsigned long sqllen)
	{
		if (!mysql)
		{
			cerr << "QUery failed mysql is null" << endl;
			return false;
		}
		if (!sql)
		{
			cerr << "sql is null" << endl;
			return false;
		}
		if (sqllen <= 0)
		{
			sqllen = (unsigned long)strlen(sql);
		}
		if (sqllen <= 0)
		{
			cerr << "QUery sql is empty or wrong format" << endl;
			return false;
		}

		int re = mysql_real_query(mysql, sql, sqllen);
		if (re != 0)
		{
			cerr << "mysql_real_query failed" << mysql_error(mysql) << endl;
			return false;
		}
		return true;
	}

	//Mysql参数设定
	bool LXMysql::Options(LX::LX_OPT opt, const void *arg)
	{
		if (!mysql)
		{
			cerr << "Options failed mysql is null" << endl;
			return false;
		}
		int re = mysql_options(mysql, (mysql_option)opt, arg);
		if (re != 0)
		{
			cerr << "mysql_options failed" << mysql_error(mysql) << endl;
			return false;
		}
		return true;

	}


	//链接超市时间
	bool LXMysql::SetConnectTimeout(int sec)
	{
		return Options(LX::LX_OPT_CONNECT_TIMEOUT, &sec);
	}
	//zidonbg自动重连
	bool LXMysql::SetReconnect(bool isre)
	{
		return Options(LX::LX_OPT_RECONNECT, &isre);
	}



	//结果集获取
	//返回全部结果
	bool LXMysql::StoreResult()
	{
		if (!mysql)
		{
			cerr << "StoreResult failed mysql is null" << endl;
			return false;
		}
		FreeResult();
		result = mysql_store_result(mysql);
		if (!result)
		{
			cerr << "mysql_store_result failed mysql is null" <<mysql_error(mysql)<< endl;
			return false;
		}
		return true;
	}

	//开始接收结果，通过Fetch获取
	bool LXMysql::UseResult()
	{
		if (!mysql)
		{
			cerr << "UseResult failed mysql is null" << endl;
			return false;
		}
		FreeResult();
		result = mysql_use_result(mysql);
		if (!result)
		{
			cerr << "mysql_use_result failed mysql is null" << mysql_error(mysql) << endl;
			return false;
		}
		return true;
	}


	//释放结果集占用的空间
	void LXMysql::FreeResult()
	{
		if (result)
		{
			mysql_free_result(result);
			result = NULL;
		}
	}


	//获取一行数据
	std::vector<LXData> LXMysql::FetchRow()
	{
		std::vector<LXData> re;
		if (!result)
		{
			return re;
		}
		MYSQL_ROW row = mysql_fetch_row(result);
		if (!row)
		{
			return re;

		}
		//.列的数量
		int num= mysql_num_fields(result);
		for (int i = 0; i < num; i++)
		{
			LXData data;
			data.data = row[i];
			re.push_back(data);
		}

		//


		return re;
	}



	////获取一行数据
	//std::vector<LXData> LXMysql::FetchRow()
	//{
	//	std::vector<LXData> re;
	//	if (!result)
	//	{
	//		return re;
	//	}
	//	MYSQL_ROW row = mysql_fetch_row(result);
	//	if (!row)
	//	{
	//		return re;
	//	}

	//	//列数
	//	int num = mysql_num_fields(result);
	//	for (int i = 0; i < num; i++)
	//	{
	//		LXData data;
	//		data.data = row[i];
	//		re.push_back(data);
	//	}
	//	return re;
	//}


	//shengche生成insert sql 语句
	std::string LXMysql::GetInsertSql(XDATA kv, std::string table)
	{
		std::string sql = "";

		if (kv.empty() || table.empty())
			return "";

		sql = "insert into `";
		sql += table;
		sql += "`";
		//insert into t_video (name,size) values("name1","1024")
		string keys = "";
		string vals = "";

		//迭代map
		for (auto ptr = kv.begin(); ptr != kv.end(); ptr++)
		{
			//字段名
			keys += "`";
			keys += ptr->first;
			keys += "`,";

			vals += "'";
			vals += ptr->second.data;
			vals += "',";
		}
		//去除多余的逗号
		keys[keys.size() - 1] = ' ';
		vals[vals.size() - 1] = ' ';

		sql += "(";
		sql += keys;
		sql += ")values(";
		sql += vals;
		sql += ")";

		return sql;
	}


	//插入非二进制数据
	bool LXMysql::Insert(XDATA kv, std::string table)
	{
		if (!mysql)
		{
			cerr << "Insert failed:mysql is NULL" << endl;
			return false;
		}
		string sql = GetInsertSql(kv, table);
		if (sql.empty())
			return false;
		if (!Query(sql.c_str()))
			return false;
		int num = mysql_affected_rows(mysql);
		if (num <= 0)
			return false;
		return true;
	}

}

