COMPATIBLE_MACHINE = "(tegra)"

TEGRA_SRC_SUBARCHIVE = "Linux_for_Tegra/source/public/nvidia-jetson-optee-source.tbz2"

inherit l4t_bsp python3native
require recipes-bsp/tegra-sources/tegra-sources-${L4T_VERSION}.inc

DEPENDS = "python3-pyelftools-native python3-cryptography-native"
# python3-cryptography needs the legacy provider, so set OPENSSL_MODULES to the
# right path until this is relocated automatically.
export OPENSSL_MODULES="${STAGING_LIBDIR_NATIVE}/ossl-modules"

OPTEE_NV_PLATFORM ?= ""
OPTEE_NV_PLATFORM:tegra194 = "t194"
OPTEE_NV_PLATFORM:tegra234 = "t234"

TA_DEV_KIT_DIR = "${STAGING_INCDIR}/optee/export-user_ta"

# Common to all of the builds
EXTRA_OEMAKE = "\
    V=1 \
    O=${B} \
    CFLAGS32='${TOOLCHAIN_OPTIONS} ${DEBUG_PREFIX_MAP}' \
    CFLAGS64='${TOOLCHAIN_OPTIONS} ${DEBUG_PREFIX_MAP}' \
    platform-aflags-generic='${DEBUG_PREFIX_MAP} -pipe' \
    TA_DEV_KIT_DIR=${TA_DEV_KIT_DIR} \
"
