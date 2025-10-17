#ifndef __sudoku__
#define __sudoku__
#include<string>
#include<cstring>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<random>
#include<ctime>
namespace sat{
    #include"DPLL.hpp"
    #undef __DPLL__
};

class SUDOKU{
    protected:
    double ms;
    int stat[10][10];
    int ans[10][10];
    int fill[10][10];
    virtual void color(int,int,int,bool=false)=0;//修改输出字体颜色及背景颜色

    virtual std::string GetRandomStat()=0;

    int encode(int l,int r,int s){
        return (l-1)*81+(r-1)*9+s;
    }
    
    void decode(int code){
        if(code>0&&code<=729){
            code-=1;
            ans[code/81+1][code%81/9+1]=code%9+1;
        }
    }

    void move_cursor(int x,int y){
        COORD position;
        position.X = x;
        position.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    }

    void put(int line,int raw,bool highlight=false){
        move_cursor(2*(raw-1),line-1);
        color(line,raw,fill[line][raw],highlight);
        std::cout<<' '<<(char)(fill[line][raw]==0?' ':fill[line][raw]+'0');
    }

    void print(int s[10][10]){//打印数独
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                int c=((i-1)/3+(j-1)/3)%2;
                color(i,j,s[i][j]);
                std::cout<<' '<<(char)(s[i][j]==0?' ':s[i][j]+'0');
            }
            std::cout<<std::endl;
        }
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 10);
    }
    
    public:
    SUDOKU(){
        memset(stat,0,sizeof(stat));
        memset(ans,0,sizeof(ans));
        memset(fill,0,sizeof(fill));
    }
    virtual ~SUDOKU(){}

    double rtime(){
        return ms;
    }

    void readString(const char str[]){
        const char *p=str;
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                if(*p=='\n'||*p=='\0') throw "string too short";
                stat[i][j]=(*p=='.'?0:*p-'0');
                p++;
            }
        }
    }
    
    void readFile(std::string file){
        std::fstream in(file,std::ios::in);
        char c;
        int code;
        in>>c>>code;
        if(code!=1) return;
        in>>c;
        for(int i=0;i<729;i++){
            in>>code;
            if(code>0) decode(code);
        }
        in.close();
    }

    virtual void writeCNF(std::string)=0;
    
    void printStat(){
        print(stat);
    }

    void printAns(){
        print(ans);
    }

    void solve(){
        writeCNF(".\\sudoku.cnf");
        sat::CNF cnf(".\\sudoku.cnf");
        cnf.solve();
        ms=cnf.ms;
        cnf.write(".\\sudoku.res");
        readFile(".\\sudoku.res");
    }

    void generate(int DEL=60){
        double start=clock();
        std::string p=GetRandomStat();
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                stat[i][j]=ans[i][j]=p[(i-1)*9+j-1]-'0';
            }
        }
        srand(time(0));
        int del_cnt=0;
        while(del_cnt<DEL){
            int ran=rand()%81;
            int l=ran%9+1;
            int r=ran/9+1;
            if(stat[l][r]==0) continue;
            stat[l][r]=0;
            del_cnt++;
        }
        while(1){
            this->writeCNF(".\\sudoku.cnf");
            sat::CNF cnf(".\\sudoku.cnf");
            int code=cnf.getDiffVar();
            if(code==0) break;
            int l=code/81+1;
            int r=code%81/9+1;
            if(stat[l][r]!=0){
                std::cout<<cnf.ans_cnt<<std::endl;
                std::cout<<l<<' '<<r<<' '<<code%9<<std::endl;
                this->printStat();
                for(int i=1;i<=729;i++){
                    if(cnf.value[0][i]>0) decode(cnf.value[0][i]);
                }
                this->printAns();
                for(int i=1;i<=729;i++){
                    if(cnf.value[1][i]>0) decode(cnf.value[0][i]);
                }
                this->printAns();
                throw "Diff error";
            }
            else stat[l][r]=ans[l][r];
        }
        ms=(clock()-start)*1000/CLOCKS_PER_SEC;
    }

    void play(){
        system("cls");
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                fill[i][j]=stat[i][j];
            }
        }

        print(stat);
        int l=1,r=1;
        put(l,r,true);
        while(1){
            if (_kbhit()){
                int asc=_getch();
                put(l,r);
                if(asc==72){//up
                    l--;
                    if(l==0) l=9;
                }
                if(asc==80){//down
                    l++;
                    if(l==10) l=1;
                }
                if(asc==75){//left
                    r--;
                    if(r==0) r=9;
                }
                if(asc==77){//right
                    r++;
                    if(r==10) r=1;
                }
                put(l,r,true);
                if(asc>='1'&&asc<='9'){
                    if(stat[l][r]!=0) continue;
                    fill[l][r]=asc-'0';
                    put(l,r,true);
                }
                if(asc==13){//enter
                    put(l,r);
                    break;
                }
            }
        }

        move_cursor(0,9);
        printAns();
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (0 * 16 + 2));
        system("pause");
    }
};

