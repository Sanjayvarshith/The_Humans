#include <bits/stdc++.h>
#include "Core.h"
#include "pipe.hpp"
#include "datapipe.hpp"
#include "CacheSimulator.hpp"
using namespace std;

class Processor {
public:
    vector<char> memory;
    vector<pipe> p;
    vector<datapipe> dp;
    vector<Core> cores;
    int dataForwarding=0;
    CacheSimulator cs;

    int clock;
    Processor() : memory(4096, 0), cores(2),clock(0),p(2),dp(2),cs() {
        //  cs = CacheSimulator(1024, 32, 1, 0);
        // cs.push_back(CacheSimulator());
        // cs.set(512, 16, 2, 0);512

    }

    void run() {
        while (cores[0].active || cores[1].active) {
            // cout<<5;
            for (int i = 0; i < 2; i++) {
                if (cores[i].active) {
                    // if(cores[i].pc/4<cores[i].program.size())cout<<cores[i].program[cores[i].pc/4];
                    // cout<<cores[i].active<<endl;
                    cores[i].vv.push_back(cores[i].v);
                    if(dataForwarding==1)
                    {
                        dp[i].implement(cores[i],memory,cs);
                    }
                    else
                    {
                        p[i].implement(cores[i],memory,cs);
                    }
                    cores[i].cycles++;
                    // cout<<cores[i].program[cores[i].pc/4];
                    // cout<<cores[i].active<<endl;
        //             for(auto i: cores[i].label) cout<<i.first<<" "<<i.second<<endl;
        // cout<<"--------------------"<<endl;
                }
            }
        }
    }
};
