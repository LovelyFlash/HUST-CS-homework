import pandas as pd
from pandas import DataFrame
from pypinyin import pinyin,Style
from itertools import chain


def create_form(excel_file_name,data,form_header):
    """创建带表头的 dataFrame
    Args:
        excel_file_name (_type_): _description_
    """
    df = pd.DataFrame(data=data, columns=form_header)
    df.to_excel(excel_file_name,index=False)

def to_pinyin(s):
    """
    转拼音
    :param s: 字符串或列表
    :type s: str or list
    :return: 拼音字符串
    >>> to_pinyin('你好吗')
    'ni3hao3ma'
    >>> to_pinyin(['你好', '吗'])
    """
    return ''.join(chain.from_iterable(pinyin(s,style=Style.TONE3)))