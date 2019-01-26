// constructing bitsets
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include <vector>
#include <unordered_map>
#include <array>

#include <assert.h>

#define N 7

std::vector<std::bitset<N> > GetValidRows();
bool ValidRow(std::bitset<N> n);

bool IsValid3Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3);
bool IsValid4Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4);
bool IsValidLastRow(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4);

std::bitset<N> ReverseBitset(std::bitset<N> row);

bool IsValid4(bool bit1, bool bit2, bool bit3, bool bit4);

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

    std::vector<std::bitset<N> > valid_rows;
    std::unordered_map<std::string, std::vector<std::bitset<N> > > a;
    Node head;

    valid_rows = GetValidRows();
    std::cout<<valid_rows.size()<<std::endl;

    GetNumGrids(valid_rows, 0, head);

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

std::bitset<N> ReverseBitset(std::bitset<N> row){
    for(std::size_t i = 0; i < N/2; ++i) {
        bool t = row[i];
        row[i] = row[N-i-1];
        row[N-i-1] = t;
    }

    return row;
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
//
//    if (n.parent != nullptr){
//        PrintGrid(*n.parent);
//        std::cout<<n.row_number<<" "<<n.row<<std::endl;
//    }else{
//        std::cout<<std::endl;
//    }
}

bool IsValid3Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3){
    for(unsigned int i=0; i<N; i++){
        if (row1.test(i) && !row2.test(i) && row3.test(i)){
            return false;
        }
    }
    return true;
}

bool IsValid4Row(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4){
    for(unsigned int i=0; i<N; i++){
        if (!IsValid4(row1.test(i), row2.test(i), row3.test(i), row4.test(i))){
            return false;
        }
    }
    return true;
}

bool IsValid4(bool bit1, bool bit2, bool bit3, bool bit4){
    return ( (!bit1 && !bit2) || (!bit3 && !bit4) || (bit2 && bit3 ));
}

bool IsValidLastRow(std::bitset<N> row1, std::bitset<N> row2, std::bitset<N> row3, std::bitset<N> row4){

    for(unsigned int i=0; i<N; i++){
        bool bit1 = row1.test(i);
        bool bit2 = row2.test(i);
        bool bit3 = row3.test(i);
        bool bit4 = row4.test(i);

        bool rbit1 = row1.test(N-i-1);
        bool rbit2 = row2.test(N-i-1);
        bool rbit3 = row3.test(N-i-1);

        if ( !(IsValid4(bit1, bit2, bit3, bit4)) || // 1 2 3 4
             !(IsValid4(bit2, bit3, bit4, rbit3)) || // 2 3 4 r3
             !(IsValid4(bit3, bit4, rbit3, rbit2)) || // 3 4 r3 r2
             !(IsValid4(bit4, rbit3, rbit2, rbit1)) ){ // 4 r3 r3 r1
            return false;
        }
    }
    return true;
}

std::vector<std::bitset<N> > GetValidRows() {
    std::vector<std::bitset<N> > valids;

    for(unsigned int i=0; i< 1<<N; i++){
        std::bitset<N> i_bits(i);
        if (ValidRow(i_bits)){
            valids.push_back(i_bits);
        }
    }

    return valids;
}

bool ValidRow(std::bitset<N> n){
    for(unsigned int i=0; i<=N-3; i++){
        if (n.test(i) && !n.test(i+1) && n.test(i+2)){
            return false;
        }
    }

    for(unsigned int i=0; i<=N-4; i++){
        if (n.test(i) && !n.test(i+1) && !n.test(i+2) && n.test(i+3)){
            return false;
        }
    }

    if ((!n.test(0) && n.test(1)) || (!n.test(0) && !n.test(1) && n.test(2))) {
        return false;
    }

    if ((!n.test(N-1) && n.test(N-2)) || (!n.test(N-1) && !n.test(N-2) && n.test(N-3))) {
        return false;
    }

    return true;
}
