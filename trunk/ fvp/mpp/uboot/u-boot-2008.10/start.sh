#!/bin/sh

MODULE_NAME="U-Boot-2008"
MODULE_DESC="U-Boot-2008"

source $HCM_CVSBASE_SCRIPTS/common.sh

#$1: dir
set_module_cc()
{
	local cc_file=Makefile

	! [ -f $1/$cc_file ] && return 0
	
	$SED -i "s/^[ \t]*CROSS_COMPILE = arm-.*$/CROSS_COMPILE = $HCM_CROSS_COMPILE-/" $1/$cc_file 
}

module_start_notify()
{
	local uboot_stddir=u-boot-2008.10
	local uboot_stdname=u-boot

	case $1 in
	"cvsexport_common")
		set_module_cc $dir_targetcvs_module/common/
		;;
	"cvsexport_chip")
		set_module_cc $dir_targetcvs_module/$expt_chip/chip
		;;
	"cvsexport_board")
		set_module_cc $dir_targetcvs_module/$expt_chip/$expt_board
		;;

	"combine_source_prepare")
		run_command_progress_float "$TAR -xvzf $uboot_stddir.tgz -C $dir_buildtime_tmp" \
			0 "$TAR -tzf $uboot_stddir.tgz | wc -l"
		[ -d $dir_combine_source ] && $RM -fr $dir_combine_source
		$MV $dir_buildtime_tmp/$uboot_stddir $dir_combine_source
		;;
	"combine_source_check")
		[ -f $dir_combine_source/Makefile ] && notify_rcode=checkok
		;;

	"prebuild_configure")
		set_module_cc ./
		$MAKE ${cfg_configure}_config
		;;
	"prebuild_check")
		[ -L include/asm/arch ] && notify_rcode=checkok
		;;

	"build_make")
		run_command_progress "$MAKE depend && $MAKE $HCM_MAKE_MP" 16
		;;
	"build_check")
		[ -f $uboot_stdname.bin ] && notify_rcode=checkok
		;;

	"install_images")
		$CP -f $uboot_stdname.bin $dir_install_images/u-boot-hi3515v100_220M_$VERSION.bin
		;;
	"install_check")
		[ -f $dir_install_images/u-boot-hi3515v100_220M_$VERSION.bin ] && notify_rcode=checkok
		;;
	"postbuild_check")
		[ -f $file_postbuild_srctarball ] && notify_rcode=checkok
		;;

	esac
}

source $HCM_CVSBASE_SCRIPTS/module_start.sh

