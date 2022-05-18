/*
@number: 02
@name: Compiles: -Wall -Wextra -pedantic -Weffc++ -Wno-unused-parameter
@points: 4
@show_output: True
@type: script
@target: functions.cpp
*/
{
    script
    script_tests/compiles.sh
}

/*
@number: 03
@name: ret4 (happy paths)
@points: 7
@show_output: True
@type: unit
@target: functions.cpp 
*/
{
EXPECT_EQ(ret_4(), 4);
}
