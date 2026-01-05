#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <numbers>


void carrierSignal(){
    std::cout<<"Input the signal. Format:(A 'cos||sin' w) ";
std::string inputCarrierSignal;
std::getline(std::cin,inputCarrierSignal);  //user enters the signal here

float amplitude=0;      //various variables
std::string functionType;
float omega=0;


std::stringstream ss(inputCarrierSignal);  //so this is where the the various
if(!(ss>>amplitude>>functionType>>omega)){   // Erorr  //variables will be extracted from the input using the stringstream function
    std::cerr<<"Invalid input\n";        
    
}
float pi=3.14159265f;
float frequency=omega/ (2*pi);

const int windowWidth=800;
const int windowHeight=400;             //seting my window size already
const float sampleFrequency=1000000.f;

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
}



void modulatingSignal(){
                           //so this will also use the same aproach. a well 
    std::cout<<"Enter the modulating/message signal\n";  //class can be used to make this 
    std::string inputMessageSignal;                     //very simple and easier
    std::getline(std::cin,inputMessageSignal);

    float amplitude=0;
    std::string functionType;
    float omega=0;

    //extracting the three components from the buffer

    std::stringstream ss(inputMessageSignal);
    if(!(ss>>amplitude>>functionType>>omega)){                //if the function doesn't extract it in this manner, then it's an error
        std::cerr<<"wrong input, checkout the format well\n";  //incase
    }

    //working on the math now

    const int windowWidth=600;
    const int windowHeight=500;
    float sampleFrequency=2000.f;

    std::vector <sf::Vector2f> points2;
    points2.reserve(600);
    
    for(int i=0;i<windowWidth;i++){
        float t=(float)i / sampleFrequency;
        float y=0;

        if(functionType=="cos"){
            y=amplitude* std::cos(omega*t);
        }
        else if(functionType=="sin"){
            y=amplitude*std::sin(omega*t);
        }

        //now, since the base values are set, the subsequent values must also be added
        points2.push_back(sf::Vector2f((float)i,(windowHeight/2.f)-y));

    }
         //getting a line to be drawn between two different point2 elements for all the elements
    sf::VertexArray wave2(sf::LineStrip,points2.size());

    //since points2 cannot simply be drawn out easily, it should point towards wave2
    //wave2 is just housing it
     for(int i=0;i<points2.size();i++){
        wave2[i].position=points2[i];
        wave2[i].color=sf::Color::Cyan;
     }


   sf::RenderWindow window(sf::VideoMode({windowWidth,windowHeight}),"Modulating signal");
   
   while(window.isOpen()){

      sf::Event event;

         while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            }
         }

         window.clear(sf::Color::Green);
         window.draw(wave2);
         window.display();




   }


}









int main(){

carrierSignal();
modulatingSignal();
std::cout<<"\n The modulated signal will be displayed using the square law modulator\n";

float a=1.0f;
float b=0.5f;

for(int i=0;i<windowWidth;i++){
    float ct=inputCarrierSignal;
    float mt=inputMessageSignal;
    std::vector<sf::Vector2f> modulatedPoints;

    float v2= a*inputCarrierSignal + 2*b*inputCarrierSignal*inputMessageSignal;
  modulatedPoints.push_back(sf::Vector2f((float)i,(windowWidth/2.f)-v2));
}




    return 0;
}
