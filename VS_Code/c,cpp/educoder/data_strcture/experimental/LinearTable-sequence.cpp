#include<bits/stdc++.h>
using namespace std;
#define InitialLength 100
#define Increment 10
template<class T>
class LinearTable{
    public:
    T* data;
    size_t length;
    size_t maxlength;
    void extend(){
        T* newdata=new T[this->maxlength+Increment];
        for(int i=0;i<this->length;i++){
            newdata[i]=data[i];
        }
        this->maxlength+=Increment;
        delete[] data;
        data=newdata;
    }
    LinearTable():data(new T[InitialLength]),length(0),maxlength(InitialLength){}
    // LinearTable(T* sq){
    //     while(sq!=0){
    //         if(length>=maxlength) extend();
    //         data[length++]=*sq++;
    //     }
    // }
    // LinearTable(size_t n){
    //     data=new T[InitialLength];
        
    // }
    T operator[](size_t index){
        if(index<0||index>=this->length) exit(-1);
        return this->data[index];
    }
    void InitFromSequence(){
        delete[] data;
        data = new T[InitialLength];
        length=0;
        maxlength=InitialLength;
        T sq;
        cout<<"Please input the sequence of numbers (0 to end): ";
        while(true){
            cin>>sq;
            if(sq==0) break;
            if(length>=maxlength) extend();
            data[length++]=sq;
        }
    }
    void ClearList(){
        length=0;
    }
    bool ListEmpty(){
        return length==0;
    }
    int ListLength(){
        return length;
    }
    bool GetElem(const size_t &i,T &e){
        if(i<1||i>length){
            return false;
        }
        e=data[i-1];
        return true;
    }
    int LocateElem(const T &e,function<bool(T,T)> cmp){
        for(int i=0;i<length;i++){
            if(cmp(e,data[i])) return i+1;
        }
        return 0;
    }
    bool PriorElem(const T &cur_e,T &pre_e){
        for(int i=1;i<length;i++){
            if(data[i]==cur_e){
                pre_e=data[i-1];
                return true;
            }
        }
        return false;
    }
    bool NextElem(const T &cur_e,T &next_e){
        for(int i=0;i<length-1;i++){
            if(data[i]==cur_e){
                next_e=data[i+1];
                return true;
            }
        }
        return false;
    }
    bool ListInsert(const size_t &k,const T &e){
        if(k<1||k>length+1) return false;
        if(length>=maxlength) extend();
        for(int i=length;i>=k-1;i--){
            data[i+1]=data[i];
        }
        data[k-1]=e;
        length++;
        return true;
    }
    bool ListDelete(const size_t &k,T &e){
        if(k<1||k>length) return false;
        e=data[k-1];
        for(int i=k-1;i<length-1;i++){
            data[i]=data[i+1];
        }
        length--;
        return true;
    }
    bool ListTraverse(function<void(T)> vis){
        for(int i=0;i<length;i++){
            vis(data[i]);
        }
        return true;
    }
    T MaxSubArray(){
        T res=data[0];
        for(size_t i=1;i<length;i++){
            if(res<=0) res=data[i];
            else res+=data[i];
        }
        return res;
    }
    size_t SubArrayNum(const T &k){
        size_t i=0,j=0,cnt=0;
        T preSum[length+1];
        memset(preSum,0,sizeof(preSum));
        preSum[1]=data[0];
        for(i=2;i<=length;i++) preSum[i]+=data[i-2];
        for(i=0;i<=length;i++){
            for(j=i+1;j<=length;j++){
                if(preSum[j]-preSum[i]==k) cnt++;
            }
        }
        return cnt;
    }
    void sortList(){
        sort(data,data+length);
    }
    bool save(){
        ofstream out("LinearTableData.bin",ios::out|ios::binary);
        if(!out) return false;
        out.write((char*)&length,sizeof(length));
        out.write((char*)&maxlength,sizeof(maxlength));
        out.write((char*)data,sizeof(T)*length);
        out.close();
        return true;
    }
    bool load(){
        ifstream in("LinearTableData.bin",ios::in|ios::binary);
        if(!in) return false;
        in.read((char*)&length,sizeof(length));
        in.read((char*)&maxlength,sizeof(maxlength));
        delete[] data;
        data=new T[maxlength];
        in.read((char*)data,sizeof(T)*length);
        in.close();
        return true;
    }
};
unordered_map<string,LinearTable<int>*> mp;
bool InitList(const string &name){
    if(mp.find(name)==mp.end()){
        mp[name]=new LinearTable<int>;
        return true;
    }
    return false;
}
bool InitListFromSequence(const string &name){
    if(mp.find(name)==mp.end()){
        mp[name]=new LinearTable<int>;
        mp[name]->InitFromSequence();
        return true;
    }
    return false;
}
bool DestroyList(const string &name){
    if(mp.find(name)!=mp.end()){
        delete mp[name];
        mp.erase(name);
        return true;
    }
    return false;
}
int main(){
    cout<<"--------------------------------------"<<endl;
    cout<<" Welcome to the Linear Table System!"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"-1.Exit                9.NextElem"<<endl;
    cout<<"0.InitListFromSequence 10.ListInsert"<<endl;
    cout<<"1.InitList             11.ListDelete"<<endl;
    cout<<"2.DestroyList          12.ListTraverse"<<endl;
    cout<<"3.ClearList            13.MaxSubArray"<<endl;
    cout<<"4.ListEmpty            14.SubArrayNum"<<endl;
    cout<<"5.ListLength           15.sortList"<<endl;
    cout<<"6.GetElem              16.save"<<endl;
    cout<<"7.LocateElem           17.load"<<endl;
    cout<<"8.PriorElem"<<endl;
    cout<<"--------------------------------------"<<endl;
    while(true){
        int cmd;
        while(true){
            cout<<"Please choose a command: ";
            cin>>cmd;
            if(cmd<-1||cmd>17) cout<<"Invalid command!"<<endl;
            else break;
        }
        if(cmd==-1) break;
        string name;
        cout<<"Please input the name of the list: ";
        cin>>name;
        if(cmd<=2){
            switch(cmd){
                case 0:{
                    if(InitListFromSequence(name)) cout<<"InitListFromSequence success!"<<endl;
                    else cout<<"Error: List \""<<name<<"\" already exists!"<<endl;
                    break;
                }
                case 1:{
                    if(InitList(name)) cout<<"InitList success!"<<endl;
                    else cout<<"Error: List \""<<name<<"\" already exists!"<<endl;
                    break;
                }
                case 2:{
                    if(DestroyList(name)) cout<<"DestroyList success!"<<endl;
                    else cout<<"Error: List \""<<name<<"\" does not exist!"<<endl;
                    break;
                }
            }
        }else{
            if(mp.find(name)==mp.end()){
                cout<<"Error: List \""<<name<<"\" does not exist!"<<endl;
                continue;
            }
            switch(cmd){
                case 3:{
                    mp[name]->ClearList();
                    cout<<"List cleared!"<<endl;
                    break;
                }
                case 4:{
                    if(mp[name]->ListEmpty()) cout<<"List is empty!"<<endl;
                    else cout<<"List is not empty!"<<endl;
                    break;
                }
                case 5:{
                    cout<<"List length: "<<mp[name]->ListLength()<<endl;
                    break;
                }
                case 6:{
                    int index;
                    cout<<"Please input the index: ";
                    cin>>index;
                    int e;
                    if(mp[name]->GetElem(index,e)) cout<<"Element at index "<<index<<": "<<e<<endl;
                    else cout<<"Error: Invalid index!"<<endl;
                    break;
                }
                case 7:{
                    int e;
                    cout<<"Please input the element: ";
                    cin>>e;
                    int index=mp[name]->LocateElem(e,[](int a,int b){return a==b;});
                    if(index) cout<<"Element "<<e<<" found at index "<<index<<endl;
                    else cout<<"Element "<<e<<" not found!"<<endl;
                    break;
                }
                case 8:{
                    int e;
                    cout<<"Please input the current element: ";
                    cin>>e;
                    int pre_e;
                    if(mp[name]->PriorElem(e,pre_e)) cout<<"Previous element of "<<e<<": "<<pre_e<<endl;
                    else cout<<"Error: No previous element!"<<endl;
                    break;
                }
                case 9:{
                    int e;
                    cout<<"Please input the current element: ";
                    cin>>e;
                    int next_e;
                    if(mp[name]->NextElem(e,next_e)) cout<<"Next element of "<<e<<": "<<next_e<<endl;
                    else cout<<"Error: No next element!"<<endl;
                    break;
                }
                case 10:{
                    int index,e;
                    cout<<"Please input the index and element: ";
                    cin>>index>>e;
                    if(mp[name]->ListInsert(index,e)) cout<<"Element "<<e<<" inserted at index "<<index<<endl;
                    else cout<<"Error: Invalid index!"<<endl;
                    break;
                }
                case 11:{
                    int index,e;
                    cout<<"Please input the index: ";
                    cin>>index;
                    if(mp[name]->ListDelete(index,e)) cout<<"Element "<<e<<" deleted from index "<<index<<endl;
                    else cout<<"Error: Invalid index!"<<endl;
                    break;
                }
                case 12:{
                    cout<<"List elements: ";
                    mp[name]->ListTraverse([](int e){cout<<e<<" ";});
                    cout<<endl;
                    break;
                }
                case 13:{
                    cout<<"Max subarray sum: "<<mp[name]->MaxSubArray()<<endl;
                    break;
                }
                case 14:{
                    int k;
                    cout<<"Please input the sum: ";
                    cin>>k;
                    cout<<"Number of subarrays with sum "<<k<<": "<<mp[name]->SubArrayNum(k)<<endl;
                    break;
                }
                case 15:{
                    mp[name]->sortList();
                    cout<<"List sorted!"<<endl;
                    break;
                }
                case 16:{
                    if(mp[name]->save()) cout<<"List saved!"<<endl;
                    else cout<<"Error: Failed to save list!"<<endl;
                    break;
                }
                case 17:{
                    if(mp[name]->load()) cout<<"List loaded!"<<endl;
                    else cout<<"Error: Failed to load list!"<<endl;
                    break;
                }
            }
        }
    }
    cout<<"Thank you for using the Linear Table System!"<<endl;
    for(auto it=mp.begin();it!=mp.end();it++){
        delete it->second;
    }
    system("pause");
    return 0;
  }