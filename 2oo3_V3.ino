int Vote[3]; //Stage one of voting. Each index represents a result of 2 values being compared 
float Value; //Is the value of the results of the votes. In this case, is the mean of the 3 votes
int VoteLen = sizeof(Vote) / sizeof(Vote[0]); //Votes length

void setup() 
{
  Serial.begin(9600);
  //These pins are variable to the set up of the Arduino. 
  //The pins MUST be consecutive and the for loop needs to be mirrored to the pins 
  //(1st for loop starting on the inital pin, both for loops ending on last pin + 1)
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  //These lines is to be changed to test the code.
  //Used to test the different possible combinations to see if 2oo3 works as intended
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  
}

//1 Out of 2 
//Optimistic voting on which sensor to choose from
//NOTE: Inside One out of Two (OooT) function, the voting system can be different to what is inside this function
//NOTE: This code uses optimistic voting, can use a different voting system
int OooT(int Sens1, int Sens2)
{
  if(Sens1 <= Sens2)
  {
    return Sens2;
  }
  else 
  {
    return Sens1;
  }
}

//Initial Voting
//This this code will go through the pins, and compare the pins to one another with all cominations
//Combinations of for loop: 
//  for loop1 - iteration 1, for loop2 - iteration 1:  PIN 1 --> PIN 2
//  for loop1 - iteration 1, for loop2 - iteration 2:  PIN 1 --> PIN 3
//  for loop1 - iteration 2, for loop2 - iteration 1:  PIN 2 --> PIN 3
void Vote1()
{
  int count = 0;
  for (int i = 11; i < 14; i++)
  {
    for (int i2 = i+1; i2 < 14; i2++)
    {
      Vote[count] = OooT(digitalRead(i), digitalRead(i2));
      count++;
    }
  }
}

//Calculates value via mean
//NOTE: 
//Does not need to be a mean average and is up for debate on how value is calculated
float Output() 
{
  Value = 0;
  for (int i = 0; i < VoteLen; i++)
  {
    Value += Vote[i];
  }
  Value /= VoteLen; 

  return Value;
}

void loop() 
{
  //Iterations
  Vote1();
  Value = Output();

  //Testing
  Serial.println("Start");
  Serial.println(Vote[0]);
  Serial.println(Vote[1]);
  Serial.println(Vote[2]);
  Serial.println(Value);
  Serial.println("End");
  delay(500);
}
