/*
@number: 1
@name: Compiles: -Wall -Wextra -pedantic -Weffc++ -Wno-unused-parameter
@points: 1
@show_output: True
@type: script
@target: stress_ball.cpp
*/
{
    script
    script_tests/compiles.sh
}

/*
@number: 2
@name: Default Constructor
@points: 5
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    Stress_ball sb;
    Stress_ball sb1 = Stress_ball();
    Stress_ball sb2;
    Stress_ball *sb3 = new Stress_ball();

    if(sizeof(sb)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb) == 0)
    ASSERT_TRUE(false);

    if(sizeof(sb1)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb1)==0)
    ASSERT_TRUE(false);

    if(sizeof(sb2)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb2)==0)
    ASSERT_TRUE(false);

    if(sizeof(sb3)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb3)==0)
    ASSERT_TRUE(false);
}

/*
@number: 3
@name: Parameterized Constructor
@points: 4
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    Stress_ball sb(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb1 = Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::small);
    Stress_ball sb2(Stress_ball_colors::green, Stress_ball_sizes::medium);
    Stress_ball *sb3 = new Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large);

    if(sizeof(sb)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb)==0)
    ASSERT_TRUE(false);

    if(sizeof(sb1)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb1)==0)
    ASSERT_TRUE(false);

    if(sizeof(sb2)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb2)==0)
    ASSERT_TRUE(false);

    if(sizeof(sb3)!=0)
    ASSERT_TRUE(true);
    if(sizeof(sb3)==0)
    ASSERT_TRUE(false);
}

/*
@number: 4
@name: Function get_color()
@points: 2
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    Stress_ball sb(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb1 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium);
    Stress_ball *sb2 = new Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::large);
    Stress_ball *sb5 = new Stress_ball();
    Stress_ball sb4 = Stress_ball();
    Stress_ball sb3;

    if(sb.get_color() == Stress_ball_colors::red || sb.get_color() == Stress_ball_colors::blue || sb.get_color() == Stress_ball_colors::yellow || sb.get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if( !(sb.get_color() == Stress_ball_colors::red || sb.get_color() == Stress_ball_colors::blue || sb.get_color() == Stress_ball_colors::yellow || sb.get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);

    if(sb1.get_color() == Stress_ball_colors::red || sb1.get_color() == Stress_ball_colors::blue || sb1.get_color() == Stress_ball_colors::yellow || sb1.get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if(!(sb1.get_color() == Stress_ball_colors::red || sb1.get_color() == Stress_ball_colors::blue || sb1.get_color() == Stress_ball_colors::yellow || sb1.get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);

    if(sb2->get_color() == Stress_ball_colors::red || sb2->get_color() == Stress_ball_colors::blue || sb2->get_color() == Stress_ball_colors::yellow || sb2->get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if(!(sb2->get_color() == Stress_ball_colors::red || sb2->get_color() == Stress_ball_colors::blue || sb2->get_color() == Stress_ball_colors::yellow || sb2->get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);

    if(sb3.get_color() == Stress_ball_colors::red || sb3.get_color() == Stress_ball_colors::blue || sb3.get_color() == Stress_ball_colors::yellow || sb3.get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if(!(sb3.get_color() == Stress_ball_colors::red || sb3.get_color() == Stress_ball_colors::blue || sb3.get_color() == Stress_ball_colors::yellow || sb3.get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);

    if(sb4.get_color() == Stress_ball_colors::red || sb4.get_color() == Stress_ball_colors::blue || sb4.get_color() == Stress_ball_colors::yellow || sb4.get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if(!(sb4.get_color() == Stress_ball_colors::red || sb4.get_color() == Stress_ball_colors::blue || sb4.get_color() == Stress_ball_colors::yellow || sb4.get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);

    if(sb5->get_color() == Stress_ball_colors::red || sb5->get_color() == Stress_ball_colors::blue || sb5->get_color() == Stress_ball_colors::yellow || sb5->get_color() == Stress_ball_colors::green)
    ASSERT_TRUE(true);
    if(!(sb5->get_color() == Stress_ball_colors::red || sb5->get_color() == Stress_ball_colors::blue || sb5->get_color() == Stress_ball_colors::yellow || sb5->get_color() == Stress_ball_colors::green))
    ASSERT_TRUE(false);
}

/*
@number: 5
@name: Function get_size()
@points: 2
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    Stress_ball sb(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium);
    Stress_ball *sb2 = new Stress_ball(Stress_ball_colors::yellow, Stress_ball_sizes::large);
    Stress_ball *sb5 = new Stress_ball();
    Stress_ball sb4 = Stress_ball();
    Stress_ball sb3;

    if(sb.get_size() == Stress_ball_sizes::small || sb.get_size() == Stress_ball_sizes::medium || sb.get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb.get_size() == Stress_ball_sizes::small || sb.get_size() == Stress_ball_sizes::medium || sb.get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);

    if(sb1.get_size() == Stress_ball_sizes::small || sb1.get_size() == Stress_ball_sizes::medium || sb1.get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb1.get_size() == Stress_ball_sizes::small || sb1.get_size() == Stress_ball_sizes::medium || sb1.get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);

    if(sb2->get_size() == Stress_ball_sizes::small || sb2->get_size() == Stress_ball_sizes::medium || sb2->get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb2->get_size() == Stress_ball_sizes::small || sb2->get_size() == Stress_ball_sizes::medium || sb2->get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);

    if(sb3.get_size() == Stress_ball_sizes::small || sb3.get_size() == Stress_ball_sizes::medium || sb3.get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb3.get_size() == Stress_ball_sizes::small || sb3.get_size() == Stress_ball_sizes::medium || sb3.get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);

    if(sb4.get_size() == Stress_ball_sizes::small || sb4.get_size() == Stress_ball_sizes::medium || sb4.get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb4.get_size() == Stress_ball_sizes::small || sb4.get_size() == Stress_ball_sizes::medium || sb4.get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);

    if(sb5->get_size() == Stress_ball_sizes::small || sb5->get_size() == Stress_ball_sizes::medium || sb5->get_size() == Stress_ball_sizes::large)
    ASSERT_TRUE(true);
    if(!(sb5->get_size() == Stress_ball_sizes::small || sb5->get_size() == Stress_ball_sizes::medium || sb5->get_size() == Stress_ball_sizes::large))
    ASSERT_TRUE(false);
}

/*
@number: 6
@name: Test Case 5 - Operator ==
@points: 5
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    Stress_ball sb(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium);
    Stress_ball *sb2 = new Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb3 = Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::medium);

    if(sb == sb)
    ASSERT_TRUE(true);
    if(!(sb == sb))
    ASSERT_TRUE(false);

    if(sb == *sb2)
    ASSERT_TRUE(true);
    if(!(sb == *sb2))
    ASSERT_TRUE(false);

    if(sb == sb1)
    ASSERT_TRUE(false);
    if(!(sb == sb1))
    ASSERT_TRUE(true);

    if(sb1 == *sb2)
    ASSERT_TRUE(false);
    if(!(sb1 == *sb2))
    ASSERT_TRUE(true);

    if(sb3 == *sb2)
    ASSERT_TRUE(false);
    if(!(sb3 == *sb2))
    ASSERT_TRUE(true);

    if(sb1 == sb3)
    ASSERT_TRUE(false);
    if(!(sb1 == sb3))
    ASSERT_TRUE(true);
}

/*
@number: 7
@name: Test Case 6 - Operator <<
@points: 5
@show_output: True
@type: unit
@target: stress_ball.cpp
*/
{
    using namespace std;

    Stress_ball sb(Stress_ball_colors::red, Stress_ball_sizes::small);
    Stress_ball sb1 = Stress_ball(Stress_ball_colors::blue, Stress_ball_sizes::medium);
    Stress_ball *sb2 = new Stress_ball(Stress_ball_colors::red, Stress_ball_sizes::small);
    std::stringstream buffer;
    buffer<<sb;

    if(buffer.str() == "(red, small)" || buffer.str() == "(red,small)" || (buffer.str().find("red") != std::string::npos && buffer.str().find("small") != std::string::npos))
    {
        string s=buffer.str();
        char cstr[s.size() + 1];
        strcpy(cstr, s.c_str());
        printf("%s",cstr);
        ASSERT_TRUE(true);
    } 
    else
    {
        ASSERT_TRUE(false);
    }

    std::stringstream buffer1;
    buffer1<<sb1;
    if(buffer1.str() == "(blue, medium)" || buffer1.str() == "(blue,medium)" || (buffer1.str().find("blue") != std::string::npos && buffer1.str().find("medium") != std::string::npos))
    {
        string s=buffer1.str();
        char cstr[s.size() + 1];
        strcpy(cstr, s.c_str());
        printf("%s",cstr);
        ASSERT_TRUE(true);
    }
    else
    {
        ASSERT_TRUE(false);
    }

    std::stringstream buffer2;
    buffer2<<*sb2;
    if(buffer2.str() == "(red, small)" || buffer2.str() == "(red,small)" || (buffer2.str().find("red") != std::string::npos && buffer2.str().find("small") != std::string::npos))
    {
        string s=buffer2.str();
        char cstr[s.size() + 1];
        strcpy(cstr, s.c_str());
        printf("%s",cstr);
        ASSERT_TRUE(true);
    }
    else
    {
        ASSERT_TRUE(false);
    }
}

/*
@number: 999
@name: Compiles: final submission
@points: 1
@show_output: True
@type: script
@target: stress_ball.cpp
*/
{
    script
    script_tests/final_submission.sh
}