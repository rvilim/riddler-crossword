// constructing bitsets
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include <vector>
#include <set>
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
    std::set<std::bitset<N>, MaskCmp> masks;
    int row_number;
};

void PrintGrid(Node &n);

int GetNumGrids(int row_number, Node &n);

std::vector<std::bitset<N> > valid_rows, valid_symmetric_rows;

int main ()
{
    if (N%2==0){
        std::cout<<"Error N must be odd"<<std::endl;
        return 1;
    }

    std::array< std::set<std::bitset<N>,MaskCmp>, 1<<N > segmented_masks;
    std::unordered_map<std::string, std::vector<std::bitset<N> > > a;
    Node head;

    segmented_masks=GetSegmentedMasks();

    valid_rows = GetValidRows();
    valid_symmetric_rows = GetValidSymmetricRows(valid_rows);

    std::cout<<GetNumGrids(-1, head)<<std::endl;
}

int GetNumGrids(int row_number, Node &n){
    int tot=0;

    if(row_number==-1) {
        n.row.set(); // This is the 0th row (not part of the grid, set everything to one

        for (int j = 0; j < valid_rows.size(); j++) {

            std::vector<Node *> children;

            n.row_number=row_number;
            n.parent= nullptr;
            n.row.set();

            Node new_node{valid_rows[j], &n, children, std::set<std::bitset<N>, MaskCmp>(), row_number + 1};

            n.children.push_back(&new_node);

            tot += GetNumGrids(0, new_node);
        }
        return tot;
    } else if(row_number==0) {
        for(int j=0; j<valid_rows.size(); j++){
                    std::set<std::bitset<N>, MaskCmp> new_masks = GetNewMasks(n.row, valid_rows[j], n.masks);

            if( (IsValid3Row(n.parent->row, n.row, valid_rows[j])) ){
                std::vector<Node*> children;

                Node new_node {valid_rows[j], &n, children, std::set<std::bitset<N>, MaskCmp>(), row_number+1};
                n.children.push_back(&new_node);
                n.masks = GetNewMasks(n.parent->row, valid_rows[j], n.parent->masks);
                tot+=GetNumGrids(row_number+1, new_node);
            }
        }
        return tot;

    } else if((row_number>=1) && (row_number<=N/2-2)) { // N=7 >=1 <=1
        for (int j = 0; j < valid_rows.size(); j++) {
            auto new_masks = GetNewMasks(n.row, valid_rows[j], n.masks);

            if (IsValid4Row(n.parent->parent->row, n.parent->row, n.row, valid_rows[j])) {
                std::vector<Node *> children;

                Node new_node{valid_rows[j], &n, children, std::set<std::bitset<N>, MaskCmp>(), row_number + 1};
                n.children.push_back(&new_node);
                n.masks = GetNewMasks(n.parent->row, valid_rows[j], n.parent->masks);

                tot += GetNumGrids(row_number + 1, new_node);
            }
        }
        return tot;

    } else if(row_number==N/2-1) { // N=7 ==2
        for(int j=0; j<valid_symmetric_rows.size(); j++) {
            std::set<std::bitset<N>, MaskCmp> new_masks = GetNewMasks(n.row, valid_symmetric_rows[j], n.masks);

            if (IsValidLastRow(new_masks, n.parent->parent->row, n.parent->row, n.row, valid_symmetric_rows[j])) {

                std::vector<Node*> children;

                Node new_node {valid_symmetric_rows[j], &n, children, std::set<std::bitset<N>, MaskCmp>(), row_number+1};
                n.children.push_back(&new_node);
                tot+=1;

                PrintGrid(new_node);
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

    while (a.parent != nullptr){
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

