#!/usr/bin/env perl 
# command to run the hadoop streaming job. 
# hadoop jar $STREAM_JAR -input collaborate \
# -output experts.novices -mapper "perl experts.novice.map.pl" \
# -combiner "sort -t ',' -k1" -reducer "perl experts.novice.reduce.pl" \
# -file experts.novice.map.pl -file experts.novice.reduce.pl

my $current = ""; 
my $cnt = 0;
while(<STDIN>) {
    $_ =~ s/\s*$//g;

    if ($current eq "") {
        $current = $_; 
        $cnt = 1; 
    } elsif ($current eq $_) {
        $cnt++; 
    } else {
        printf "%s,%d\n", $current, $cnt; 
        $current = $_; 
        $cnt = 1; 
    }
}
printf "%s,%d\n", $current, $cnt; 
