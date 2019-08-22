void setup() {
    Serial.begin( 9600 );
    Serial.setTimeout(20);
    Serial.println(" init");
}

void test_w() {
    Serial.println("Pong");
    delay( 0 );
}

void test_wr() {
    if (Serial.available() > 0) {
        Serial.println(Serial.readString());
        delay( 0 );
    }
}

void loop() {
    test_w();
}