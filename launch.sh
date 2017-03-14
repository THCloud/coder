#! /bin/bash

ROOT_PATH=`cd $(dirname $0);pwd`

function log_info()
{
    local message="$1"
    echo -e "\e[1;32m[INFO]\e[m" ${message}
}

function log_error()
{
    local message="$1"
    echo -e "\e[1;31m[ERROR]\e[m" ${message}
}

function build_src_and_test()
{
    if [ -d "${ROOT_PATH}/build" ]; then
        rm -rf ${ROOT_PATH}/build
    fi
    mkdir ${ROOT_PATH}/build && cd ${ROOT_PATH}/build
    cmake ..
    make -j8
}

function run_demo()
{
    build_src_and_test
    cp ../test_data/test_file .
    cp ../conf/typelist .
    ./dict_parse_demo -flagfile=../conf/goodcoder.gflags

    [[ $? -ne 0 ]] && log_error "exit with error" || log_info "finished."

    rm ./test_file
    rm ./typelist
}

function run_tests()
{
    build_src_and_test
    tests=(
        "test_util"
        "test_parse_base_type"
        "test_parse_user_define_type"
        "test_user_function"
        "test_dict_handler"
    )
    for test in ${tests[@]} ; do
        echo "run $test."
        ./test/$test
        if [ $? -ne 0 ] ; then
            log_error "run $test failed."
            exit 1
        fi
    done
    log_info "run tests finished."
}

function help()
{
    echo "Usage: bash launch.sh [options]"
    echo "    options:"
    echo "    -h               : get help."
    echo "    run              : run demo."
    echo "    test             : run unit tests."
}

Main()
{
    if [ "$1" == "test" ]; then
        run_tests
    elif [ "$1" == "run" ]; then
        run_demo
    else
        help
    fi

    return $?
}

Main "$@"
