#!/usr/bin/env perl

my $msg = "";
my $user = ""; 
my $subject = "";
my $orig = "";

while (<STDIN>) {
    if($_ =~ m/From ([a-z\-]+)-return-([0-9]+)-apmail-([a-z\-]*)-archive/) {
        # Start of a new message. 
        if($msg !~ m//) { $msg = ""; }

        if($orig =~ m/R(E|e)/) {
            printf "%s\t%s\tREPLY\n", $subject, $user; 
        } else {
            if ($user =~ m/.*@.*/) {
                printf "%s\t%s\tORIGINAL\n", $subject, $user;
            }
        }
    } elsif ($_ =~ m/^From: [^<]+<([^>]*)>/) {
        $user = $1; 
    } elsif ($_ =~ m/^Subject: (R(e|E): )*([^\n]*)$/) {
        $subject = $3; 
        $orig = $1; 
        # printf "Subject: %s\n", $3; 
    } else {
        # Start of body. 
        $msg = $msg . $_; 
    }
}
