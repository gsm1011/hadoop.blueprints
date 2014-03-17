#!/usr/bin/env perl 
# use the following command to get the final count 
#  perl topics.user.count.pl < part-00000 | sort | uniq -c | sort -k2 -n
while (<STDIN>) {
    my @records = $_ =~ m/([^,]+),?/g;
    printf "%d\n", $#records + 1;
}
