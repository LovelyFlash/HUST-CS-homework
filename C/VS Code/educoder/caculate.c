/*
任务描述
本关任务：实验教材P64 程序设计第(10)题
输入一段含西文字符和中文字符的正文，统计字数、字符数和行数。

注意
 在本实验环境中，一个中文字符需要三个字节的存储空间

测试说明
平台会对你编写的代码进行测试：

测试输入：
你好
hello Hello     HELLO
^Z

预期输出：
字数 5
字符数 17   (字符数不计空白符)
行数 2

开始你的任务吧，祝你成功！
*/

#include <stdio.h>
#include <ctype.h>

int main() {
    char c;
    int word_count = 0, char_count = 0, line_count = 0, i= 0;
    int in_word = 0;  // 标记是否在一个单词/汉字内

    while ((c = getchar()) != EOF) {
        // 统计行数
        if (c == '\n') {
            line_count++;
        }

        // 统计字符数（不包括空白符）
        if (c != ' ' && c != '\n' && c != '\t') {
            if (c & 0x80) {  // 检查高位是否为1，判断是否为中文字符
                ++i;
                if((i%3) == 0)
                {
                    char_count += 1;
                }   // 中文字符占3个字节
            } else {
                char_count += 1;  // 西文字符占1个字节
            }

            // 统计字数
            if (!in_word || c & 0x80) {  // 如果之前不在单词/汉字内，现在进入一个单词/汉字
                in_word = 1;

                if((i%3) == 0) 
                {
                    word_count += 1;
                } 
            }
        } else {
            in_word = 0;  // 遇到空白符时，标记为不在单词/汉字内
        }
    }

    // 输出统计结果
    printf("字数 %d\n", word_count);
    printf("字符数 %d\n", char_count);
    printf("行数 %d\n", line_count);

    return 0;
}

