#!/usr/bin/env perl 
use Time::Piece; 

print "Date,Time\n";
while(<STDIN>) {
    if ($_ =~ m/Date: [A-Z][a-z]{2}, ([0-9]{1,2} [A-Z][a-z]{2} [0-9]{4}) ([0-9:]+) (\+|\-)[0-9]{4}/) {
        printf "%s,%s\n", $1, $2;
    }
}
