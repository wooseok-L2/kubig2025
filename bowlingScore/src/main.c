#include "bbowling.h"


int main(void)
{
    MYSQL *conn;
    char *host = "localhost";
    char *user = "myuser";
    char *pass = "0000";
    char *db = "mydb";
    int port = 3306;
    int choice;

    // 연결
    conn = mysql_init(NULL); // DB 연결 요청 준비
    if (mysql_real_connect(conn, host, user, pass, db, port, NULL, 0))
        printf("MySQL 연결 성공\n");
    else
    {
        printf("MySQL 연결 실패\n");
        return 1;
    }

    while(true){
        printf_menu();
        scanf("%d%*c", &choice);
        switch (choice){
        case START:
            gamestart();
            printf("next level \n");
            add_score(conn);  
            waitEnter();              
            break;
        case SCORE:
            checkscore(conn);
            waitEnter();
            break;
        case HISTORY:
            checkHistory(conn);
            waitEnter();
            break;
        }

        printf("If you want to exit, press enter! \n");

    }

    mysql_close(conn);

    return 0;
}