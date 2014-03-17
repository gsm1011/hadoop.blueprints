#!/usr/bin/env perl 
# command to run the hadoop streaming job. 
# hadoop jar $STREAM_JAR -input collaborate \
# -output experts.novices -mapper "perl experts.novice.map.pl" \
# -combiner "sort -t ',' -k1" -reducer "perl experts.novice.reduce.pl" \
# -file experts.novice.map.pl -file experts.novice.reduce.pl

my $currentuser = ""; 
my $askCnt = 0; 
my $answerCnt = 0; 
while(<STDIN>) {
    m/([^,]+),(0|1),(0|1)/; 
    if ($currentuser eq "") {
        $currentuser = $1; 
        $askCnt = $2; 
        $answerCnt = $3; 
    } elsif ($currentuser eq $1) {
        $askCnt += $2; 
        $answerCnt += $3;
    } else {
        printf "%s,%d,%d\n", $currentuser, $askCnt, $answerCnt; 
        $askCnt = $2;
        $answerCnt = $3;
        $currentuser = $1; 
    }
}
printf "%s,%d,%d\n", $currentuser, $askCnt, $answerCnt;
