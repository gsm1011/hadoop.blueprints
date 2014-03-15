#!/usr/bin/env perl 
while(<STDIN>) {
    if ($_ =~ m/Date: [A-Z][a-z]{2}, [0-9]{1,2} ([A-Z][a-z]{2} [0-9]{4}) ([0-9:]+) (\+|\-)[0-9]{4}/) {
        printf "%s\n", $1;
    }
}
