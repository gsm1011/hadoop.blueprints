#!/usr/bin/env perl 

while(<STDIN>) {
    my @records = $_ =~ m/([^,]+),?/g; 
    my $cnt = 0; 
    foreach my $record (@records) {
        $record =~ s/\s//g; 
        if ($cnt == 0) { 
            printf "%s,1,0\n", $record; 
        } else { 
            printf "%s,0,1\n", $record; 
        }
        $cnt++; 
    }
}
