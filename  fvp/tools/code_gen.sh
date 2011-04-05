#!/bin/bash
#author :  dcdcmin@gmail.com


if [ $# -lt 2 ];then
    echo "11111usage:code_gen.sh filename IsHeadFile[y,n]"
    exit 1
fi

if [ $2 != "y" -a $2 != "n" ];then
    echo "2222usage:code_gen.sh filename IsHeadFile[y,n]"
    exit 1
fi

FileName=$1

if [ $2 == "y" ];then
    IsHeadFile=y
else
    IsHeadFile=n
fi

echo "
/*
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



echo "aaaaaaaaaaaaa$IsHeadFile"
TempString=$FileName
if [ $IsHeadFile = "y" ];then
        echo "hello world"
        declare -u TempString
        TempString=$FileName
        echo "$TempString"

fi

if [ $IsHeadFile = "y" ];then
    echo "google"

fi










