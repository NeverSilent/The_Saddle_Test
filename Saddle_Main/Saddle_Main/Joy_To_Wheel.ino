/* 
 * Method to turn Joystick input into motor output
 * Will proly do the work here and then copy and paste back to the main
 * 2021.08.31
 * The Saloon
 * Alex Lamey
 * Eric Suszerk
 * J.D. Herlehy
 * Octavio Diaz
 */

//define the axis inputs
#define XAxis 4
#define YAxis 14

void setup() {
  //delete this when debuging is done
  Serial.begin(9600);

  //set up for axis
  pinMode(INPUT, XAxis);
  pinMode(INPUT, YAxis);

}

void loop() {
  //The following is the pesudocode for the conversion
  //Have to scale the 16bit input to 0 -> 200 and then subtract 100 then invert it
  /*
    Get X and Y from the Joystick, do whatever scaling and calibrating you need to do based on your hardware.
    Invert X
    Calculate R+L (Call it V): V =(100-ABS(X)) * (Y/100) + Y
    Calculate R-L (Call it W): W= (100-ABS(Y)) * (X/100) + X
    Calculate R: R = (V+W) /2
    Calculate L: L= (V-W)/2
    Do any scaling on R and L your hardware may require.
    Send those values to your Robot.
    Go back to 1
  */
}
