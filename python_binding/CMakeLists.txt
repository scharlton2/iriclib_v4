# Partially based on https://github.com/Mizux/cmake-swig/blob/main/Foo/python/CMakeLists.txt

# this defines swig_add_library and was set by FindSWIG aka find_package(SWIG ...)
# see https://cmake.org/cmake/help/latest/module/FindSWIG.html
# and https://cmake.org/cmake/help/latest/module/UseSWIG.html
include(${SWIG_USE_FILE})

# iric.i
set_property(SOURCE iric.i PROPERTY SWIG_MODULE_NAME iric)
set_property(SOURCE iric.i PROPERTY CPLUSPLUS ON)
swig_add_library(iric LANGUAGE python SOURCES ${CMAKE_CURRENT_LIST_DIR}/iric.i)

# this is required to avoid a header file (pyconfig.h) forcing
# a link against python38_d.lib during debug builds
target_compile_definitions(iric
  PRIVATE
    SWIG_PYTHON_INTERPRETER_NO_DEBUG
)

# use imported targets for iric
target_link_libraries(iric
  PRIVATE
    iriclib::iriclib
    Python::Python
)
