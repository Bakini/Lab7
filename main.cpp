#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> create_matrix(size_t n,int prob){
    std::vector<std::vector<int>> matrix(n,std::vector<int>(n,0));

    for(size_t i=0;i<n;i++){
        for(size_t j=i+1;j<n;j++){
            int value=rand()%100<prob;
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
    NUM[I]=true;
    std::cout<<I+1<<"\n";

    for(size_t i=0;i<matrix.size();i++){
        if(matrix[I][i]==1&&!NUM[i]){
            DFS(matrix,NUM,i);
        }
    }    
}

std::vector<std::vector<int>> create_spisok(const std::vector<std::vector<int>>& matrix){
    std::vector<std::vector<int>> neighbors(matrix.size());

    for(size_t i=0;i<matrix.size();i++){
        for(size_t j=0;j<matrix[i].size();j++){
            if(matrix[i][j]==1)neighbors[i].push_back(j+1);
        }
    }
    return neighbors;
}

void print_spisok(const std::vector<std::vector<int>>& neighbors){
    for(size_t i=0;i<neighbors.size();i++){
        std::cout<<i+1<<": ";

        for(int schet:neighbors[i]){
            std::cout<<schet<<" ";
        }
        std::cout<<"\n";
    }
}

void DFS_spisok(const std::vector<std::vector<int>>& spisok,std::vector<bool>& NUM,size_t I){
    NUM[I]=true;
    std::cout<<I+1<<"\n";

    for(int neighbor:spisok[I]){
        if(!NUM[neighbor-1]){
            DFS_spisok(spisok,NUM,neighbor-1);
        }
    }
}

void DFS_dop(const std::vector<std::vector<int>>& matrix,std::vector<bool>& NUM,size_t start){
    std::vector<size_t> stack;
    std::vector<size_t> next(matrix.size(),0);

    stack.push_back(start);
    NUM[start]=true;
    std::cout<<start+1<<"\n";

    while(!stack.empty()){
        size_t v=stack.back();

        while(next[v]<matrix.size()){
            size_t neighbor=next[v];
            next[v]++;

            if(matrix[v][neighbor]==1&&!NUM[neighbor]){
                NUM[neighbor]=true;
                std::cout<<neighbor+1<<"\n";
                stack.push_back(neighbor);
                break;
            }
        }

        if(stack.back()==v)stack.pop_back();
    }
}

int main(){
    srand(time(NULL));
    int n;
    clock_t start,end;
    std::cout<<"Введите количество вершин: ";
    start=clock();
    if(!(std::cin>>n)||n<=0){
        std::cout<<"НЕ ВЕРНЫЙ ВВОД.\nРАЗМЕР ДОЛЖЕН БЫТЬ ЧИСЛОМ БОЛЬШЕ НУЛЯ\n";
        return 1;
    }

    int prob;
    std::cout<<"Введите вероятность ребра: ";
    if(!(std::cin>>prob)||prob<0||prob>100){
        std::cout<<"НЕВЕРНАЯ ВЕРОЯТНОСТЬ!\n";
        return 1;
    }

    std::vector<std::vector<int>> matrix=create_matrix(n,prob);

    std::cout<<"\n";
    std::cout<<"МАТРИЦА СМЕЖНОСТИ:\n";
    print_matrix(matrix);
    
    std::vector<bool> NUM(n,false);
    
    std::cout<<"\n";
    std::cout<<"ОБХОД ГРАФА В ГЛУБИНУ:\n";
    for(size_t i=0;i<NUM.size();i++){
        if(!NUM[i]){
            DFS(matrix,NUM,i);
        }
    }

    std::vector<std::vector<int>> spisok=create_spisok(matrix);
    std::cout<<"\n";
    std::cout<<"СПИСОК СМЕЖНОСТИ ПЕРВОГО ГРАФА:\n";
    print_spisok(spisok);

    NUM.assign(n,false);

    std::cout<<"\n";
    std::cout<<"ОБХОД В ГЛУБИНУ ПО СПИСКУ СМЕЖНОСТИ:\n";
    for(size_t i=0;i<NUM.size();i++){
        if(!NUM[i]){
            DFS_spisok(spisok,NUM,i);
        }
    }   
    
    NUM.assign(n,false);

    std::cout<<"\n";
    std::cout<<"НЕРЕКУРСИВНЫЙ ОБХОД ПО МАТРИЦЕ:\n";

    for(size_t i=0;i<NUM.size();i++){
        if(!NUM[i]){
            DFS_dop(matrix,NUM,i);
        }
    } 
    end=clock();   
    std::cout << "ОБщее время всех обходов: "<<(double)(end - start)/CLOCKS_PER_SEC << "\n";
}