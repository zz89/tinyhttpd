// cgi程序，可以用别的语言更方便的写，但是功能类似。
// 这里的输入输出已经被重定向了

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *method = getenv("REQUEST_METHOD");
    char *query = NULL;
    char contentLength[1024] = {0};

    printf("Content-Type:text/html;charset=gb2312\n\n");

    // 对于POST请求，先读取Content-Length头部字段，以获取POST数据长度
    if (strcmp(method, "POST") == 0) {
        char *p = NULL;

        while ((p = getenv("CONTENT_LENGTH")) != NULL) {
            strcat(contentLength, p);
            break;
        }

        if (contentLength[0] != '\0') {
            int len = atoi(contentLength);

            if (len > 0) {
                char *buf = (char *)malloc(sizeof(char) * (len + 1));
                if (buf != NULL) {
                    fread(buf, len, 1, stdin);
                    buf[len] = '\0';
                    query = buf;
                }
            }
        }
    }
    // 对于GET请求，直接读取QUERY_STRING参数值
    else if (strcmp(method, "GET") == 0) {
        query = getenv("QUERY_STRING");
    }

    if (query != NULL) {
        char *color = strstr(query, "color=");

        printf("<html>");
        printf("<head><title>Color</title></head>");
        printf("<body>");

        if (color) {
            color += 6; // 跳过"color="这6个字符
            printf("<h1 style=\"color:%s\">Hello, world!</h1>", color);
        } else {
            printf("<h1>No color specified!</h1>");
        }

        printf("</body>");
        printf("</html>");
    } else {
        printf("<html>");
        printf("<head><title>Color</title></head>");
        printf("<body>");
        printf("<h1>Invalid request</h1>");
        printf("</body>");
        printf("</html>");
    }

    return 0;
}