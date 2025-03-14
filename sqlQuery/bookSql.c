#include <mysql.h>
#include <stdio.h>
#include <string.h>
// sudo apt install libmysql++*
// dpkg -L libmysqlclient-dev | grep mysql.h
// cc -o bookSql bookSql.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
// libmysqlclient.so libmysqlclient.a
enum menu{
    SELECT,
    INSERT,
    DROP,
    ALTER,
    QUERY
};

typedef struct
{
    int bookid;
    char bookname[40];
    char publisher[40];
    int price;
} Book;

void fetch_books(MYSQL *conn);
void add_books(MYSQL *conn);
void delete_books(MYSQL *conn);
void update_books(MYSQL *conn);
void query_books(MYSQL *conn);
void print_menu(void);

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
    while (true)
    {
        //printf("1 , 2 번 고르세요!");
        print_menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case SELECT:
            fetch_books(conn);
            break;
        case INSERT:
            add_books(conn);
            break;
        case DROP:  
            delete_books(conn);
            break;
        case ALTER:    
            update_books(conn);
            break;
        case QUERY:
            query_books(conn);
            break;
        }
    }

    mysql_close(conn);

    return 0;
}
void add_books(MYSQL *conn)
{
    printf("--- 도서 추가 ---\n");
    Book newbook;
    char query[255];
    // 정보 입력 scanf
    printf("ID : ");
    scanf("%d", &newbook.bookid);
    printf("NAME : ");
    scanf("%s", newbook.bookname);
    printf("PUBLISHER : ");
    scanf("%s", newbook.publisher);
    printf("PRICE : ");
    scanf("%d", &newbook.price);
    // query 문 작성 strcpy... "insert ....."
    sprintf(query, "insert into book value (%d, %s, %s, %d)",newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
    // sprintf(query, "insert into Book values (%d, '%s', '%s', %d)", newbook.bookid, .....);
    // query 요청 mysql_query();
    if (mysql_query(conn, query)){
        printf("data fail : %s \n", mysql_error(conn));
    }
    else{
        printf("succes \n");
    }
    return;
}

void delete_books(MYSQL *conn)
{
    // index 번호 받기scanf
    int bookid;
    printf("Enter the bookid you want delete : ");
    scanf("%d", &bookid);
    // 지우는 쿼리
    char query[255];
    char temp[] = ;
    
    sprintf(query, "delete 
                     from  book 
                    where  bookid == %d", bookid);

    if (mysql_query(conn, query))
    {
        printf("쿼리 실패 : %s", mysql_error(conn));
    }
    else{
        my_ulonglong affected_row = mysql_affected_rows(conn);
        printf("delete success \n")   
    }
}
void update_books(MYSQL *conn)
{
    // 모든 번호 받기scanf
    
    // 변경하는 쿼리
    Book newbook;
    char query[255];
    sprintf(query, "update book 
                    set    bookname = %s, publisher = %s, price = %d
                    where  bookid = %d", newbook.bookname, newbook.price, newbook.publisher, newbook.bookid);
    
    if (mysql_query(conn, query))
    {
        printf("data update 실패");
        return;
    }
}
void query_books(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    // 쿼리 스트링을 받아서
    char query[255];
    printf("Enter Query: ");
    scanf("%s", query);

    // 쿼리 요청
    if (mysql_query(conn, query))
    {
        printf("쿼리 실패 : %s \n", mysql_error(conn));
        return;
    }
    
    res = mysql_store_result(conn);
    
    // 결과 프린트
    if (res){
        while(row = mysql_fetch_row(res)){
            for (int i = 0; i < mysql_num_field(res); i++){
                printf("%s", row[i]);
            }
        }
    }
    else{
        printf("가져오기 실패!\n");
        return;
    }
}
void fetch_books(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    Book *pBook; 
    char query[255];
    
    strcpy(query, "select * from book");

    // 쿼리 요청
    if (mysql_query(conn, query))
    {
        printf("쿼리 실패");
        return;
    }

    res = mysql_store_result(conn);
    if (!res)
    {
        printf("가져오기 실패!\n");
        return;
    }

    pBook = (Book *)malloc(sizeof(Book));  // dynamic 
    // Book book[100]; // 동적 할당이 좋지만 일단... 스택에 만들자.
    int i = 0;
    // 데이터 베이스의 정보를 구조체에 저장 - ORM
    while (row = mysql_fetch_row(res))
    {
        (pBook+i)->bookid = atoi(row[0]);
        strcpy((pBook+i)->bookname, row[1]);
        strcpy((pBook+i)->publisher, row[2]);
        (pBook+i)->price = atoi(row[3]);
        ++i;
        pBook = realloc(pBook, sizeof(Book)*(i + 1));
    }

    for (int j = 0; j < i; j++)
    {
        printf("%d \t%s \t%s \t%d \n",
               (pBook+j)->bookid, (pBook+j)->bookname,
               (pBook+j)->publisher, (pBook+j)->price);
    }

    free(pBook);

    // TODO: 여기 엔터만 쳐도 넘어가게 변경
    waitEnter();

}

void print_menu(void){
    system("clear");

    printf("=== Book Control System")
    printf("0. Book Search \n")
    printf("1. Add Book \n")
    printf("2. Delete Book \n")
    printf("3. Alter Book \n")
    printf("4. Enter Query \n")
} 

void waitEnter(void){
   
    char ch;

    printf("엔터를 쳐 주세요....\n");

    while (ch != '\n');
}