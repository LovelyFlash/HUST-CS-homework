import os

# import redis


class Config:
    PROJECT_NAME = "学业分析管理系统"

    API_V1_STR = "/api/v1"

    # 用户认证相关
    SECRET_KEY = "{{cookiecutter.secret_key}}"
    ALGORITHM = "HS256"
    ACCESS_TOKEN_EXPIRE_MINUTES = 30

    # 在数据库中不必要增加或者显示的课程
    NOT_SHOW_COURSE_NAME = [
        "田径（一）",
        "田径（二）",
        "乒乓球（一）",
        "乒乓球（二）",
        "体育保健",
        "网球（一）",
        "网球（二）",
        "羽毛球（一）",
        "羽毛球（二）",
        "羽毛球（三）",
        "羽毛球（四）",
        "户外运动（一）",
        "户外运动（二）",
        "户外运动（三）",
        "户外运动（四）",
        "手球（一）",
        "手球（二）",
        "手球（三）",
        "手球（四）",
        "排球（一）",
        "排球（二）",
        "排球（三）",
        "排球（四）",
        "网球（一）",
        "网球（二）",
        "网球（三）",
        "网球（四）",
        "足球（一）",
        "足球（二）",
        "足球（三）",
        "足球（四）",
        "篮球（一）",
        "篮球（二）",
        "篮球（三）",
        "篮球（四）",
        "大众健美操（一）",
        "大众健美操（二）",
        "传统武术（一）",
        "传统武术（二）",
        "瑜伽（一）",
        "瑜伽（二）",
        "舞龙（一）",
        "舞龙（二）",
        "龙舟运动（一）",
        "龙舟运动（二）",
        "龙舟运动（三）",
        "龙舟运动（四）",
        "散打（一）",
        "散打（二）",
        "啦啦操（一）",
        "啦啦操（二）",
        "健美（一）",
        "健美（二）",
        "啦啦操（一）",
        "太急柔力球（一）",
        "太急柔力球（二）",
        "跆拳道（一）",
        "跆拳道（二）",
        "双健（一）",
        "双健（二）",
        "橄榄球（一）",
        "橄榄球（二）",
        "跑射联项（一）",
        "跑射联项（二）",
        "体育保健（一）",
        "体育保健（二）",
        "太极柔力球（一）",
        "太极柔力球（二）",
        "毽球（一）",
        "毽球（二）",
        "体育舞蹈（一）",
        "体育舞蹈（二）",
        "乒乓球（一）",
        "乒乓球（二）",
        "乒乓球（三）",
        "乒乓球（四）",
        "女子形体（一）",
        "女子形体（二）",
        "女子形体（三）",
        "女子形体（四）",
        "机械设计理论与方法（一）上",
        "工程制图（一）",
        "工程化学",
    ]

    # 数据库的配置信息
    HOSTNAME = "localhost"
    PORT = "3306"

    DATABASE = "termsystem"
    USERNAME = "root"
    PASSWORD = "jzj123"
    DB_URI = "mysql+pymysql://{}:{}@{}:{}/{}?charset=utf8".format(
        USERNAME, PASSWORD, HOSTNAME, PORT, DATABASE
    )
    DB_URI_async = "mysql+aiomysql://{}:{}@{}:{}/{}?charset=utf8".format(
        USERNAME, PASSWORD, HOSTNAME, PORT, DATABASE
    )

    SQLALCHEMY_DATABASE_URI = DB_URI
    SQLALCHEMY_DATABASE_URI_async = DB_URI_async

    # 是更新模式还是直接读取已经计算好的数据
    UPDATE_DATA = False  # True 重新计算， False 直接读取已经计算好得数据
    UPDATE_DATA_NAME = "read_from_origin"
    # 学期代号 11：第一学年上半学期
    Term_List = ["11", "12", "21", "22", "31", "32", "41", "42"]
    Grade_List = ["18", "19", "20", "21"]
    # 创建redis实例用到的参数
    REDIS_HOST = "127.0.0.1"
    REDIS_PORT = 6379
    REDIS_PASSWORD = "redis_jzj"
    # flask-session使用的参数
    # SESSION_TYPE = "redis"  # 保存session数据的地方
    # SESSION_USE_SIGNER = True  # 为session id进行签名
    # SESSION_REDIS = redis.StrictRedis(host=REDIS_HOST, port=REDIS_PORT,password=REDIS_PASSWORD)  # 保存session数据的redis配置
    PERMANENT_SESSION_LIFETIME = 86400  # session数据的有效期秒
    # SQLALCHEMY_TRACK_MODIFICATIONS = True

    # 有不及格科目学生学号缓存时间 120分钟
    FAILED_STUID_INFO_REDIS_CACHE_EXPIRES = 7200 * 2
    # 班级信息缓存时间
    CLASS_INFO_REDIS_CACHE_EXPIRES = 7200 * 2

    # 上传文件保存的文件夹
    SAVE_ROOT_DIR = "./documents/"
    SAVE_FILE_DIR = "./documents/grade/"
    SAVE_SCORE_FILE_DIR = "./documents/score/"
    SAVE_COURSE_FILE_DIR = "./documents/course/"
    SAVE_STUDENT_INFO_FILE_DIR = "./documents/studentInfo/"
    SAVE_FAILED_STUDENT_BY_TERM_FILE_DIR = "./documents/failedStudentByTerm/"
    SAVE_FAILED_STUDENT_BY_COURSE_FILE_DIR = "./documents/failedStudentExcel/"

    # 允许上传的文件
    ALLOWED_EXTENSIONS = {"xlsx"}
    # ALLOWED_EXTENSIONS_OLD = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif', 'xlsx'}

    # 如果该课程的人数少于 15 则认为该课程可能是转专业同学的课程 或者是补考的课程
    NUM_STUDENTS_IN_COURSE = 25

    # 如果四个年级 在 term 学习上该 课程人数小于 30，则认为该课程是其他学院来的 or 该课程不在该学期开设，可能是补考出现的成绩
    NUM_STUDENTS_IN_COURSE_COURSE_DIM = 30


config = Config()
