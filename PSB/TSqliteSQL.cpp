//---------------------------------------------------------------------------

#pragma hdrstop

#include "TSqliteSQL.h"
#include "sqlite3.h"
#include <System.Classes.hpp>
#include<string>
//---------------------------------------------------------------------------
#pragma package(smart_init)

#define DB_NAME "PSBDB.db"

/// <summary>
/// 创建表
/// </summary>
/// <param name="tablename">表名称</param>
/// <param name="strSql">SQL语句</param>
int __fastcall CreateTable()
{
	//打开sqlite3
	char *errMsg;
	sqlite3 *slit = NULL;
	char* pFileName = DB_NAME;
	int res = sqlite3_open(pFileName,&slit);
	if(res!= SQLITE_OK)
	{
	   //数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}
	//创建表格
	char *strSql = "CREATE TABLE CbrtOnlinek(ID integer primary key autoincrement"
	",bw_id integer,bw_bh text,bw_datafrom integer,bw_rtime TimeStamp,bw_wtime TimeStamp,bw_data text,"//blob,"
	"tmp1 integer,tmp2 integer,tmp3 integer,tmp4 integer,tmp5 integer,text1 TEXT,UNIQUE(bw_id,bw_bh,bw_rtime));";

	res = sqlite3_exec(slit,strSql,0,0,&errMsg);
	if(res != SQLITE_OK)
	{
		//数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}

	strSql = "CREATE TABLE CbrtOfflinek(ID integer primary key autoincrement"
	",bw_id integer,bw_bh text,bw_datafrom integer,bw_rtime TimeStamp,bw_wtime TimeStamp,bw_data text,"
	"tmp1 integer,tmp2 integer,tmp3 integer,tmp4 integer,tmp5 integer,text1 TEXT,UNIQUE(bw_id,bw_bh,bw_rtime));";
	res = sqlite3_exec(slit,strSql,0,0,&errMsg);
	if(res != SQLITE_OK)
	{
		//数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}

	sqlite3_close(slit);
	return 0;
}
/// <summary>
/// 删除数据库表
/// </summary>
int __fastcall DeleteTable()
{
	//打开sqlite3
	char *errMsg;
	sqlite3 *slit = NULL;
	char* pFileName = DB_NAME;
	int res = sqlite3_open(pFileName,&slit);
	if(res!= SQLITE_OK)
	{
	   //数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}

   //如果存在就删除
	std::string dropTab = "drop table CbrtOnlinek;" ;
	res = sqlite3_exec(slit,dropTab.c_str(),0,0,&errMsg);
	if(res != SQLITE_OK)
	{
	  //数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}
	dropTab = "drop table CbrtOfflinek;" ;
	res = sqlite3_exec(slit,dropTab.c_str(),0,0,&errMsg);
	if(res != SQLITE_OK)
	{
	  //数据库打开失败
	   sqlite3_close(slit);
	   return -1;
	}

}
/// <summary>
/// 插入操作
/// </summary>
/// <param name="strSql">插入sql语句</param>
int __fastcall InsertDbDate(sqlite3 *pDB,char* strSql)
{
	char* errMsg;
	int res;
	sqlite3_exec(pDB,"begin transaction;",0,0,&errMsg);

	res = sqlite3_exec(pDB,strSql,0,0,&errMsg);
	if(res != SQLITE_OK)
	{
		return -1;
	}
	res = sqlite3_exec(pDB,"commit transaction;",0,0,&errMsg);
	if(res != SQLITE_OK)
	{
		return -1;
	}
	return 0;
}
/// <summary>
/// 获取查询数据库的数据，（回调函数）
/// </summary>
/// <param name="para">数据库指针</param>
/// <param name="nCount">记录有多少个字段</param>
/*****************************************************************************
		  sqlite 每查到一条记录，就调用一次这个回调
		  para是你在 sqlite3_exec 里传入的 void * 参数, 通过para参数，你可以传入一些特殊的指针（比如类指  针、结构指针），然后在这里面强制转换成对应的类型（这里面是void*类型，必须强制转换成你的类型才可用）。然后操作这些数据
		  nCount是这一条(行)记录有多少个字段 (即这条记录有多少列)
		  char ** pValue 是个关键值，查出来的数据都保存在这里，它实际上是个1维数组（不要以为是2维数组），每一个元素都是一个 char* 值，是一个字段内容（用字符串来表示，以/0结尾）
		  char ** pName 跟pValue是对应的，表示这个字段的字段名称, 也是个1维数组
*******************************************************************************/
int  MyCallback(void*para , int n_column, char** column_value, char** column_name)
{
	String s;
	for(int i=0;i<n_column;i++)
	{
		  s+=column_name[i];
		  s+=":";
		  s+=column_value[i];
		  s+="\n";
	}
	return 0;
}

bool __fastcall SelectbufDate(Byte *buf,AnsiString bh,AnsiString rtime,int id,int flag)
{
	//打开sqlite3
	sqlite3 *database = NULL;
	char* pFileName = DB_NAME;
	int res = sqlite3_open(pFileName, &database );
	if( res != SQLITE_OK )
	{
	  //数据库打开失败
	  sqlite3_close(database);
	  return false;
	}
	//查询数据库记录
	char * errMsg = NULL;
	char** pResult;
	int nRow;
	int nCol;
	char strSql[130];
	switch(flag)
	{
	case 1:
		sprintf(strSql, "SELECT  DISTINCT bw_data from CbrtOnlinek where bw_bh = '%s' and bw_id = %d and bw_rtime = '%s'"
		,bh,id,rtime);   //SQL语句
		break;
	case 2:
		sprintf(strSql, "SELECT  DISTINCT bw_data from CbrtOfflinek where bw_bh = '%s' and bw_id = %d and bw_rtime = '%s'"
		,bh,id,rtime);   //SQL语句
		break;
	}
	res = sqlite3_get_table(database,strSql,&pResult,&nRow,&nCol,&errMsg);
	if(res != SQLITE_OK)
	{
		sqlite3_close(database);
		sqlite3_free(errMsg);
		return false;
	}

	for(int i=0;i<nRow;i++)
	{
		AnsiString sstr = pResult[nCol*(i+1)+0];
		memmove(buf,sstr.c_str(),256);
	}
	sqlite3_free_table(pResult);
	sqlite3_close(database);

	return nRow > 0 ? true:false;
}

bool __fastcall  InsertDatafromSql(char *strSql)
{

	//打开sqlite3
	sqlite3 *database = NULL;
	char* pFileName = DB_NAME;
	int res = sqlite3_open(pFileName, &database );
	if( res != SQLITE_OK )
	{
	  //数据库打开失败
	  sqlite3_close(database);
	  return false;
	}
	int flag ;
	try
	{
		flag = InsertDbDate(database, strSql);
	}
	catch(...)
	{
		return false;
	}
	//关闭sqlite3
	sqlite3_close(database);
	return true;
}