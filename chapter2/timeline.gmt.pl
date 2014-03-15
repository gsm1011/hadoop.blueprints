#!/usr/bin/env perl 
use Time::Piece; 

print "Date,Time\n";
while(<STDIN>) {
    if ($_ =~ m/Date: [A-Z][a-z]{2}, ([0-9]{1,2} [A-Z][a-z]{2} [0-9]{4} [0-9:]+ (\+|\-)[0-9]{4})/) {

        #@printf "%s ---->>>> ", $1;

        my $dt = Time::Piece->strptime($1, '%d %b %Y %H:%M:%S %z');
        print $dt->strftime('%d %b %Y,%H:%M:%S');
        printf "\n";
    }
}
