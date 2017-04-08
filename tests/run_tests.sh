#!/usr/bin/sh

any_tests_failed=false
failed_tests=()

cd build
cmake ../../
make

if [ "$?" == 0 ] ; then
    cp ./tests/*_tests/*_tests ./
    for test_file in ../build/*_tests
    do
        file_name=${test_file##*/}
        echo "Running $file_name"
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

