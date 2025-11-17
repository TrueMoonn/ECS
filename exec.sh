#!/bin/bash
if [[ $1 == "--build" || $1 == "-b" ]]
then
    echo "------------BUILD"------------
    if [ ! -d "./build/" ]
    then
        mkdir ./build/ && cd ./build/
        cmake ..
        cd ..
    fi
    cmake --build ./build/
    echo "------------END------------"

elif [[ $1 == "--re-build" || $1 == "-rb" ]]
then
    clear
    echo "------------RE-BUILD"------------
    rm -rf ./build/ ./*.a
    mkdir ./build/ && cd ./build/
    cmake ..
    cmake --build .
    cd ..
    echo "------------END------------"

elif [[ $1 == "--build-tests" || $1 == "-t" ]]
then
    clear
    echo "------------TESTS------------"
    rm -rf ./build/ ./*.a
    mkdir ./build/ && cd ./build/
    cmake .. -DENABLE_ECS_TESTS=ON -DENABLE_ECS_COVERAGE=ON
    cmake --build .
    ctest --output-on-failure
    gcovr --root .. \
        --filter '../src/.*' \
        --filter '../include/.*' \
        --html --html-details -o coverage.html
    xdg-open coverage.html
    cd ..
    echo "------------END------------"

elif [[ $1 == "--debug-build" || $1 == "-d" ]]
then
    echo ""------------DEBUG"------------"
    rm -rf ./build/ ./*.a
    mkdir ./build/ && cd ./build/
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build . -v
    cd ..
    echo "------------END------------"

elif [[ $1 == "--clear" || $1 == "-c" ]]
then
    rm -rf ./build/ ./*.a
    clear

elif [[ $1 == "--style-checker" || $1 == "-cs" ]]
then
    echo "------------CS CHECKER------------"
    rm -rf ./build/
    pip install cpplint
    cpplint --recursive .
    echo "------------END------------"
else
    echo "Missing flag"
fi