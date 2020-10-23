#include <mysql.h>

#include <iostream>

using namespace std;

//Global variables
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;


class QueryInstructions
{
public:
	void connentDatabase(const char* server, const char* username, const char* password, const char* database, int port);
	void printData(string table);
	void runQuery(string query);
private:
	MYSQL_ROW row;
	int num_fields;
};
void QueryInstructions::connentDatabase(const char* server, const char* username, const char* password, const char* database, int port) {
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
void QueryInstructions::runQuery(string query) {
	qstate = mysql_query(conn, query.c_str());
	if (!qstate)
	{
		cout << "query: <<" << query << ">>executed successfully :)" << endl;
	}
	else
	{
		cout << ":( Query failed: " << mysql_error(conn) << endl;
	}
}
void QueryInstructions::printData(string table)
{
	string query = "SELECT * FROM student";
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
		cout << "\n";
	}
	cout << "-----------------------------------------" << endl;
}


int main()
{
	QueryInstructions instructions;
	instructions.connentDatabase("localhost", "root", "ashkan79", "test", 3306);
	instructions.runQuery("");
	instructions.printData("student");
	mysql_free_result(res);//clear result set from memory
	return 0;
}
