//
//  main.cpp
//  test
//
//  Created by dizwe on 04/11/2019.
//  Copyright © 2019 dizwe. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0

#define SWAP(a,b) {int tmp; tmp =a; a=b; b=tmp;}

int partition(int * a, int left, int right){
    int i, pivot;
    
    pivot = left;
    
    for(i=left;i<right;i++){
        // 얘가 pivot 자리에 오 ㄹ애다
        if(a[i]<a[right]){
            // pviot 자리에는 나보다 큰 애가 시작되는 지점이다. 내가 작은 자리로 가도록 한다.
            SWAP(a[i], a[pivot]);
            // 나보다 작은 애 수가 늘었으니 ++
            pivot++;
        }
    }
    // 나를 pivot 자리로 옮긴다.
    SWAP(a[right], a[pivot]);
    return pivot;
}

void quicksort_(int *a, int left, int right){
    if(right>left){
        int pivot = partition(a, left, right);
        // pivot을 중심으로 잘라서 다시 recursion을 실행한다.
        quicksort_(a,left, pivot-1);
        quicksort_(a,pivot+1, right);
    }
}



void radixsort_(int *a, int n){
    // find max value
    int max_val = 0;
    int now_digit = 1;
    int bin_count[10];
    int i;
    // 임시로 넣을 자리를 만든다.
    int * b = (int *)malloc(n * sizeof(int));
    
    // 최대값을 찾는다(자리수를 알기 위하여)
    for(i=0; i<n; i++){
        if(a[i]>max_val)
            max_val = a[i];
    }
    
    // 최대값 자리수만큼 돌아야 한다.
    while((max_val/now_digit)>0){
        for(i=0;i<10;i++) bin_count[i]=0;
        
        // 원하는 자리수의 값에 1을 더해준다.
        for(i=0;i<n;i++)
            bin_count[(a[i]/now_digit)%10]++;
        // 누적해서 나중에 위치를 찾을수 있도록 한다.
        for(i=1;i<10;i++)
            bin_count[i] += bin_count[i-1];
            
        for(i = n-1; i>=0; i--){
            // 정렬한 값을 넣는다.
            b[--bin_count[(a[i]/now_digit)%10]] = a[i];
        }
        // 다 끝나면 a[i] 자리에 넣는다.
        for(i=0;i<n;i++)
            a[i]= b[i];
        // 자리수를 한칸 올린다.
        now_digit*=10;
    }


    free(b);
    
}

void adjust(int *a, int root, int n){
    int child, rootkey;
    // 비교할 root key를 지정한다.
    rootkey = a[root];
    child = 2*root;
    
    while(child<=n){
        // 왼쪽 오른쪽 중 무엇을 할지 찾는다.
        if((child<n)&&(a[child]<a[child+1])){
            child++;
        }
        
        // 내가 가장 큰 값이면 끝낸다.
        if(rootkey > a[child]){
            break;
        }else{
            // 내가 작으면 child 자리를 위로 올린다.
            // 자식이 크니까 부모자리로 간다.
            a[child/2] = a[child];
            child *=2;
        }
    }
    a[child/2] = rootkey;
}

void heapsort_(int* a, int n){
    int i;
    
    // 일단 max heap을 생성한다.
    // leaf는 제외하고 돌린다.
    for(i=n/2 ; i>0; i--){
        adjust(a, i, n);
    }
    
    // 하나씩 뽑으면서 최대값을 찾고 뒤에 놓아서 정렬한다.
    for(i=n-1 ; i>0; i--){
        SWAP(a[1],a[i+1]);
        adjust(a, 1, i);
    }
}


int main(int argc, char *argv[]) {
    
    //argc : number of arguments
    //argv[1], argv[2] , ... is the arguments
    // 실행할 떄 option 읽어오기
    FILE *fp, *fp_w;
    char* file_name, * option;
    
    // 파일이름을 지정하기 위해 input과 붙여준다.
    file_name = argv[1];
    option = argv[2];
    char result_file_name[30] = "result_";
    strcat(result_file_name,option);
    strcat(result_file_name,"_");
    strcat(result_file_name,file_name);
    int i;
    
    //파일에서 데이터 읽어오기
    fp = fopen(file_name, "r");
    fp_w = fopen(result_file_name, "w");
    fprintf(fp_w, "%s\n", file_name);
    fprintf(fp_w, "%s\n", option);
    
    int num;
    fscanf(fp,"%d", &num);
    fprintf(fp_w, "%d\n", num);
    
    // 파일 데이터 읽어서 써주기
    // heapsort 1부터 시작하기 위해서 크기 하나더 크게 만들기
    int * list = (int *)malloc((num+1) * sizeof(int));
    
    for(i=0;i<num;i++){
        int data;
        fscanf(fp,"%d",&data);
        list[i] = data;
    }
    
    clock_t start =clock();
    
    // Insertion Sort
    if(!strcmp(option,"1")){
        int i, j, tmp;
        for (i=1;i<num;i++){
            tmp = list[i];
            j = i;
            // 내가 더 작을 때까지 계속해서 자리를 바꿔준다.
            while((j>0)&&(tmp<list[j-1])){
                list[j] = list[j-1];
                j--;
            }
            list[j] = tmp;
        }
    //quick Sort
    }else if(!strcmp(option,"2")){
        quicksort_(list, 0, num-1);
    // Heap Sort
    }else if(!strcmp(option,"3")){
        // heapsort 하나씩 밀어서 시작점 1로 만들기
        for(i=num;i>0;i--)
            list[i] = list[i-1];
        
        heapsort_(list,num);
        
        // 다시 떙기기
        for(i=0;i<num;i++)
            list[i] = list[i+1];
    // combination or algorithim : radix Sort
    }else if(!strcmp(option,"4")){
        // 음수랑 양수랑 따로 구분해서 만들기
        int * neg_list = (int *)malloc(num * sizeof(int));
        int * pos_list = (int *)malloc(num * sizeof(int));
        int neg_idx = 0;
        int pos_idx = 0;
        int whole_idx = 0;
        
        for(i=num-1;i>=0;i--){
            // 음수는 계싼 못하므로 절대값으로 만들기
            if(list[i]<0)
                neg_list[neg_idx++] = -1*list[i];
            else
                pos_list[pos_idx++] = list[i];
        }

        radixsort_(neg_list,neg_idx);
        radixsort_(pos_list,pos_idx);

        // 음수에 다시 마이너스 붙이기.
        for(i=neg_idx-1;i>=0;i--)
            list[whole_idx++] = -1* neg_list[i];
        
        for(i=0;i<pos_idx;i++)
            list[whole_idx++] = pos_list[i];
        
    }

    // 시간을 체크한다.
    clock_t end =clock();
    fprintf(fp_w, "%.3f\n", (double)(end-start)/CLOCKS_PER_SEC*1000);
    // 결과 인쇄
    for(i=0;i<num;i++)
        fprintf(fp_w, "%d ", list[i]);
    
}


