<!DOCTYPEhtml>
  <html>
    <body>

<h1>Brain-Fuck-Interpreter</h1>
<p>Interpret Brainfuck (BF) code and handle errors.</p>

<h2>Background</h2>
<p>BF is an esoteric programming language created in 1993 by Urban Müller. The language only has eigth commands, but it is fully Turing complete. BF has no practical uses, but it does challenge programmers, while testing the bounds of computer science.</p>

<h2>How to Code in BF</h2>
<ol>
  <li>'>' Forward pointer. Tell C++ to point to the memory block that is infront of the current memory block</li>
  <li>'<' Backward pointer. Tell C++ to point to the memory block that is behind the current memory block</li>
  <li>'.' Print. Tell C++ to print what is in the memory block that C++ is currently pointing too</li>
  <li>',' User input. Tell C++ to take user input</li>
  <li>'+' Increment. Tell C++ to increment the memory block by 1</li>
  <li>'-' Decrement. Tell C++ to decrement the memory block by 1</li>
  <li>'[' Start a loop. Tell C++ where the start a loop is located. When a loop starts over it will go to wherever the '[' char is located</li>
  <li>']' End a loop. Tell C++ where the end of a loop is located</li>
</ol>

<h2>Rules</h2>
<ol>
  <li>This interpreter does not read white spaces</li>
  <li>Loops must start and end on the same line</li>
  <li>There are 30,000 memory blocks</li>
  <li>Each memory block is initialized with the value 0</li>
  <li>Each memory block cannot be more than 0x7f (127)</li>
  <li>Each memory block cannot be less than -0x80 (-128)</li>
  <li>User input is taken one char at a time, not one line at a time</li>
  <li>The BF code must be stored in a text file</li>
</ol>

<h2>Example of Good BF Code</h2>

![image](https://user-images.githubusercontent.com/42715109/118883792-a7e70200-b8c3-11eb-89d8-3c10fd140bf3.png)

<h2>Enviorment</h2>
<ol>
  <li>Built in Visual Studio 2019</li>
  <li>C++ Language standard: ISO C++17 Standard (/std:c++17)</li>
  <li>C Language standard: ISO C17 (2018) Standard (/std:c17)</li>
  <li>Complied on the x86 platform</li> 
</ol>

  </body>
</html>
