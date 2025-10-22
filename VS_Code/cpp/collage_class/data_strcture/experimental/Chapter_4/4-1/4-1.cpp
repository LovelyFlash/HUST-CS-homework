#include "def.h"
#include "stu.h"
int main()
{
ALGraph G;
VertexType V[30];
KeyType VR[100][2];
int i=0,j;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
if (CreateCraph(G,V,VR)==ERROR) printf("输入数据错，无法创建");
else 
    {
         if (G.arcnum!=i-1) {
     	    printf("边的数目错误！\n");
            return 0; 
        }
        for(j=0;j<G.vexnum;j++)
	    {
            ArcNode *p=G.vertices[j].firstarc;
            printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
            while (p)
            {
                printf(" %d",p->adjvex);
                p=p->nextarc;
            }
            printf("\n");
	    }
    }
    return 1;
}
