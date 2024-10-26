#include "Inventory.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//GitHub项目地址
// https://github.com/WULINYOU/inventory
// GitHub用户名
// WULINYOU
// 联系邮箱
// 3330452578@qq.com
int main() {
    // 假设 db 是一个已经初始化的数据库对象
    Com_inv* db = Com_inv::GetInstance();

    while (true) {
        cout << "-----------------------" << endl;
        cout << "请选择操作：" << endl;
        cout << "1. 表操作" << endl;
        cout << "2. 记录操作" << endl;
        cout << "3. 退出" << endl;
        cout << "-----------------------" << endl;
        cout << "请输入序号: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {  // 表操作
            cout << "表操作：" << endl;
            cout << "1. 创建表" << endl;
            cout << "2. 删除表" << endl;
            cout << "3. 查询所有表" << endl;
            cout << "请输入序号: ";

            int table_choice;
            cin >> table_choice;

            switch (table_choice) {
            case 1: {  // 创建表
                string table_name;
                cout << "请输入表名: ";
                cin >> table_name;
                if (db->create_table(table_name)) {
                    cout << "表 " << table_name << " 创建成功" << endl;
                }
                else {
                    cout << "表 " << table_name << " 创建失败" << endl;
                }
                break;
            }
            case 2: {  // 删除表
                string table_name;
                cout << "请输入表名: ";
                cin >> table_name;
                if (db->delete_table(table_name)) {
                    cout << "表 " << table_name << " 删除成功" << endl;
                }
                else {
                    cout << "表 " << table_name << " 删除失败" << endl;
                }
                break;
            }
            case 3: {  // 查询所有表
                vector<string> tables = db->show_table();
                if (!tables.empty()) {
                    cout << "数据库中的表:" << endl;
                    db->print_table1(tables);
                }
                else {
                    cout << "没有找到任何表" << endl;
                }
                break;
            }
            default:
                cout << "无效的选择" << endl;
            }
            break;
        }
        case 2: {  // 记录操作
            cout << "记录操作：" << endl;
            cout << "1. 插入记录" << endl;
            cout << "2. 更新记录" << endl;
            cout << "3. 删除记录" << endl;
            cout << "4. 查询记录" << endl;
            cout << "请输入序号: ";

            int record_choice;
            cin >> record_choice;

            switch (record_choice) {
            case 1: {  // 插入记录
                Inventory inv;
                cout << "请输入库存ID: ";
                cin >> inv.id;
                cout << "请输入商品名称: ";
                cin >> inv.name;
                cout << "请输入数量: ";
                cin >> inv.number;
                cout << "请输入库存类型:(成品库存、季节库存、退货库存) ";
                cin >> inv.type;
                cout << "请输入价格: ";
                cin >> inv.price;
                cout << "请输入入库时间 (格式: YYYY-MM-DD HH:MM:SS): ";
                cin >> inv.in_time;
                cout << "请输入出库时间 (格式: YYYY-MM-DD HH:MM:SS, 可以输入 NULL): ";
                cin >> inv.out_time;
                cout << "请输入入库操作员: ";
                cin >> inv.in_op;

                if (db->insert_record(inv)) {
                    cout << "记录插入成功" << endl;
                }
                else {
                    cout << "记录插入失败" << endl;
                }
                break;
            }
            case 2: {  // 更新记录
                Inventory inv;
                cout << "请输入库存ID: ";
                cin >> inv.id;
                cout << "请输入商品名称: ";
                cin >> inv.name;
                cout << "请输入数量: ";
                cin >> inv.number;
                cout << "请输入库存类型:(成品库存、季节库存、退货库存) ";
                cin >> inv.type;
                cout << "请输入价格: ";
                cin >> inv.price;
                cout << "请输入入库时间 (格式: YYYY-MM-DD HH:MM:SS): ";
                cin >> inv.in_time;
                cout << "请输入出库时间 (格式: YYYY-MM-DD HH:MM:SS, 可以输入 NULL): ";
                cin >> inv.out_time;
                cout << "请输入入库操作员: ";
                cin >> inv.in_op;

                if (db->update_record(inv)) {
                    cout << "记录更新成功" << endl;
                }
                else {
                    cout << "记录更新失败" << endl;
                }
                break;
            }
            case 3: {  // 删除记录
                int id;
                cout << "请输入要删除的记录ID: ";
                cin >> id;

                if (db->delete_record(id)) {
                    cout << "记录删除成功" << endl;
                }
                else {
                    cout << "记录删除失败" << endl;
                }
                break;
            }
            case 4: {  // 查询记录
                string condition;
                cout << "日常条件1  price>200 ";
                cout << "日常条件2 *";
                cout << "请输入查询条件: ";
                cin >> condition;

                vector<Inventory> invList = db->get_record(condition);

                if (invList.empty()) {
                    cout << "没有找到符合条件的记录" << endl;
                }
                else {
                    db->print_table(invList);
                }
                break;
            }
            default:
                cout << "无效的选择" << endl;
            }
            break;
        }
        case 3: {  // 退出
            cout << "退出程序" << endl;
            return 0;
        }
        default:
            cout << "无效的选择" << endl;
        }
    }

    return 0;
}