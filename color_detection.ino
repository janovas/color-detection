#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
#define max_size  20
int index = 0;

float R_component = 0;
float G_component = 0;
float B_component = 0;

float R_componentRAW[max_size] = {0};
float G_componentRAW[max_size] = {0};
float B_componentRAW[max_size] = {0};

float LPF(float b, float n, float o) {
  return o + b * (n - o);
}
void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaeling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(115200);
}

void loop() {
  index ++ ;
  if (index == max_size)index = 0;

  // Seting red filtered  photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(10);
  // Reading the output frequency
  R_componentRAW[index] =(float)pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  R_componentRAW[index] = map(R_componentRAW[index], 29,310,255,0);
  // Printing the value on the serial monitor
  //  Serial.print("R="); // Printing Name
  //  Serial.print(R_component); //Printing RED color frequency
  //  Serial.print(" ");
  delay(10);

  // Seting red filtered  photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(10);
  // Reading the output frequency
  G_componentRAW[index] =(float)pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  G_componentRAW[index]  = map(G_componentRAW[index] , 30,323,255,0);
  // Printing the value on the serial monitor
  //  Serial.print("G="); // Printing Name
  //  Serial.print(G_component); //Printing RED color frequency
  //  Serial.print(" ");
  delay(10);

  // Seting red filtered  photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(10);
  // Reading the output frequency
  B_componentRAW[index] = (float)pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  B_componentRAW[index] = map(B_componentRAW[index], 21,226,255,0);
  // Printing the value on the serial monitor
  //  Serial.print("B="); // Printing Name
  //  Serial.print(B_component); //Printing RED color frequency
  //  Serial.println(" ");
  delay(10);

  R_component = 0;
  G_component = 0;
  B_component = 0;

  for (int i = 0; i < max_size; i++ ) {
    R_component += R_componentRAW[i];
    G_component += G_componentRAW[i];
    B_component += B_componentRAW[i];
  }
  R_component /= max_size;
  G_component /= max_size;
  B_component /= max_size;
  Serial.print(400); Serial.print(" "); // Printing Name
  Serial.print(0); Serial.print(" "); // Printing Name
  Serial.print(R_component); Serial.print(" "); // Printing Name
  Serial.print(G_component); Serial.print(" "); // Printing Name
  Serial.print(B_component); //Printing RED color frequency
  Serial.println(" ");

}
