@echo off
setlocal

:: 切换到脚本所在目录（确保找到termsystem.sql）
:: 此代码需要用户自行修改为当前安装目录
cd /d "F:\Programming\Code\VS_Code\python\distribute\setup"

:: 1. 初始化MySQL（如果data目录已存在，先删除）
if exist "data\" (
    echo 正在移除旧的data目录...
    rmdir /s /q "data"
)
mysqld --initialize-insecure --user=mysql

:: 2. 安装并启动服务
mysqld --install mysql
net start mysql

:: 3. 等待服务启动
timeout /t 5

:: 4. 设置root密码和数据库
mysqladmin -uroot password jzj123
mysql -uroot -pjzj123 -e "CREATE DATABASE termsystem"
mysql -uroot -pjzj123 -e "SET GLOBAL sql_mode=''"

:: 5. 导入SQL文件（使用当前目录下的termsystem.sql）
if exist "termsystem.sql" (
    echo 正在导入termsystem.sql...
    mysql -uroot -pjzj123 termsystem --default-character-set=utf8 < termsystem.sql
    echo 导入完成！
) else (
    echo 错误：未找到termsystem.sql文件！
    pause
    exit /b 1
)

pause