class sudoku:public SUDOKU{
    private:
    int bgcolor[10][10]={
        0,0,0,0,0,0,0,0,0,0,
        0,9,9,9,11,11,11,9,9,9,
        0,9,9,9,11,11,11,9,9,9,
        0,9,9,9,11,11,11,9,9,9,
        0,11,11,11,9,9,9,11,11,11,
        0,11,11,11,9,9,9,11,11,11,
        0,11,11,11,9,9,9,11,11,11,
        0,9,9,9,11,11,11,9,9,9,
        0,9,9,9,11,11,11,9,9,9,
        0,9,9,9,11,11,11,9,9,9
    };

    std::string preset[14]={
        "582649173319782645746315982894136527157928364623574891971463258468251739235897416",
        "942718563863925714157346829386459271215873946794261385529684137438197652671532498",
        "712469385596831742438275169984316527653792814271548936145687293867923451329154678",
        "368451972427698315951732468582346197649187253173925684296574831835219746714863529",
        "982635147153479628764218395428796513671523984395841276246157839819364752537982461",
        "513948267842763951967521438756139824321485679498672315185296743634817592279354186",
        "289456317516973824347128596724589631693714258851632479475261983168395742932847165",
        "789235416156874329342691875523748691964152783871963254298316547615487932437529168",
        "384697251129435867576281934243976185798512346651843729835169472967324518412758693",
        "321956478485273196976148325532489617694721853817365942263514789749832561158697234",
        "254619837168327549397584621873452196641973258529861473415738962786295314932146785",
        "439582176825761934176943258987256413612437589543819627391628745264375891758194362",
        "812456739639278145574391682456913278193827456728645391387562914245139867961784523",
        "924761538165834297783259416698123745512478963347596821256917384471382659839645172"
    };

    virtual std::string GetRandomStat()override{
        srand(time(0));
        return preset[rand()%14];
    }

    virtual inline void color(int line,int raw,int value,bool highlight=false)override{
        int color1=(stat[line][raw]!=0?0:(ans[line][raw]==value?2:4));
        int color2=(highlight?7:bgcolor[line][raw]);
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (color2 * 16 + color1));
    }
    
    public:
    virtual void writeCNF(std::string file)override{
        std::fstream out(file,std::ios::out);

        out<<"c sudoku\n";

        int cnt=0;
        for(int i=1;i<=9;i++){
            out<<"c ";
            for(int j=1;j<=9;j++){
                if(stat[i][j]!=0) cnt++;
                out<<(char)(stat[i][j]==0?' ':stat[i][j]+'0');
                if(j==3||j==6) out<<"|";
            }
            out<<std::endl;
            if(i==3||i==6) out<<"c ---+---+---\n";
        }

        out<<"p cnf 729 "<<10287+cnt<<std::endl;

        //格约束
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                for(int k=1;k<=9;k++){//一格有至少一个元素
                    out<<encode(i,j,k)<<' ';
                }
                out<<0<<std::endl;

                for(int k=1;k<=8;k++){//一格没有重复元素
                    for(int p=k+1;p<=9;p++){
                        out<<-encode(i,j,k)<<' '<<-encode(i,j,p)<<" 0\n";
                    }
                }
            }
        }

        //行约束
        for(int i=1;i<=9;i++){//每一行没有相同元素
            for(int j1=1;j1<=8;j1++){
                for(int j2=j1+1;j2<=9;j2++){
                    for(int k=1;k<=9;k++){
                        out<<-encode(i,j1,k)<<' '<<-encode(i,j2,k)<<" 0\n";
                    }
                }
            }
        }

        //列约束
        for(int j=1;j<=9;j++){//每一列没有相同元素
            for(int i1=1;i1<=8;i1++){
                for(int i2=i1+1;i2<=9;i2++){
                    for(int k=1;k<=9;k++){
                        out<<-encode(i1,j,k)<<' '<<-encode(i2,j,k)<<" 0\n";
                    }
                }
            }
        }

        //单元格约束
        for(int _i=0;_i<3;_i++){//大行
            for(int _j=0;_j<3;_j++){//大列
                for(int l=0;l<9;l++){
                    for(int r=l+1;r<9;r++){
                        int i1=_i*3+l%3+1;
                        int i2=_i*3+r%3+1;
                        int j1=_j*3+l/3+1;
                        int j2=_j*3+r/3+1;
                        if(i1==i2||j1==j2) continue;//去除同行、同列重复
                        for(int k=1;k<=9;k++){//单元格中没有相同元素
                            out<<-encode(i1,j1,k)<<' '<<-encode(i2,j2,k)<<" 0\n";
                        }
                    }
                }
            }
        }

        //已有文字约束
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                if(stat[i][j]!=0) out<<encode(i,j,stat[i][j])<<" 0\n";
            }
        }

        out.close();
    }
};

class psudoku:public SUDOKU{
    private:
    int bgcolor[10][10]={
        0,0,0,0,0,0,0,0,0,0,
        0,9,9,9,11,11,11,9,9,1,
        0,9,1,1,3,11,11,9,1,9,
        0,9,1,1,3,11,11,1,9,9,
        0,11,3,3,1,9,1,11,11,11,
        0,11,11,11,9,1,9,11,11,11,
        0,11,11,11,1,9,1,3,3,11,
        0,9,9,1,11,11,3,1,1,9,
        0,9,1,9,11,11,3,1,1,9,
        0,1,9,9,11,11,11,9,9,9
    };

