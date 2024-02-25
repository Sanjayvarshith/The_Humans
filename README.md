Date: Feb 12th 2024 <br>
Members: Sanjay,Aarya <br>
Description: Created github repository <br>
Date: Feb 16th 2024 <br>
Description: We analyzed the code given by sir in the lab and created main,core and processor files <br>
Date: Feb 18th 2024 <br>
Implemented basic commands like add,sub,addi,lw,sw <br>
Date: Feb 20th 2024 <br>
Description: We started implementing branch instructions,we decided to split the given input file into programs and labels <br>
Date: Feb 21th 2024 <br>
Description: Implemented branch instructions like ble,bne,bge,jal,jalr <br>
Date: Feb 22th 2024 <br>
Description: Implemented alias names to registers, implemented ecall and started implementing Datasegment <br>
Date: Feb 24th 2024 <br>
Description: Fixed all bugs and tried to run different risc v codes and compared the corresponding outputs and register values with ripes <br>
Date: Feb 25th 2024 <br>
Description: Added instruction to ignore comments and printed contents of each register and memory <br>

Key Ideas: <br>
We created memory array of char datatype of 4kb storage, each index representing each byte. <br>
We have combined 4 bytes from the starting address to implement lw, and we splited and stored word in 4 bytes to implement sw.(In Little Endian format) <br>
We took input of a program as a file, we read each line of the file at starting and divided them into programs and labels. <br>
We have used string map to store the PC value of given label and we use them to jump to that label if we required in the program. <br>
We have used string map to store starting address of the strings and arrays to point at them when needed.Stored '\0' at the next byte after storing each char of string to identify end of the string. <br>
We decided to split the memory to the two cores and for 1st core we decided to start memory from 1000th byte and for 2nd core we decided to start memory from 3000th byte for storing strings and array elements.<br>
We have also written code to identify and split commas and ignore comments. <br>






