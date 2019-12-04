//
//  main.cpp
//  huffman
//
//  Created by dizwe on 2019/12/04.
//  Copyright © 2019 dizwe. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#define ASCII_NUM 128
#define SWAP(a,b) { struct huff_heap tmp; tmp = a; a=b; b=tmp;}
using namespace std;

typedef  struct  BIT
{
    unsigned   char   b0 : 1;     // 0,1
    unsigned   char   b1 : 1;     // 0,1
    unsigned   char   b2 : 1;     // 0,1
    unsigned   char   b3 : 1;     // 0,1
    unsigned   char   b4 : 1;     // 0,1
    unsigned   char   b5 : 1;     // 0,1
    unsigned   char   b6 : 1;     // 0,1
    unsigned   char   b7 : 1;     // 0,1
}BIT;

typedef  struct  huff_heap
{
    struct huff_heap *left = NULL;
    struct huff_heap *right = NULL;
    unsigned int freq;
    char c;
}huff_heap;

int get_val(struct BIT *ep, int n)
{
    // 8bit 안에 있는 정보를 하나씩 얻을 수 있게 커트텀하기
    switch(n)
    {
        case 0: return ep->b0;
        case 1: return ep->b1;
        case 2: return ep->b2;
        case 3: return ep->b3;
        case 4: return ep->b4;
        case 5: return ep->b5;
        case 6: return ep->b6;
        case 7: return ep->b7;
    }
    return -1; /* Indicates illegal field index. */
}

void store_val(struct BIT *ep, int n, int val)
{
    // 원하는 자리에 원하는 값을 집어넣기.
    switch(n)
    {
        case 0:  ep->b0=val;
        case 1:  ep->b1=val;
        case 2:  ep->b2=val;
        case 3:  ep->b3=val;
        case 4:  ep->b4=val;
        case 5:  ep->b5=val;
        case 6:  ep->b6=val;
        case 7:  ep->b7=val;
    }
}

unsigned char bytes_to_ascii(struct BIT *ep)
{
    // unsinged로 작업해야 256까지 집어넣을 수 있음
    // char로 바꿔서 8비트 정보를 를 한 char에 다 집어넣도록 하기
    return ep->b0*1 + ep->b1*2 + ep->b2*4 + ep->b3*8+
           ep->b4*16 + ep->b5*32 + ep->b6*64 + ep->b7*128;
}

struct huff_heap *h_heap;
int h_heap_num;

void heap_init(int *frequencies){
    // 값 집어넣기
    int f_idx = 0;
    for(int i=0;i<ASCII_NUM;i++){
        if(frequencies[i]>0){
            h_heap[f_idx].freq = frequencies[i];
            h_heap[f_idx].c = i;
            f_idx++;
        }
    }
}

int quick_sort_partition(int left, int right){
    int pivot = left;
    for(int i=left;i<right;i++){
        if(h_heap[i].freq < h_heap[right].freq){
            SWAP(h_heap[i], h_heap[pivot]);
            pivot++;
        }
    }
    SWAP(h_heap[right], h_heap[pivot]);
    return pivot;
}

void quick_sort_heap(int left, int right){
    int pivot;
    if(right - left > 0){
        pivot = quick_sort_partition(left, right);
        quick_sort_heap(left, pivot-1);
        quick_sort_heap(pivot+1, right);
    }
}


huff_heap get_min_heap(int n){
    // 첫번째꺼 return 하고 다시 sorting한다.
    //left right는 주소값을 가르켜야 해서  & 사용함...
    // 주소를 주는거라 값이 바뀌면 얘도 바뀌지??
    struct huff_heap min_heap;
    memcpy(&min_heap, &h_heap[0], sizeof(struct huff_heap));

//    printf("\n");
//    for(int i=0; i<h_heap_num; i++)
//        cout << " " << h_heap[i].c;
//
    // 개수가 2개라도 있을 때
    if(h_heap_num>=2){
        // 하나 뺴냈으니 한칸씩 당기기
        for(int i=1; i<h_heap_num; i++)
            h_heap[i-1] = h_heap[i];
    }
    // 제일 마지막 자리 초기화
    h_heap[h_heap_num-1].freq = 0;
    h_heap[h_heap_num-1].c = 0;
    
//    printf("\n");
//    for(int i=0; i<h_heap_num; i++)
//        cout << " " << h_heap[i].c;
    
    // 쓰는 개수 하나ㅏ 줄어들었으니까 계산
    h_heap_num--;
//    cout << " check-" << min_heap->c;
    return min_heap;
}


