#!/bin/sh

MODULE_NAME="kbuild_head"
MODULE_DESC="kbuild_head"

source $HCM_CVSBASE_SCRIPTS/common.sh

module_start_notify()
{
	case $1 in
	"combine_source_prepare")		
		run_command_progress_float "$TAR -xvzf kbuild-FULL_REL.tgz -C $dir_buildtime_tmp" \
				0 "$TAR -tzf kbuild-FULL_REL.tgz | wc -l"
		[ -d $dir_combine_source ] && $RM $dir_combine_source -rf		
		$MV $dir_buildtime_tmp/kbuild-FULL_REL $dir_combine_source 		
		
		ECHO "rebuild kernel headers ..." 
		pushd $dir_combine_source
		make scripts archprepare
		popd
		;;
		
	"postbuild_cptorelease")
		;;
				
	esac
}

source $HCM_CVSBASE_SCRIPTS/module_start.sh

