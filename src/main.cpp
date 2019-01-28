// constructing bitsets
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include <vector>
#include <unordered_map>
#include <array>

#include <assert.h>

#include "params.h"
#include "rows.h"
#include "masks.h"

struct Node {
    std::bitset<N> row;
    Node *parent;
    std::vector<Node*> children;
    int row_number;
};

void PrintGrid(Node &n);

int GetNumGrids(std::vector<std::bitset<N> > &valid_rows, int i, Node &n);

int main ()
{
    if (N%2==0){
        std::cout<<"Error N must be odd"<<std::endl;
        return 1;
    }

    std::array<std::vector<std::bitset<N> >, 1<<N > segmented_masks;
    std::vector<std::bitset<N> > valid_rows;
    std::unordered_map<std::string, std::vector<std::bitset<N> > > a;
    Node head;

    segmented_masks=GetSegmentedMasks();

    for(int i=0; i<segmented_masks[4].size(); i++){
        std::cout<<segmented_masks[4][i]<<std::endl;
    }

    valid_rows = GetValidRows();
    std::cout<<"Number of valid rows: "<<valid_rows.size()<<std::endl;

//    GetNumGrids(valid_rows, 0, head);

}

int GetNumGrids(std::vector<std::bitset<N> > &valid_rows, int i, Node &n){
    int tot=0;

    if(i==0){
        for(int j=0; j<valid_rows.size(); j++){

            std::vector<Node*> children;

            Node new_node {valid_rows[j], &n, children, i+1};

            n.row = valid_rows[valid_rows.size()-1];
            n.children.push_back(&new_node);
            n.parent = nullptr;

            tot+=GetNumGrids(valid_rows, 1, new_node);
            std::cout<<j<<" "<<tot<<std::endl;
        }
        return tot;

    } else if(i==1) {

        for(int j=0; j<valid_rows.size(); j++){
            if(IsValid3Row(n.parent->row, n.row, valid_rows[j])){

                std::vector<Node*> children;

                Node new_node {valid_rows[j], &n, children, i+1};
                n.children.push_back(&new_node);

                tot+=GetNumGrids(valid_rows, 2, new_node);
            }
        }
        return tot;

    } else if((i>=2) && (i<N/2)) {
        for (int j = 0; j < valid_rows.size(); j++) {
            if (IsValid4Row(n.parent->parent->row, n.parent->row, n.row, valid_rows[j])) {
                std::vector<Node *> children;

                Node new_node{valid_rows[j], &n, children, i + 1};
                n.children.push_back(&new_node);

                tot += GetNumGrids(valid_rows, i + 1, new_node);
            }
        }
        return tot;
    } else if(i==N/2) {
        for(int j=0; j<valid_rows.size(); j++) {
            if (IsValidLastRow(n.parent->parent->row, n.parent->row, n.row, valid_rows[j])) {

                std::vector<Node*> children;

                Node new_node {valid_rows[j], &n, children, i+1};
                tot+=1;
//                PrintGrid(new_node);
            }
        }
        return tot;
    }
    return 1;
}

void PrintGrid(Node &n){
    auto a=n;
    int i=N/2;

    std::array<std::bitset<N>, N> rows;

    while (a.parent!=nullptr){
        if(i==N/2){
            rows[i]=a.row;
        }else{
            rows[i]=a.row;
            rows[N-i-1]=ReverseBitset(a.row);
        }

        a=*a.parent;
        i--;
    }
    for(const std::bitset<N> &row : rows){
        std::cout<<row<<std::endl;
    }
    std::cout<<std::endl;
}

