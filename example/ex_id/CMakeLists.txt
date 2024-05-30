# xo-function/exampple/ex_id/CMakeLists.txt

set(SELF_EXE xo_function_ex_id)
set(SELF_SRCS ex_id.cpp)

if (XO_ENABLE_EXAMPLES)
    xo_add_executable(${SELF_EXE} ${SELF_SRCS})
    xo_self_headeronly_dependency(${SELF_EXE} xo_function)
    # {xo_function -> indentlog} dep is declared in toplevel xo-function CMakeLists.txt,
    # but for some reason need to reassert it here
    xo_dependency(${SELF_EXE} indentlog)
endif()

# end CMakeLists.txt
