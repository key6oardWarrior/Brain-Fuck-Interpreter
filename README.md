<!DOCTYPEhtml>
  <html>
    <body>

<h1>Esoteric Interpreter</h1>
<p>Interpret an esoteric programming language's code and handle errors.</p>

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
  <li>']' End a loop. Tell C++ where the end of a loop is located. A Loop will only end if the value of the current memory block is 0 and the current char being read is '['</li>
</ol>

<h2>Rules</h2>
<ol>
  <li>This interpreter does not read white spaces</li>
  <li>Loops must start and end on the same line</li>
  <li>There are 30,000 memory blocks</li>
  <li>Each memory block is initialized with the value 0</li>
  <li>Each memory block cannot be more than 127</li>
  <li>Each memory block cannot be less than -128</li>
  <li>Attemping to go above 127, or below -128, will result in an error</li>
  <li>If during user input a user enter a std::string each char will be put in a memory block of it's own</li>
  <li>The BF code must be stored in a .bf file</li>
</ol>

<h2>Example of Good BF Code</h2>

![image](https://user-images.githubusercontent.com/42715109/120082546-9ce55c00-c091-11eb-8b9c-67ad29e9fe26.png)

<h2>Enviorment</h2>
<ol>
  <li>Built in Visual Studio 2022</li>
  <li>C++ Language standard: ISO C++20 Standard (/std:c++20)</li>
  <li>C Language standard: ISO C17 (2018) Standard (/std:c17)</li>
  <li>Complied on the x64 platform</li> 
</ol>

<h2>Note:</h2>
<p>When running the unit test ensure that Visual Studio Code 2022's configuration manager is set to Debug, or else not all the assert functions will not be called.</p>

  </body>
</html>
