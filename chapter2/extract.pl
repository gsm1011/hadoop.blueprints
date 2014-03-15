#!/usr/bin/env perl
# This script is used to extract meta-data and body of ASF archive
# mails. 

my $msg = "";

while (<STDIN>) {
    if($_ =~ m/From ([a-z\-]+)-return-([0-9]+)-apmail-([a-z\-]*)-archive/) {
        # Start of a new message. 
        if($msg !~ m//) {
            # printf "Message body: \n";
            # printf "%s\n", $msg; 
            $msg = ""; 
        }

        printf "\n\n%s %s %s ----->>>>>\n", $1, $2, $3;
       
    } elsif($_ =~ m/(^[A-Z][a-zA-Z\-]+:)( [^\n]+)/) {
        my $metaData = $_; 
        my $metaHeader = $1; 
        my $metaBody = $2; 

        # Header info. 
        if($msg !~ m//) { 
            # meta data of the previous meta. 
            # printf "%s", $msg;
            $msg = ""; 
        }

        if ($metaHeader =~ m/^(From:|Date:|Subject:)/) {
            printf "%s", $metaData; 
        }

        # printf "%s\n", $1; 

    } else {
        # Start of body. 
        $msg = $msg . $_; 
    }
}
