#include <stdio.h>
#include <string.h>
#include <mysql.h>  // mysql server function access

typedef struct{
    int bookid;
    char bookname[40];
    char publisher[40];
    int price;
} Book;

int main(void){

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *host = "localhost";
    char *user = "myuser";
    char *pass = "0000";
    char *db = "mydb";
    char query[255];
    int port = 3306;

    strcpy(query, "select * from book");
    conn = mysql_init(NULL);  // DB connection ready

    if(mysql_real_connect(conn, host, user, pass, db, port, NULL, 0)){
        printf("MySQL connect succes \n");
    }
    else {
        printf("MySQL connect fail \n");
        return 1;
    }

    // Query request
    // succes -> return 0; 
    if (mysql_query(conn, query)){  
        printf("query fail \n");
        return 1;
    }

    res = mysql_store_result(conn);
    Book book[100];
    int i = 0;
    while(row = mysql_fetch_row(res)){
        
        book[i].bookid = atoi(row[0]);
        strcpy(book[i].bookname, row[1]);
        strcpy(book[i].publisher, row[2]);
        book[i].price = atoi(row[3]);
        i++;
    }

    for (int j = 0; j < i; j++){
        printf("%d \t %s \t %s \t %d \n", book[j].bookid, book[j].bookname, book[j].publisher, book[j].price);
    }

    mysql_close(conn);

    return 0;
}

// cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
// libmysqlclient.so libmysqlclient.a