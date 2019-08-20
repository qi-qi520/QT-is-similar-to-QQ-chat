#ifndef _DATAMESSAGE_
#define _DATAMESSAGE_

#include <sqlite3.h>

/**********************************************************************************
 * 函数：       db_create
 * 功能描述：   创建数据库mydb，如果没有相应的数据表会创建
 *                          1.user表（id,username,userpass,usericon）
 *                          2.userfriend表（Aid,Bid）
 *                          3.online临时表（id,isonline，sockfd）
 * 参数：       无
 * 返回值：     数据库的文件描述符,NULL传建失败
 * 其他：       无
**********************************************************************************/
sqlite3 *db_create(void);

/**********************************************************************************
 * 函数：       sign_in_db
 * 功能描述：   登录函数
 * 参数：       db: db_create()函数返回值
 *              id:用户id(至少8位数)
 *              userpass:用户密码
 *              username:查找到用户和密码正确回返回用户名
 *              usericon:查找到用户和密码正确回返回用户图标
 *              sockfd:客户端的套接字
 * 返回值：     -1代表失败，0代表成功，1表示在线
 * 其他：       无
**********************************************************************************/
int sign_in_db(sqlite3 *db,int id,char *userpass,char *username,char *usericon,int sockfd);

/**********************************************************************************
 * 函数：       logon_db
 * 功能描述：   注册函数
 * 参数：       db: db_create()函数返回值
 *              id:用户id(至少8位数)
 *              userpass:用户密码
 *              username:用户密码
 * 返回值：     -1代表失败，0代表成功，1表示用户已存在
 * 其他：       有个默认图标
**********************************************************************************/
int logon_db(sqlite3 *db,int id,char *username,char *userpass);

/**********************************************************************************
 * 函数：       find_friend_db
 * 功能描述：   查找A的朋友函数
 * 参数：       db: db_create()函数返回值
 *              Aid:用户id(至少8位数)
 *              n:返回的朋友数
 *              m:字段数
 *              pazresult：返回的结果，可用n,m进行遍历
 * 返回值：     -1代表失败，0代表成功，1表示无朋友
 * 其他：       一个朋友字段包括：朋友id、朋友名、朋有在线信息（0不在线，1在线）、朋友图标
**********************************************************************************/
int find_friend_db(sqlite3 *db,int Aid,int *n,int *m,char ***pazresult);

/**********************************************************************************
 * 函数：       add_friend_db
 * 功能描述：   添加朋友函数
 * 参数：       db: db_create()函数返回值
 *              Aid:A用户id(至少8位数)
 *              Bid:B用户id（至少8位数）
 * 返回值：     -1代表失败，0代表成功，1表示本就是朋友关系
 * 其他：       无
**********************************************************************************/
int add_friend_db(sqlite3 *db,int Aid,int Bid);

/**********************************************************************************
 * 函数：       delete_friend_db
 * 功能描述：   删除朋友函数
 * 参数：       db: db_create()函数返回值
 *              Aid:A用户id(至少8位数)
 *              Bid:B用户id（至少8位数）
 * 返回值：     -1代表失败，0代表成功，1表示本就不是朋友关系
 * 其他：       无
**********************************************************************************/
int delete_friend_db(sqlite3 *db,int Aid,int Bid);

/**********************************************************************************
 * 函数：       update_online_db
 * 功能描述：   更新用户在线信息
 * 参数：       db: db_create()函数返回值
 *              id:用户id(至少8位数)
 * 返回值：     -1代表失败，0代表成功
 * 其他：       无
**********************************************************************************/
int update_online_db(sqlite3 *db,int sockfd);

/**********************************************************************************
 * 函数：       update_user_db
 * 功能描述：   更新用户信息
 * 参数：       db: db_create()函数返回值
 *              id:用户id(至少8位数)
 *              username：更改的用户名
 *              usericon：更改的图标
 * 返回值：     -1代表失败，0代表成功
 * 其他：       无
**********************************************************************************/
int update_user_db(sqlite3 *db,int id,char *username,char *usericon);

/*********************************************************************************
 * 函数：   db_close
 * 功能描述：关闭数据库
 * 参数：   db :db_create()的返回值
 * 返回值   ：0：代表成功、-1代表失败
 * 其他：
*********************************************************************************/
int db_close(sqlite3 *db);

/*********************************************************************************
 * 函数：   find_sockfd_db
 * 功能描述：查找id的套接字
 * 参数：   db :db_create()的返回值
 *          id:要查找的用户id
 *          sockfd:返回的套接字
 * 返回值   ：0：代表成功、-1代表失败,1表示不在线
 * 其他：
*********************************************************************************/
int find_sockfd_db(sqlite3* db,int id,int *sockfd);
#endif