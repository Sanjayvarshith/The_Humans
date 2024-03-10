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
       map<string, int> op_map = {
        {"add", 1}, {"sub", 2}, {"mul", 3}, {"div", 4}, {"rem", 5},
        {"sll", 6}, {"srl", 7}, {"sra", 8}, {"slt", 9}, {"sltu", 10},
        {"xor", 11}, {"or", 12}, {"and", 13}, {"addi", 14},
        {"slli", 15}, {"srli", 16}, {"srai", 17}, {"slti", 18},
        {"xori", 19}, {"ori", 20}, {"andi", 21}, {"beq", 22},
        {"bne", 23}, {"blt", 24}, {"bgt", 25}, {"ble", 26}, {"bge", 27},
        {"jal", 28}, {"jalr", 29}, {"j", 30}, {"jr", 31}, {"lw", 32},
        {"sw", 33}, {"lb", 34}, {"sb", 35}, {"la", 36},
        {"li", 37}, {"ecall", 38}
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

    sim.run();
    cout<<"--------------------PIPELINE DIAGRAM------------------------"<<endl;
    for(int i=0;i<2;i++)
    {
        cout<<"---------------------Core "<<i<<"----------------------"<<endl;
        // int n=sim.cores[i].vv.size();
        // int m=sim.cores[i].vv[0].size();
        // for(int j=0;j<m;j++)
        // {
        //     cout<<sim.cores[i].program[j]<<endl;
        //     for(int k=0;k<n;k++)
        //     {
        //         cout<<sim.cores[i].vv[k][j]<<" ";
        //     }
        //     cout<<endl;
        // }
    }
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

    // for(auto i: sim.cores[1].label) cout<<i.first<<" "<<i.second<<endl;
        cout<<"--------------------------------------------------------"<<endl;
        for(int i=0;i<2;i++)
        {
            cout<<"---------------------Core "<<i<<"----------------------"<<endl;
            cout<<"Cycles: "<<sim.cores[i].cycles<<endl;
            cout<<"Instructions: "<<sim.cores[i].instructions<<endl;
            cout<<"Stalls: "<<sim.cores[i].stalls<<endl;
            cout<<"Wrong Predictions: "<<sim.cores[i].wrongPredictions<<endl;
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
    cout<<"----------------------------------"<<endl;
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