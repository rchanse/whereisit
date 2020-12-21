#!/bin/bash 	
#
function ech0 () {     # turn on debugging with  export ech0=ON
  if [ ".$ech0" == ".ON" ]; then
    echo $@
  fi  
}


function vhich () {
# This  is almost the same code as meminpath - it tells which
# library in $PATH that $1 (of the function) is found.
  file_to_check=$1
  First_find=NONE              # default is not found (NONE)

# parse the $PATH into an array (who)   note the sep char is ':'
  FSsave=$IFS
  IFS=":"
  read -r -a who <<< $PATH
  IFS=$IFSsave
  let ub=${#who[@]}         # number of elt in array  (based 0)jjj
#	echo $ub

  found="no"                 # none found yet
  let j=0                    # remember array start at 0 not 1

  while [ $j -lt $ub ] && [ ".$found" == ".no" ]; do

    if [ ".${who[$j]}" == ".." ]; then
      who[$j]=$PWD
    fi

    if [ -f ${who[$j]}/$file_to_check ]; then
      ech0 "$j $file_to_check  is in ${who[$j]}."
      First_find=${who[j]}     # <<<======== indicate where found
      found="yes"
    fi

    let j=$j+1
  done

#if [ ".$found" == ".no" ]; then
#  echo "$file_to_check is not in your PATH."
#else
#  echo "$file_to_check is first found in PATH-lib $First_find."
#fi
#export First_find=$First_find
#echo "export \$First_find = $First_find"
#
#echo "before \First_find = $first_find."

####################################################################
# Leaving the function vhich  $First_found is 1st-lib  or  NONE
####################################################################
}
function gocdit () {
orig=$1
action=$2
acro=$3
newdir=$4
   if [ ".$action" == ".show" ]; then  # if part just lists the acro / file
      echo $acro $newdir 
   else
      if [ ".$orig" == ".$acro" ]; then        # go find the acroo
	     echo "change to "$newdir
         OLDPWD=$PWD               # remember where I came from
                                   # in case I want to go back
         cd  $newdir   
	     pwd
	     found="yes"
      else
         return
      fi
   fi
 }
# end of function godo

# Start of real code
vhich c                    # we are interested in the 'c' script
ech0 "\$First_find = $First_find"


# IMPORTANT  this is fall through exec  because it must be activated by .
# this mean you stay in the same shell and the use if exit closes the window
# for this reason the code in kind of goofy
# the variable found  is need to determine whether to produce the last msg
# also cannot use $0 this becomes bash
c_dir=$First_find

# # testing
# ech0="ON"
# ech0 "\$1=<$1>, \$2=<$2>, \$3=<$3>, \$4=<$4> "
# ech0="Off"
# echo -n "view input parm, hit enter to go onward:"
# read whocares

#  first make sure there is a parm
if [ ".$1" == "." ] ; then
  found="yes"
  cat << EOF-usage
usage: quick change to another director by acronym

syntax;
 . c  parm
   parm1  null - this help info
          .    - edit on this script to view/alter the acronym list
	  show - show the list of known acronym-dir pairs
	  - , old, back - all act like  cd -  back prev dir \$OLDDIR
	                  Note this is a toggle  prev-dir and current-dir
EOF-usage
return
fi
if [ "$1" == "old" ] || [ "$1" == "back" ] || [ "$1" == "-" ]; then
   echo "Remember '-', 'old' and 'back' are special to return to the" 
   echo "calling cd-dir, so  returning to $OLDPWD"
   cd $OLDPWD
   return
fi

found="nope"
# special case to edit the list of acronyms
if [ ".$1" == ".." ] ; then 
  echo " editing the 'c' script to view/alter the list "
  vim $c_dir/c      # <<<-- this much change  org was cd0
  found="yes"
  return
fi

# set the second parm and make certain only certain one are used

if [ ".$2" == "." ]; then
  action="cd"
  if [ ".$1" == ".show" ]; then
     action="show"
     found="yes"
  fi
else
  echo "need proper action in parm 2 - null"
  found="yes"     # kill end  not found mismessage
  return
fi

#  godo $1 $action    
#     orig action acro      newdir
#ocdit $1 $action chard      ~/blp/c_the_hard_way
gocdit $1 $action wi      ~/whereisit
gocdit $1 $action wally    /home/wally
gocdit $1 $action fu      ~/fubar       
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


if [ ".x" == ".a" ]; then
  echo lfjs
fi
# fall through to message that cd path not found 
if [ ".$found"  == ".yes" ]; then
  dummy="None"
else
   if [ ".$1" != "old" ]; then   # suppress due to $OLDPWD
     echo "$1 NOT FOUND  as an cd path "
   else
     dummy="None"
   fi
fi
