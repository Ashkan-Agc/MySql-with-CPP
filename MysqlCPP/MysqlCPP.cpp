#include <mysql.h>
#include <iostream>

using namespace std;

//Global variables
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;


class QueryTools
{
public:
	void connentDatabase(const char* server, const char* username, const char* password, const char* database, int port);
	void printTable(string table);
	void printData(MYSQL_RES* data);
	void runQuery(string query);
	void search(string table, string column, string key);
private:
	int num_fields;
};
void QueryTools::connentDatabase(const char* server, const char* username, const char* password, const char* database, int port) {
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, server, username, password, database, port, NULL, 0);
	if (conn) {
		puts("Successful connection to database!");
		cout << "-----------------------------------------" << endl;
	}
	else {
		cout << ":( failed to connect database(check password , username , server address , port) " << endl;
		exit(0);
	}
}
void QueryTools::runQuery(string query) {
	qstate = mysql_query(conn, query.c_str());
	if (qstate == 0)
	{
		cout << "query: <<" << query << ">>executed successfully :)" << endl;
	}
	else
	{
		cout << ":( Query failed: " << mysql_error(conn) << endl;
	}
}
void QueryTools::printTable(string table)
{
	string query = "SELECT * FROM " + table;
	mysql_query(conn, query.c_str());
	res = mysql_store_result(conn);
	num_fields = mysql_num_fields(res);
	cout << "-----------------------------------------" << endl;
	while ((row = mysql_fetch_row(res)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			cout << row[i] << "\t";
		}
		cout << endl;
	}
	cout << "-----------------------------------------" << endl;
	mysql_free_result(res);//clear result set from memory
}
void QueryTools::printData(MYSQL_RES* data) {
	num_fields = mysql_num_fields(data);
	while ((row = mysql_fetch_row(data)))
	{
		for (int i = 0; i <= num_fields; i++)
		{
			cout << row[i] << "\t";
		}
		cout << endl;
	}
}
void QueryTools::search(string table, string column, string key)
{
	string q = "select * from " + table + " where "+ column + " = " + key;
	runQuery(q);
	mysql_commit(conn);
	res = mysql_store_result(conn);
	
	cout << "-------------------search result----------------------" << endl;
	cout << "found : " << mysql_num_rows(res) << endl;
	printData(res);
}


int main()
{
	QueryTools instructions;
	instructions.connentDatabase("localhost", "root", "ashkan79", "test", 3306);
	//instructions.runQuery("select * from student");
	//instructions.printData("student");
	instructions.search("student", "age", "43");
	mysql_close(conn);//close initialize connection
	return 0;
}
