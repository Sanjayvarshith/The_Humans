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
    sim.cores[1].loc=3500;
    sim.cores[0].insLoc=300;
    sim.cores[1].insLoc=2800;
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
       map<string, int> op_map = {
        {"add", 1}, {"sub", 2}, {"mul", 3}, {"div", 4}, {"rem", 5},
        {"sll", 6}, {"srl", 7}, {"sra", 8}, {"slt", 9}, {"sltu", 10},
        {"xor", 11}, {"or", 12}, {"and", 13}, {"addi", 14},
        {"slli", 15}, {"srli", 16}, {"srai", 17}, {"slti", 18},
        {"xori", 19}, {"ori", 20}, {"andi", 21}, {"beq", 22},
        {"bne", 23}, {"blt", 24}, {"bgt", 25}, {"ble", 26}, {"bge", 27},
        {"jal", 28}, {"jalr", 29}, {"j", 30}, {"jr", 31}, {"lw", 32},
        {"sw", 33},  {"la", 34},
        {"li", 35}, {"ecall", 36}
    };
    sim.cores[0].setLatency();
    sim.cores[1].setLatency();
    cout<<"Enter 1 to enable DATA FORWARDING: "<<endl;
    cout<<"Enter 2 to continue without DATA FORWARDING: "<<endl;
    int enable=0;
    cin>>enable;
    if(enable == 1)
    {
        sim.dataForwarding=1;
    }
    else
    {
        sim.dataForwarding=0;
    }
    cout<<"Enter 1 to change latency: "<<endl;
    cout<<"Enter -1 to stop changing latency: "<<endl;
    int latencyChange=0;
    cin>>latencyChange;
    while(latencyChange!=-1)
    {
        cout<<"Enter the instruction:(Ex: add,addi,sw etc) ";
        string ins;
        cin>>ins;
        cout<<"Enter the latency: ";
        int lat;
        cin>>lat;
        sim.cores[0].latency[op_map[ins]].second=lat;
        sim.cores[1].latency[op_map[ins]].second=lat;
        cout<<endl;
        cout<<"Enter 1 to change latency: "<<endl;
        cout<<"Enter -1 to stop changing latency: "<<endl;
        cin>>latencyChange;
    }

    cout<<"Enter The size of cache: "<<endl;
    int cacheSize;
    cin>>cacheSize;
    cout<<"Enter The size of block: "<<endl;
    int blockSize;
    cin>>blockSize;
    blockSize=16;
    cout<<"Enter The associativity of cache: "<<endl;
    int associativity;
    cin>>associativity;
    cout<<"Enter 0 to enable LRU: "<<endl;
    cout<<"OR Enter any number for Random policy: "<<endl;
    int policy;
    cin>>policy;
    if(policy!=0) policy=1;
    cout<<"Enter access time for Main memory: "<<endl;
    int lat;
    cin>>lat;
    sim.p[0].cacLatency=lat;
    sim.p[1].cacLatency=lat;
    sim.dp[0].cacLatency=lat;
    sim.dp[1].cacLatency=lat;
    sim.cs.set(cacheSize,blockSize,associativity,policy);

    sim.run();
    cout<<"--------------------PIPELINE DIAGRAM------------------------"<<endl;
    // for(int i=0;i<2;i++)
    // {
    //     cout<<"---------------------Core "<<i<<"----------------------"<<endl;
    //     int n=sim.cores[i].vv.size();
    //     int m=sim.cores[i].vv[0].size();
    //     for(int j=0;j<m;j++)
    //     {
    //         cout<<sim.cores[i].program[j]<<endl;
    //         for(int k=0;k<n;k++)
    //         {
    //             cout<<sim.cores[i].vv[k][j]<<" ";
    //         }
    //         cout<<endl;
    //     }
    // }
    string str="";
    ofstream outdata;
    outdata.open("pipelineDiagram1.csv");
    int n=sim.cores[0].vv.size();
        int m=sim.cores[0].vv[0].size();
        for(int j=0;j<m;j++)
        {
            // cout<<sim.cores[0].program[j]<<endl;
            str+=sim.cores[0].program[j];
            str+=',';
            for(int k=0;k<n;k++)
            {
                int y=(sim.cores[0].vv[k][j]);
                if(y==1) str+="IF";
                if(y==2) str+="ID/RF";
                if(y==3) str+="EXE";
                if(y==4) str+="MEM";
                if(y==5) str+="WB";
                if(y==0) str+="-";
                if(k!=n-1) str+=',';
            }
            str+='\n';
        }
        outdata<<str;
        outdata.close();
        ofstream outdata2;
        str="";
        outdata2.open("pipelineDiagram2.csv");
        n=sim.cores[1].vv.size();
        m=sim.cores[1].vv[0].size();
        for(int j=0;j<m;j++)
        {
            // cout<<sim.cores[0].program[j]<<endl;
            str+=sim.cores[1].program[j];
            str+=',';
            for(int k=0;k<n;k++)
            {
                int y=(sim.cores[1].vv[k][j]);
                if(y==1) str+="IF";
                if(y==2) str+="ID/RF";
                if(y==3) str+="EXE";
                if(y==4) str+="MEM";
                if(y==5) str+="WB";
                if(y==0) str+="-";
                if(k!=n-1) str+=',';
            }
            str+='\n';
        }
        outdata2<<str;
        outdata2.close();
