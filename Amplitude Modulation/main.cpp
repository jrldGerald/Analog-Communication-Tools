#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <numbers>



class Signals{


public:

float amplitude[3]={0,0,0};      //various variables
std::string functionType[3];   // had to make these variable vectors to
float omega[3]={0,0,0};    //to cater for the multi-tone signal while
float pi=3.14159265f;     // using the same function for both other than writing a new one
 int NTones;//to keep track of the number of tones we have


void inputSignal(std::string signal){
    
    std::cout<<"Input the "<<signal<<" signal. Format:(A 'cos||sin' w) ";
std::string inputTheSignal;
std::getline(std::cin,inputTheSignal);  //user enters the signal here

points.clear(); //this ensures previous data is cleared and not drawn on top of it

//after some intense digging have to modify this same concept to take multi-tone 
//modulating signals as well. based on the same principle

if(signal=="modulatingSignal"){

    std::stringstream hugeStream(inputTheSignal); //this function will take care of the whole line 
// it'll split it into tones and then we can move ahead and split it again to get our values

std::string individualTones;  // the splited function will be kept in segments in this


int nTones=0;
while(std::getline(hugeStream,individualTones, '+') && nTones<3){

    std::stringstream toneStream(individualTones);

    if(!(toneStream>>amplitude[nTones] >> functionType[nTones]>>omega[nTones])){
        std::cerr<<"Invalid forma, make spaces in between\n";
    }
    
    




nTones++;
}
 NTones=nTones;

// display the full signal before processing
std::cout<<"\nYou entered......\n";
for(int i=0;i<NTones;i++){
    std::cout<<amplitude[i]<<" "<<functionType[i]<<" "<<omega[i]<<" + ";
    
}


}

//this is where the program will continue if it's a carrier signal
else{  // this is the best approach to make sure that that the data is not overwritten immediately after the modulating signal
std::stringstream ss(inputTheSignal);  //so this is where the the various
if(!(ss >> amplitude[0]>>functionType[0]>>omega[0])){   // Erorr  //variables will be extracted from the input using the stringstream function
    std::cerr<<"Invalid input\n";        
    
}
NTones=1;  // to draw only one tone
}

for(int i=0;i<windowWidth;i++){
    float t=(float)i/sampleFrequency;   //the basic math
    float yTotals=0;                      //this will add all the functions, even if it's a single tone
// the thing is, everything's been initialed to zero. so unless it's a multi-tone that it'll add 
                                 //it's fine actually
for(int j=0;j<NTones;j++){
    if(functionType[j] == "cos"){  
        yTotals+=amplitude[j]* std::cos(omega[j]*t);
    }
    else if(functionType[j] == "sin"){
        yTotals+=amplitude[j]* std::sin(omega[j]*t);
    }
}
    points.push_back(sf::Vector2f((float)i,(windowHeight/2.f)-yTotals));    //a vector

}


}

const unsigned int windowWidth=800;
const unsigned int windowHeight=400;             //seting my window size already
const float sampleFrequency=5000000.f;

std::vector<sf::Vector2f> points;      //the Vector2f function actually repressent a point on the screen which will be ideal to plot (x,y)
              

void displayWaveSignal(){
    //holding on calculating the frequency a bit frequency needs to be calculated for each band
    //float frequency=omega/ (2*pi);
sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight)," Signal");  //this function will basically create a window where the program will run
//std::cout<<"The Frequency is: "<<frequency<<std::endl;
sf::VertexArray wave(sf::LineStrip,points.size());   //the logic behind this is to point "point" towards wave which will link it to 
for(int i=0; i<points.size();i++){                  // look as if it was a joined line
    wave[i].position=points[i];
    wave[i].color=sf::Color::Magenta;
  
}

sf::View view=window.getDefaultView();
view.setCenter((windowWidth/2.f),(windowHeight/2));
window.setView(view);

while(window.isOpen()){                        //while this window is opened, the functions below will start to execute
                                               //unless it's closed from the inner while loop  
   sf::Event event;
    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();           
        }
        if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Up) view.zoom(0.9f);
                if(event.key.code==sf::Keyboard::Down) view.zoom(1.1f);

                if(event.key.code==sf::Keyboard::W) view.move(0,-10);
                if(event.key.code==sf::Keyboard::S) view.move(0,10);
                if(event.key.code==sf::Keyboard::A) view.move(-10,0);
                if(event.key.code==sf::Keyboard::D) view.move(10,0);

            } 

       
     
    }


window.clear(sf::Color::Red);
window.draw(wave);
window.setView(view);
window.display();
}
}






};



























int main(){


    Signals carrierSignal,modulatingSignal,modulatedSignal;

    carrierSignal.inputSignal("carrierSignal");
    //
    carrierSignal.displayWaveSignal();

    modulatingSignal.inputSignal("modulatingSignal");
    modulatingSignal.displayWaveSignal();





std::cout<<"\n The modulated signal will be displayed using the square law modulator\n";

float a=1.0f;
float b=0.1f;

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

//let's see if simple modulating index will work

sf::View modulatedView=window.getDefaultView();
modulatedView.setCenter((modulatedSignal.windowWidth/2.f),(modulatedSignal.windowHeight/2));

//float modulatingIndex = modulatingSignal.amplitude / carrierSignal.amplitude;
//std::cout<<"The modulating index is: "<<modulatingIndex;
while(window.isOpen()){
 sf::Event event;

    while(window.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            window.close();         
        }
         if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Up) modulatedView.zoom(0.9f);
                if(event.key.code==sf::Keyboard::Down) modulatedView.zoom(1.1f);
            }
    }

  window.clear(sf::Color::Black);

  window.draw(ModulatedWave);
  window.setView(modulatedView);
  window.display();







}





    return 0;
}