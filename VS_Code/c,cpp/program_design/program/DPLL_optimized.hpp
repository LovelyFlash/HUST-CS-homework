#ifndef __DPLL_optimized__
#define __DPLL_optimized__
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
    bool timeout;
    bool solved;
    std::string path;
    clock_t start;
    int var_c=-1,cls_c=-1;
    double ms;
    bool flag;
    bool *value;
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
        int pos_num;
        int neg_num;
        Node head;
        Title():num(0),status(false),pos_num(0),neg_num(0){}
        
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
    
    CNF():var_c(-1),cls_c(-1),var(nullptr),cls(nullptr),flag(false),value(nullptr),solved(false),timeout(false){}

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
                value=new bool[var_c+1];
                memset(value,0,(var_c+1)*sizeof(bool));
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

    CNF(const char file[]):var_c(-1),cls_c(-1),var(nullptr),cls(nullptr),flag(false),value(nullptr),solved(false),timeout(false){
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
        value[v]=sign;
        for(Node *i=var[v].head.vnxt;i!=nullptr;i=i->vnxt){//遍历变元所在的子句
            if(i->status) continue;
            if(sign^i->sign){//符号相反，删除文字
                del(i,bp);
                // if(cls[i->cls].num==0) return false;
                // if(cls[i->cls].num==1) q.push(i->cls);
            }else{//符号相同，删除子句
                del_cls(i->cls,bp);
            }
        }
        var[v].status=true;
        // return true;
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
            value[v]=sign;

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

    bool dpll(){
        ms=(clock()-start)*1000/CLOCKS_PER_SEC;
        if(ms>=TIMELIMIT){
            timeout=true;
            return true;
        }

        mystl::stack<Node*> bp; // 全局本层已做的修改（用于回溯）

        // 单子句传播
        if(!simplify(bp)){
            rec(bp);
            return false;
        }

        //纯字面消去：只以同一符号出现的变元，可令其文字为真而不影响满足性
        bool changed = true;
        while(changed){
            changed = false;
            for(int i=1;i<=var_c;i++){
                if(var[i].status) continue;
                int mask = 0; // 1: only positive, 2: only negative, 3: both
                for(Node *p = var[i].head.vnxt; p != nullptr; p = p->vnxt){
                    if(p->status) continue;
                    if(p->sign) mask |= 1; else mask |= 2;
                    if(mask == 3) break;
                }
                if(mask == 1 || mask == 2){
                    // 发现纯字面，赋值并删除相关子句/文字
                    mystl::stack<Node*> tmp;
                    del_var(i, mask == 1, tmp);
                    // 将 tmp 的变更并入本层 bp，以便回溯时一并恢复
                    while(!tmp.empty()) bp.push(tmp.pop());
                    changed = true;
                }
            }
            if(changed){
                // 每次纯字面消去后都做一次单子句传播以继续剪枝
                if(!simplify(bp)){
                    rec(bp);
                    return false;
                }
            }
        }

        // 检查是否所有子句都已被删除（满足）
        bool emp = true;
        for(int i=1;i<=cls_c;i++){
            if(!cls[i].status){ emp = false; break; }
        }
        if(emp) {
            // 不回溯 bp，保留赋值结果到 value[]
            return true;
        }

        // 选择分支变量：按出现次数最多的未赋值变量（启发式）
        int best_v = -1;
        int best_cnt = -1;
        for(int i=1;i<=var_c;i++){
            if(var[i].status) continue;
            if(var[i].num > best_cnt){
                best_cnt = var[i].num;
                best_v = i;
            }
        }

        // 如果没有可选变量但还有子句，说明冲突（UNSAT）
        if(best_v == -1){
            rec(bp);
            return false;
        }

        // 两个分支：先尝试 true，再尝试 false （可调整优先顺序）
        mystl::stack<Node*> branch;
        del_var(best_v, true, branch);
        if(dpll()) return true;
        rec(branch);

        del_var(best_v, false, branch);
        if(dpll()) return true;
        rec(branch);

        // 恢复本层所有变更后返回 false
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

    friend std::ostream& operator<<(std::ostream& out,CNF &cnf){
        if(cnf.ms>=TIMELIMIT){
            out<<"s -1\n";
        }else{
            out<<"s "<<cnf.flag<<std::endl;
            if(cnf.flag){
                out<<"v";
                for(int i=1;i<=cnf.var_c;i++){
                    out<<' '<<(cnf.value[i]?1:-1)*i;
                }
                out<<std::endl;
            }
        }
        out<<"t "<<cnf.ms;
        return out;
    }
};

#endif