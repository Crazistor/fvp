#!/bin/sh

MODULE_NAME="linux-2.6.24"
MODULE_DESC="linux-2.6.24"

source $HCM_CVSBASE_SCRIPTS/common.sh

#$1: dir
set_module_cc()
{
	local cc_file=.hil_config

	! [ -f $1/$cc_file ] && return 0

	$SED -i "s/[ \t]*CROSS_COMPILE[ \t]*=.*/CROSS_COMPILE=$HCM_CROSS_COMPILE-/" $1/$cc_file 
}

module_start_notify()
{
	case $1 in
	"combine_source_prepare")
		run_command_progress_float "$TAR -xvzf linux-2.6.24.tgz -C $dir_buildtime_tmp" \
				0 "$TAR -tzf linux-2.6.24.tgz | wc -l"
		[ -d $dir_combine_source ] && $RMDIR $dir_combine_source
		$MV $dir_buildtime_tmp/linux-2.6.24 $dir_combine_source
		;;
	"combine_source_check")
		[ -f $dir_combine_source/Makefile ] && notify_rcode=checkok
		;;

	"prebuild_configure")
		set_module_cc ./
		run_command_progress "$MAKE ${cfg_configure}_defconfig" 20
		;;
	"prebuild_check")
		[ -f .config ] && notify_rcode=checkok
		;;

	"build_make")
		run_command_progress "$MAKE $HCM_MAKE_MP" 26
		$MAKE uImage
		;;
	"build_check")
		[ -x vmlinux ] && notify_rcode=checkok
		;;

	"install_images")
		$CP arch/arm/boot/uImage $dir_install_images/kernel-hi3515v100_full_release_$VERSION.img
		;;
	"install_check")
		[ -f $dir_install_images/kernel-hi3515v100_full_release_$VERSION.img ] && \
			notify_rcode=checkok
		;;

	"postbuild_check")
		[ -f $file_postbuild_srctarball ] && notify_rcode=checkok
		;;
	esac
}

source $HCM_CVSBASE_SCRIPTS/module_start.sh

