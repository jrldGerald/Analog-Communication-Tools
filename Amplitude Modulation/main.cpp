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





class multipleCalculation{    // hoping this will handle the calculations when its a multitone signal

public:

struct multipleTones{       // a struct to hold the data for each tone
    std::string functionType;
    double amplitude;
    double omega;
};

multipleTones carrier, tone1, tone2, tone3;  // defining the carrier and 3 tones

// now we need to take the input from the user and split it into individual tones
void getInput(){

std::cout<<"\nEnter the modulated signal in the format: Ac [ 1 + u1 func W1t + u2 func W2t + u3 func W2t ] func Wct. The 't' is not important\n ";
std::string input;
std::getline(std::cin, input);
std::cin.clear();  // clearing the input buffer

// now using the same logic as before, hoping it'll work out
std::stringstream hugeStream(input);
std::string firstSplit;  // this is the will split it at the ']' character

std::getline(hugeStream, firstSplit, ']');  // get the first part of the string
hugeStream >> carrier.functionType >> carrier.omega; // Carrier is what's left in hugeStream
std::string firstPart; // these will hold the two parts of the string
 // split at the ']' character


// now we have the two parts, we can process them





// now we need to process the first part to get the tones
// removing the 'Ac [ ' part

std::stringstream hugeStream2(firstSplit);
std::string gettingAc;  // getting the value of Ac from the firstPart
std::getline(hugeStream2, gettingAc, '['); 
std::stringstream toneStream2(gettingAc);
toneStream2 >> carrier.amplitude; // Get Ac from the part before '['

std::string insideTheBrackets;  // this will hold the inside of the brackets

std::getline(hugeStream2, insideTheBrackets);

// now we have the inside of the brackets, we can process it to get the tones

std::stringstream hugeStream3(insideTheBrackets);
std::string individualTones;

int i=0; // since it needs to loop through the bracket four times
int carrierConstant=1; // to skip the first part which is always 1
while(std::getline(hugeStream3,individualTones,'+') && i<4){
    
    std::stringstream toneStream3(individualTones);

    if(i==0){
        carrierConstant=1; // just to skip the first part
    }
    else if(i==1){
        toneStream3>>tone1.amplitude>>tone1.functionType>>tone1.omega;
    }
    else if(i==2){
        toneStream3>>tone2.amplitude>>tone2.functionType>>tone2.omega;
    }
    else if(i==3){
        toneStream3>>tone3.amplitude>>tone3.functionType>>tone3.omega;
    }
    else{
     std::cerr<<"Invalid input\n";     // do nothing
     std::cout<<"Exiting...\n";
     std::cin.ignore();
     exit(0);
    }

i++;
}



}


void display(){


    float u1 = tone1.amplitude;
    float u2 = tone2.amplitude;
    float u3 = tone3.amplitude;

    float modulationIndex = sqrt((u1*u1)+(u2*u2)+(u3*u3));
    float carrierPower =(carrier.amplitude*carrier.amplitude)/2.f;
    float sideBandPower = (carrierPower/2.f)*(modulationIndex*modulationIndex);
    float totalPower = carrierPower + sideBandPower;
    float efficiency = (sideBandPower/totalPower) * 100.f ;   


    std::cout<<"Just to be sure! this is the wave\n";  // displaying the wave
    std::cout<<"AM= "<<carrier.amplitude<<" [ 1 + "<<tone1.amplitude<<"*"<<tone1.functionType<<"*"<<tone1.omega<<"t + "<<tone2.amplitude<<"*"<<tone2.functionType<<"*"<<tone2.omega<<"t + "<<tone3.amplitude<<"*"<<tone3.functionType<<"*"<<tone3.omega<<"t ] * "<<carrier.functionType<<"*"<<carrier.omega<<"t\n";
    
    std::cout<<"\nThe various parameters are as follows:\n";
    std::cout<<"Carrier Frequency: "<<(carrier.omega/(2*3.14159))<<"\n";
    std::cout<<"There are 6 bands in total, 3 USBs and 3 LSBs\n";
    std::cout<<"Modulating index of the first tone: "<<tone1.amplitude<<"\n";
    std::cout<<"Modulating index of the second tone: "<<tone2.amplitude<<"\n";
    std::cout<<"Modulating index of the third tone: "<<tone3.amplitude<<"\n";
    std::cout<<"Total Modulating index: "<<modulationIndex<<"\n";
    std::cout<<"Carrier Power: "<<carrierPower<<" W\n";
    std::cout<<"Sideband Power: "<<sideBandPower<<" W\n";
    std::cout<<"Total Power: "<<totalPower<<" W\n";
    std::cout<<"Efficiency: "<<efficiency<<" %\n";

    // now on the various bands
    std::cout<<"The various bands are as follows:\n";
    std::cout<<"Frequency of USB1: "<<(carrier.omega/(2*3.14159))+(tone1.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of LSB1: "<<(carrier.omega/(2*3.14159))-(tone1.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of USB2: "<<(carrier.omega/(2*3.14159))+(tone2.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of LSB2: "<<(carrier.omega/(2*3.14159))-(tone2.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of USB3: "<<(carrier.omega/(2*3.14159))+(tone3.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of LSB3: "<<(carrier.omega/(2*3.14159))-(tone3.omega/(2*3.14159))<<"\n";

std::cin.clear();
std::cin.get();

}


multipleTones carrier1, tone1_1, tone2_1;  // defining the carrier and 2 tones for the 2 tone version
void getInput1(){   // manually create this to display the 2 tone version, since trying to make it dynamic will be tedious


std::cout<<"\nEnter the modulated signal in the format: Ac [ 1 + u1 func W1t + u2 func W2t ] func Wct. The 't' is not important\n ";
std::string input;
std::getline(std::cin, input);
std::cin.clear();  // clearing the input buffer

// now using the same logic as before, hoping it'll work out
std::stringstream hugeStream(input);
std::string firstSplit;  // this is the will split it at the ']' character

std::getline(hugeStream, firstSplit, ']');  // get the first part of the string
hugeStream >> carrier1.functionType >> carrier1.omega; // Carrier is what's left in hugeStream
std::string firstPart; // these will hold the two parts of the string
 // split at the ']' character


// now we have the two parts, we can process them





// now we need to process the first part to get the tones
// removing the 'Ac [ ' part

std::stringstream hugeStream2(firstSplit);
std::string gettingAc;  // getting the value of Ac from the firstPart
std::getline(hugeStream2, gettingAc, '['); 
std::stringstream toneStream2(gettingAc);
toneStream2 >> carrier1.amplitude; // Get Ac from the part before '['

std::string insideTheBrackets;  // this will hold the inside of the brackets

std::getline(hugeStream2, insideTheBrackets);

// now we have the inside of the brackets, we can process it to get the tones

std::stringstream hugeStream3(insideTheBrackets);
std::string individualTones;

int i=0; // since it needs to loop through the bracket four times
int carrierConstant=1; // to skip the first part which is always 1
while(std::getline(hugeStream3,individualTones,'+') && i<4){
    
    std::stringstream toneStream3(individualTones);

    if(i==0){
        carrierConstant=1; // just to skip the first part
    }
    else if(i==1){
        toneStream3>>tone1_1.amplitude>>tone1_1.functionType>>tone1_1.omega;
    }
    else if(i==2){
        toneStream3>>tone2_1.amplitude>>tone2_1.functionType>>tone2_1.omega;
    }
    else{
     std::cerr<<"Invalid input\n";     // do nothing
     std::cout<<"Exiting...\n";
     std::cin.ignore();
     exit(0);
    }

i++;
}



}




void display1(){           // manually create this to display the 2 tone version, since trying to make it dynamic will be tedious


    float u1_1 = tone1_1.amplitude;
    float u2_1 = tone2_1.amplitude;
    //float u3_1 = tone3_1.amplitude;

    float modulationIndex = sqrt((u1_1*u1_1)+(u2_1*u2_1));
    float carrierPower =(carrier1.amplitude*carrier1.amplitude)/2.f;
    float sideBandPower = (carrierPower/2.f)*(modulationIndex*modulationIndex);
    float totalPower = carrierPower + sideBandPower;
    float efficiency = (sideBandPower/totalPower) * 100.f ;   


    std::cout<<"Just to be sure! this is the wave\n";  // displaying the wave
    std::cout<<"AM= "<<carrier1.amplitude<<" [ 1 + "<<tone1_1.amplitude<<"*"<<tone1_1.functionType<<"*"<<tone1_1.omega<<"t + "<<tone2_1.amplitude<<"*"<<tone2_1.functionType<<"*"<<tone2_1.omega<<"t ] * "<<carrier1.functionType<<"*"<<carrier1.omega<<"t\n";
    
    std::cout<<"\nThe various parameters are as follows:\n";
    std::cout<<"Carrier Frequency: "<<(carrier1.omega/(2*3.14159))<<"\n";
    std::cout<<"There are 4 bands in total, 2 USBs and 2 LSBs\n";
    std::cout<<"Modulating index of the first tone: "<<tone1_1.amplitude<<"\n";
    std::cout<<"Modulating index of the second tone: "<<tone2_1.amplitude<<"\n";
    //std::cout<<"Modulating index of the third tone: "<<tone3_1.amplitude<<"\n";
    std::cout<<"Total Modulating index: "<<modulationIndex<<"\n";
    std::cout<<"Carrier Power: "<<carrierPower<<" W\n";
    std::cout<<"Sideband Power: "<<sideBandPower<<" W\n";
    std::cout<<"Total Power: "<<totalPower<<" W\n";
    std::cout<<"Efficiency: "<<efficiency<<" %\n";

    // now on the various bands
    std::cout<<"The various bands are as follows:\n";
    std::cout<<"Frequency of USB1: "<<(carrier.omega/(2*3.14159))+(tone1.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of LSB1: "<<(carrier.omega/(2*3.14159))-(tone1.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of USB2: "<<(carrier.omega/(2*3.14159))+(tone2.omega/(2*3.14159))<<"\n";
    std::cout<<"Frequency of LSB2: "<<(carrier.omega/(2*3.14159))-(tone2.omega/(2*3.14159))<<"\n";
    //std::cout<<"Frequency of USB3: "<<(carrier.omega/(2*3.14159))+(tone3.omega/(2*3.14159))<<"\n";
    //std::cout<<"Frequency of LSB3: "<<(carrier.omega/(2*3.14159))-(tone3.omega/(2*3.14159))<<"\n";

std::cin.clear();
std::cin.get();

}





};







class Calculation{

// i want to find a new approach for this to work out using my own basic logic and understanding

public:

// want to use the same variable name for all my functions so a class or a struct will do this perfectly
struct Tone{
    float amplitude=0.0f;
    float omega=0.0f;
    std::string typeOfFunction;

};

// made the first object but didn't make secondTone an object because i am still going to extract again
Tone firstTone,secondTone;
// so the firstTone will represent the carrier signal while the secondTone will represent the modulating signal
// i think in short form, kinda make sense
void getModulatedSignal(){

    std::string signal;
    std::cout<<"Enter the modulated signal to proceed: Format: A sin Wct + u sin Wmt * sin Wct . Of course! the 't' isn't important here\n";
    std::getline(std::cin,signal);

    //now is the time to first split in segments and later split again

    std::stringstream hugeStream(signal);

    std::string individualTones;

    int i=0;
std::string secondToneAsAString;

    while(std::getline(hugeStream, individualTones, '+') && i<2){

        std::stringstream toneStream(individualTones);

        if(i==0){
            toneStream>>firstTone.amplitude>>firstTone.typeOfFunction>>firstTone.omega;
        }

        else if(i==1){
            secondToneAsAString=individualTones;  // i have no idea but i have an idea of what am doing , huh?
        }

        i++;
    }

    //now, i want to use the same logic to geteverything in here
    std::string sideBand;

    std::stringstream hugeStream2(secondToneAsAString);
    int j=0;  // it's just like repeating the same logic over and over 
    // seems tedious and unproffesional but , the logic is fine and easier to implement

    while(std::getline(hugeStream2, sideBand, '*') && j<2){

        std::stringstream toneStream2(sideBand);
               //this will handle the first part of the sideband, the amplitude in here will represent the modulating index
        if(j==0){
            toneStream2>>secondTone.amplitude>>secondTone.typeOfFunction>>secondTone.omega;
        }

        // looking at the formula this is not relevant since we'll need what's only above
        // so i don't know yet if j==1 will cause a problem or not
        //it's set!!!!

        // okey dokey, after consulting gemini, it'll be best if i still keep the j==1 as a junk and verify if it matches the carrier
        if(j==1){
            std::string checkCarrier; float notUseful;
            toneStream2>>checkCarrier>>notUseful; // just to make sure it matches the carrier signal
            if(checkCarrier!=firstTone.typeOfFunction){
                std::cerr<<"The carrier signal in the sideband doesn't match the initial carrier signal\n";
                if(notUseful!=firstTone.omega){
                    std::cerr<<"The omega of the carrier signal in the sideband doesn't match the initial carrier signal\n";
            }
        }
        }

        j++;
    }




}







void display(){

    std::cout<<"\n For better results, the signal you entered is: \n";
    std::cout<<firstTone.amplitude<<"*"<<firstTone.typeOfFunction<<"("<<firstTone.omega<<"t) + ";
    std::cout<<secondTone.amplitude<<"*"<<secondTone.typeOfFunction<<"("<<secondTone.omega<<"t) * "<<firstTone.typeOfFunction<<"("<<firstTone.omega<<"t))\n";
}


//now to calculate the important parameters
void calculatedParameters(){
    float modulatingIndex=secondTone.amplitude;
    float carrierFrequency=firstTone.omega/(2*3.14159265f);
    float modulatingFrequency=secondTone.omega/(2*3.14159265f);
    float USB=carrierFrequency + modulatingFrequency;
    float LSB=carrierFrequency - modulatingFrequency;
    float carrierPower= (firstTone.amplitude * firstTone.amplitude) /2.f;
    float sideBandPower= (carrierPower/4 )* (modulatingIndex * modulatingIndex);
    float totalPower= carrierPower + sideBandPower;
    float efficiency= (sideBandPower / totalPower) *100.f;
    
    std::cout<<"\n The calculated parameters are as follows:\n";
    std::cout<<"Modulating Index: "<<modulatingIndex<<"\n";
    std::cout<<"Carrier Frequency: "<<carrierFrequency<<" Hz\n";
    std::cout<<"Modulating Frequency: "<<modulatingFrequency<<" Hz\n";
    std::cout<<"Upper Side Band Frequency: "<<USB<<" Hz\n";
    std::cout<<"Lower Side Band Frequency: "<<LSB<<" Hz\n";
    std::cout<<"Carrier Power: "<<carrierPower<<" W\n"; 
    std::cout<<"Side Band Power: "<<sideBandPower<<" W\n";
    std::cout<<"Total Power: "<<totalPower<<" W\n";
    std::cout<<"Efficiency: "<<efficiency<<" %\n";


    std::cin.clear();
    std::cin.get();

}






};






















int main(){


std::cout<<"What do you wanna do?,\n";
std::cout<<"1. Visualize a carrier and a modulating signal and their modulated signal\n";
std::cout<<"2. Calculate \n";
int choice;
std::cin>>choice;
std::cin.ignore();


if(choice==1){
    
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




}


else if(choice==2){
    std::cout<<"What is the format of the signal.\n";
    std::cout<<"1. With a single tone modulating signal\n";
    std::cout<<"2.  With a multi tone modulating signal\n";
    int choice;
    std::cin>>choice;
    std::cin.ignore();

    if(choice==1){
        Calculation calculation;
    calculation.getModulatedSignal();
    calculation.display();
    calculation.calculatedParameters();

    }
    else if(choice==2){
        std::cout<<"What's the format of the AM wave: ?\n";
        std::cout<<"1. Ac [ 1 + u1 func W1t + u2 func W2t ] func Wct\n";
        std::cout<<"2. Ac [ 1 + u1 func W1t + u2 func W2t + u3 func W3t ] func Wct  \n";
        int ichoice;
        std::cin>>ichoice;
        std::cin.ignore();
        if(ichoice==1){
            multipleCalculation signal;
            signal.getInput1();
            signal.display1();
        }
        else if(ichoice==2){
            multipleCalculation signal;
        signal.getInput();
        signal.display();
        }
        else{
            std::cerr<<"Invalid choice\n";
            std::cout<<"Exiting program...\n";
            
            std::cin.get();

            
        }
        
        

    }
    else{
        std::cerr<<"Invalid choice\n";
        std::cout<<"Exiting program...\n";
        
        std::cin.get();

        
    }


    

}

else{
    std::cerr<<"Invalid choice\n";
    std::cout<<"Exiting program...\n";
    
    std::cin.get();

    
}








    return 0;
}
