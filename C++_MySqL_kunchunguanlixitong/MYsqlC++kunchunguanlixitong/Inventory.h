#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include<vector>
#include <io.h>
#include <fcntl.h>
using namespace std;
//GitHub项目地址
// https://github.com/WULINYOU/inventory
// GitHub用户名
// WULINYOU
// 联系邮箱
// 3330452578@qq.com
typedef struct Inventory {
    
    int id;                // 库存ID
    string name;           // 商品名称
    int number;            // 数量
    string type;           // 库存类型
    int price;           // 价格
    string in_time;        // 入库时间
    string out_time;       // 出库时间
    string in_op;          // 入库操作员
} Inventory;
class Com_inv
{
    Com_inv();
    ~Com_inv();
public://单例模式
    static Com_inv* GetInstance()
    {
        static Com_inv DBManager;
        return  &DBManager;
    }
       
public:
    
    bool insert_record(Inventory& i); // 插入记录
    bool update_record(Inventory& i);//更新记录
    bool delete_record(int id);//删除记录
    vector<Inventory>get_record(string condition = "");//查询记录
    bool create_table(const string& table_name); // 创建表
    vector<string>show_table();//显示表
    bool delete_table(const string& table_name); // 删除表
    void print_table(const vector<Inventory>& invList);//记录数据边框
    void print_table1(const vector<string>& invList);//表名数据边框
private:
    MYSQL* con;
    const char* host = "127.0.0.1";          // 数据库主机地址
    const char* user = "root";               // 数据库用户名
    const char* pw = "123456";               // 数据库密码
    const char* databases_name = "inventory"; // 数据库名称
    const int port = 3306;                   // 数据库端口号
};
