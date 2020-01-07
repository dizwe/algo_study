#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

long long int power(int a, int b);
int string_to_int(char[]);
int main(int argc, char* argv[]) {
	long long int sizeN;
	int i, seed, down, up;
	int arg1, arg2, arg3, arg4, arg5;
	arg1 = atoi(argv[1]);
	arg2 = atoi(argv[2]);
	arg3 = atoi(argv[3]);
	arg4 = atoi(argv[4]);
	arg5 = atoi(argv[5]);


	int* arr;
	seed = arg1;
	/*
	std::cout << "SEED NUMBER :" << std::endl;
	std::cin >> seed;*/
	srand((unsigned int)seed);

	int boundDown, boundUp;
	boundDown = arg2; boundUp = arg3;
	int hab = boundDown * -1 + boundUp + 1;

	down = arg4; up = arg5;
	/*
	std::cout << "How much Number generate? a to the power of n " << std::endl;
	std::cout << "type the a and n orderly please" << std:: endl;
	std::cin >> down >> up;
	*/
	sizeN = power(down, up);
	arr = (int*)malloc(sizeof(int) * (sizeN + 1));
	std::ofstream myfile;

	myfile.open("inputfile.txt", std::ios::out | std::ios::trunc);
	myfile << sizeN << " ";
	int temp;
	for (i = 1; i <= sizeN; i++) {
		temp = boundDown + (rand() % hab);
		//std::cout << temp << std::endl;
		myfile << temp << " ";

	}
	//myfile << arr;
	myfile.close();
	return 0;
}

//a¸¦ b¹ø °öÇÑ´Ù.
long long int power(int a, int b) {
	long long int result = 1;
	int i;
	for (i = 0; i < b; i++)
		result *= a;

	return result;
}

int string_to_int(char argu[]) {
	int ha = strlen(argu);
	printf("ha : %d\n", ha);
	int answer = (int)argu[ha-1] - '0', i;
	printf("asdf : %d\n\n\n" , answer);
	for (i = ha-2; i >= 0; i--){
	//	printf("answer : %d\n %d\n", answer, i);
		answer *= 10;
		answer += argu[i] - '0';
	}
	return answer;
}
