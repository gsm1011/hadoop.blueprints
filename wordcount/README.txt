*About
This is the word count example using hadoop/mapreduce. 
The program accepts an input and generates output containing
the number of words in the input(s).

*Dependency
Hadoop must be deployed, either pseudo distributed or fully 
distributed. The the hadoop examples jar file should be avaiable
to run the teragen for generating the sample input. 

*How to run
The project is managed with Makefile, so, use generic make commands
to run this program. Specifically, use the following steps to run:
- Modify the environment variables in the Makefile.
- Generate sample random input data with teragen using "make geninput". 
- Run the program with command "make run"
- If you type the "make" command, the .java files will be compiled to 
  .class files and nothing else will be done. 

*License
This code is free, you can freely distributed it. 
