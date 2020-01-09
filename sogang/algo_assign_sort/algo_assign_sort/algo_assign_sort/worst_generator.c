//
//  worst_generator.c
//  algo_assign_sort
//
//  Created by dizwe on 2019/11/04.
//  Copyright © 2019 dizwe. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {

    //argc : number of arguments
    //argv[1], argv[2] , ... is the arguments
    // 실행할 떄 option 읽어오기
    FILE *fp;
    char* option;

    // 파일이름을 지정하기 위해 input과 붙여준다.
    option = argv[1];
    
    fp = fopen("worst.txt", "w");
    long long int num = pow(2,25);
    long long int i;
    
    fprintf(fp,"%lld ",num);
    for(i = num;i>0;i--){
        fprintf(fp,"%lld ",i);
    }
    
};
