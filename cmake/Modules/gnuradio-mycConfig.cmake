find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_MYC gnuradio-myc)

FIND_PATH(
    GR_MYC_INCLUDE_DIRS
    NAMES gnuradio/myc/api.h
    HINTS $ENV{MYC_DIR}/include
        ${PC_MYC_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_MYC_LIBRARIES
    NAMES gnuradio-myc
    HINTS $ENV{MYC_DIR}/lib
        ${PC_MYC_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-mycTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_MYC DEFAULT_MSG GR_MYC_LIBRARIES GR_MYC_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_MYC_LIBRARIES GR_MYC_INCLUDE_DIRS)
