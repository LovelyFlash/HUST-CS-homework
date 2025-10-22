/*
this is a menu chooser with keyboard hit(arrows for move & enter for choose)
usage:
initialize an object of MenuTable: 
MenuTable chooser(size_t collum,"YourTitle",{
    "yourfunction1",
    "yourfunction2",
    ...
});
use chooser.choose() to open the menu
and the funcion will return the index of the function chosen(start from 1)
*/
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
#ifndef __menuChooser_h__
#define __menuChooser_h__
namespace menu{
    class MenuTable{
        private:
        std::string title;
        std::vector<std::string> funcs;
        size_t maxlength,collum,remain,maxy;
        inline void color(const unsigned short color1, const unsigned short color2){
            SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), (color2 * 16 + color1));
        }
        inline void cursor_move(short x, short y){
            COORD position;
            position.X = (maxlength+1)*x;
            position.Y = y+3;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
        }
        inline void print(){
            for(size_t i=0;i<maxlength*collum+collum-1;i++){
                std::cout<<"=";
            }
            std::cout<<std::endl;
            for(size_t i=0;i<(maxlength*collum+collum-1-title.length())/2;i++){
                std::cout<<" ";
            }
            std::cout<<title<<std::endl;
            for(size_t i=0;i<maxlength*collum+collum-1;i++){
                std::cout<<"=";
            }
            std::cout<<std::endl;
            for(size_t y=0;y<maxy;y++){
                for(size_t x=0;x<collum;x++){
                    if(x+y*collum>=funcs.size()) continue;
                    std::cout<<funcs[x+y*collum];
                    for(size_t k=0;k<maxlength+1-funcs[x+y*collum].length();k++){
                        std::cout<<" ";
                    }
                }
                std::cout<<std::endl;
            }
            for(int i=0;i<maxlength*collum+collum-1;i++){
                std::cout<<"-";
            }
            std::cout<<std::endl;
        }
        public:
        MenuTable(const size_t &collum,const std::string &title,const std::vector<std::string> &funcs):funcs(funcs),title(title),collum(collum){
            maxlength=0;
            for(auto it:funcs){
                maxlength=std::max(maxlength,it.length());
            }
            remain=(collum-funcs.size()%collum)%collum;
            maxy=(funcs.size()+remain)/collum;
        }
        size_t choose(){
            int x=0,y=0;
            cursor_move(0,-3);
            color(10,0);
            print();
            cursor_move(x,y);
            color(9,0);
            std::cout<<funcs[x+y*collum];
            while(1){
                if (_kbhit()){
                    int asc=_getch();
                    cursor_move(x,y);
                    color(10,0);
                    std::cout<<funcs[x+y*collum];
                    if(asc==72&&y>0){//up
                        y--;
                    }
                    if(asc==80&&y<maxy-1){//down
                        if(y==maxy-2&&x>=collum-remain) x=collum-remain-1;
                        y++;
                    }
                    if(asc==75&&x>0){//left
                        x--;
                    }
                    if(asc==77&&x<collum-1){//right
                        if(x==collum-remain-1&&y==maxy-1) y--;
                        x++;
                    }
                    cursor_move(x,y);
                    color(9,0);
                    std::cout<<funcs[x+y*collum];
                    if(asc==13){
                        system("cls");
                        color(10,0);
                        print();
                        cursor_move(x,y);
                        color(9,0);
                        std::cout<<funcs[x+y*collum];
                        cursor_move(0,maxy+1);
                        color(10,0);
                        return x+y*collum+1;
                    }
                }
            }
        }
    };
}
#endif

