#include <bits/stdc++.h>
using namespace std;

int main() {
    random_device ran;
    mt19937 gen(ran());
    uniform_int_distribution<int> dist(60, 100);

    int result = dist(gen);
    if (result == 67) {
        cout << "hahahahahaha 67)";
        return 0;
    }
    cout << result;
}