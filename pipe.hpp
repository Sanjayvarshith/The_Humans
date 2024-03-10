#include <bits/stdc++.h>
using namespace std;

class pipe
{
    public:
    bool stallIF,stallID,stallEXE,stallMEM,stallWB, prevMem, prevExe, prevID, prevIF;
    int IFpc,IDpc,Exepc,Mempc,Wbpc;
    int predictBranch,nextpc;
    bool checkbranch,checkReg;
    unordered_map<int,bool> hazardReg;
    int pipeReg[15];
    int tempReg[5];
    // vector<int> pipeReg(15);
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
    pipe()
    {   
        stallIF=false;
        stallID=false;
        stallEXE=false;
        stallMEM=false;
        stallWB=false;
        prevMem = false;
        prevExe = false;
        prevID = false;
        prevIF = false;
        predictBranch = 0;
        checkbranch = false;
        checkReg = false;
        Mempc=0;
        Wbpc=0;
        Exepc=0;
        IDpc=0;
        IFpc=0;
        // pipeReg={};
        nextpc=0;
        for(int i=0;i<31;i++){
            hazardReg[i]=false;
        }
        for(int i=0;i<15;i++) pipeReg[i]=0;
    }
    public:
    void implement(Core & c,vector<char> &memory)
    {
        // cout<<"No";
        c.registers[0]=0;
        // cout<<hazardReg[1]<<hazardReg[3]<<endl;
        if(prevMem && !stallWB)        //Wb
        {   
            // cout<<"Yes5";
            // cout<<"wb"<<Mempc<<endl;
            // cout<<"Yes"<<endl;
            c.instructions++;
            Wbpc=Mempc;
            c.vv[c.cycles][Wbpc/4]=5;
            if(pipeReg[8]<22 || pipeReg[8]==32 || pipeReg[8]==34 || pipeReg[8]==36 || pipeReg[8]==37 || pipeReg[8]==28 || pipeReg[8]==29) c.registers[pipeReg[9]]=pipeReg[10];               
            prevMem=false;
            hazardReg[pipeReg[9]]=false;
            if(pipeReg[1]<14&& checkReg)
            {
                if(hazardReg[tempReg[3]]||hazardReg[tempReg[4]]) checkReg=true;
                else checkReg=false;
                if(tempReg[3]==pipeReg[9]) pipeReg[3]=pipeReg[10];
                if(tempReg[4]==pipeReg[9]) pipeReg[4]=pipeReg[10];
                // cout<<pipeReg[9]<<tempReg[3]<<tempReg[4]<<checkReg<<hazardReg[tempReg[3]]<<hazardReg[tempReg[4]]<<endl;
            }
            else if(pipeReg[1]<22 && checkReg)
            {
                if(hazardReg[tempReg[3]]) checkReg=true;
                else checkReg=false;
                if(tempReg[3]==pipeReg[9]) pipeReg[3]=pipeReg[10];
                // cout<<pipeReg[9]<<tempReg[3]<<tempReg[4]<<checkReg<<hazardReg[tempReg[3]]<<hazardReg[tempReg[4]]<<endl;
            }
            else if(pipeReg[1]<28&& checkReg)
            {
                if(hazardReg[tempReg[3]]||hazardReg[tempReg[4]]) checkReg=true;
                else checkReg=false;
                if(tempReg[3]==pipeReg[9]) pipeReg[2]=pipeReg[10];
                else if(tempReg[4]==pipeReg[9]) pipeReg[3]=pipeReg[10];
                // cout<<pipeReg[9]<<tempReg[3]<<tempReg[4]<<checkReg<<hazardReg[tempReg[3]]<<hazardReg[tempReg[4]]<<endl;
            }
            else if(pipeReg[1]<32 && checkReg)
            {
                if(!hazardReg[tempReg[3]]) checkReg=false;
                if(tempReg[3]==pipeReg[9]) pipeReg[3]=pipeReg[10];
            }
            else if((pipeReg[1]==32 || pipeReg[1]==34) && checkReg)
            {
                if(!hazardReg[tempReg[4]]) checkReg=false;
                if(tempReg[4]==pipeReg[9]) pipeReg[4]=pipeReg[10];
            }
            else if(pipeReg[1]<36 && checkReg)
            {
                if(hazardReg[tempReg[3]]||hazardReg[tempReg[4]]) checkReg=true;
                else checkReg=false;
                if(tempReg[3]==pipeReg[9]) pipeReg[2]=pipeReg[10];
                else if(tempReg[4]==pipeReg[9]) pipeReg[4]=pipeReg[10];
            }
            // for(int i=0;i<32;i++)
            // {
            //     if(!hazardReg[i])
            //     {
            //         checkReg=false;
            //     }
            //     else
            //     {
            //         checkReg=true;
            //         break;
            //     }
            // }
            // checkReg=false;
        }
        if(prevExe && !stallMEM)       //Mem
        {
            // cout<<"Yes3";
            // cout<<"mem"<<Exepc<<endl;
            // c.instructions++;
            Mempc=Exepc;
            c.vv[c.cycles][Mempc/4]=4;
            pipeReg[8]=pipeReg[5];
            pipeReg[9]=pipeReg[6];
            pipeReg[10]=pipeReg[7];
            if(pipeReg[5]==32)
            {   
                int pos=pipeReg[7];
                int s=0;
                for(int i=0;i<4;i++)
                {
                    int d=memory[pos+i];
                    for(int j=0;j<8;j++)
                    {
                        if(i==3 && j==7)
                        {
                            if(d>>7&1==1) s-=pow(2,31);
                            continue;
                        }
                        if(d>>j&1==1) s+=pow(2,8*i+j);
                    }
                }
                pipeReg[10]=s;
            }
            else if(pipeReg[5]==33)
            {
            // memory[pipeReg[10]]=c.registers[pipeReg[9]];
                int s=pipeReg[6];
                for(int i=0;i<4;i++)
                {
                    int t=0;
                    for(int j=0;j<8;j++)
                    {
                        if((s>>(8*i+j)&1==1)) t+=pow(2,j);
                    }
                    memory[pipeReg[7]+i]=t;
                }
            }
            else if(pipeReg[5]==34)
            {
                int s=0;
                int d=memory[pipeReg[7]];
                for(int j=0;j<8;j++)
                {
                    if( j==7)
                    {
                        if(d>>7&1==1) s-=pow(2,7);
                        continue;
                    }
                    if(d>>j&1==1) s+=pow(2,j);
                }
                pipeReg[10]=s;
            }
            else if(pipeReg[5]==35)
            {
                int s=pipeReg[6];
                int t=0;
                for(int j=0;j<8;j++)
                {
                    if((s>>(j)&1==1)) t+=pow(2,j);
                }
                memory[pipeReg[7]]=t;
            }
            else if(pipeReg[5]<=37)
            {
                pipeReg[10]=pipeReg[7];
            }
            prevMem=true;                    
            prevExe=false;
        }
        if(prevID && !stallEXE)      //Exe
        {
            // cout<<"Yes2";
            // cout<<"exe"<<IDpc<<endl;
            // c.instructions++;
            pipeReg[5]=pipeReg[1];
            pipeReg[6]=pipeReg[2];
            if(pipeReg[5]<14)
            {
                pipeReg[7]=ALU(pipeReg[5],pipeReg[3],pipeReg[4]);
            }
            else if(pipeReg[5]<22)
            {
                pipeReg[7]=ALU(pipeReg[5],pipeReg[3],pipeReg[4]);
            }
            else if(pipeReg[5]<28)
            {
                int branch=ALU(pipeReg[5],pipeReg[2],pipeReg[3]);
                // cout<<branch<<endl;
                if(branch)
                {
                    checkbranch=true;
                    nextpc=pipeReg[4];
                }
            }
            else if(pipeReg[5]==28)
            {
                nextpc=pipeReg[3];
                pipeReg[7]=c.pc-4;
                checkbranch=true;
            }
            else if(pipeReg[5]==29)
            {
                nextpc=pipeReg[3]+pipeReg[4];
                pipeReg[7]=c.pc-4;
                checkbranch=true;
            }
            else if(pipeReg[5]==30)
            {
                nextpc=pipeReg[3];
                checkbranch=true;
            }
            else if(pipeReg[5]==31)
            {
                nextpc=pipeReg[3];
                checkbranch=true;
            }
            else if(pipeReg[5]>=32 && pipeReg[5]<=35)
            {
                pipeReg[7]=ALU(pipeReg[5],pipeReg[4],pipeReg[3]);
            }
            else if(pipeReg[5]<=37) pipeReg[7]=pipeReg[3];
            Exepc=IDpc;
            c.vv[c.cycles][Exepc/4]=3; 
            if(pipeReg[1]<22 || (pipeReg[1]>27 && pipeReg[1]!=30 && pipeReg[1]!=31 && pipeReg[1]!=33 && pipeReg[1]!=35))hazardReg[pipeReg[2]]=true;
            prevExe=true;
            prevID=false;
        }
        
        if(prevIF && !stallID)     //ID
        {
            
            // c.instructions++;
            // cout<<"ID"<<IFpc<<endl;
            // cout<<"Yes100";
            vector<string> parts = c.split(c.program[pipeReg[0]/4]);
            pipeReg[1]=op_map[parts[0]];
            if(pipeReg[1]<14)
            {
                tempReg[3]=c.regNum(parts[2]);
                tempReg[4]=c.regNum(parts[3]);
                pipeReg[2]=c.regNum(parts[1]);
                pipeReg[3]=c.registers[c.regNum(parts[2])];
                pipeReg[4]=c.registers[c.regNum(parts[3])];
            if(hazardReg[tempReg[3]]||hazardReg[tempReg[4]])
            {
                // cout<<"yes"<<endl;
                checkReg=true;
            }
            else
            {
                checkReg=false;
            }
            }
            else if(pipeReg[1]<22)
            {
                tempReg[3]=c.regNum(parts[2]);
                tempReg[4]=stoi(parts[3]);
                pipeReg[2]=c.regNum(parts[1]);
                pipeReg[3]=c.registers[c.regNum(parts[2])];
                pipeReg[4]=stoi(parts[3]);
            if(hazardReg[tempReg[3]])
            {
                checkReg=true;
            }
            else
            {
                checkReg=false;
            }
                // cout<<tempReg[4]<<endl;
            }
            else if(pipeReg[1]<28)
            {
                tempReg[3]=c.regNum(parts[1]);
                tempReg[4]=c.regNum(parts[2]);
                pipeReg[2]=c.registers[c.regNum(parts[1])];
                pipeReg[3]=c.registers[c.regNum(parts[2])];
                pipeReg[4]=c.label[parts[3]];
                if(hazardReg[tempReg[3]]||hazardReg[tempReg[4]])
                {
                    // cout<<"yes"<<endl;
                    checkReg=true;
                }
                else checkReg=false;
            }
            else if(pipeReg[1]==28 || pipeReg[1]==30)
            {
               if(parts.size()==2)
            {
            tempReg[2]=1;
            tempReg[3]=c.label[parts[1]];
            pipeReg[2]=1;
            pipeReg[3]=c.label[parts[1]];
            // nextpc=c.label[parts[1]];
            // checkbranch=true;            
            }
            else{
            tempReg[3]=c.label[parts[2]];
            pipeReg[2]=  c.regNum(parts[1]);
            // nextpc=c.label[parts[2]];
            // checkbranch=true;
            pipeReg[3]=c.label[parts[2]];
            }
            }
            else if(pipeReg[1]==29 || pipeReg[1]==31)
            {
                if(parts.size()==2)
                {
                    tempReg[3]=c.regNum(parts[1]);   
                    tempReg[4]=0;  
                    pipeReg[2]=1;
                    pipeReg[3]=c.registers[c.regNum(parts[1])];   
                    pipeReg[4]=0;
                    if(hazardReg[tempReg[3]])
                    {
                        checkReg=true;
                    }
                    else
                    {
                        checkReg=false;
                    }    
                }
                else
                {
                    tempReg[3]=c.regNum(parts[2]);
                    tempReg[4]=stoi(parts[3]);
                    pipeReg[2]=c.regNum(parts[1]);
                    pipeReg[3]=c.registers[c.regNum(parts[2])];
                    pipeReg[4]=stoi(parts[3]);
                    if(hazardReg[tempReg[3]])
                    {
                        checkReg=true;
                    }
                    else
                    {
                        checkReg=false;
                    }
                }
            }
            else if(pipeReg[1]<36)
            {   
                
                pipeReg[2]=c.regNum(parts[1]);
                if(pipeReg[1]==33 || pipeReg[1]==35) pipeReg[2]=c.registers[c.regNum(parts[1])];
                tempReg[3]=c.regNum(parts[1]);
                int openParenthesisPos = parts[2].find("(");
                int closeParenthesisPos = parts[2].find(")");
                if (openParenthesisPos == string::npos) 
                {
                    pipeReg[3]=0;
                    pipeReg[4]=c.data[parts[2]];
                }
                else
                {
                    pipeReg[3] = stoi(parts[2].substr(0, openParenthesisPos));
                    pipeReg[4]= c.registers[c.regNum(parts[2].substr(openParenthesisPos + 1, closeParenthesisPos - openParenthesisPos - 1))];
                    tempReg[4]=c.regNum(parts[2].substr(openParenthesisPos + 1, closeParenthesisPos - openParenthesisPos - 1));
                    if(hazardReg[tempReg[4]]) checkReg=true;
                        else checkReg=false;
                    if(pipeReg[1]==33 || pipeReg[1]==35)
                    {
                        if(hazardReg[tempReg[3]]) checkReg=true;
                        else checkReg=false;
                    }
                }
            }
            else if(pipeReg[1]==36)
            {
                pipeReg[2]=c.regNum(parts[1]);
                pipeReg[3]=c.data[parts[2]];
                pipeReg[4]=0;
            }
            else if(pipeReg[1]==37)
            {
                pipeReg[2]=c.regNum(parts[1]);
                pipeReg[3]=stoi(parts[2]);
                pipeReg[4]=0;
            }
           
            // if(pipeReg[1]<22 || (pipeReg[1]>27 && pipeReg[1]!=30 && pipeReg[1]!=31 && pipeReg[1]!=33 && pipeReg[1]!=35))hazardReg[pipeReg[2]]=true;
            IDpc=pipeReg[0];
            c.vv[c.cycles][IDpc/4]=2;
            prevID=true;
            prevIF=false;
            // cout<<"ID"<<pipeReg[0]<<c.pc<<endl;
        }
        if(c.pc<c.program.size()*4 && !stallIF) //IF
        {   
            // cout<<"Yes1";
            // cout<<c.pc<<endl;
            // c.instructions++;
            pipeReg[0]=c.pc;
            IFpc=c.pc;
            c.vv[c.cycles][IFpc/4]=1;
            prevIF=true;
            c.pc+=4;
        }
        // cout<<"Yes1";
        // cout<<c.pc<<endl;
        if(checkReg)
        {
            c.stalls++;
            stallIF=true;
            stallID=true;
            stallEXE=true;
        }
        else
        {
            if(stallEXE)c.stalls++;
            stallIF=false;
            stallID=false;
            stallEXE=false;
        }
        if(checkbranch)
        {
            c.pc=nextpc;
            checkbranch=false;
            prevIF=false;
            prevID=false;
        }
        if(!(prevIF || prevID || prevExe || prevMem) )
        {
            c.active=false;
            // cout<<"Yes1";
        }
        // cout<<c.pc<<endl;
        // cout<<c.cycles<<endl;
        // // for(auto i: c.label) cout<<i.first<<" "<<i.second<<" "<<endl;
        // //   for(auto i: c.label) cout<<i.first<<" "<<i.second<<endl;
        // for(int i=0;i<32;i++) cout<<c.registers[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<15;i++) cout<<pipeReg[i]<<" ";
        // cout<<endl;
        // for(int i=0;i<32;i++) cout<<hazardReg[i]<<" ";
        // cout<<checkReg;
        // cout<<endl<<"=========Word Memory=========="<<endl;
    // int start=3000;
    // while(memory[start]!=0)
    // {
    //     int s=0;
    //     for(int i=0;i<4;i++)
    //     {
    //         int c=memory[start+i];
    //         for(int j=0;j<8;j++)
    //         {
    //             if(i==3 && j==7)
    //             {
    //                 if(c>>7&1==1) s-=pow(2,31);
    //                 continue;
    //             }
    //             if(c>>j&1==1) s+=pow(2,8*i+j);
    //         }
    //     }
    //     cout<<"address: "<<start<<"   ||  value: " <<s<<endl;
    //     start+=4;
    // }
    //     cout<<endl<<"--------------------"<<endl;
    }

    int ALU(int op,int a,int b)
    {
        if(op==1) return a+b;
        if(op==2) return a-b;
        if(op==3) return a*b;
        if(op==4) return a/b;
        if(op==5) return a%b;
        if(op==6) return a<<b;
        if(op==7) return a>>b;
        if(op==8) return a>>b;
        if(op==9) return a<b;
        if(op==10) return a<b;
        if(op==11) return a^b;
        if(op==12) return a|b;
        if(op==13) return a&b;
        if(op==14) return a+b;
        if(op==15) return a<<b;
        if(op==16) return a>>b;
        if(op==17) return a>>b;
        if(op==18) return a<b;
        if(op==19) return a^b;
        if(op==20) return a|b;
        if(op==21) return a&b;
        if(op==22) return a==b;
        if(op==23) return a!=b;
        if(op==24) return a<b;
        if(op==25) return a>b;
        if(op==26) return a<=b;
        if(op==27) return a>=b;
        if(op==32) return a+b;
        if(op==33) return a+b;
    }
};