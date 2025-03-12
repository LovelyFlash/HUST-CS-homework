.\setup\mysql-8.4.0-winx64\bin\mysqld
start cmd /k "cd ./Redis-x64-5.0.14.1 &&redis-server.exe redis.windows.conf"
start cmd /k "cd backend &&conda activate fastapi_env &&python main.py"
start cmd /k "cd frontend &&npm run dev"