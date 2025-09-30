mysqld --initialize-insecure --user=mysql 
mysqld 
net start mysql
mysqladmin -uroot password jzj123
mysql -uroot -pjzj123 -e "CREATE DATABASE termsystem"
mysql -uroot -pjzj123 -e "USE termsystem"
mysql -uroot -pjzj123 -e "SET @@global.sql_mode= '';"
mysql -uroot -pjzj123 -D termsystem < termsystem.sql --default-character-set=utf8

pause