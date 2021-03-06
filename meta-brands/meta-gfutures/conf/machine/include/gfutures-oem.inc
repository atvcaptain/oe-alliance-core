# We know about rtc
include conf/machine/include/build-extras.inc

BRAND_OEM = "gfutures"

MACHINE_NAME = "\
${@bb.utils.contains('MACHINEBUILD', 'mutant1100', 'HD1100' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1265', 'HD1265' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1500', 'HD1500' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1100', 'HD1100' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant500c', 'HD500C' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1200', 'HD1200' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'vizyonvita', 'Vita' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant11', 'HD11' , '', d)}\
"

MACHINE_BRAND = "\
${@bb.utils.contains('MACHINEBUILD', 'mutant1100', 'Mut@nt' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1265', 'Mut@nt' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1500', 'Mut@nt' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant500c', 'Mut@nt' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1200', 'Mut@nt' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'vizyonvita', 'Vizyon' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant11', 'Mut@nt' , '', d)}\
"

IMAGEDIR ?= "\
${@bb.utils.contains('MACHINEBUILD', 'mutant1100', 'hd1100' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1265', 'hd1265' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1500', 'hd1500' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant500c', 'hd500c' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant1200', 'hd1200' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'vizyonvita', 'hd1100' , '', d)}\
${@bb.utils.contains('MACHINEBUILD', 'mutant11', 'hd11' , '', d)}\
"

MTD_KERNEL = "mtd1"
MTD_ROOTFS = "mtd2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.bin"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = "\
    gfutures-dvb-modules-${MACHINE} \
    kernel-vmlinux \
    "

DVBPROVIDER = "kernel"
DVBSKYPROVIDER = "kernel"

MACHINE_ESSENTIAL_EXTRA_RRECOMMENDS = "\
    kernel-module-cdfs \
    "

MACHINE_EXTRA_RRECOMMENDS = " \
    gstreamer1.0-plugin-dvbmediasink \
    "

include conf/machine/include/autoload-filesystems.inc

DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 \
    ${@bb.utils.contains('MACHINEBUILD', 'mutant1265', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
    ${@bb.utils.contains('MACHINEBUILD', 'mutant1500', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
    ${@base_contains('MACHINEBUILD', 'mutant11', '--with-h265 --with-vb6 --with-vb8 --with-spark' , '', d)} \
"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

PREFERRED_PROVIDER_virtual/kernel = "linux-gfutures"

KERNEL_IMAGETYPE = "vmlinux"
KERNEL_OUTPUT = "${KERNEL_IMAGETYPE}"
KERNEL_CONSOLE = "ttyS0,115200n8"

IMAGE_FSTYPES ?= "ubi"

IMAGEDIR ?= "${MACHINE}"

IMAGE_CMD_ubi_append = "\
    mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/splash.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash.bin; \
    mv ${DEPLOY_DIR_IMAGE}/${IMAGE_NAME}.rootfs.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ROOTFS_FILE}; \
    gzip -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${IMAGE_VER_STRING} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
    echo "rename this file to 'force' to force an update without confirmation" > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/noforce; \
    cd ${DEPLOY_DIR_IMAGE}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
    rm -f ${DEPLOY_DIR_IMAGE}/.ubifs; \
    rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
    rm -Rf ${DEPLOY_DIR_IMAGE}/boot; \
    rm -Rf ${IMAGEDIR}; \
    "


MACHINE_FEATURES += "3dtv alsa hdmicec switchoff bootsplash omb boxmodel feature1"

BOOTLOGO_FILENAME = "splash.bin"

require conf/machine/include/tune-mips32.inc

EXTRA_IMAGEDEPENDS += " \
    enigma2-plugin-systemplugins-remotecontrolcode \
    "

MACHINE_EXTRA_RDEPENDS_${PN} = " \
    enigma2-plugin-systemplugins-remotecontrolcode \
    "

# add support for extra feeds
PACKAGE_ARCHS += " ${MACHINEBUILD}"
