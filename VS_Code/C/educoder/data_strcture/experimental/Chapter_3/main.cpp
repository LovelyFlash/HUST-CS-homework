#include <bits/stdc++.h>
#include "fun.c"
#include "def.h"

using namespace std;

template<class T>
class BiTree{
    private:
        T data;
        BiTree<T> *lchild, *rchild;
    public:
        BiTree(T e){
            data = e;
            lchild = NULL;
            rchild = NULL;
        }
        void setLchild(BiTree<T> *l){
            lchild = l;
        }
        void setRchild(BiTree<T> *r){
            rchild = r;
        }
        T getData(){
            return data;
        }
        BiTree<T>* getLchild(){
            return lchild;
        }
        BiTree<T>* getRchild(){
            return rchild;
        }
}

int main(){
    
}