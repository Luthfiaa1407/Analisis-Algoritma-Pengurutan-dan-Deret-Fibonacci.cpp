#include <iostream>
#include <map>
#include <chrono>

using namespace std;

//                                 i : 1, 2, 3, 4, 5, 6, 7, 8 , 9 , 10
// sample deretan fibonacci sequence : 0, 1, 1, 2, 3, 5, 8, 13, 21, 34

double fibRecursive(int num) {
    if (num == 1) {
        return 0;
    }
    else if (num == 2) {
        return 1;
    }
    else {
        return fibRecursive(num - 1) + fibRecursive(num - 2);
    }
}

map<int, double> processedValue;

double fibDynamic(int num) {
    if (processedValue[num] != 0) {
        return processedValue[num];
    }

    if (num == 1) {
        processedValue[num] = 0;
        return 0;
    }
    else if (num == 2) {
        processedValue[num] = 1;
        return 1;
    }
    else {
        int res = fibDynamic(num - 1) + fibDynamic(num - 2);
        processedValue[num] = res;
        return res;
    }
}


void benchmarkRecursive(int num) {\
    printf("executing fibRecursive(%d)\n", num);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    
    cout << "Result: " << fibRecursive(num) << endl;
    
    chrono::steady_clock::time_point elapsed = chrono::steady_clock::now();
    cout << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(elapsed - start).count() << "µs" << endl;
    cout << endl;
}

void benchmarkDynamic(int num) {
    printf("executing fibDynamic(%d)\n", num);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    
    cout << "Result: " << fibDynamic(num) << endl;
    
    chrono::steady_clock::time_point elapsed = chrono::steady_clock::now();
    cout << "Time elapsed: " << chrono::duration_cast<chrono::microseconds>(elapsed - start).count() << "µs" << endl;
    cout << endl;
}



int main() {
    printf("---------------------------------\n");
    printf(" Benchmarking Recursive Approach \n");
    printf("---------------------------------\n");
    benchmarkRecursive(10);
    benchmarkRecursive(25);
    benchmarkRecursive(30);
    benchmarkRecursive(40);
    benchmarkRecursive(50);

    printf("---------------------------------\n");
    printf("  Benchmarking Dynamic Approach  \n");
    printf("---------------------------------\n");
    benchmarkDynamic(10);
    benchmarkDynamic(25);
    benchmarkDynamic(30);
    benchmarkDynamic(40);
    benchmarkDynamic(50);

    return 0;
}
