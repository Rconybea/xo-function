# xo-function/utest/CMakeLists.txt

set(SELF_EXE utest.fn)
set(SELF_SRCS
    function_utest_main.cpp
    grid1d_fn.test.cpp
)

if (ENABLE_TESTING)
    xo_add_utest_executable(${SELF_EXE} ${SELF_SRCS})

    # ----------------------------------------------------------------
    # dependencies..

    xo_self_dependency(${SELF_EXE} xo_function)
    #xo_headeronly_dependency(${SELF_EXE} xo_indentlog)
    xo_external_target_dependency(${SELF_EXE} Catch2 Catch2::Catch2)
endif()

# end CMakeLists.txt
