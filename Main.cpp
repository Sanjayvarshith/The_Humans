#include <bits/stdc++.h>
#include"Processor.h"
using namespace std;

int main() {
    Processor sim;
    ifstream fin1,fin2;
    string line1,line2;

    fin1.open("p1.txt");
    int a=0;
    sim.cores[0].loc=1000;
    sim.cores[1].loc=3000;
    while(getline(fin1,line1))
    {
        if(sim.cores[0].add(line1,a,sim.memory)) a+=4;   
    }
    fin1.close();
    fin2.open("p2.txt");
    a=0;
    while(getline(fin2,line2))
    {
        if(sim.cores[1].add(line2,a,sim.memory)) a+=4;
        // cout<<line2<<endl;   
    }
    fin2.close();
    // cout<<1;
    sim.run();
    cout<<"--------------------PIPELINE DIAGRAM------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
        cout<<"---------------------Core "<<i<<"----------------------"<<endl;
        // for(int j=0;j<sim.cores[i].vv.size();j++)
        // {
        //     for(int k=0;k<sim.cores[i].vv[j].size();k++)
        //     {
        //         cout<<sim.cores[i].vv[j][k]<<" ";
        //     }
        //     cout<<endl;
        // }
        int n=sim.cores[i].vv.size();
        int m=sim.cores[i].vv[0].size();
        for(int j=0;j<m;j++)
        {
            cout<<sim.cores[i].program[j]<<endl;
            for(int k=0;k<n;k++)
            {
                cout<<sim.cores[i].vv[k][j]<<" ";
            }
            cout<<endl;
        }
    }
    // for(auto i: sim.cores[1].label) cout<<i.first<<" "<<i.second<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        for(int i=0;i<2;i++)
        {
            cout<<"---------------------Core "<<i<<"----------------------"<<endl;
            cout<<"Cycles: "<<sim.cores[i].cycles<<endl;
            cout<<"Instructions: "<<sim.cores[i].instructions<<endl;
            cout<<"Stalls: "<<sim.cores[i].stalls<<endl;
            if(sim.cores[i].instructions==0 || sim.cores[i].cycles==0) {
                cout<<"IPC: "<<endl;
                cout<<"CPI: "<<endl;
                continue;
            }
            cout<<"IPC: "<<(float)sim.cores[i].instructions/sim.cores[i].cycles<<endl;
            cout<<"CPI: "<<(float)sim.cores[i].cycles/sim.cores[i].instructions<<endl;
        }
 cout << "============ After Run ============" << endl;

    for (int i = 0; i < 2; i++) {
        cout << "Core " << i << " Registers: ";
        for (int j = 0; j < 32; j++) {
            cout << sim.cores[i].registers[j] << " ";
        }
        cout << endl;
    }
    int start;
    cout<<"=========Word Memory=========="<<endl;
    start=1000;
    while(sim.memory[start]!=0)
    {
        int s=0;
        for(int i=0;i<4;i++)
        {
            int c=sim.memory[start+i];
            for(int j=0;j<8;j++)
            {
                if(i==3 && j==7)
                {
                    if(c>>7&1==1) s-=pow(2,31);
                    continue;
                }
                if(c>>j&1==1) s+=pow(2,8*i+j);
            }
        }
        cout<<"address: "<<start<<"   ||  value: " <<s<<endl;
        start+=4;
    }
    int end1=start;
    start=3000;
    while(sim.memory[start]!=0)
    {
        int s=0;
        for(int i=0;i<4;i++)
        {
            int c=sim.memory[start+i];
            for(int j=0;j<8;j++)
            {
                if(i==3 && j==7)
                {
                    if(c>>7&1==1) s-=pow(2,31);
                    continue;
                }
                if(c>>j&1==1) s+=pow(2,8*i+j);
            }
        }
        cout<<"address: "<<start<<"   ||  value: " <<s<<endl;
        start+=4;
    }
   
    

    return 0;
}