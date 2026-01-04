#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <numbers>


int main(){

std::cout<<"Input the signal. Format:(A 'cos||sin' w) ";
std::string inputCarrierSignal;
std::getline(std::cin,inputCarrierSignal);

float amplitude=0;
std::string functionType;
float omega=0;


std::stringstream ss(inputCarrierSignal);
if(!(ss>>amplitude>>functionType>>omega)){
    std::cerr<<"Invalid input\n";
    return -1;
}
float pi=3.14159265f;
float frequency=omega/ (2*pi);

const int windowWidth=800;
const int windowHeight=400;
const float sampleFrequency=100.f;

std::vector<sf::Vector2f> points;
points.reserve(800);


for(int i=0;i<windowWidth;i++){
    float t=(float)i/sampleFrequency;
    float y=0;

    if(functionType == "cos"){
        y=amplitude* std::cos(omega*t);
    }
    else if(functionType=="sin"){
        y=amplitude* std::sin(omega*t);
    }

    points.push_back(sf::Vector2f((float)i,(windowHeight/2.f)-y));

}


sf::RenderWindow window(sf::VideoMode({windowWidth,windowHeight}),"Carrier Signal");
std::cout<<"The Frequency is: "<<frequency<<std::endl;
sf::VertexArray wave(sf::LineStrip,points.size());
for(int i=0; i<points.size();i++){
    wave[i].position=points[i];
    wave[i].color=sf::Color::Magenta;
  
}

while(window.isOpen()){

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