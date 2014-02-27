#!/usr/bin/env perl
# Map function for hadoop streaming using Perl.

while (<STDIN>) {
    foreach my $word (split /\s+/, $_) {
        $word =~ tr/A-Z/a-z/;
        $word =~ s/[[:punct:]]//g;
        printf "%s\n", $word;
    }
}
