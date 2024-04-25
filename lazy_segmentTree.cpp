#include <iostream>
#include <vector>
#include <deque>
using namespace std;
struct node
{
   int start, end;
   node* left=nullptr, *right=nullptr ,*parent=nullptr;
   int maxValue=-1;
   int lazy =0;
   node(int s,int e,int m):start(s),end(e),maxValue(m){}

    int getMax(){
        return this->maxValue;
    }
    void add(int i, int j, int x){
        i=max(i,start);
        j=min(j,end);
        if(i>j) return;
        if(i==start && j==end){
            maxValue+=x;
            lazy+=x;
            updateMax();
        }
        else{
            if(left!=nullptr) left->add(i,j,x);
            if(right!=nullptr) right->add(i,j,x);
        }
    }
    void updateMax(){
        node* p =parent;
        while (p!=nullptr)
        {
          p->maxValue=max(
            p->left->maxValue+p->lazy, 
            p->right->maxValue+p->lazy
        );
          p=p->parent;
        }
    }
};

node* makeTree(vector<int> A){
    deque<node*> nodearray;
    for(int i=0;i<A.size();++i){
        nodearray.push_back(new node(i,i,A[i]));
    }
    while(nodearray.size()>1){
        node* node1=nodearray.front();
        nodearray.pop_front();
        node* node2=nodearray.front();
        nodearray.pop_front();
        node* parent = new node(node1->start,node2->end,max(node1->maxValue,node2->maxValue));
        parent->left=node1;
        parent->right=node2;
        node1->parent=parent;
        node2->parent=parent;
        nodearray.push_back(parent);
    }
    return nodearray[0];
}

int main(){
    node* root =  makeTree({2,0,8,6,4,4,9,0});
    root->add(3,5,4);
    //{2,0,8,10,8,8,9,0}
    cout<<root->getMax()<<endl;
    //output 10

    root->add(4,4,4);
    //{2,0,8,10,12,8,9,0}
    cout<<root->getMax()<<endl;
     //output 12

    root->add(4,6,5);
    //{2,0,8,10,17,13,14,0}
    cout<<root->getMax()<<endl;
    //output 17

    root->add(2,5,5);
    //{2,0,13,15,22,18,14,0}
    cout<<root->getMax()<<endl;
    //output 22
}