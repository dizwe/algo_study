//
//  main.cpp
//  test
//
//  Created by dizwe on 16/06/2019.
//  Copyright © 2019 dizwe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

// 모두가 마이너스일 때는 다른 방식을 사용해야하므로 확인하기 위한 bool을 사용한다.
bool check_all_neg(int **square, int row_num, int col_num){
    bool check = true;
    for(int i=0;i<row_num;i++){
        for(int j=0;j<col_num;j++){
            // 1보다 큰게 있으면 false return
            if(square[i][j]>0)
                check= false;
        }
    }
    return check;
}

// 모두가 마이너스일 떄 최대값을 따로따로 찾는다.
void find_single_max(int **square, int row_num, int col_num, FILE *fp_w){
    int max = -9999999;
    for(int i=0;i<row_num;i++){
        for(int j=0;j<col_num;j++){
            // 가장 큰 음수값을 찾는다.
            if(square[i][j]>max)
                max = square[i][j];
        }
    }
    fprintf(fp_w, "%d\n", max);
}

int main(int argc, char *argv[]) {
    
    //argc : number of arguments
    //argv[1], argv[2] , ... is the arguments
    // 실행할 떄 option 읽어오기
    FILE *fp, *fp_w;
    char* file_name, * option;
    
    // 파일이름을 지정하기 위해 input과 붙여준다.
    file_name = argv[1];
    char result_file_name[30] = "result_";
    strcat(result_file_name,file_name);
    option = argv[2];
    
    //파일에서 데이터 읽어오기
    fp = fopen(file_name, "r");
    fp_w = fopen(result_file_name, "w");
    fprintf(fp_w, "%s\n", file_name);
    fprintf(fp_w, "%s\n", option);
    
    int row_num, col_num;
    fscanf(fp,"%d %d", &row_num,&col_num);
    fprintf(fp_w, "%d\n", row_num);
    fprintf(fp_w, "%d\n", col_num);
    
    // 파일 데이터 읽어서 써주기
    int **square = (int **)malloc(row_num * sizeof(int *));
    for (int i=0; i<row_num; i++)
          square[i] = (int *)malloc(col_num * sizeof(int));
    
    for(int i=0;i<row_num;i++){
        for(int j=0;j<col_num;j++){
            int data;
            fscanf(fp,"%d",&data);
            square[i][j] = data;
        }
    }
    
    clock_t start =clock();
    int this_sum=0,max_sum=0;
    
    // O(n^6)
    if(!strcmp(option,"1")){
        if(check_all_neg(square,row_num,col_num)){
            find_single_max(square,row_num,col_num,fp_w);
        }else{
        // 왼쪽 위 점
        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                // 오른쪽 아래 점
                for(int k=i;k<row_num;k++){
                    for(int h=j;h<col_num;h++){
                        this_sum = 0;
                        // 실제로 sum 찾기
                        for(int a=i;a<=k;a++){
                            for(int b=j;b<=h;b++){
                                // 전체적으로 돌아가면서 합을 체크한다.
                                this_sum += square[a][b];
                            }
                        }
                        // 합 비교하기
                        if(max_sum<this_sum)
                            max_sum = this_sum;
                    }
                }
            }
        }
             fprintf(fp_w, "%d\n", max_sum);
        }
       
   // O(n^4)
    }else if(!strcmp(option,"2")){
        if(check_all_neg(square,row_num,col_num)){
           find_single_max(square,row_num,col_num,fp_w);
        }else{
            // 시작점
            for(int i=0;i<row_num;i++){
                for(int j=0;j<col_num;j++){
                    this_sum = 0;
                    // column별로 데이터를 넣어서 다음 row로 넘어갈 때 이용할 수 있도록 한다.
                    // 초기화 까지 하기
                    int* col_sum = (int *)malloc(col_num * sizeof(int));
                    for(int a=0;a<col_num;a++)
                        col_sum[a]=0;
                    
                    // 새롭게 추가할 row
                    for(int k=i;k<row_num;k++){
                        // 새롭게 추가된 사각형을 따로 계산하기 위해 초기화 한다.
                        int* new_col_sum = (int *)malloc(col_num * sizeof(int));
                        for(int a=0;a<col_num;a++)
                            new_col_sum[a]=0;
                        
                        for(int h=j;h<col_num;h++){
                            // 새로 추가되는 사각형의 합을 구한다. 이 사각형은 n[2]일 때 첫번째 colum과 두번째 colum의 합과 새로 추가된 값을 가진다.
                            if(h>0)
                                new_col_sum[h] = new_col_sum[h-1]+square[k][h];
                            else
                                new_col_sum[h] = square[k][h]; // 얘는 자기 자신이니까
                            
                            // 지금까지 쌓아온 col_sum(사각형)에서 새로 추가되는 사각형 한줄을 추가한다.
                            col_sum[h] +=  new_col_sum[h];
                            
                            // 합 비교하기
                            if(max_sum<col_sum[h])
                                max_sum = col_sum[h];
                        }
                        // 나중에 loop에 쓰이지 않으므로 free 한다.
                        free(new_col_sum);
                    }
                    // 나중에 loop에 쓰이지 않으므로 free 한다.
                    free(col_sum);
                }
            }
            fprintf(fp_w, "%d\n", max_sum);
        }
        
    // O(n^3)
    }else if(!strcmp(option,"3")){
        if(check_all_neg(square,row_num,col_num)){
            find_single_max(square,row_num,col_num,fp_w);
        }else{
        // column별로 데이터를 넣어서 다음 row로 넘어갈 때 이용할 수 있도록 한다.
        // 초기화 까지 하기
        int **col_sum = (int **)malloc(col_num * sizeof(int *));
        for (int i=0; i<col_num; i++)
            col_sum[i] = (int *)malloc(col_num * sizeof(int));
        
        // row는 조건에 따라서 0으로 만들어서 col_sum을 계산할 수 있지만, col까지는 커버하지 못하기 때문에, col_sum을 이차원으로 만들어서
        // 앞부분은 col의 시작점, 뒷부분은 col의 끝 점으로 잡는다.
        for(int i=0;i<col_num;i++){
            for(int j=0;j<col_num;j++){
                col_sum[i][j]=0;
            }
        }
            
        // 시작점
        for(int i=0;i<row_num;i++){
            for(int j=0;j<col_num;j++){
                
                // 새롭게 sum 한것들만 col_sum에 더해줘야 한다.
                int* new_col_sum = (int *)malloc(col_num * sizeof(int));
                for(int a=0;a<col_num;a++)
                    new_col_sum[a]=0;
                
                // col의 시작점에 따른 끝점 h로 조합을 확인한다.
                for(int h=j;h<col_num;h++){
                    // 새로 추가되는 사각형의 합을 구한다. 이 사각형은 n[2]일 때 첫번째 colum과 두번째 colum의 합과 새로 추가된 값을 가진다.
                    if(h>0)
                        new_col_sum[h] = new_col_sum[h-1] + square[i][h];
                    else
                        new_col_sum[h] = square[i][h]; // 얘는 자기 자신이니
                    
                    // j부터 시작해서 h까지의 column 범위를 가지는 부분에서 최대값을 저장한다.
                    col_sum[j][h] += new_col_sum[h];
                    
                    // 합 비교하기
                    if(max_sum<col_sum[j][h])
                        max_sum = col_sum[j][h];
                    else if(col_sum[j][h]<0) // 0보다 작을 때는 row를 그 다음부터 새로 시작하도록 설정한다.
                        col_sum[j][h] = 0;
                }
                // 나중에 loop에 쓰이지 않으므로 free 한다.
                free(new_col_sum);
            }
        }
        
        // 나중에 loop에 쓰이지 않으므로 free 한다.
        for(int a=0;a<col_num;a++)
            free(col_sum[a]);
        free(col_sum);
            
        fprintf(fp_w, "%d\n", max_sum);
        }
    }
    // 시간을 체크한다.
    clock_t end =clock();
    fprintf(fp_w, "%.3f\n", (double)end-start);
    
}
