#!/usr/bin/perl -w
#
# Use this script to download extra introduction to LPC documentation.
# You should run this script from the gurbalib directory 
# (./scripts/download_lpc_docs.pl)
# $root is the final location of the docs.
my $root = "./lib/doc/lpc";
my ($fh, $i, $wget);

if (-f "/usr/bin/wget") {
   $wget = "/usr/bin/wget";
} elsif (-f "/usr/bin/curl") {
   $wget = "/usr/bin/curl -C - -O";
} else {
   $wget = `which wget`;
   if (!-f $wget) {
      $wget = `which curl`;
      if (-f $wget) {
         $wget = "$wget -C - -O";
      } else {
         print "Unable to find wget or curl.\n";
         exit (1);
      }
   } 
}

if (!-d "./lib/doc") { 
   print "Cannot find the mudlib directory.\n";
   print "You should run this script from the gurablib dir.\n";
   exit 1;
}

if (!-d $root) {
	mkdir($root);
}

unlink("$root/readme.txt");
open($fh,">","$root/readme.txt") or die "Unable to open readme.txt\n";
print $fh "Check out http://en.wikipedia.org/wiki/LPC_(programming_language)\n";
print $fh "Some of the documenation has been downloaded to this dir.\n";
print $fh "George Reese's LPC Basics (the html pages)\n";
print $fh "And discworld MUD's LPC for Dummies (the pdf docs.)\n";
close $fh;

system("cd $root; $wget http://www.monkeys-at-keyboards.com/lpc1.pdf");
system("cd $root; $wget http://www.monkeys-at-keyboards.com/lpc2.pdf");

system("cd $root; $wget http://wl.mud.de/mud/doc/lpc/introduction.html");
for ($i=0;$i<7;$i++) {
   system("cd $root; $wget http://wl.mud.de/mud/doc/lpc/chapter$i.html");
   system("cd $root; $wget http://wl.mud.de/mud/doc/lpc/chapter1$i.html");
}

system("cd $root; $wget http://wl.mud.de/mud/doc/lpc/chapter8.html");

