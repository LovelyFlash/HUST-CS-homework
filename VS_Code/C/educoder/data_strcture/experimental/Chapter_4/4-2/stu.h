void free0(void *p);

status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode *p = G.vertices[i].firstarc;
        while (p != NULL) {
            ArcNode *temp = p;
            p = p->nextarc;
            free0(temp); // 使用自定义的 free0 函数释放内存
        }
        G.vertices[i].firstarc = NULL;
    }
    G.vexnum = 0; // 清空顶点数
    G.arcnum = 0; // 清空边数
    return OK;
    /********** End **********/
}
