SUMMARY = "direct Flashing and Backup for Enigma2"
MAINTAINER = "gutemine <gutemine@oozoon.de>"
SECTION = "base"
PRIORITY = "required"
LICENSE = "proprietary"
PACKAGE_ARCH = "all"
RDEPENDS_${PN} = "dreambox-buildimage"

require conf/license/license-gplv2.inc

inherit gitpkgv
SRCREV = "${AUTOREV}"
PV = "13.7+git${SRCPV}"
PKGV = "13.7+git${GITPKGV}"
VER ="13.7"
PR = "r0"

SRC_URI="git://github.com/openatv/enigma2-plugin-extensions-dflash.git"

S = "${WORKDIR}/git"

FILES_${PN} = "/usr/*"

do_install() {
    cp -rp ${S}/usr ${D}/
    install -d ${D}/usr/sbin
    install -m 0755 ${S}/bin/nand_check ${D}/usr/sbin/nand_check
    install -m 0755 ${S}/bin/nfiwrite ${D}/usr/sbin/nfiwrite
}

pkg_postrm_${PN}() {
#!/bin/sh
rm /usr/lib/enigma2/python/Plugins/Extensions/WebInterface/web-data/img/dflash.png > /dev/null 2>&1
rm /usr/lib/enigma2/python/Plugins/Extensions/WebInterface/web-data/img/ring.png > /dev/null 2>&1
rm -r /usr/lib/enigma2/python/Plugins/Extensions/dFlash > /dev/null 2>&1
exit 0
}

do_package_qa[noexec] = "1"
