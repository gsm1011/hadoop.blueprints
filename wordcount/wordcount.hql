-- This is hive version of word count. 

CREATE TABLE documents ( line STRING ); 

LOAD DATA INPATH '$inputPath' OVERWRITE INTO TABLE documents; 

CREATE TABLE wordcount AS 
  SELECT word, COUNT(1) AS count FROM 
    (SELECT explode(split(line, '\s')) AS word FROM documents) w
  GROUP BY word
ORDER BY word; 