std::ofstream outputFile3; 
    outputFile3.open("static/output3.txt");
    // for(auto i: sim.cores[1].label) cout<<i.first<<" "<<i.second<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        for(int i=0;i<2;i++)
        {
            outputFile3<<"---------------------Core "<<i<<"----------------------"<<endl;
            outputFile3<<"Cycles: "<<sim.cores[i].cycles<<endl;
            outputFile3<<"Instructions: "<<sim.cores[i].instructions<<endl;
            outputFile3<<"Stalls: "<<sim.cores[i].stalls<<endl;
            outputFile3<<"Wrong Predictions: "<<sim.cores[i].wrongPredictions<<endl;
            if(sim.cores[i].instructions==0 || sim.cores[i].cycles==0) {
                outputFile3<<"IPC: "<<endl;
                outputFile3<<"CPI: "<<endl;
                continue;
            }
            outputFile3<<"IPC: "<<(float)sim.cores[i].instructions/sim.cores[i].cycles<<endl;
           outputFile3<<"CPI: "<<(float)sim.cores[i].cycles/sim.cores[i].instructions<<endl;
        }
        std::ofstream outputFile4; 
    outputFile4.open("static/output4.txt");
        outputFile4<<"==================Cache=================="<<endl;
         outputFile4<<"Cache Accesses: "<<sim.cs.hits+sim.cs.misses<<endl;
        outputFile4<<"Cache Hits: "<<sim.cs.hits<<endl;
         outputFile4<<"Cache Misses: "<<sim.cs.misses<<endl;
         outputFile4<<"Cache Hit Rate: "<<(float)sim.cs.hits/(sim.cs.hits+sim.cs.misses)<<endl;
        outputFile4<<"Cache Miss Rate: "<<(float)sim.cs.misses/(sim.cs.hits+sim.cs.misses)<<endl;
        // cout<<"========================================"<<endl;
 cout << "============ After Run ============" << endl;
std::ofstream outputFile2; 
    outputFile2.open("static/output2.txt");
    for (int i = 0; i < 2; i++) {
        outputFile2 << "Core " << i <<endl;
        
        for (int j = 0; j < 32; j++) {
            outputFile2 << "x"<<j<<"    : "<<sim.cores[i].registers[j] << " "<<endl;
        }
        outputFile2 << endl;
    }
    int start;
     std::ofstream outputFile1; 
    outputFile1.open("static/output1.txt");
    outputFile1<<"=========Word Memory==========\n";
    start=1000;
    while(sim.memory[start]!=0 || start<1050)
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
        outputFile1<<"address: "<<start<<"   ||  value: " <<s<<endl;
        start+=4;
    }
    outputFile1<<"----------------------------------"<<endl;
    int end1=start;
    start=3500;
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
        outputFile1<<"address: "<<start<<"   ||  value: " <<s<<endl;
        start+=4;
    }
    outputFile1<<"----------------------------------"<<endl;
    // cout<<sim.cs.hits<<" "<<sim.cs.misses<<endl;
    // cout<<"Hit Rate: "<<(float)sim.cs.hits/(sim.cs.hits+sim.cs.misses)<<endl;
    

    return 0;
}