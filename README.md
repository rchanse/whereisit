Sat 21 Nov 2020 12:45:30 PM CST     (finally some doc)

Motivation: I keep forgetting where I put stuff and asking myself
 whereis ---

There will be two main tools  'f' and 'g'
f  is to help you find stuff by an acronym that you choose
g  is to find stuff in a list you have by number

'whereis' system

Parts:
1. 1 global variable '$rchjlp' initials Robert C Hansen, Jean-Luc Picard
2. a library which contains the code.  (usually called build-lib.
3. a library which has the running code (usually called exec-lib.

Assumptions:
 a. the build-lib will be in directory   $HOME/whereis
 b. the exec-lib will be in directory    $HOME/fubar
 c. you (or some software) are not otherwise using $rchjlp
( there will be a note below on how to override a. and b.  BUT
  to override c. you will need to copy and rewrite this code.)

I N S T A L L A T I O N:

1. Obtain the code:   git clone https://github.com/rchanse/whereis.git
( I'll assume you did this from $HOME be if you were cautious and
pulled it down to another directory, please move it to  $HOME/whereis)

. ~/whereis/setvar      (or  source ~/whereis/setvar
                        This will set global $rchjlp  <<====

. ~/whereis/INSTALL     (or   source ~/whereis/INSTALL
                        create and populate exec-lib
                        remember the default will  $HOME/fubar dir.
. ~/whereis/engage      (hook the exec-lib into your environment

That's it.

So -- What next??

Here are some commands you can try

dirinpath ~/fubar                 (will show if fubar member will
                                   conflict with your PATH
  1 nm,.    
f .                                (shows a list of preset acronyms

g q README                       
g 0






Stop for a moment  Sat 21 Nov 2020 01:41:45 PM CST

