#!/bin/bash 	
# IMPORTANT  this is fall through exec  because it must be activated by .
# this mean you stay in the same shell and the use if exit closes the window
# for this reason the code in kind of goofy
# the variable found  is need to determine whether to produce the last msg
# also cannot use $0 this becomes bash
vimfnt=~/bin/c                   # need to change as edit needed

if [ -f $HOME/rchtest/c ]; then
  vimfnt=$HOME/rchtest/c
else
  vimfnt=$HOME/rchbuild/c
fi

# quick goback to previous pw  (made typo)
if [ "$1" == "old" ] || [ "$1" == "back" ]; then
   echo Remember old and back are special to return to calling cd dir
   echo returning to $OLDPWD
   cd $OLDPWD
   return
fi

function gocdit
 {
   if [ $2 == "show" ]; then  # if part just lists the acro / file
      echo $3 $4 
   else
      if [ "$1" == "$3" ]; then        # go find the acroo
	     echo "change to "$4
         OLDPWD=$PWD               # remember where I came from
                                   # in case I want to go back
         cd  $4   
	     pwd
	     found="yes"
      else
         return
      fi
   fi
 }
# end of function godo
 
found="nope"

#  first make sure there is a parm
if [ "$1" == "" ] ; then
  found="yes"
  echo "You must enter a value  ( '. show' - to list,  - to edit )"
fi

# special case to edit the list of acronyms
if [ "$1" == "-" ] ; then 
  echo " editing the $0 file itself "
  vim $vimfnt      # <<<-- this much change  org was cd0
  found="yes"
fi

# set the second parm and make certain only certain one are used

if [ "$2" == "" ]; then
   action="cd"
elif [ "$2" == "show" ]; then
   action="show"
   found="yes"
else
   echo "need proper action in parm 2 - null  or show"
   found="yes"     # kill end  not found mismessage
fi

#  godo $1 $action    
#ocdit $1 $action chard      ~/blp/c_the_hard_way
gocdit $1 $action apache   /etc/apache2
gocdit $1 $action apachedoc /usr/share/doc/apache2
gocdit $1 $action bin        ~/bin
gocdit $1 $action binl       ~/.local/bin
gocdit $1 $action binlocal   ~/.local/bin
gocdit $1 $action bintest    ~/bintest
gocdit $1 $action bt         ~/bintest
gocdit $1 $action dc     ~/Documents
gocdit $1 $action dl     ~/Downloads
gocdit $1 $action down   ~/Downloads
gocdit $1 $action py27       /usr/lib/python2.7
gocdit $1 $action py34       /usr/lib/python3.4
gocdit $1 $action vimcolor  ~/.vim/colors
# sample   :63,125 sort
#  cd /home/rchansen/Downloads/hp_printing/hplip-3.14.6


# fall through to message that cd path not found 
#echo $found "found"
if [ $found  == "yes" ]; then
  dummy="None"
else
   if [ "$1" != "old" ]; then   # suppress due to $OLDPWD
     echo $1 "not found as an cd path "
   else
     dummy="None"
   fi
fi




