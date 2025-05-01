#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较两个字符串的字典序
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n, m, k;
    
    // 读取n, m, k
    scanf("%d %d %d", &n, &m, &k);
    
    // 用指针数组存储昨天派遣潜艇的节点
    char *sent_nodes[n];
    for (int i = 0; i < n; i++) {
        sent_nodes[i] = (char *)malloc(11 * sizeof(char)); // 最大长度10+1
        scanf("%s", sent_nodes[i]);
    }

    // 用指针数组存储已完全探索的节点
    char *fully_explored_nodes[m];
    for (int i = 0; i < m; i++) {
        fully_explored_nodes[i] = (char *)malloc(11 * sizeof(char)); // 最大长度10+1
        scanf("%s", fully_explored_nodes[i]);
    }

    // 用指针数组存储新发现的节点
    char *new_discovered_nodes[k];
    for (int i = 0; i < k; i++) {
        new_discovered_nodes[i] = (char *)malloc(11 * sizeof(char)); // 最大长度10+1
        scanf("%s", new_discovered_nodes[i]);
    }

    // 使用动态数组存储今天需要探索的节点
    char *explore_today[k];
    int explore_today_count = 0;

    // 查找今天需要探索的节点
    for (int i = 0; i < k; i++) {
        int should_explore = 1;
        
        // 检查当前节点是否在已完全探索的节点中
        for (int j = 0; j < m; j++) {
            if (strcmp(new_discovered_nodes[i], fully_explored_nodes[j]) == 0) {
                should_explore = 0;
                break;
            }
        }
        
        // 如果需要探索，则加入到探索列表
        if (should_explore) {
            explore_today[explore_today_count] = new_discovered_nodes[i];
            explore_today_count++;
        }
    }

    // 对探索的节点按字典序排序
    qsort(explore_today, explore_today_count, sizeof(char *), compare);

    // 输出今天需要探索的节点
    for (int i = 0; i < explore_today_count; i++) {
        printf("%s\n", explore_today[i]);
    }

    // 释放分配的内存
    for (int i = 0; i < n; i++) {
        free(sent_nodes[i]);
    }
    for (int i = 0; i < m; i++) {
        free(fully_explored_nodes[i]);
    }
    for (int i = 0; i < k; i++) {
        free(new_discovered_nodes[i]);
    }

    return 0;
}
