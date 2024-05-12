Members: Sanjay,Aarya <br>
Date:May 11th 2024<br>
DEscription:Designed a graphical frontend to display the register content,memeory content,cycles,program1,program2, cache content.<br>
Date:April 10th 2024<br>
Description: Succesfully added inputs to choose replacement policy and latency<br>
Date:April 9th 2024<br>
Description: Succesfully fixed bugs in pipe class(without data forwarding)<br>
Date:April 8th 2024<br>
Description: Succesfully completed lru and started implementing cache in pipe and datapipe class<br>
Date:April 7th 2024<br>
Description: Succesfully added cache simulator class and tried to write algorithm for lru<br>
Date: March 10th 2024 <br>
Description: Successfully completed implementation of phase 2 of this project (adding pipelining,enable/disable dataforwarding,hazard detection and latency) <br>
Date: Feb 25th 2024 <br>
Description: Added instruction to ignore comments and printed contents of each register and memory <br>
Date: Feb 24th 2024 <br>
Description: Fixed all bugs and tried to run different risc v codes and compared the corresponding outputs and register values with ripes <br>
Date: Feb 22th 2024 <br>
Description: Implemented alias names to registers, implemented ecall and started implementing Datasegment <br>
Date: Feb 21th 2024 <br>
Description: Implemented branch instructions like ble,bne,bge,jal,jalr <br>
Date: Feb 20th 2024 <br>
Description: We started implementing branch instructions,we decided to split the given input file into programs and labels <br>
Date: Feb 18th 2024 <br>
Implemented basic commands like add,sub,addi,lw,sw <br>
Date: Feb 16th 2024 <br>
Description: We analyzed the code given by sir in the lab and created main,core and processor files <br>
Date: Feb 12th 2024 <br>
Description: Created github repository <br>

Key Ideas: <br>
Phase 3:<br>
We made a struct set in which vector of blocks will be there<br>
In struct set there is a int variable lru which specifies the position of a block in terms of how recently it was added<br>
We specified address of every instruction as pc+300(core 1) or pc+1500(core 2), we kept some offset for instruction address so that it wont overlap with memory adrres location<br>
For every instruction we will be checking whether the instruction is present in cache or not in IF stage , for every lw instruction also we will be checking whether the memory location is loaded in to cache or not in MEM stage <br> 
Phase 2:<br>
We have used 12 registers for implementation in pipeling for each different cycle <br>
We have used a boolean array to detect hazards.It helps to check whether there is any register which has not gone to WB cycle but used in ID stage<br>
We have used temp registers to store the indexes of current registers in ID stage <br>
We have fowarded data from WB stage to Exe stage if there is an hazard when data forwaring is disabled <br>
We have forwared data from Exe to Exe stage if there is an hazard when data forwarding is enabled. <br>
We have created 2 excel sheets show the pipeline Diagram of 2 different programs we had runned. <br>
Phase 1:<br>
We created memory array of char datatype of 4kb storage, each index representing each byte. <br>
We have combined 4 bytes from the starting address to implement lw, and we splited and stored word in 4 bytes to implement sw.(In Little Endian format) <br>
We took input of a program as a file, we read each line of the file at starting and divided them into programs and labels. <br>
We have used string map to store the PC value of given label and we use them to jump to that label if we required in the program. <br>
We have used string map to store starting address of the strings and arrays to point at them when needed.Stored '\0' at the next byte after storing each char of string to identify end of the string. <br>
We decided to split the memory to the two cores and for 1st core we decided to start memory from 1000th byte and for 2nd core we decided to start memory from 3000th byte for storing strings and array elements.<br>
We have also written code to identify and split commas and ignore comments. <br>
We designed our simulator such that it executes two programs p1.txt and p2.txt parallely <br>
After executing two programs we have printed contents of registers of two cores and data in combined memory with address <br>




