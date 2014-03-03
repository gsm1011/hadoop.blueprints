book = LOAD 'pittutorial/book.txt' USING PigStorage('\t') AS (isbn:chararray, name:chararray);
customer = LOAD 'pittutorial/customer.txt' USING PigStorage('\t') AS (cid:chararray, name:chararray, age:int, city:chararray, sex:chararray);
purchase = LOAD 'pittutorial/purchase.txt' USING PigStorage('\t') AS (year:int, cid:chararray, isbn:chararray, seller:chararray, price:int);

grouppurchase = GROUP purchase BY seller;
sellerearn = FOREACH grouppurchase GENERATE group, SUM(purchase.price);
STORE sellerearn INTO 'sellerearn';
cat sellerearn/part-r-00000

rawcitypurchase = JOIN purchase BY cid, customer BY cid;
groupcitypurchase = GROUP rawcitypurchase BY customer::city;
citypurchase = FOREACH groupcitypurchase GENERATE group, SUM(rawcitypurchase.purchase::price);
STORE citypurchase INTO 'citypurchase';
cat citypurchase/part-r-00000

rawgenderpurchase = JOIN purchase BY cid, customer BY cid;
groupgenderpurchase = GROUP rawgenderpurchase BY customer::sex;
genderpurchase = FOREACH groupgenderpurchase GENERATE group, SUM(rawgenderpurchase.purchase::price);
STORE genderpurchase INTO 'genderpurchase';
cat genderpurchase/part-r-00000

groupedpurchase = GROUP purchase BY isbn;
filteredpurchase = FILTER groupedpurchase BY COUNT(purchase) > 1;
minprice = FOREACH filteredpurchase GENERATE purchase, MIN(purchase.price) as minp;
flattened = FOREACH minprice GENERATE flatten(purchase), minp;
filteredhighprice = FILTER flattened BY price <= minp;
uniqsellerforbook1 = FOREACH filteredhighprice GENERATE isbn, seller, price, minp;
uniqsellerforbook2 = DISTINCT uniqsellerforbook1;
countlowestpricesellers = GROUP uniqsellerforbook2 BY isbn;
lowestsellers = FILTER countlowestpricesellers BY COUNT(uniqsellerforbook2) == 1;
flattenseller = FOREACH lowestsellers GENERATE flatten($1);
amazonislowest = FILTER flattenseller BY seller == 'Amazon';
cleanedresult = FOREACH amazonislowest GENERATE isbn, seller, minp;
STORE cleanedresult INTO 'amazonlowest';
cat amazonlowest
