#!/bin/bash

shopt -s expand_aliases

if [ ".$1" == ".un" ]; then   # don't seem to work ?? tbd
    unalias ..
    unalias cdt
    unalias cdn
    unalias cdb
    unalias cdx
    unalias cx
    unalias cnx
    unalias now
    unalias p3
    unalias path
    unalias v1
    unalias v2
    unalias varshow
else
   alias ..='cd ..'
   if [ ".$rchbls" != "." ]; then
     alias cdn='cd ~/newtest'
     alias cdt='cd ~/testwit'
     echo "\$rchbls = $rchbls"
     read build_dir rest < $rchbls/builddir
     read exec_dir  rest < $rchbls/execdir
     echo "build-dir = $build_dir, exec-dir = $exec_dir"
     echo "alias cdx='cd $exec_dir'"
     alias cdx='cd $exec_dir'             # to exec-lib dir.
     echo "alias cdb='cd $build_dir'"
     alias cdb='cd $build_dir'            # to build-lib dir.
   fi  
   alias cnx='chmod -x '    
   alias cx='chmod +x '    
   alias hal='ls -alh '
   alias now='date +"%T"'
   alias path='echo -e ${PATH//:/\\n}'
   alias v1='vim  tempname'
   alias v2='vim ~/tempname'
   alias varshow='echo \$rchbls is $rchbls'
fi
