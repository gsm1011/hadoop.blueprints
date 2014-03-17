#!/usr/bin/env perl 

while(<STDIN>) {
    my @records = $_ =~ m/([^,]+),?/g; 
    my $cnt = 0; 
    my $from = "";
    my $to = "";
    foreach my $record (@records) {
        $record =~ s/\s//g; 
        if ($cnt == 0) { 
            $from = $record; 
            #printf "%s,1,0\n", $record; 
        } else { 
            printf "%s,%s\n", $from, $record; 
        }
        $cnt++; 
    }
}
