#ifndef __DPLL__
#define __DPLL__
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<windows.h>
#define TIMELIMIT 20000

namespace mystl{

    template<class T>
    class queue{
        private:
        struct Node{
            T data;
            Node *next;
            Node():next(nullptr){}
        };
        Node *head,*tail;
        public:
        queue(){
            head=tail=nullptr;
        }
        // ~queue(){
        //  for(Node *p=head;p!=nullptr;){
        //      Node *temp=p;
        //      p=p->next;
        //      delete temp;
        //  }
        // }
        void push(T a){
            Node *newnode=new Node;
            newnode->data=a;
            newnode->next=nullptr;
            if(head==nullptr){
                head=tail=newnode;
            }else{
                tail->next=newnode;
                tail=newnode;
            }
        }
        bool empty(){
            return head==nullptr;
        }
        T pop(){
            if(empty()) throw "queue pop on empty";
            T a=head->data;
            Node *tmp=head;
            head=head->next;
            delete tmp;
            return a;
        }
        
    };

    template<class T>
    class stack{
        private:
        struct Node{
            T data;
            Node* next;
            Node():next(nullptr){}
        } *head;

        public:
        stack():head(nullptr){}
        void push(T a){
            Node *newnode = new Node;
            newnode->data=a;
            newnode->next=head;
            head=newnode;
        }
        bool empty(){
            return head==nullptr;
        }
        T pop(){
            if(empty()) throw "stack pop on empty";
            Node *p=head;
            T a=p->data;
            head=head->next;
            delete p;
            return a;
        }
    };

};

struct CNF{
    int diff_var;
    int ans_cnt;
    bool timeout;
    bool solved;
    std::string path;
    clock_t start;
    int var_c=-1,cls_c=-1;
    double ms;
    bool flag;
    bool *value[2];
    struct Node{
        bool sign;
        bool status;
        int var,cls;
        Node *vnxt,*vpre,*cnxt,*cpre;
        Node():sign(true),status(false),vnxt(nullptr),vpre(nullptr),cnxt(nullptr),cpre(nullptr),var(-1),cls(-1){}

    };
    struct Title{
        int num;
        bool status;
        Node head;
        Title():num(0),status(false){}
        
    } *var,*cls;

    void push(int c,int v,bool sign){
        v=abs(v);
        Node *newnode=new Node;
        newnode->sign=sign;
        newnode->var=v;
        newnode->cls=c;
        newnode->cnxt=cls[c].head.cnxt;
        if(newnode->cnxt!=nullptr) newnode->cnxt->cpre=newnode;
        cls[c].head.cnxt=newnode;
        newnode->cpre=&cls[c].head;
        cls[c].num++;

        newnode->vnxt=var[v].head.vnxt;
        if(newnode->vnxt!=nullptr) newnode->vnxt->vpre=newnode;
        var[v].head.vnxt=newnode;
        newnode->vpre=&var[v].head;
        var[v].num++;
    }
    
    CNF():var_c(-1),cls_c(-1),var(nullptr),cls(nullptr),flag(false),solved(false),timeout(false),ans_cnt(0),diff_var(0){
        value[0]=nullptr;
        value[1]=nullptr;
    }

    bool read(const char file[]){//cnf文件读取
        path=std::string(file);
        FILE *fin=fopen(file,"r");
        if(!fin){
            throw "文件读取失败";
            return false;
        }
        int cl=0;//读取字句的序号
        while(!feof(fin)){
            char buff[1000];
            fgets(buff,1000,fin);
            if(*buff=='c'){//注释
                continue;
            }
            else if(*buff=='p'){//初始化
                if(var_c!=-1&&cls_c!=-1){
                    throw "CNF文件错误:文件信息重复定义";
                    return false;
                }
                char format[100];
                char temp;
                try{
                    sscanf(buff,"%c%s%d%d",&temp,format,&var_c,&cls_c);
                }
                catch(const std::exception& e){
                    throw e.what();
                    return false;
                }
                if(strcmp(format,"cnf")!=0){
                    throw "CNF文件错误:文件类型错误";
                    return false;
                }
                if(var_c<=0||cls_c<=0){
                    throw "CNF文件错误:文件信息错误";
                    return false;
                }
                var=new Title[var_c+1];
                cls=new Title[cls_c+1];
                value[0]=new bool[var_c+1];
                value[1]=new bool[var_c+1];
                memset(value[0],0,(var_c+1)*sizeof(bool));
                memset(value[1],0,(var_c+1)*sizeof(bool));
            }
            else if(*buff>='0'&&*buff<='9'||*buff=='-'){
                cl++;
                if(cl>cls_c){
                    // std::cout<<"CNF文件错误:字句过多,将忽略多余字句\n";
                    break;
                }
                int a;
                char *bp=buff;
                while(1){
                    if(*bp=='\0'){
                        throw "CNF文件错误:缺失子句终止标识";
                        return false;
                    }
                    int a=0,f=1;
                    while(*bp!=' '&&*bp!='\n'&&*bp!='\0'){
                        if(*bp=='-') f=-1;
                        else if(*bp>='0'&&*bp<='9'){
                            a=a*10+*bp-'0';
                        }
                        else{
                            // std::cerr<<buff<<" bp:"<<(int)(*bp)<<std::endl;
                            throw "CNF文件错误:数字中含有非法字符";
                            return false;
                        }
                        bp++;
                    }
                    a*=f;
                    if(a==0) break;
                    // cls_mp[cl].join(a);
                    push(cl,a,a>0);
                    bp++;
                }
            }
            else{
                throw "CNF文件错误:未知标识符";
                return false;
            }
        }

        if(cl<cls_c) throw "CNF error:clause not enough";
        fclose(fin);
        return true;
    }

