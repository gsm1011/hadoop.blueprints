#!/usr/bin/env perl 

my $currentsub = ""; 
my $collaborators = ""; 
while(<STDIN>) {
    if ($_ =~ m/^(.*)\t(.*)\t(.*)$/) {
        my $subject = $1; 
        my $user = $2; 
        my $type = $3; 
        if ($currentsub eq "") {
            # Begin. 
            $currentsub = $subject;
            $collaborators = $user;
            
        } elsif ($currentsub eq $subject) {
            # Same as the previous subject. 
            if ($collaborators !~ m/$user/) {
                if($type =~ m/ORIGINAL/) {
                    $collaborators = $user . "," . $collaborators;
                } else {
                    $collaborators = $collaborators . "," . $user;
                }
            }
        } else {
            # A new subject.
            printf "%s\n", $collaborators; 
            $currentsub = $subject; 
            $collaborators = $user;
        }
    }
}
printf "%s\n", $collaborators;
