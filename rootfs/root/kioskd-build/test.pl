#!/usr/bin/env perl
use strict;
use warnings;
use JSON::RPC2::Client;
use IO::Socket::INET;

my $socket = IO::Socket::INET->new(
    #PeerAddr => '10.42.0.16',
    PeerAddr => 'localhost',
    PeerPort => 24054,
    Proto => 'tcp'
);

die 'Could not connect to Kioskd' unless defined $socket;

my $client = JSON::RPC2::Client->new();

sub make_call {

    my $json_request = shift;
    print "<<<<<<<<<<\n$json_request\n>>>>>>>>>>\n";
    

    print $socket $json_request;
    while(<$socket>) {
        print $_;
        last if m/^\}/;
    }

}

# sleep 2;
# 
make_call($client->call_named('Update', (
    name => 'testtext',
    type => 'text',
    text => 'Hello, World!',
    x => 0, 
    y => 0,
    w => 100,
    h => 100,
    font_path => 'fonts/quartzregulardb.ttf',
    font_point_size => 24,
    colour => [255, 255, 255, 255],
)));

make_call($client->call_named('Update', (
    name => 'testimage',
    type => 'image',
    image_path => '/home/rikki/Pictures/test.png',
    x => 0, y => 0,
    w => 1336, h => 768,
)));

sleep 1;

make_call($client->call_named('Update', (
    name => 'testtext',
    type => 'text',
    x => 100, 
    y => 100,
    w => 500,
)));

sleep 1;

make_call($client->call_named('Update', (
    name => 'testtext',
    type => 'text',
    x => 200, 
    y => 200,
    w => 50,
    wrap => 0,
    colour => [255, 128, 0, 128],
)));

sleep 1;

make_call($client->call_named('Destroy', (
    name => 'testtext',
    type => 'text',
)));

sleep 1;

make_call($client->call_named('Destroy', (
    name => 'testimage',
    type => 'image'
)));

sleep 1;

make_call($client->call_named('ExitKiosk', ()));



__END__
