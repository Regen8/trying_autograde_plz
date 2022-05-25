#include <iostream>
#include <string>

using namespace std;
	
	//part a
	enum class Stress_ball_colors {red, blue, yellow, green};
	enum class Stress_ball_sizes {small, medium, large};
	
	class Stress_ball{
		private: //part a
			Stress_ball_colors color;
			Stress_ball_sizes size;
		
		public: 
		
		//part a
		Stress_ball() : color(Stress_ball_colors::red), size(Stress_ball_sizes::small) {
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
		
		//part b
		Stress_ball(Stress_ball_colors c, Stress_ball_sizes s) : color(c), size(s){}
		
		//part c
		Stress_ball_colors get_color() const{
			return color;
		}
		
		//part d
		Stress_ball_sizes get_size() const{
			return size;
		}
		
		//part e
		bool operator==(const Stress_ball& sb2){
			bool same = true;
			if(this->color != sb2.color){ same = false; }
			if(this->size != sb2.size) {same = false;}
			return same;
		}
	};

//part f
ostream& operator<<(ostream& o, const Stress_ball& sb) {
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
		o << "(" << colorStr << "," << sizeStr << ")" << endl;
		return o;
	}