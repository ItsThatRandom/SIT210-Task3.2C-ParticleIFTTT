// ------------
// IFTTT - Terrarium Sunlight Notifications
// ------------

int phototransistor = A0;
int analogValue;
String start = "Terrarium is now in sunlight.";
String stop = "Terrarium is no longer in sunlight.";
String data;
bool sunlight = false;



void setup() {
    
    pinMode(phototransistor, INPUT);
    Serial.begin(9600);
    
}

void loop() {
    analogValue = analogRead(phototransistor);

    if (analogValue > 50 && sunlight == false)  {
        // Ensures 2 same consecutive results before publishing in case of poor reading/temporary light blockage. 
        if(data == start) {
            Particle.publish("Terrarium_Status", data, PRIVATE);
            sunlight = true;
        }
        data = start;
    }
    
    else if (analogValue < 50 && sunlight == true) {
        // Ensures 2 same consecutive results before publishing in case of poor reading/temporary light blockage. 
        if (data == stop) {
            Particle.publish("Terrarium_Status", data, PRIVATE);
            sunlight = false;
        }
        data = stop;
    }
    
    delay(2000); // Delay would be changed for the application to the specific scenario to a larger gap, but for demonstration purposes remains 2 seconds.
}