#!/usr/bin/sh

any_tests_failed=false
failed_tests=()

make tests
if [ "$?" == 0 ] ; then
    echo "Running htmlvalidation_tests"
    ./htmlparser_tests/htmlvalidation_tests
    if [ "$?" != 0 ] ; then
        any_tests_failed=true
        failed_tests=(${failed_tests[@]} "htmlvalidation_tests")
    fi

    echo "Running htmltokenization_tests"
    ./htmlparser_tests/htmltokenization_tests
    if [ "$?" != 0 ] ; then
        any_tests_failed=true
        failed_tests=(${failed_tests[@]} "htmltokenization_tests")
    fi

    if "$any_tests_failed" == true ; then
        echo -e "Failures in:\n\t${failed_tests[@]}"
    else
        echo "All tests complete without failures"
    fi
else
    echo "Compilation error, giving up"
fi

