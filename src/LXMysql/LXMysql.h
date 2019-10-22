#pragma once

#ifdef LXMYSQL_EXPORTS
//动态链接库调用
#define LXAPI __declspec(dllexport)
#else
//执行程序调用
#define LXAPI __declspec(dllimport)
#endif

#include<string>
#include<vector>
#include<map>

struct MYSQL;
struct MYSQL_RES;
namespace LX {
	enum  LX_OPT {
		LX_OPT_CONNECT_TIMEOUT,
		LX_OPT_COMPRESS,
		LX_OPT_NAMED_PIPE,
		LX_INIT_COMMAND,
		LX_READ_DEFAULT_FILE,
		LX_READ_DEFAULT_GROUP,
		LX_SET_CHARSET_DIR,
		LX_SET_CHARSET_NAME,
		LX_OPT_LOCAL_INFILE,
		LX_OPT_PROTOCOL,
		LX_SHARED_MEMORY_BASE_NAME,
		LX_OPT_READ_TIMEOUT,
		LX_OPT_WRITE_TIMEOUT,
		LX_OPT_USE_RESULT,
		LX_REPORT_DATA_TRUNCATION,
		LX_OPT_RECONNECT,
		LX_PLUGIN_DIR,
		LX_DEFAULT_AUTH,
		LX_OPT_BIND,
		LX_OPT_SSL_KEY,
		LX_OPT_SSL_CERT,
		LX_OPT_SSL_CA,
		LX_OPT_SSL_CAPATH,
		LX_OPT_SSL_CIPHER,
		LX_OPT_SSL_CRL,
		LX_OPT_SSL_CRLPATH,
		LX_OPT_CONNECT_ATTR_RESET,
		LX_OPT_CONNECT_ATTR_ADD,
		LX_OPT_CONNECT_ATTR_DELETE,
		LX_SERVER_PUBLIC_KEY,
		LX_ENABLE_CLEARTEXT_PLUGIN,
		LX_OPT_CAN_HANDLE_EXPIRED_PASSWORDS,
		LX_OPT_MAX_ALLOWED_PACKET,
		LX_OPT_NET_BUFFER_LENGTH,
		LX_OPT_TLS_VERSION,
		LX_OPT_SSL_MODE,
		LX_OPT_GET_SERVER_PUBLIC_KEY,
		LX_OPT_RETRY_COUNT,
		LX_OPT_OPTIONAL_RESULTSET_METADATA,
		LX_OPT_SSL_FIPS_MODE
	};

	struct LXAPI LXData
	{
		 LXData(const char* data=0)
		{
			if (!data) return;
			this->data = data;
			this->size = strlen(data);
		}
		const char* data = 0;
		int size = 0;
	};
	//插入和更新数据
	typedef std::map<std::string,  LXData>  XDATA;

	class LXAPI LXMysql
	{
	public:
		//初始化mysql api
		bool Init();
		//清理
		void Close();

		//数据库连接 flag 设置多条语句
		bool Connect(const char* host, const char* user, const char* pass, const char*db, unsigned short port = 3306, unsigned short flag = 0);

		//执行sql语句
		bool Query(const char* sql, unsigned long sqllen = 0);

		//Mysql参数设定 connext之前调用
		bool Options(LX::LX_OPT opt, const void *arg);
		//链接超市时间
		bool SetConnectTimeout(int sec);
		//zidonbg自动重连
		bool SetReconnect(bool isre = true);


		//结果集获取
		//返回全部结果
		bool StoreResult();

		//开始接收结果，通过Fetch获取
		bool UseResult();

		//释放结果集占用的空间
		void FreeResult();

		//获取一行数据
		std::vector<LXData> FetchRow();

		//shengche生成insert sql 语句
		std::string GetInsertSql(XDATA kv, std::string table);




		//插入非二进制数据
		bool Insert(XDATA kv, std::string table);









	protected:
		MYSQL *	mysql = 0;
		MYSQL_RES *result = 0;
		//字段名称和类型
		std::vector<LXData> cols;
	};

}