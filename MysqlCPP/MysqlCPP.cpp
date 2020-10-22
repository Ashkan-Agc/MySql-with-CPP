// MySqlTest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <mysql.h>
#include <iostream>

using namespace std;
int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;



class QueryInstructions
{
public:
	void printData(string table);
	void runQuery(string query);
private:
	MYSQL_ROW row;
	int num_fields;
};
void QueryInstructions::runQuery(string query) {
	qstate = mysql_query(conn, query.c_str());
	if (!qstate)
	{
		cout << "<<query: >>" << query << " executed successfully :)" << endl;
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
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "ashkan79", "test", 3306, NULL, 0);
	QueryInstructions instructions;
	if (conn) {
		puts("Successful connection to database!");
		cout << "-----------------------------------------" << endl;
		instructions.runQuery("delete from student whre id=2");
		instructions.printData("student");
		mysql_free_result(res);//clear result set from memory
		/*if (!qstate)
		{
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			while (row)
			{
				cout << ("ID: %s, fist_name: %s,last_name: %s, age: %s\n", row[0], row[1], row[2], row[3]);
			}
		}
		else
		{
			cout << "Query failed: " << mysql_error(conn) << endl;
		}*/
	}
	//else {
	//	puts("Connection to database has failed!");
	//}

	return 0;
}
