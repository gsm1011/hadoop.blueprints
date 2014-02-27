#!/usr/bin/env perl
# Map function for hadoop streaming using Perl.

our %wordmap={};
while (<STDIN>) {
    $word=$_;
    if($word ne "") {
        if (exists($wordmap{$word})) {
            $wordmap{$word} += 1;
        } else {
            $wordmap{$word} = 1;
        }
    }
}

for my $word (keys %wordmap) {
    my $cnt = $wordmap{$word};
    print $word . "$cnt\n";
}