// 여기서도 * 넣으면 struct 자체가 바뀔듯!
void insert_to_heap(struct huff_heap new_heap){
    // 넣고나서 정렬
    // 일단 넣을 자리 찾아서 넣어야지
    // 자리 찾고 그 자리에 집어넣기
    for(int i =0; i<h_heap_num;i++){
        cout << " " <<h_heap[i].freq<< "-" <<(char)h_heap[i].c;
    }

    h_heap[h_heap_num] = new_heap;

    quick_sort_heap(0,h_heap_num);
    // 추가되었으니까 값 올리기
    h_heap_num++;
    printf("check");
   
    printf("\n");
}

void get_huffman_table(string letters, int *frequencies){
    // !! 없는 문자 깔끔하게 처리할 방법도 생각해보자...(근데 어차피 안쓸꺼면 만들어도 상관없을듯) -> 디버깅이 너무 힘들어요!!
    int ascii_real_num=0;
    for(int i=0;i<ASCII_NUM;i++)
        if(frequencies[i]>0) ascii_real_num++;
    
    h_heap = (struct huff_heap*) malloc(sizeof(struct huff_heap)* ascii_real_num);

    // 각자 떨어져있는 heap을 만들고 정렬한다.
    heap_init(frequencies);
    
//    for(int i =0; i<ascii_real_num;i++){
//        cout <<" " <<h_heap[i].freq<<"-" <<(char)h_heap[i].c;
//    }

    
    // 정렬하기(by quick sort)
    quick_sort_heap(0, ascii_real_num-1);
    // sorting 잘 되었는지 확인
    for(int i =0; i<ascii_real_num;i++){
        cout << " " <<h_heap[i].freq<< "-" <<(char)h_heap[i].c;
    }
    printf("\n");


    h_heap_num = ascii_real_num;
    
    for(int i=1; i<ascii_real_num; i++){\
        huff_heap * u_temp = (struct huff_heap*) malloc(sizeof(struct huff_heap));
        huff_heap * v_temp = (struct huff_heap*) malloc(sizeof(struct huff_heap));
        huff_heap u;
        huff_heap v;
        
        // ?? 이렇게 temp 안쓰고 받을 방법이 없나? 꼭 struct 안에는 *로 나를 refer 해야하나?
        u = get_min_heap(h_heap_num);
        u_temp = &u;
//        u = &u_temp;
        cout << " " <<u_temp->freq<< "_____" <<(char)u_temp->c;
        v = get_min_heap(h_heap_num);
        v_temp = &v;
//        v = &v_temp;
        cout << " " <<v_temp->freq<< "_____" <<(char)v_temp->c;
        
        struct huff_heap w;
        w.left = u_temp;
        w.right = v_temp;
        w.freq = u_temp->freq + v_temp->freq;
        cout << " !@#" << w.freq;
        w.c = '$'; // parent 알아보기 쉽게 표현

        insert_to_heap(w);
    }
    cout << " !@#" << h_heap[0].right->left->freq;
    cout << " !@#" << h_heap[0].left->freq;
    printf("hihi");
//    for(int i =0; i<ASCII_NUM;i++){
//        cout << " " <<h_heap[i].freq<< "-" <<(char)h_heap[i].c;
//    }
}

int main(int argc, char *argv[])
{
    ifstream ifs ("/Users/dizwe/programm/algo/huffman/shorter.txt", ios::in);
    char ascii = ifs.get();
    string input_string;
    //0으로 초기화해야 아무것도 없는 값도 잘 처리됨
    int ascii_num[ASCII_NUM] = {0};
//    char * option = argv[1];
//    char * file_name = argv[2];
    
    while(true){
        if(ifs.eof()) break;
        if(ifs.good()){
            ascii_num[ascii]++;
            input_string += ascii;
            ascii = ifs.get();
        }
    }
    

    // compress하기!
//    if(!strcmp(option,"-c")){
    
    get_huffman_table(input_string, ascii_num);
//    BIT * zip_info;
//    zip_info = (struct BIT *) malloc(sizeof(struct BIT)*input_string.size());
//    int k;
//    int real_length=0;
//    int byte_idx, bit_idx;
    
    //    byte_idx = real_length/8;
    //    bit_idx = real_length%8;
    ////            store_val(&bb[byte_idx],bit_idx,0);
    //    k = get_val(&bb[byte_idx],bit_idx);
    //    real_length++;

        
        // 파일에 쓰기
    //    ofstream ofs ("/Users/dizwe/programm/algo/huffman/mino.txt", ios::out|ios::trunc|ios::binary);
    //    for(int i=0;i<300; i++){
    //        cout << " " << (int)bytes_to_ascii((&bb[i]));
    //        ofs << bytes_to_ascii((&bb[i]));
    //    }

//    }
    
    // 인코딩하고 table 만들기
    
    // 글자씩 돌아가면서 encoding 하기
    
    // encoding 하고 어떻게 하냐...?
    



//
    

//
//    printf(" BIT = %lu byte \n", sizeof(bb[0]) );
    

        
    return 0;
}
