#include "Inventory.h"
#include <iomanip>
//GitHub项目地址
// https://github.com/WULINYOU/inventory
// GitHub用户名
// WULINYOU
// 联系邮箱
// 3330452578@qq.com
// 
// 连接数据库模块
Com_inv::Com_inv()
{
    con = mysql_init(NULL);
    // 设置字符编码
    mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");
    if (!mysql_real_connect(con, host, user, pw, databases_name, port, NULL, 0)) {
        fprintf(stderr, "连接数据库失败:%s", mysql_error(con));
    }
}
Com_inv::~Com_inv()
{
    // 关闭数据库连接
    mysql_close(con);
}
//插入数据模块
bool Com_inv::insert_record(Inventory& inv) {
   
    
       
        char sql[1024];
        int ret = snprintf(sql, sizeof(sql), "INSERT INTO inv_table(id, name, number, type, price, in_time, out_time, in_op) "
            "VALUES ('%d', '%s', %d, '%s', %d, '%s', '%s', '%s')",
            inv.id, inv.name.c_str(), inv.number, inv.type.c_str(), inv.price,
            inv.in_time.c_str(), inv.out_time.c_str(), inv.in_op.c_str());
        // 检查 snprintf 是否成功
        if (ret < 0 || ret >= sizeof(sql)) {
            std::cerr << "构建 SQL 语句失败" << std::endl;
            return false;
        }
        if (mysql_query(con, sql)) {
            fprintf(stderr, "插入记录失败: %s\n", mysql_error(con));
            return false;
        }
        return true;
    }
     //(inv.out_time.empty() ? "NULL" : inv.out_time.c_str())
    //condition：stu.out_time.empty()，检查 out_time 字段是否为空字符串。
    //expression_if_true："NULL"，如果 out_time 为空字符串，则返回字符串 "NULL"。
    //expression_if_false：stu.out_time.c_str()，如果 out_time 不为空字符串，则返回 out_time 的 C 风格字符串。
    // 检查 snprintf 是否成功
//更新数据模块
bool Com_inv::update_record(Inventory& inv)
{
    char sql[1024];

    sprintf_s(sql, "UPDATE inv_table SET id=%d, name='%s', number=%d, type='%s', price=%d, in_time='%s', out_time=%s, in_op='%s' "
        "WHERE id=%d",
        inv.id, inv.name.c_str(), inv.number, inv.type.c_str(), inv.price,
        inv.in_time.c_str(), (inv.out_time.empty() ? "NULL" : inv.out_time.c_str()), inv.in_op.c_str(), inv.id);

    if ( mysql_query(con, sql))
    {
        fprintf(stderr, "更新失败:%s\n", mysql_error(con));
        return false;
    }
    return true;
}
//删除数据模块
bool Com_inv::delete_record(int id)
{
    char sql[1024];
    sprintf_s(sql, "DELETE FROM inv_table where id=%d", id);
    if ( mysql_query(con, sql))
    {
        fprintf(stderr, "删除失败:%s\n", mysql_error(con));
        return false;
    }
    return true;
}
//查询数据模块
vector<Inventory> Com_inv::get_record(string condition)
{
    vector<Inventory> InvList;
    char sql[1024];
    int ret = sprintf_s(sql, sizeof(sql), "SELECT * FROM inv_table WHERE %s;", condition.c_str());
    if (ret < 0 || ret >= sizeof(sql)) {
        cout << "SELECT SQL ERROR." << endl;
        return {};
    }
    if (mysql_query(con, sql) != 0) {
        cout << "查询失败:" << mysql_error(con) << endl;
        return {};
    }
    MYSQL_RES* res = mysql_store_result(con);
    if (res == NULL) {
        cout << "查询失败: " << mysql_error(con) << endl;
        return {};
    }
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Inventory inv;
        inv.id = atoi(row[0]);
        inv.name = row[1] ? row[1] : "";
        inv.number = atoi(row[2]);
        inv.type = row[3] ? row[3] : "";
        inv.price = atoi(row[4]);
        inv.in_time = row[5] ? row[5] : "";
        inv.out_time = row[6] ? row[6] : "";
        inv.in_op = row[7] ? row[7] : "";
        InvList.push_back(inv);
    }
    mysql_free_result(res);
    return vector<Inventory>(InvList);
}

//新建数据表模块
bool Com_inv::create_table(const string& table_name)
{
    char sql[1024];
    sprintf_s(sql, "CREATE TABLE %s ("
        "id INT PRIMARY KEY AUTO_INCREMENT, "
        "name VARCHAR(255), "
        "number INT, "
        "type VARCHAR(255), "
        "price INT, "
        "in_time DATETIME, "
        "out_time DATETIME, "
        "in_op VARCHAR(255))", table_name.c_str());
    if (mysql_query(con, sql) != 0) {
        cerr << "创建表失败: " << mysql_error(con) << endl;
        return false;
    }
    return true;
}
//显示数据表模块
vector<string> Com_inv::show_table()
{
    vector<string> tables;
    MYSQL_RES* res;
    MYSQL_ROW row;
    if (mysql_query(con, "SHOW TABLES")) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return tables;
    }
    res = mysql_store_result(con);
    if (res == NULL) {
        fprintf(stderr, "查询失败: %s\n", mysql_error(con));
        return tables;
    }
    while ((row = mysql_fetch_row(res))) {
        tables.push_back(row[0]);
    }
    mysql_free_result(res);
    return tables;
}
//删除数据表模块
bool Com_inv::delete_table(const string& table_name)
{
    // 用户输入密钥确认
    string input_key;
    cout << "请输入删除表的密钥: ";
    cin >> input_key;
    // 假设密钥为 "123456"，实际应用中应使用更安全的方式存储和验证密钥
    string correct_key = "123456";
    if (input_key != correct_key) {
        cerr << "密钥错误，无法删除表" << endl;
        return false;
    }
    // 构建 SQL 语句
    string sql = "DROP TABLE IF EXISTS " + table_name;
    // 执行 SQL 语句
    if (mysql_query(con, sql.c_str()) != 0) {
        cerr << "删除表失败: " << mysql_error(con) << endl;
        return false;
    }
    return true;
}
// 打印表格边框函数
void Com_inv::print_table(const vector<Inventory>& invList)
{
    // 打印表头
    cout << "+------+------------------+--------+-------------+---------------+---------------------------+---------------------+----------------+" << endl;
    cout << "| ID   | Name             | Number | Type        |     Price     | In Time                   | Out Time            | In Op          |" << endl;
    cout << "+------+------------------+--------+-------------+---------------+---------------------------+---------------------+----------------+" << endl;
    // 打印记录
    for (const auto& inv : invList) {
        cout << "| " << setw(2) << inv.id << " | "
            << setw(16) << left << inv.name << " | "
            << setw(6) << inv.number << " | "
            << setw(8) << inv.type << "    | "
            << setw(6) << fixed << setprecision(2) << inv.price << "        | "
            << setw(19) << inv.in_time << "       | "
            << setw(19) << inv.out_time << " |"
            << setw(16) << inv.in_op << "|" << endl;
        cout << "+------+------------------+--------+-------------+---------------+---------------------------+---------------------+----------------+" << endl;
    } 
}

// 打印表名边框函数
void Com_inv::print_table1(const vector<string>& tables)
{
    // 打印表头
    cout << "+--------------------+" << endl;
    cout << "| 表名               |" << endl;
    cout << "+--------------------+" << endl;
    // 打印表名
    for (const auto& table : tables) {
        cout << "| " << setw(16) << left << table << "   |" << endl;
        cout << "+--------------------+" << endl;
    }
}

 