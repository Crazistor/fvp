#!/bin/sh

MODULE_NAME="rootfs-FULL_REL-Flash"
MODULE_DESC="rootfs-FULL_REL-Flash"

source $HCM_CVSBASE_SCRIPTS/common.sh

module_start_notify()
{
	case $1 in
	"combine_source_prepare")
		run_command_progress_float "$TAR -xvzf rootfs-FULL_REL-Flash.tgz -C $dir_buildtime_tmp" \
				0 "$TAR -tzf rootfs-FULL_REL-Flash.tgz | wc -l"
		cp rootfs-FULL_REL $dir_buildtime_tmp -rf
		ln -s libstdc++.so.6.0.3  $dir_buildtime_tmp/rootfs-FULL_REL/lib/libstdc++.so.6	
		ln -s libstdc++.so.6  $dir_buildtime_tmp/rootfs-FULL_REL/lib/libstdc++.so
		[ -d $dir_combine_source ] && $RM $dir_combine_source -rf		
		$MV $dir_buildtime_tmp/rootfs-FULL_REL $dir_combine_source
		
		pushd $dir_combine_source/
		rm dev/console -rf
		mknod dev/console c 5 1
		popd	
		;;
		
	"combine_source_check")
		pushd $dir_combine_source/..
		find ./ -type d -name ".svn" | xargs rm -fr
		sync
		mkfs.jffs2 -e 0x20000 -d ./rootfs-FULL_REL -o rootfs.jffs2
		$MV -f rootfs.jffs2 $dir_install_images/rootfs_full_rel_master_$VERSION.jffs2
		popd
		notify_rcode=checkok
		;;
		
	"postbuild_cptorelease")
		;;				
	esac
}

source $HCM_CVSBASE_SCRIPTS/module_start.sh

