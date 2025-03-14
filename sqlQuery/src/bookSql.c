#include "booksql.h"

void print_menu(void)
{
    system("clear");
    printf("=== 도서 관리 시스템 ===\n");
    printf("0. 도서 조회\n");
    printf("1. 도서 추가\n");
    printf("2. 도서 삭제\n");
    printf("3. 도서 변경\n");
    printf("4. 쿼리문 입력\n");
}

void add_books(MYSQL *conn)
{
    printf("--- 도서 추가 ---\n");
    Book newbook;
    char query[255];
    // 정보 입력 scanf
    printf("도서 ID: ");
    scanf("%d%*c", &newbook.bookid);
    printf("도서 명: ");
    scanf("%s%*c", newbook.bookname);
    printf("출판사: ");
    scanf("%s%*c", newbook.publisher);
    printf("가격: ");
    scanf("%d%*c", &newbook.price);
    // query 문 작성 strcpy... "insert ....."
    sprintf(query, "insert into Book values (%d, '%s', '%s', %d)", newbook.bookid, newbook.bookname, newbook.publisher, newbook.price);
    // query 요청 mysql_query();
    if (mysql_query(conn, query))
    {
        printf("데이터 입력 실패: %s\n", mysql_error(conn));
    }
    else
    {
        printf("입력 성공\n");
    }

    return;
}

void delete_books(MYSQL *conn)
{
    int bookid;
    printf("삭제할 도서명 : ");
    scanf("%d%*c", &bookid);
    char query[255];
    sprintf(query, "delete from book where bookid = %d", bookid);

    if (mysql_query(conn, query))
    {
        printf("쿼리 실패 : %s", mysql_error(conn));
    }
    else
    {
        my_ulonglong affected_row = mysql_affected_rows(conn);
        printf("삭제 성공 : %lu 개", affected_row);
    }
}

void update_books(MYSQL *conn)
{
    printf("--- 도서 변경 ---\n");
    Book newbook;
    char query[255];
    // 정보 입력 scanf
    printf("변경할 도서 ID: ");
    scanf("%d%*c", &newbook.bookid);
    printf("도서 명: ");
    scanf("%s%*c", newbook.bookname);
    printf("출판사: ");
    scanf("%s%*c", newbook.publisher);
    printf("가격: ");
    scanf("%d%*c", &newbook.price);

    sprintf(query, "update book set bookname = '%s', publisher = '%s', price = %d where bookid = %d", newbook.bookname, newbook.publisher, newbook.price, newbook.bookid);
    // query 요청 mysql_query();
    if (mysql_query(conn, query))
    {
        printf("데이터 변경 실패: %s\n", mysql_error(conn));
    }
    else
    {
        printf("변경 성공\n");
    }
    int temp;
    getchar();
    scanf("%d%*c", &temp);
}

void query_books(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[255];
    printf("실행할 쿼리를 넣어 주세요: ");
    fgets(query, sizeof(query), stdin);
    query[strcspn(query, "\n")] = 0;
    printf("쿼리 : %s\n", query);

    if (mysql_query(conn, query))
    {
        printf("쿼리 실패, %s\n", mysql_error(conn));
        return;
    }
    res = mysql_store_result(conn);
    if (res)
    {
        while (row = mysql_fetch_row(res))
        {
            for (int i = 0; i < mysql_num_fields(res); ++i)
            {
                printf("%s\t", row[i]);
            }
            printf("\n");

        }
    }
    else
    {
        printf("요청한 데이터가 없습니다.\n");
    }
    waitEnter();
}

void fetch_books(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
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
    Book *pBook;
    pBook = (Book *)malloc(sizeof(Book));
    int i = 0;
    // 데이터 베이스의 정보를 구조체에 저장 - ORM
    while (row = mysql_fetch_row(res))
    {
        (pBook + i)->bookid = atoi(row[0]);
        strcpy((pBook + i)->bookname, row[1]);
        strcpy((pBook + i)->publisher, row[2]);
        (pBook + i)->price = atoi(row[3]);
        ++i;
        pBook = realloc(pBook, sizeof(Book) * (i + 1));
    };
    for (int j = 0; j < i; ++j)
    {
        printf("%d \t%s \t%s \t%d \n",
               (pBook + j)->bookid, (pBook + j)->bookname,
               (pBook + j)->publisher, (pBook + j)->price);
    }
    free(pBook);
    // TODO: 여기 엔터만 쳐도 넘어가게 변경
    char temp;
    getchar();
    scanf("%c%*c", &temp);
}

void waitEnter(void)
{
    printf("엔터를 쳐 주세요....\n");
    char temp;
    while (temp != '\n')
        scanf("%c%*c", &temp);
}