#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <numbers>


int main(){

std::cout<<"Input the signal. Format:(A 'cos||sin' w) ";
std::string inputCarrierSignal;
std::getline(std::cin,inputCarrierSignal);  //user enters the signal here

float amplitude=0;      //various variables
std::string functionType;
float omega=0;


std::stringstream ss(inputCarrierSignal);  //so this is where the the various
if(!(ss>>amplitude>>functionType>>omega)){   // Erorr  //variables will be extracted from the input using the stringstream function
    std::cerr<<"Invalid input\n";        
    return -1;
}
float pi=3.14159265f;
float frequency=omega/ (2*pi);

const int windowWidth=800;
const int windowHeight=400;             //seting my window size already
const float sampleFrequency=100.f;

std::vector<sf::Vector2f> points;      //the Vector2f function actually repressent a point on the screen which will be ideal to plot (x,)
points.reserve(800);                 //best if the gpu allocate some bit before hand


for(int i=0;i<windowWidth;i++){
    float t=(float)i/sampleFrequency;   //the basic math
    float y=0;                          //it's advisable to do this outside that while loop

    if(functionType == "cos"){
        y=amplitude* std::cos(omega*t);
    }
    else if(functionType=="sin"){
        y=amplitude* std::sin(omega*t);
    }

    points.push_back(sf::Vector2f((float)i,(windowHeight/2.f)-y));    //a vector

}


sf::RenderWindow window(sf::VideoMode({windowWidth,windowHeight}),"Carrier Signal");  //this function will basically create a window where the program will run
std::cout<<"The Frequency is: "<<frequency<<std::endl;
sf::VertexArray wave(sf::LineStrip,points.size());   //the logic behind this is to point "point" towards wave which will link it to 
for(int i=0; i<points.size();i++){                  // look as if it was a joined line
    wave[i].position=points[i];
    wave[i].color=sf::Color::Magenta;
  
}

while(window.isOpen()){                        //while this window is opened, the functions below will start to execute
                                               //unless it's closed from the inner while loop  
   sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }

       
     
    }


window.clear(sf::Color::Red);
window.draw(wave);
window.display();




}

    return 0;
}
