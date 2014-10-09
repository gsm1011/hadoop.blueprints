About
=====

This is the sort example using hadoop/mapreduce. 
The program accepts an input of files that contain randomly 
generated integers and generates sorted numbers. 

Dependency
==========

Hadoop must be deployed, either pseudo distributed or fully 
distributed. 

How to run
==========

The project is managed with Makefile, so, use generic make commands
to run this program. Specifically, use the following steps to run:
- Modify the environment variables in the Makefile.
- Generate sample random input data with RandomGen using "make geninput". 
- Run the program with command "make run"
- If you type the "make" command, the .java files will be compiled to 
  .class files and nothing else will be done. 

License
=======

This code is free, you can freely distributed it. 
