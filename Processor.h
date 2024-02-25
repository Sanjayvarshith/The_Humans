#include <bits/stdc++.h>
#include "Core.h"
using namespace std;

class Processor {
public:
    vector<char> memory;
    vector<Core> cores;

    Processor() : memory(4096, 0), cores(2) {}

    void run() {
        while (cores[0].active || cores[1].active) {
            for (int i = 0; i < 2; i++) {
                if (cores[i].active) {
                    cores[i].execute(memory);
                }
            }
        }
    }
};
