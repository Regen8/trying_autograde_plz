/*
@number: 1
@name: Compiles: -Wall -Wextra -pedantic -Weffc++ -Wno-unused-parameter
@points: 4
@show_output: True
@type: script
@target: main.cpp
*/
{
    script
    script_tests/compiles.sh
}

/*
@number: 2
@name: Compiles: -std=c++17 -Wall -Wextra -pedantic -Weffc++
@points: 4
@show_output: True
@type: unit
@target: function.cpp
*/
{
    EXPECT_EQ(ret_4(), 4);
}

/*
@number: 3
@name: Compiles: -std=c++17 -Wall -Wextra -pedantic -Weffc++
@points: 4
@show_output: True
@type: i/o
@target: main.cpp
*/
{
    input
    io_tests/input.txt
    output
    io_tests/output.txt
}

/*
@number: 4
@name: Compiles: -std=c++17 -Wall -Wextra -pedantic -Weffc++
@points: 4
@show_output: True
@type: script
@target: main.cpp
*/
{
    script
    script_tests/final_submission.sh
}

/*
@number: 5
@name: End of tests
@points: 0
@show_output: True
@type: eot
@target: main.cpp 
*/
{
}