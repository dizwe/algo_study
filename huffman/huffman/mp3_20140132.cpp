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
#include <math.h>
#include <string.h>

#define ASCII_NUM 128
#define SWAP(a,b) { struct huff_heap tmp; tmp = a; a=b; b=tmp;}
#define SWAP_TABLE(a,b) { struct huff_encode tmp; tmp = a; a=b; b=tmp;}

using namespace std;

// 한 element 크기가 1bit인 struct
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
    unsigned int parent = 0;
}huff_heap;

typedef  struct  huff_encode
{
    char c;
    string code;
    int use =0;
}huff_encode;

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
    return ep->b7*1 + ep->b6*2 + ep->b5*4 + ep->b4*8+
            ep->b3*16 + ep->b2*32 + ep->b1*64 + ep->b0*128;
}

////////////// heap 관련
struct huff_heap *h_heap;
int h_heap_num;
struct huff_encode huff_table[ASCII_NUM];

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


// freq에 따라 sorting 한다.
int quick_sort_partition(int left, int right){
    int pivot = left;
    for(int i=left;i<right;i++){
        //right가 pivot이 될 애다.
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


huff_heap * get_min_heap(int n){
    // 첫번째꺼 return 하고 다시 한칸씩 당겨야 한다.
    struct huff_heap * min_heap = (struct huff_heap*) malloc(sizeof(struct huff_heap));
    
    memcpy(min_heap, &h_heap[0], sizeof(struct huff_heap));

    // 개수가 2개라도 있을 때 한칸씩 당기자.
    if(h_heap_num>=2){
        // 하나 뺴냈으니 한칸씩 당기기
        for(int i=1; i<h_heap_num; i++)
            h_heap[i-1] = h_heap[i];
    }

    // 제일 마지막 자리 초기화
    h_heap[h_heap_num-1].freq = 0;
    h_heap[h_heap_num-1].c = 0;
    h_heap[h_heap_num-1].parent = 0;
    
    // 쓰는 개수 하나 줄어들었으니까 계산
    h_heap_num--;

    return min_heap;
}


// 여기서도 * 넣으면 struct 자체가 바뀔듯!
void insert_to_heap(struct huff_heap new_heap){
    // 넣고나서 정렬
    // 일단 넣을 자리 찾아서 넣어야지

    h_heap[h_heap_num] = new_heap;

    quick_sort_heap(0,h_heap_num);
    // 추가되었으니까 값 올리기
    h_heap_num++;
}

void build_huffman_table(struct huff_heap * h ,string encode){
    // h_heap 기반으로 만든다.
    // !!! h->parent가 parent가 아닌데도 1이 되는 경우 잇음. h->c가 0인지도 체크한다.
    if((h->parent==1)&&(h->c==0)){
        // C!!! check NULL은 아닌데 주소값만 있는 경우도 있음. freq>0 추가.
        if((h->left!=NULL)&&(h->left->freq>0)){
            build_huffman_table(h->left, encode+"0");
        }
        if((h->right!=NULL)&&(h->right->freq>0)){
            build_huffman_table(h->right, encode+"1");
        }
    }else{
        // leaf일 때 table에 작성하기(leaf가 실제정보니까)
        if((h->left==NULL&&h->right==NULL)||(h->freq>0&&h->c)){
            huff_table[h->c].c = h->c;
            huff_table[h->c].code = encode;
            huff_table[h->c].use = 1;
        }
    }
}

void get_huffman_table_encode(string letters, int *frequencies, char * file_name){
    // !! 없는 문자 깔끔하게 처리할 방법도 생각해보자...(근데 어차피 안쓸꺼면 만들어도 상관없을듯) -> 디버깅이 너무 힘들어요!!

    // ascii_real_num으로 실제로 "쓴 단어만 사용하자"
    int ascii_real_num=0;
    for(int i=0;i<ASCII_NUM;i++)
        if(frequencies[i]>0) ascii_real_num++;
    
    h_heap = (struct huff_heap*) malloc(sizeof(struct huff_heap)* ascii_real_num);

    // 각자 떨어져있는 heap을 만들어 init한다.
    heap_init(frequencies);
    
    // 정렬하기(by quick sort)
    quick_sort_heap(0, ascii_real_num-1);
    // sorting 잘 되었는지 확인
    //    for(int i =0; i<ascii_real_num;i++){
    //        cout << " " <<h_heap[i].freq<< "-" <<(char)h_heap[i].c;
    //    }
    //    printf("\n");

    huff_heap * u;
    huff_heap * v;
    h_heap_num = ascii_real_num;
    
    for(int i=1; i<ascii_real_num; i++){
        // ?? 이렇게 temp 안쓰고 받을 방법이 없나? 꼭 struct 안에는 *로 나를 refer 해야하나?!!!(github 이상한점 보기)
        u = get_min_heap(h_heap_num);
        // cout << " " <<u->freq<< "_____" <<(char)u->c;
        v = get_min_heap(h_heap_num);
        // cout << " " <<v->freq<< "_____" <<(char)v->c;
        
        struct huff_heap w;
        w.left = u;
        w.right = v;
    
        w.freq = u->freq + v->freq;
        w.parent = 1; // parent 알아보기 쉽게 표현
        w.c = 0;// parent 는 NULL 문자로도 바꾼다. 안하면 엉뚱한 문자가 null이 되더라.(build huff table에서 체크 함)

        // parent heap에 넣기
        insert_to_heap(w);
    }

    // 이제 h_heap[0]만 있음(다 합쳐졌으니까)
    // heap tree 기반으로 huffman table 만들기
    build_huffman_table(&h_heap[0],"");
    
    // huffman tree 이용해서 encoding 하기
    BIT * zip_info;
    zip_info = (struct BIT *) malloc(sizeof(struct BIT)*letters.size());
    int real_length=0;
    int byte_idx, bit_idx;
    
    // 각 문자별로 대응하는 코드 찾아서 value 넣기
    for(int i =0 ; i<letters.size();i++){
        string code = huff_table[letters[i]].code;
        // cout << "- " <<  code << "\n";
        for(int j =0 ; j<code.size();j++){
            byte_idx = real_length/8;
            bit_idx = real_length%8;
            store_val(&zip_info[byte_idx],bit_idx,(int)code[j]-'0');
            real_length++;
        }
    }
    
    // 잘들어갔는지 확인 -> 잘들어감
    //    for(int i =0 ; i<real_length;i++){
    //        byte_idx = i/8;
    //        bit_idx = i%8;
    //        printf("%d ", get_val(&zip_info[byte_idx],bit_idx));
    //    }
    
    // encoding 한것 파일에 쓰기
    string huffman_encoded_file;
    huffman_encoded_file = string(file_name) + ".zz";
    ofstream ofs (huffman_encoded_file, ios::out|ios::trunc|ios::binary);
    
    // encoding 위한 table 정보(전체 개수)를 먼저 작성한다
    int use_char_in_table_len = 0;
    for(int i =0 ; i<ASCII_NUM;i++)
        if(huff_table[i].use==1) use_char_in_table_len++;
    
    ofs << use_char_in_table_len << endl;

    // 인코딩 테이블 담기
    for(int i =0 ; i<ASCII_NUM;i++){
        if(huff_table[i].use==1) {
            // "|"로 구분한다. \n으로 구분했더니, line break가 \n\n으로 읽혀셔 getline할 떄 따로 읽히는 문제가 있었다.
            ofs << huff_table[i].c << huff_table[i].code << "|";
        }
    }
    
    // 마지막 바이트는 전체 8bit가 차있지 않을수도 있으므로 어디까지가 진짜 정보인지 파악할 수 있도록 따로 저장한다.
    ofs << real_length%8 << "\n";
    // 전체 개수도 체크하면서 작성한다.
    ofs << real_length/8+1 << "\n";
    
    // bit단위로 되어있던 정보를 8bit가 한 byte가 되게 ascii로 얻는다.
    // real_length가 실제 길이이므로 /8 한다.
    for(int i=0;i<real_length/8+1; i++){
        ofs << (unsigned char) bytes_to_ascii((&zip_info[i]));
    }

     // C!!! tree 다니면서 free 해야할 듯.
}

// partition table정렬하기
int quick_sort_partition_table(struct huff_encode * table, int left, int right){
    int pivot = left;
    for(int i=left;i<right;i++){
        // right가 pivot인 테이블이쥐
        if(table[i].code.size() < table[right].code.size()){
            SWAP_TABLE(table[i], table[pivot]);
            pivot++;
        }
    }
    
    SWAP_TABLE(table[right], table[pivot]);
    return pivot;
}

void quick_sort_table(struct huff_encode * table, int left, int right){
    int pivot;
    if(right - left > 0){
        pivot = quick_sort_partition_table(table, left, right);
        quick_sort_table(table, left, pivot-1);
        quick_sort_table(table, pivot+1, right);
    }
}

string char_to_bits(unsigned char one_char){
    // 캐릭터 하나를 8bit로 다시 쪼개기
    // unsigned로 받아야 255까지 표현 가능하다.
    unsigned int char_int_info = (unsigned int)one_char;
    string bits_string = "";
    // 각자리 비트 확인하면서 0인지 1인지 확인하기
    for(int i=7;i>=0;i--){
        // 몫이 1이면 걔는 1인거임
        if(char_int_info/(int)pow(2,i)==1){
            bits_string += "1";
        }else if(char_int_info/(int)pow(2,i)==0){
            bits_string += "0";
        }
        // 나머지가 그 아래 자리수 값이다.
        char_int_info = char_int_info%((int)pow(2,i));
    }

    return bits_string;
}


int main(int argc, char *argv[])
{
    char* file_name, * option;
    option = argv[1];
    file_name = argv[2];

    if(!strcmp(option,"-c")){
        // 파일 읽어오기
        ifstream ifs (file_name, ios::in);
        if(!ifs.is_open())
        {
          // error! maybe the file doesn't exist.
            cout << "FILE NOT EXIST ERROR!";
            return 0;
        }
        char ascii = ifs.get();
        string input_string;
        //0으로 초기화해야 아무것도 없는 값도 잘 처리됨
        int ascii_num[ASCII_NUM] = {0};

        // 문자 하나씩 세면서 아스키 코드별 몇개인지 센다.
        while(true){
            if(ifs.eof()) break;
            if(ifs.good()){
                ascii_num[ascii]++;
                input_string += ascii;
                ascii = ifs.get();
            }
        }

        // compress하기!
        get_huffman_table_encode(input_string, ascii_num, file_name);

    }
    else if(!strcmp(option,"-d")){
        // 읽어올 파일 열기
        ifstream ifs (file_name, ios::in|ios::binary);
        // 파일 없을 때 에러를 일으킨다.
        if(!ifs.is_open())
        {
           // error! maybe the file doesn't exist.
            cout << "FILE NOT EXIST ERROR!";
            return 0;
        }
        
        // 인쇄할 파일 열기
        string huffman_decoded_file = string(file_name) + ".yy";
        ofstream ofs (huffman_decoded_file, ios::out|ios::trunc|ios::binary);
        
        // 인코딩 테이블 얻기
        string buffer;
        getline(ifs, buffer);
        ifs.peek();
        int table_num = atoi(buffer.c_str());

        // !!! C++에서 같은 의미다!
        // struct huff_encode * code_table = (struct huff_encode *) malloc(sizeof(struct huff_encode)*table_num);
        struct huff_encode * code_table = new huff_encode[table_num];

        for(int i=0;i<table_num; i++){
            string c_string;
            // !!! '|'를 구분자로 하면 a11||22로 해도 a11을 읽다가 |가 보이면 |는 무시하고 다음 글자(|)를 읽으므로 문제가 없다.
            // |뒤에 바로 last_bit_num 정보가 있어도 |를 제외하고 다음 한줄을 읽는것이므로 잘 읽히는 것이다.
            getline(ifs, c_string,'|');
            char c = (char)c_string[0];

            code_table[i].c = c;
            // !!! 첫번째 문자는 잘랐으니까 두번째 문자부터 얻는다
            code_table[i].code = c_string.substr(1);
        }

        // code table 정렬하기(왜냐면 짧은거 부터 조건 찾아가면서 확인해야 하니까)
        quick_sort_table(code_table, 0, table_num-1);
        
        // 정보가 8비트 단위로 잘라지는 것이 아니라서 뒤에 쓰레기 정보를 자를 수 있는 정보를 얻는다.
        string last_bit_num_str;
        getline(ifs, last_bit_num_str);
        // atoi 를 써야하는 것이 개수가 여러 자리일 수 있다.
        int last_bit_num = atoi(last_bit_num_str.c_str());
        // int last_bit_num = (int)ifs.get()-'0';
        ifs.peek();

        // 전체 bit 정보도 얻는다.
        string total_bit_num_str;
        getline(ifs, total_bit_num_str);
        int total_bit_num = atoi(total_bit_num_str.c_str());;
  
        // 한바이트씩 읽으면서 맞는 패턴이 있는지 체크하면서 decoding 한다.
        int byte_count = 0;
        string one_byte_bit_info;
        unsigned char one_byte = ifs.get();
        // check_string은 패턴이 만족될때까지 하나씩 채워넣는 역할을 한다.
        string check_string = "";
        string decoded_string = "";
        
        while(true){
            if(ifs.eof()) break;
            if(ifs.good()){
                // 한글자를 bit 단위로 다시 풀기
                one_byte_bit_info = char_to_bits(one_byte);
                
                byte_count++;
                // 한bit씩 집어넣으면서 확인한다
                for(int i=0;i<8;i++){
                   check_string += one_byte_bit_info[i];
                   // 한 문자 인코딩마다 길이 짧은 순서대로 확인한다.
                    for(int j=0; j<table_num;j++){
                        // 마지막 bit이면서 실제 데이터가 아닌 비트일때 짤라버리기
                        // last_bit_num은 1부터 시작하도록 작서했으므로 -1하기
                        if((byte_count==total_bit_num)&&(i>last_bit_num-1)){
                            break;
                        }else{
                            if(check_string.compare(code_table[j].code)== 0){
                                decoded_string += code_table[j].c;
                                check_string = "";
                                break;
                            }
                        }
                    }
                }
                // THANKYOU. NEXT,
                one_byte = ifs.get();
            }
        }
        ofs << decoded_string;
    }else{
        cout << "option ERROR!";
    }
        
    return 0;
}
