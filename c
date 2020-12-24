#!/bin/bash 	
#
function ech0 () {     # turn on debugging with  export ech0=ON
  if [ ".$ech0" == ".ON" ]; then
    echo $@
  fi  
}

# # testing
# ech0="ON"
# ech0 "\$1=<$1>, \$2=<$2> "
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
	      - , old, back - all act like  cd -  back prev dir \$OLDDIR
	                  Note this is a toggle  prev-dir and current-dir
          other - search c_acrolist to see which dir. to use in cd 

EOF-usage
return
fi
if [ "$1" == "old" ] || [ "$1" == "back" ] || [ "$1" == "-" ]; then
   echo "Remember '-', 'old' and 'back' are special to return to the" 
   echo "calling cd-dir, so  returning to $OLDPWD"
   cd $OLDPWD
   return
fi

acro_to_find=$1
c_dir=/home/$USER/bin             # if in bin

c_dir=$rchbls           # for whereisit system to get this into
                        # ~/bin comment out this line.

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
else
  echo "need proper action in parm 2 - null"
  found="yes"     # kill end  not found mismessage
  return
fi

acro_found="no"
line_item=''
ech0 "\$line_item = $line_item."
while [ ".$acro_found" == ".no" ] && 
 read line_item  ; do
# while  read line_item  ; do
  ech0 $line_item
  IFSsave=$IFS
  IFS=" "
  read acro_item new_dir_item <<< $line_item
  IFS=$IFSsave
# ech0 "dir_new_item=$dir_new_item, arco_item=$acro_item,
if [ ".$acro_item" == ".$acro_to_find" ]; then
  echo
  echo "$acro_to_find in c_acrolis at line: $line_item"
  ## convert '~' to full name
  if [ ${new_dir_item:0:1} == "~" ]; then
    lead=$HOME
    tailend=${new_dir_item:1}
    new_dir_item=$lead$tailend
  fi
  ## check to see if new directory exists.
  answer=FALSE
    if [ -e $new_dir_item ]; then
      if [ -d $new_dir_item ]; then
        echo $new_dir_item exists as a directory
        answer=TRUE
      else
        echo $new_dir_item exists but NOT as a directory
      fi
    else
      echo $new_dir_item doe not exist
    fi
  if [ ".$answer" == ".FALSE" ]; then
    echo "Quiting No work done."
    echo
    return
  fi

    
  ## check to see if new directory exists.
  acro_found="yes"
  ech0 "MATCH MATCH $acro_item  $acro_to_find"
#  gocdit $acro_to_find $action $acro_item $dir_new_item 
#function gocdit () {
  echo "change to $new_dir_item"
  echo
  OLDPWD=$PWD               # remember where I came from
                            # in case I want to go back
  ech0 "cd $new_dir_item"                   
                            # also cannot use $0 this becomes bash
  cd $new_dir_item                   
    
  ech0 "PWD=$PWD"
else
  ech0 ".$arco_item. <> .$acro_to_find. "
fi
done <   $c_dir/c_acrolist      # <<<-- this much change  org was cd0

# fall through to message that cd path not found 
if [ ".$acro_found"  == ".no" ]; then
     echo
     echo "$acro_to_find NOT FOUND  as an cd path "
     echo "Check your typing  or look  '. c .'"
fi


