#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "any.h"
const int N = 100;

std::mt19937_64 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

int main() {
	#ifdef DEBUG
    printf("Debug mode open!\n");
    #endif
	printf("================================\n");
	printf("Testing integer: \n");
	printf("Testing valid integer: ");
	for (int i = 0; i < N; i++) {
		int64_t rngnum = rnd() & (0x1FFFFFFFFFFFF);
		AnyC T = constructor(rngnum);
		if (!is_int(T)) {
			printf("Test failed on TC %d: input %lld\n", i, rngnum);
			return 0;
		}
		if (is_double(T) || is_ptr(T)) {
			printf("Test failed on TC %d: input %lld\n", i, rngnum);
			return 0;
		}
		int64_t result = to_int(T);
		if (result != rngnum) {
			printf("Test failed on TC %d: input %lld, output %lld\n", i, rngnum, result);
			return 0;
		}

		T = constructor(-rngnum);
		if (!is_int(T)) {
			printf("Test failed on TC %d: input %lld\n", i, -rngnum);
			return 0;
		}
		if (is_double(T) || is_ptr(T)) {
			printf("Test failed on TC %d: input %lld\n", i, -rngnum);
			return 0;
		}
		result = to_int(T);
		if (result != -rngnum) {
			printf("Test failed on TC %d: input %lld, output %lld\n", i, -rngnum, result);
			return 0;
		}
	}
	printf("All tests passed!\n");
	printf("Testing invalid integer: ");
	for (int i = 0; i < N; i++) {
		int64_t rngnum = rnd() & (0xFFF);
		rngnum += 0x1FFFFFFFFFFFF;
		if (rngnum & 1) rngnum = -rngnum;
		try {
			constructor(rngnum);
		} catch (std::runtime_error& e) {
			continue;
		}
		printf("Test failed on TC %d: input %lld\n", i, rngnum);
		return 0;
	}
	printf("All tests passed!\n");
	printf("================================\n");

}

// int main() {
// 	printf("================================\n");
// 	printf("Basic tests: \n");
// 	{
// 		printf("Tests for int: ");
// 		printf("Randomly generate 100 uint64_t: \n");
// 		bool ok = true;
// 		uint64_t* a = new uint64_t(0);
// 		for (int i = 0; i < 100; i++) {
// 			uint64_t rngnum = rnd() % ((1ull << 50) - 1);
// 			Any T(rngnum);
// 			T.Data(a);
// 			if (*a != rngnum) {
// 				printf("Test failed on TC %d: input %llu, output %llu\n", i, rngnum, *a);
// 				ok = false;
// 				break;
// 			}
// 		}
// 		if (ok) printf("All tests passed!\n");
// 		delete a;
// 		printf("-------------------------------\n");
// 	}

// 	{
// 		printf("Tests for double: ");
// 		printf("Randomly generate 100 double: \n");
// 		std::random_device rd;
// 		std::mt19937 gen(rd());
// 		std::uniform_real_distribution<double> dis(0.0, 1.0);
// 		bool ok = true;
// 		double* a = new double(0.0f);
// 		for (int i = 0; i < 100; i++) {
// 			double randomDouble = dis(gen);
// 			Any T(randomDouble);
// 			T.Data(a);
// 			if (*a != randomDouble) {
// 				printf("Test failed on TC %d: input %f, output %f\n", i, randomDouble, *a);
// 				ok = false;
// 				break;
// 			}
// 		}
// 		if (ok) printf("All tests passed!\n");
// 		delete a;
// 		printf("-------------------------------\n");
// 	}

// 	{
// 		printf("Tests for pointer: ");
// 		printf("Randomly generate 100 pointers: \n");
// 		bool ok = true;
// 		u_int64_t** a = new uint64_t*;
// 		for (int i = 0; i < 100; i++) {
// 			uint64_t rngnum = rnd();
// 			uint64_t* b = new uint64_t(rngnum);
// 			Any T(b);
// 			T.Data(a);
// 			if (*a != b) {
// 				printf("Test failed on TC %d: input pointer %llx, output %llx\n", i, reinterpret_cast<uint64_t>(b), reinterpret_cast<uint64_t>(*a));
// 				ok = false;
// 				break;
// 			}
// 			delete b;
// 		}
// 		if (ok) printf("All tests passed!\n");
// 		delete a;
// 	}
// 	printf("================================\n");

// }
