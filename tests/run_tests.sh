#!/usr/bin/sh

any_tests_failed=false
failed_tests=()

make tests
if [ "$?" == 0 ] ; then
    echo "Running htmlparser_tests"
    ./htmlparser_tests/htmlparser_tests
    if [ "$?" != 0 ] ; then
        any_tests_failed=true
        failed_tests=(${failed_tests[@]} "htmlparser_tests")
    fi

    if "$any_tests_failed" == true ; then
        echo "Failures in $failed_tests"
    else
        echo "All tests complete without failures"
    fi
else
    echo "Compilation error, giving up"
fi

