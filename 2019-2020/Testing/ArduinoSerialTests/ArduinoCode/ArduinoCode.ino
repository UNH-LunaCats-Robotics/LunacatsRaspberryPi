void setup() {
    Serial.begin( 9600 );
    Serial.setTimeout(20);
}

void test_w() {
    Serial.println("Pong");
    delay( 1000 );
}

void test_wr() {
    if (Serial.available() > 0) {
        Serial.println(Serial.readString());
        delay( 1000 );
    }
}

void loop() {
    test_w();
}