    CNF(const char file[]):var_c(-1),cls_c(-1),var(nullptr),cls(nullptr),flag(false),solved(false),timeout(false),ans_cnt(0),diff_var(0){
        value[0]=nullptr;
        value[1]=nullptr;
        this->read(file);
    }

    bool write(const char file[]){
        if(!solved){
            throw "SAT not solved";
            return false;
        }
        std::fstream out(file,std::ios::out);
        out<<*this<<std::endl;
        return true;
    }

    void del(Node *p,mystl::stack<Node*> &bp){
        p->status=true;
        var[p->var].num--;
        cls[p->cls].num--;
        bp.push(p);
    }
    void rec(mystl::stack<Node*> &bp){
        while(!bp.empty()){
            Node *p=bp.pop();
            if(!p->status) continue;
            p->status=false;
            var[p->var].num++;
            cls[p->cls].num++;
            var[p->var].status=false;
            cls[p->cls].status=false;
        }
    }

    void del_cls(int c,mystl::stack<Node*> &bp){
        for(Node *i=cls[c].head.cnxt;i!=nullptr;i=i->cnxt){
            if(i->status) continue;
            del(i,bp);
            if(var[i->var].num==0) var[i->var].status=true;
        }
        cls[c].status=true;
    }

    void del_var(int v,bool sign,mystl::stack<Node*> &bp){
        value[ans_cnt][v]=sign;
        for(Node *i=var[v].head.vnxt;i!=nullptr;i=i->vnxt){//遍历变元所在的子句
            if(i->status) continue;
            if(sign^i->sign){//符号相反，删除文字
                del(i,bp);
            }else{//符号相同，删除子句
                del_cls(i->cls,bp);
            }
        }
        var[v].status=true;
    }

    bool simplify(mystl::stack<Node*> &bp){//单子句传播
        mystl::queue<int> q;
        for(int i=1;i<=cls_c;i++){//单子句入队
            if(cls[i].status) continue;
            if(cls[i].num==0) return false;
            if(cls[i].num==1) q.push(i);
        }
        
        while(!q.empty()){//去除单子句
            int c=q.pop();
            if(cls[c].status) continue;
            if(cls[c].num==0) return false;
            

            int v;
            bool sign;
            for(Node *i=cls[c].head.cnxt;i!=nullptr;i=i->cnxt){//获取变元
                if(i->status) continue;
                v=i->var;
                sign=i->sign;
                break;
            }
            value[ans_cnt][v]=sign;

            for(Node *i=var[v].head.vnxt;i!=nullptr;i=i->vnxt){//遍历变元所在的子句
                if(i->status) continue;
                if(sign^i->sign){//符号相反，删除文字
                    del(i,bp);
                    if(cls[i->cls].num==0) return false;
                    if(cls[i->cls].num==1) q.push(i->cls);
                }else{//符号相同，删除子句
                    del_cls(i->cls,bp);
                }
            }
            var[v].status=true;
        }
        return true;
    }

    bool dpll(bool multi_ans=false){
        ms=(clock()-start)*1000/CLOCKS_PER_SEC;
        if(ms>=TIMELIMIT&&!multi_ans){
            timeout=true;
            return true;
        }

        mystl::stack<Node*> bp;
        if(!simplify(bp)){//单子句传播
            rec(bp);
            return false;
        }

        bool emp=true;//判断范式是否为空
        for(int i=1;i<=cls_c;i++){
            if(!cls[i].status){
                emp=false;
                break;
            }
        }
        if(emp){
            if(!multi_ans){
                return true;
            }else{
                // 当前解已写入 value[ans_cnt]（del_var 使用该索引）
                ans_cnt++; // 记录一个解
                if(ans_cnt==1){
                    for(int i=1;i<=var_c;i++){
                        value[1][i]=value[0][i];
                    }
                }
                if(ans_cnt >= 2){
                    // 找到足够多的解，立刻上报 true 以停止搜索
                    return true;
                }
                // 继续搜索更多解：恢复本层变更并继续
                rec(bp);
                return false;
            }
        }

        int v=1;//寻找未被删除的变元
        while(v<=var_c&&var[v].status) v++;

        mystl::stack<Node*> branch;
        del_var(v,true,branch);
        if(dpll(multi_ans)){
            // if(!multi_ans||ans_cnt>=2){
                return true;
            // }
        }
        rec(branch);

        del_var(v,false,branch);
        if(dpll(multi_ans)){
            // if(!multi_ans||ans_cnt>=2){
                return true;
            // }
        }
        
        rec(branch);
        rec(bp);
        return false;
    }

    void solve(){
        if(solved){
            throw "SAT already solved";
            return;
        }
        solved=true;
        start=clock();
        flag=this->dpll();
        ms=(clock()-start)*1000/CLOCKS_PER_SEC;
    }

    int getDiffVar(){
        if(solved){
            throw "SAT already solved";
            return 0;
        }
        start=clock();
        flag=this->dpll(true);
        if(flag==false||ans_cnt<2) return 0;
        for(int i=1;i<=var_c;i++){
            if(value[0][i]!=value[1][i]){
                diff_var=i;
                break;
            }
        }
        return diff_var;
    }

    friend std::ostream& operator<<(std::ostream& out,CNF &cnf){
        if(cnf.ms>=TIMELIMIT){
            out<<"s -1\n";
        }else{
            out<<"s "<<cnf.flag<<std::endl;
            if(cnf.flag){
                out<<"v";
                for(int i=1;i<=cnf.var_c;i++){
                    out<<' '<<(cnf.value[0][i]?1:-1)*i;
                }
                out<<std::endl;
            }
        }
        out<<"t "<<cnf.ms;
        return out;
    }
};

#endif