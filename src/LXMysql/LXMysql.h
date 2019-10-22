#pragma once

#ifdef LXMYSQL_EXPORTS
//��̬���ӿ����
#define LXAPI __declspec(dllexport)
#else
//ִ�г������
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
	//����͸�������
	typedef std::map<std::string,  LXData>  XDATA;

	class LXAPI LXMysql
	{
	public:
		//��ʼ��mysql api
		bool Init();
		//����
		void Close();

		//���ݿ����� flag ���ö������
		bool Connect(const char* host, const char* user, const char* pass, const char*db, unsigned short port = 3306, unsigned short flag = 0);

		//ִ��sql���
		bool Query(const char* sql, unsigned long sqllen = 0);

		//Mysql�����趨 connext֮ǰ����
		bool Options(LX::LX_OPT opt, const void *arg);
		//���ӳ���ʱ��
		bool SetConnectTimeout(int sec);
		//zidonbg�Զ�����
		bool SetReconnect(bool isre = true);


		//�������ȡ
		//����ȫ�����
		bool StoreResult();

		//��ʼ���ս����ͨ��Fetch��ȡ
		bool UseResult();

		//�ͷŽ����ռ�õĿռ�
		void FreeResult();

		//��ȡһ������
		std::vector<LXData> FetchRow();

		//shengche����insert sql ���
		std::string GetInsertSql(XDATA kv, std::string table);




		//����Ƕ���������
		bool Insert(XDATA kv, std::string table);









	protected:
		MYSQL *	mysql = 0;
		MYSQL_RES *result = 0;
		//�ֶ����ƺ�����
		std::vector<LXData> cols;
	};

}