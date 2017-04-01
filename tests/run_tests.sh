#!/usr/bin/sh

any_tests_failed=false
failed_tests=()

make tests
if [ "$?" == 0 ] ; then
    for test_file in build/bin/*_tests
    do
        echo "Running $test_file"
        $test_file
        if [ "$?" != 0 ] ; then
            any_tests_failed=true
            failed_tests=(${failed_tests[@]} ${test_file##*/})
        fi
    done

    if "$any_tests_failed" == true ; then
        echo -e "Failures in:\n\t${failed_tests[@]}"
    else
        echo "All tests complete without failures"
    fi
else
    echo "Compilation error, giving up"
fi

