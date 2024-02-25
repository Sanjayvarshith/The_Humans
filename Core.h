#include <bits/stdc++.h>
using namespace std;

class Core {
public:
    array<int, 32> registers;
    int pc;
    bool active;
    bool check=true;
    // int memStart=0;
    vector<string> program;
    unordered_set <string> keyword ={ "add","ble","addi", "sub", "lw", "sw","mv", "jal", "jalr", "la", "li", "srl", "srli", "sra", "srai", "bne", "beq","bge", "blt","and","or","xor","andi","ori","xori","j","jr","sll","slli","ecall","ret"};
    unordered_map<string,int> data;
    int loc;
    unordered_map<string,int> label;
    Core() : pc(0), registers({}),active(true) {}
    int hexToDecimal(const string& hexString) {
    std::stringstream ss;
    ss << std::hex << hexString;
    int decimalNumber;
    ss >> decimalNumber;

    return decimalNumber;
    }

    bool add(string line,int a,vector<char>& memory)
    {
        if(line=="") return false;
        int hash=line.find("#");
        if(hash!=string::npos) line=line.substr(0,hash);
        vector<string> parts = split(line);
        if(parts.size()==0) return false;
        // for(auto x:parts)
        // {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
        if(parts[0]=="ret") 
        {
            program.push_back("jalr x0 x1 0");
            return true;
        }
         if(parts[0]==".data") 
        {
            check=false;
            return false;
           
        }
        if(parts[0]==".text") 
        {
            check=true;
            return false;
           
        }
        if(!check){  
            size_t colon = parts[0].find(":");
            size_t found1 = parts[0].find(".string");
            size_t found2 = parts[1].find(".string");
            if(found1 != string::npos){
                string s="";
            for(int i=1;i<parts.size();i++) 
            {
                s+=parts[i];
                s+=" ";
            }
            s=s.substr(1,s.length()-3);
            data[parts[0].substr(0,colon)]=loc;
            loc+=s.length()+1;
            for(int i=0;i<s.length();i++)
            {
                if(s[i]=='\\')
                {
                    if(s[i+1]=='n') memory[loc]='\n';
                    if(s[i+1]=='t') memory[loc]='\t';
                    i++;
                }
                else memory[loc]=s[i];
                loc++;
            }
            memory[loc+s.length()]='\0';
            loc++;
            }
            else if(found2!= string::npos){
                 string s="";
            for(int i=2;i<parts.size();i++) 
            {
                s+=parts[i];
                s+=" ";
            }
            s=s.substr(1,s.length()-3);
            data[parts[0].substr(0,colon)]=loc;
            for(int i=0;i<s.length();i++)
            {
                if(s[i]=='\\')
                {
                    if(s[i+1]=='n') memory[loc]='\n';
                    if(s[i+1]=='t') memory[loc]='\t';
                    i++;
                }
                else memory[loc]=s[i];
                loc++;
            }
            memory[loc+s.length()]='\0';
            loc++;
            }
    
            else if(parts[0]==".word"){
            for(int i=1;i<parts.size();i++) 
            {
                int s;
                if(parts[i][1]=='x') s=hexToDecimal(parts[i]);
                else s=stoi(parts[i]);
                for(int i=0;i<4;i++)
                {
                    int t=0;
                    for(int j=0;j<8;j++)
                    {
                        if((s>>(8*i+j)&1==1)) t+=pow(2,j);
                    }
                    memory[loc]=t;
                    loc++;
                }
            }
            
            }
            else if(parts[1]==".word"){
            data[parts[0].substr(0,colon)]=loc;
            for(int i=2;i<parts.size();i++) 
            {
                int s;
                if(parts[i][1]=='x') s=hexToDecimal(parts[i]);
                else s=stoi(parts[i]);
                for(int i=0;i<4;i++)
                {
                    int t=0;
                    for(int j=0;j<8;j++)
                    {
                        if((s>>(8*i+j)&1==1)) t+=pow(2,j);
                    }
                    memory[loc]=t;
                    loc++;
                }
                size_t colon = parts[0].find(":");
            }
            
            }
            
            else{
                size_t found = parts[0].find(".word");
                size_t colon = parts[0].find(":");
                if(found!= string::npos&&(parts[0].compare(".word")!=0)){
                data[parts[0].substr(0,colon)]=loc;
                }
                for(int i=1;i<parts.size();i++) 
                {
                    int s;
                    if(parts[i][1]=='x') s=hexToDecimal(parts[i]);
                    else s=stoi(parts[i]);
                    for(int i=0;i<4;i++)
                    {
                        int t=0;
                        for(int j=0;j<8;j++)
                        {
                            if((s>>(8*i+j)&1==1)) t+=pow(2,j);
                        }
                        memory[loc]=t;
                        loc++;
                    }
                }
            
            return false;
            }
        }
        if(parts[0][0]=='#') return false;
        if(isKeyword(parts[0]))
        {
            string s="";
            for(int i=0;i<parts.size();i++) 
            {
                s+=parts[i];
                s+=" ";
            }
            program.push_back(s);
            return true;
        }
        label[parts[0].substr(0,parts[0].size()-1)]=a;
        if(parts.size()>1)
        {
            string s="";
            for(int i=1;i<parts.size();i++) 
            {
                s+=parts[i];
                s+=" ";
            }
            program.push_back(s);
            return true;
        }
        return false;
    }


