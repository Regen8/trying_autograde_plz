#include "Stress_ball.h"

// default constructor 
Stress_ball::Stress_ball() : color(Stress_ball_colors::red), size(Stress_ball_sizes::small) {
			int rngColor = rand()%4;
			int rngSize = rand()%3;
			
			if(rngColor == 0){
				color = Stress_ball_colors::red;
			} else if(rngColor == 1){
				color = Stress_ball_colors::blue;
			} else if (rngColor == 2){
				color = Stress_ball_colors::yellow;
			} else {
				color = Stress_ball_colors::green;
			}
			
			if(rngSize == 0){
				size = Stress_ball_sizes::small;
			} else if (rngSize == 1) {
				size = Stress_ball_sizes::medium;
			} else {
				size = Stress_ball_sizes::large;
			}
}

// constructor
Stress_ball::Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) : color(c), size(s)
{ }

Stress_ball_colors Stress_ball::get_color() const{
	return color;
}

Stress_ball_sizes Stress_ball::get_size() const{
	return size;
}

bool Stress_ball::operator==(const Stress_ball& sb){
			bool same = true;
			if(this->color != sb.color){ same = false; }
			if(this->size != sb.size) {same = false;}
			return same;
}

ostream& operator<<(ostream& os, const Stress_ball& sb){
string colorStr;
		string sizeStr;
		
		int colNum = static_cast<int>(sb.get_color());
		int sizeNum = static_cast<int>(sb.get_size());
		
		switch(colNum){
			case 0:
				colorStr = "red";
				break;
			case 1:
				colorStr = "blue";
				break;
			case 2:
				colorStr = "yellow";
				break;
			case 3:
				colorStr = "green";
				break;
			default:
				colorStr = "null";
				break;
		}
		
				switch(sizeNum){
			case 0:
				sizeStr = "small";
				break;
			case 1:
				sizeStr = "medium";
				break;
			case 2:
				sizeStr = "large";
				break;
			default:
				sizeStr = "undefined";
				break;
		}
		os << "(" << colorStr << "," << sizeStr << ")" << endl;
		return os;
}
