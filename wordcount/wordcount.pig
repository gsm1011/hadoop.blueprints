-- This is the word count implementation using apache pig script. 

inputData = load '$input' USING PigStorage('\n') AS (line); 
words     = FOREACH inputData GENERATE flatten(TOKENIZE(line)) AS word; 
words_grped = GROUP words BY word; 
words_cnt = FOREACH words_grped GENERATE group, COUNT(words); 
DUMP words_cnt; 