    void execute(vector<char>& memory) {
        vector<string> parts = split(program[pc/4]);
        string opcode = parts[0];
        registers[0]=0;
        // for(auto x:parts)
        // {
        //     cout<<x<<" ";
        // }
        // cout<<endl;
        // for(int i=2000;i<=2006;i++) cout<<memory[i]<<" ";
        // cout<<endl;
        if (opcode == "add") {
            int rd = regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] + registers[rs2];
        } 
         else if (opcode == "sub") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] - registers[rs2];
        } 
         else if (opcode == "addi") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] + val;
        } 
         else if (opcode == "lw") {
            int rd =  regNum(parts[1]);
            int val = 0;
            int val1 = 0;
            if(data.find(parts[2])!=data.end())
            {
                int pos=data[parts[2]];
                int s=0;
                for(int i=0;i<4;i++)
                {
                    int c=memory[pos+i];
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
                registers[rd]=s;
            }
            else{
            int openParenthesisPos = parts[2].find("(");
            int closeParenthesisPos = parts[2].find(")");
                val = stoi(parts[2].substr(0, openParenthesisPos));
                val1 =  regNum(parts[2].substr(openParenthesisPos + 1, closeParenthesisPos - openParenthesisPos - 1));
            int s=0;
            for(int i=0;i<4;i++)
            {
                int c=memory[val+registers[val1]+i];
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
            registers[rd]=s;
            }
             
        }
        else if (opcode == "sw") {
            int rd =  regNum(parts[1]); 
            int val = 0;
            int val1 = 0;
            size_t openParenthesisPos = parts[2].find("(");
            size_t closeParenthesisPos = parts[2].find(")");
                val = stoi(parts[2].substr(0, openParenthesisPos));
                val1 =  regNum(parts[2].substr(openParenthesisPos + 1, closeParenthesisPos - openParenthesisPos - 1));
            // memory[val + registers[val1]]= registers[rd] ;
            int s=registers[rd];
            for(int i=0;i<4;i++)
            {
                int t=0;
                for(int j=0;j<8;j++)
                {
                    if((s>>(8*i+j)&1==1)) t+=pow(2,j);
                }
                memory[val+registers[val1]+i]=t;
            }
        }
        else if(opcode=="mv")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            registers[rd]=registers[rs1];
        }
        else if (opcode=="jal"){
        if(parts.size()==2)
        {
            registers[1]=pc+4;
            pc=label[parts[1]];
            pc-=4;
        }
        else{
            int rd =  regNum(parts[1]);
            registers[rd]=pc+4;
            pc=label[parts[2]];
            pc-=4;
        }
        }
        else if (opcode=="jalr"){
        if(parts.size()==2)
        {
            registers[1]=pc+4;
            int rd=regNum(parts[1]);
            pc=registers[rd];
        }
        else{
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd]=pc+4;
            pc=registers[rs1+val];
        }
        pc-=4;
        }
        else if(opcode=="j")
        {
            pc=label[parts[1]]-4;
        }
        else if(opcode=="jr")
        {
            int rd=regNum(parts[0]);
            pc=registers[rd]-4;
        }
        else if(opcode=="ble")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            if(registers[rd]<=registers[rs1]){
                pc=label[parts[3]]-4;
            }
        }
        else if(opcode=="blt")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            if(registers[rd]<registers[rs1]){
                pc=label[parts[3]]-4;
            }
        }
        else if(opcode=="bne")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            if(registers[rd]!=registers[rs1]){
                pc=label[parts[3]]-4;
            }
            // cout<<registers[rd]<<" "<<registers[rs1]<<" "<<pc<<endl;
        }
        else if(opcode=="bge")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            if(registers[rd]>=registers[rs1]){
                pc=label[parts[3]]-4;
            }
        }
        else if(opcode=="beq")
        {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            if(registers[rd]==registers[rs1]){
                pc=label[parts[3]]-4;
            }
        }
        else if(opcode=="li"){
              int rd =  regNum(parts[1]);
            //   cout<<rd<<" "<<parts[0]<<" "<<parts[1]<<" "<<pc;
              int val=stoi(parts[2]);
              registers[rd]=val;
        }
        else if(opcode=="and")
        {
            int rd = regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] & registers[rs2];
        }
        else if (opcode == "andi") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] & val;
        } 
        else if(opcode=="or")
        {
            int rd = regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] | registers[rs2];
        }
        else if (opcode == "ori") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] | val;
        } 
        else if(opcode=="xor")
        {
            int rd = regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] ^ registers[rs2];
        }
        else if (opcode == "xori") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] ^ val;
        }
        else if (opcode == "sll") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] >> registers[rs2];
        } 
        else if (opcode == "slli") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] >> val;
        } 
        else if (opcode == "sra") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = registers[rs1] >> registers[rs2];
        } 
        else if (opcode == "srai") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] >> val;
        }
        else if(opcode == "la"){
                int rd =  regNum(parts[1]);
                registers[rd]=data[parts[2]];
        }
        else if (opcode == "srl") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int rs2 =  regNum(parts[3]);
            registers[rd] = (registers[rs1] >> registers[rs2]);
        } 
        else if (opcode == "srli") {
            int rd =  regNum(parts[1]);
            int rs1 =  regNum(parts[2]);
            int val =  stoi(parts[3]);
            registers[rd] = registers[rs1] >> val;
        } 
        else if (opcode == "ecall") {
            if(registers[17]==10)
            {
                active=false;
                cout<<"Program Exited Successfully"<<endl;
                return;
            }
            if(registers[17]==1)  
                cout<<(int)registers[10];
            if(registers[17]==4)
            {
                int i=registers[10];
                while(memory[i]!='\0')
                {
                    cout<<memory[i];
                    i++;
                }
            }
            if(registers[17]==11)
                cout<<(char)registers[10];
            if(registers[17]==2)
                cout<<(float)registers[10];
            if(registers[17]==34)
                cout<<hex<<registers[10];
        }          
        pc+=4;
        // cout<<pc<<" ";
        if(pc>=program.size()*4) active=false;
    }

private:
    vector<string> split(string str)
    {
        vector<string> v;
        string s="";
        for(int i=0;i<str.length();i++)
        {
            // cout<<1;
            if(str[i]==' ' || str[i]==',')
            {
                if(s=="") continue;
                v.push_back(s);
                s="";
                continue;
            }
            s+=str[i];
        }
        if(s!="") v.push_back(s);
        return v;
    }
    bool isKeyword(string s)
    {
        if(keyword.find(s)!=keyword.end()){
            return true;
        }
        return false;
    }
    int regNum(string s)
    {
        if(s[0]=='x') return stoi(s.substr(1));
        if(s[0]=='a') return stoi(s.substr(1))+10;
        if(s=="sp") return 2;
        if(s=="ra") return 1;
        if(s=="gp") return 3;
        if(s=="tp") return 4;
        if(s=="zero") return 0;
        if(s[0]=='s')
        {
            int y=stoi(s.substr(1));
            if(y<2) return 8+y;
            return 16+y;
        }
        if(s[0]=='t')
        {
            int y=stoi(s.substr(1));
            if(y<3) return 5+y;
            return 25+y;
        }
    }
};