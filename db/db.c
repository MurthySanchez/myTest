#include <stdio.h>
#include "mysql.h"

int main(void){
	MYSQL mysql;
	mysql_init(&mysql);
	mysql_real_connect(&mysql,"localhost","root","123456","LWJ",3306,NULL,0);
	mysql_free_result(res);
	mysql_close(&mysql);
	return 0;
}