    std::string preset[13]={
        "875641293941235678236798145158924736723186954469573812582319467394867521617452389",
        "345678912672391584891425637156834279983257461427169853569743128238916745714582396",
        "491526378285973146367418925713285469948637512526194783152849637879361254634752891",
        "935182467781946235462375189154768392398421756276593814529817643847639521613254978",
        "258674931913258647674913258465827193327491586891365472146739825782546319539182764",
        "536784192971526834482913657863495271295671483714832965329167548647258319158349726",
        "981236745623475891457891236769153428532748619814629573298514367375962184146387952",
        "415627893768593214392148657134765928957281346826439571549376182671852439283914765",
        "815679234497823516236145789942516873758934621361287495179458362684392157523761948",
        "461273958923581476578649213749126835815437629632958147284795361356812794197364582",
        "961273458423581976578649213749126835815437629632958147284795361356812794197364582"
    };

    virtual std::string GetRandomStat()override{
        srand(time(0));
        return preset[rand()%13];
    }

    virtual inline void color(int line,int raw,int value,bool highlight=false)override{
        int color1=(stat[line][raw]!=0?0:(ans[line][raw]==value?2:4));
        int color2=(highlight?7:bgcolor[line][raw]);
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (color2 * 16 + color1));
    }

    public:
    virtual void writeCNF(std::string file)override{
        std::fstream out(file,std::ios::out);

        out<<"c sudoku\n";

        int cnt=0;
        for(int i=1;i<=9;i++){
            out<<"c ";
            for(int j=1;j<=9;j++){
                if(stat[i][j]!=0) cnt++;
                out<<(char)(stat[i][j]==0?' ':stat[i][j]+'0');
                if(j==3||j==6) out<<"|";
            }
            out<<std::endl;
            if(i==3||i==6) out<<"c ---+---+---\n";
        }

        out<<"p cnf 729 "<<11272-13+cnt<<std::endl;

        //格约束
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                for(int k=1;k<=9;k++){//一格有至少一个元素
                    out<<encode(i,j,k)<<' ';
                }
                out<<0<<std::endl;

                for(int k=1;k<=8;k++){//一格没有重复元素
                    for(int p=k+1;p<=9;p++){
                        out<<-encode(i,j,k)<<' '<<-encode(i,j,p)<<" 0\n";
                    }
                }
            }
        }

        //行约束
        for(int i=1;i<=9;i++){//每一行没有相同元素
            for(int j1=1;j1<=8;j1++){
                for(int j2=j1+1;j2<=9;j2++){
                    for(int k=1;k<=9;k++){
                        out<<-encode(i,j1,k)<<' '<<-encode(i,j2,k)<<" 0\n";
                    }
                }
            }
        }

        //列约束
        for(int j=1;j<=9;j++){//每一列没有相同元素
            for(int i1=1;i1<=8;i1++){
                for(int i2=i1+1;i2<=9;i2++){
                    for(int k=1;k<=9;k++){
                        out<<-encode(i1,j,k)<<' '<<-encode(i2,j,k)<<" 0\n";
                    }
                }
            }
        }

        //单元格约束
        for(int _i=0;_i<3;_i++){//大行
            for(int _j=0;_j<3;_j++){//大列
                for(int l=0;l<9;l++){
                    for(int r=l+1;r<9;r++){
                        int i1=_i*3+l%3+1;
                        int i2=_i*3+r%3+1;
                        int j1=_j*3+l/3+1;
                        int j2=_j*3+r/3+1;
                        if(i1==i2||j1==j2) continue;//去除同行、同列重复
                        for(int k=1;k<=9;k++){//单元格中没有相同元素
                            out<<-encode(i1,j1,k)<<' '<<-encode(i2,j2,k)<<" 0\n";
                        }
                    }
                }
            }
        }

        //%约束
        int base[]={2,6};//oo约束
        for(int p=0;p<2;p++){
            for(int l=0;l<9;l++){
                for(int r=l+1;r<9;r++){
                    int i1=base[p]+l%3;
                    int i2=base[p]+r%3;
                    int j1=base[p]+l/3;
                    int j2=base[p]+r/3;
                    for(int k=1;k<=9;k++){
                        out<<-encode(i1,j1,k)<<' '<<-encode(i2,j2,k)<<" 0\n";
                    }
                }
            }
        }
        for(int i1=1;i1<=9;i1++){// /约束
            int j1=10-i1;
            for(int i2=i1+1;i2<=9;i2++){
                int j2=10-i2;
                for(int k=1;k<=9;k++){
                    out<<-encode(i1,j1,k)<<' '<<-encode(i2,j2,k)<<" 0\n";
                }
            }
        }

        //已有文字约束
        for(int i=1;i<=9;i++){
            for(int j=1;j<=9;j++){
                if(stat[i][j]!=0) out<<encode(i,j,stat[i][j])<<" 0\n";
            }
        }

        out.close();
    }
};

#endif