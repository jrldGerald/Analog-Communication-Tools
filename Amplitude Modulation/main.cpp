#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <numbers>



class Signals{


public:

float amplitude=0;      //various variables
std::string functionType;
float omega=0;
float pi=3.14159265f;



void inputSignal(std::string signal){
    
    std::cout<<"Input the "<<signal<<" signal. Format:(A 'cos||sin' w) ";
std::string inputTheSignal;
std::getline(std::cin,inputTheSignal);  //user enters the signal here

std::stringstream ss(inputTheSignal);  //so this is where the the various
if(!(ss>>amplitude>>functionType>>omega)){   // Erorr  //variables will be extracted from the input using the stringstream function
    std::cerr<<"Invalid input\n";        
    
}

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


}

const unsigned int windowWidth=800;
const unsigned int windowHeight=400;             //seting my window size already
const float sampleFrequency=5000000.f;

std::vector<sf::Vector2f> points;      //the Vector2f function actually repressent a point on the screen which will be ideal to plot (x,y)
              

void displayWaveSignal(){
    
    float frequency=omega/ (2*pi);
sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight)," Signal");  //this function will basically create a window where the program will run
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
}






};



























int main(){


    Signals carrierSignal,modulatingSignal,modulatedSignal;

    carrierSignal.inputSignal("carrier");
    //
    carrierSignal.displayWaveSignal();

    modulatingSignal.inputSignal("Modulating");
    modulatingSignal.displayWaveSignal();





std::cout<<"\n The modulated signal will be displayed using the square law modulator\n";

float a=1.0f;
float b=0.5f;

std::vector<sf::Vector2f> modulatedPoints;
for(int i=0;i<modulatedSignal.windowWidth;i++){
    float ct = (carrierSignal.windowHeight / 2.f) - carrierSignal.points[i].y;
    float mt = (modulatingSignal.windowHeight / 2.f) - modulatingSignal.points[i].y;
    

    float v2= a*ct + 2*b*ct*mt;
  modulatedPoints.push_back(sf::Vector2f((float)i,200.f-v2));
}




//now everything looks set, gotta display the modulated signal on a window
sf::VertexArray ModulatedWave(sf::LineStrip, modulatedPoints.size());

for(int i=0;i<modulatedPoints.size();i++){
    ModulatedWave[i].position=modulatedPoints[i];
    ModulatedWave[i].color = sf::Color::Red;
}


sf::RenderWindow window(sf::VideoMode(modulatedSignal.windowWidth,modulatedSignal.windowHeight),"Modulated Signal");


while(window.isOpen()){
 sf::Event event;

    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();
        }
    }

  window.clear(sf::Color::Black);

  window.draw(ModulatedWave);
  window.display();







}





    return 0;
}
