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
   echo "orig=$orig, action=$action, acro=$acro, newdir=$newdir."
   if [ ".$action" == ".show" ]; then  # if part just lists the acro / file
      echo $acro $newdir 
   else
      if [ ".$orig" == ".$acro" ]; then        # go find the acroo
	     echo "change to "$newdir
         OLDPWD=$PWD               # remember where I came from
                                   # in case I want to go back
         echo "cd $newdir"                         
         # handle ~ so ~/anything becomes /home/$USER/anything
         if [ ${newdir:0:1} == "~" ]; then
           lead=$HOME
           tailend=${newdir:1}
           newdir=$lead$tailend
        fi
         cd  $newdir   
         echo "pwd=$PWD"
	     found="yes"
      else
         return
      fi
   fi
 }
# end of function godo

# Start of real code
search_acro=$1
vhich d                    # we are interested in the 'c' script
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
# vim $c_dir/c      # <<<-- this much change  org was cd0
  vim $c_dir/c_acrolist      # <<<-- this much change  org was cd0
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

acro_found="no"
line_item=''
ech0 "\$line_item = $line_item."
ech0 "orig=$orig"
while [ ".$acro_found" == ".no" ] && 
 read line_item  ; do
# while  read line_item  ; do
  ech0 $line_item
  IFSsave=$IFS
  IFS=" "
  read acro_item dir_new_item <<< $line_item
  IFS=$IFSsave
  ech0 "dir_new_item=$dir_new_item, arco_item=$acro_item,
  orig=$search_acro"
if [ ".$acro_item" == ".$search_acro" ]; then
  acro_found="yes"
  ech0 "MATCH MATCH $acro_item  $search_acro"
  gocdit $search_acro $action $acro_item $dir_new_item 
  echo "PWD=$PWD"
else
  ech0 ".$arco_item. <> .$search_acro. "
fi
done <   $c_dir/c_acrolist      # <<<-- this much change  org was cd0


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

