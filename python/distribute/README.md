# 学业分析系统第二版

#### backend

后端文件夹

#### frontend

前端文件夹

# setup:

1. 将distribute压缩包解压至任意位置
2. 打开distribute/setup文件夹
3. 将文件夹内"mysql-8.4.0-winx64\bin"位置(此为绝对路径，即"(...)\distribute\setup\mysql-8.4.0-winx64\bin"  ...为distribute文件夹的位置)添加到环境变量的"路径(Path)"中
4. 使用"Anaconda3-2023.09-0-Windows-x86_64.exe"安装包将Anaconda3安装到任意位置，在安装时先选择"Just Me(Recommended)"，再选择"Add Anaconda3 to my PATH environment variable"、"Register Anaconda3 as my default Python 3.11"两个选项，其余任意，再将"fastapi_env.tar.gz"压缩包拷贝到安装路径下的envs文件夹(如"D:\Anaconda3\envs")并解压
5. 使用"node-v18.17.1-x64.msi"安装包将node安装到任意位置
6. 双击打开setup.cmd两次，即同时出现两个窗口，等待运行结束 (若未成功可右键点击文件，选择"以管理员权限运行")
7. 最后回到distribute文件夹，点击start.bat启动
