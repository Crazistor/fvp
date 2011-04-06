#!/bin/bash
#authr :  dcdcmin@gmail.com


if [ $# -lt 2 ];then
    echo "usage:code_gen.sh filename IsHeadFile[y,n]"
    exit 1
fi

if [ $2 != "y" -a $2 != "n" ];then
    echo "usage:code_gen.sh filename IsHeadFile[y,n]"
    exit 1
fi



FileName=$1

if [ -f $FileName ];then
    echo "The file[$FileName] is exist"
    exit 
fi 

if [ $2 == "y" ];then
    IsHeadFile=y
else
    IsHeadFile=n
fi

echo "/*
 * File: $FileName
 * Author:  zhoumin  <dcdcmin@gmail.com>
 * Brief:   
 *
 * Copyright (c) 2010 - 2013  zhoumin <dcdcmin@gmail.com>>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * $(date) zhoumin <dcdcmin@gmail.com> created
 *
 */"> $FileName



#insert space line
echo "


" >> $FileName

echo "$IsHeadFile"
TempString=$FileName
if [ $IsHeadFile = "y" ];then
        declare -u TempString
        TempString=$FileName
#        echo "$TempString"

fi

if [ $IsHeadFile = "y" ];then
    echo "#ifndef $TempString" >> $FileName
    echo "#define $TempString" >> $FileName
fi








echo "



">> $FileName


if [ $IsHeadFile = "y" ];then
    echo "#endif /*$TempString*/" >> $FileName
fi

#insert a space line
echo "

" >> $FileName


if [ $IsHeadFile = "y" ];then
    sed 's/.H/_H/g' $FileName > temp
    mv temp $FileName
    rm -f temp
fi

