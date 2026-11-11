#include <iostream>
#include <vector>
#include <cstdlib>

std::vector<std::vector<int>> create_matrix(size_t n){
    std::vector<std::vector<int>> matrix(n,std::vector<int>(n,0));

    for(size_t i=0;i<n;i++){
        for(size_t j=i+1;j<n;j++){
            int value=rand()%2;
            matrix[i][j]=value;
            matrix[j][i]=value;
        }
    }
    return matrix;
}

void print_matrix(std::vector<std::vector<int>>& matrix){
    for(size_t i=0;i<matrix.size();i++){
        for(size_t j=0;j<matrix[i].size();j++){
            std::cout<<matrix[i][j]<<" "; 
        }
        std::cout<<"\n";
    }
}

void DFS(std::vector<std::vector<int>>& matrix,std::vector<bool>& NUM,size_t I){
    NUM[I]=true;;
    std::cout<<I+1<<"\n";

    for(size_t i=0;i<matrix.size();i++){
        if(matrix[I][i]==1&&!NUM[i]){
            DFS(matrix,NUM,i);
        }
    }    
}

int main(){
    int n;
    std::cout<<"Введите количество вершин: ";
    if(!(std::cin>>n)||n<=0){
        std::cout<<"НЕ ВЕРНЫЙ ВВОД.\nРАЗМЕР ДОЛЖЕН БЫТЬ ЧИСЛОМ БОЛЬШЕ НУЛЯ\n";
        return 1;
    }
    std::cout<<"\n";

    std::vector<std::vector<int>> matrix=create_matrix(n);

    std::cout<<"МАТРИЦА СМЕЖНОСТИ:\n";
    print_matrix(matrix);
    
    std::vector<bool> NUM(n,false);
    
    std::cout<<"ОБХОД ГРАФА В ГЛУБИНУ:\n";
    for(size_t i=0;i<NUM.size();i++){
        if(!NUM[i]){
            DFS(matrix,NUM,i);
        }
    }

}