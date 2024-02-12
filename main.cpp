#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "Any.h"

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());


int main() {
	printf("================================\n");
	printf("Basic tests: \n");
	{
		printf("Tests for int: ");
		printf("Randomly generate 100 uint64_t: \n");
		bool ok = true;
		uint64_t* a = new uint64_t(0);
		for (int i = 0; i < 100; i++) {
			uint64_t rngnum = rnd() % ((1ull << 50) - 1);
			Any T(rngnum);
			T.Data(a);
			if (*a != rngnum) {
				printf("Test failed on TC %d: input %llu, output %llu\n", i, rngnum, *a);
				ok = false;
				break;
			}
		}
		if (ok) printf("All tests passed!\n");
		delete a;
		printf("-------------------------------\n");
	}

	{
		printf("Tests for double: ");
		printf("Randomly generate 100 double: \n");
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0.0, 1.0);
		bool ok = true;
		double* a = new double(0.0f);
		for (int i = 0; i < 100; i++) {
			double randomDouble = dis(gen);
			Any T(randomDouble);
			T.Data(a);
			if (*a != randomDouble) {
				printf("Test failed on TC %d: input %f, output %f\n", i, randomDouble, *a);
				ok = false;
				break;
			}
		}
		if (ok) printf("All tests passed!\n");
		delete a;
		printf("-------------------------------\n");
	}

	{
		printf("Tests for pointer: ");
		printf("Randomly generate 100 pointers: \n");
		bool ok = true;
		u_int64_t** a = new uint64_t*;
		for (int i = 0; i < 100; i++) {
			uint64_t rngnum = rnd();
			uint64_t* b = new uint64_t(rngnum);
			Any T(b);
			T.Data(a);
			if (*a != b) {
				printf("Test failed on TC %d: input pointer %llx, output %llx\n", i, reinterpret_cast<uint64_t>(b), reinterpret_cast<uint64_t>(*a));
				ok = false;
				break;
			}
			delete b;
		}
		if (ok) printf("All tests passed!\n");
		delete a;
	}
	printf("================================\n");

}
