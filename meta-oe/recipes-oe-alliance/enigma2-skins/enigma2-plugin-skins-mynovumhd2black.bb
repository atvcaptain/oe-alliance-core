SUMMARY = "myNOVUM_HD2_Black by Nashu"
MAINTAINER = "rossi2000"

require conf/license/license-gplv2.inc

inherit gitpkgv allarch

SRCREV = "${AUTOREV}"
PV = "18.9+git${SRCPV}"
PKGV = "18.9+git${GITPKGV}"
PR = "r2"

RDEPENDS_${PN} = "enigma2-plugin-skincomponents-novum enigma2-plugin-systemplugins-weathercomponenthandler"

SRC_URI = "git://github.com/oe-alliance/oe-alliance-skins.git;protocol=git"

FILES_${PN} = "/usr/share/enigma2/myNOVUM_HD2_Black"

S = "${WORKDIR}/git"

do_compile_append() {
   python -O -m compileall ${S}
}

do_install() {
    install -d ${D}/usr/share/enigma2
    cp -rp ${S}/Nashu/myNOVUM_HD2_Black ${D}/usr/share/enigma2/
    chmod -R a+rX ${D}/usr/share/enigma2/
}

do_package_qa[noexec] = "1"
