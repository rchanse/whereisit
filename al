#!/bin/bash

shopt -s expand_aliases

if [ ".$1" == ".un" ]; then   # don't seem to work ?? tbd
    unalias ..
    unalias cdt
    unalias cdb
    unalias cde
    unalias cdx
    unalias cx
    unalias cnx
    unalias now
    unalias path
    unalias v1
    unalias v2
    unalias varshow
else
   alias ..='cd ..'

     alias cdt='cd ~/witest'
     read -r build_dir rest < $rchbls/builddir
     echo "alias cdb='cd $build_dir'"
     alias cdb='cd $build_dir'            # to build-lib dir.

     read -r exec_dir  rest < $rchbls/execdir
     echo "alias cde='cd $exec_dir'"
     alias cde='cd $exec_dir'             # to exec-lib dir.
     alias cdx='cd $exec_dir'             # to exec-lib dir.

     echo "\$rchbls is rchbls"
     echo "\$build-dir = $build_dir"
     echo "\$exec-dir = $exec_dir"
     
   alias cnx='chmod -x '    
   alias cx='chmod +x '    
   alias hal='ls -alh '
   alias now='date +"%T"'
   alias path='echo -e ${PATH//:/\\n}'
   alias v1='vim  tempname'
   alias v2='vim ~/tempname'
   alias varshow='echo \$rchbls is $rchbls'
fi

