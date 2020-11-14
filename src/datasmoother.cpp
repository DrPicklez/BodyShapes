include "datasmoother.h"

//--------------------------------------------------------------
int dataSmoother::smootherSetup(int nBuffer){
        int sum;
        int average;
        int counter = 0;
        int buffer[nBuffer];


            buffer[counter] = input;

            for(int i = 0; i < nBuffer; i ++){
                sum += buffer[i];
                return sum / nBuffer;
            }

            counter++;
        }
    }
//--------------------------------------------------------------
int dataSmoother::smoother(int input){

}
