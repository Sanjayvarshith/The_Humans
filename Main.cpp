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
        // cout<<line<<endl;   
    }
    fin2.close();
    // cout<<1;
    sim.run();
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
    int end2=start;
    cout << "===========Byte Memory===========" << endl;
    start=1000;
    while(start!=end1+4)
    {
        cout<<"address: "<<start<<"   ||  value: " <<(int)sim.memory[start]<<endl;
        start++;
    }
    start=3000;
    while(start!=end2+4)
    {
        cout<<"address: "<<start<<"   ||  value: " <<(int)sim.memory[start]<<endl;
        start++;
    }
   
    

    return 0;
}