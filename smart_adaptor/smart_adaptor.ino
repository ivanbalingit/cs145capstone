#include <EtherCard.h>
#include <ArduinoJson.h>

#define RELAY_PIN A0
#define OPTO_PIN A5

// Ethernet interface mac address, must be unique on the LAN
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

// Setup Ethernet data buffer
byte Ethernet::buffer[700];
static uint32_t timer;

// Setup JSON parser
StaticJsonBuffer<200> jsonBuffer;

// Called when the client request is complete
static void my_callback (byte status, word off, word len) {
  Serial.println(">>>");
  Ethernet::buffer[off+300] = 0;
  Serial.println((const char*) Ethernet::buffer + 384);
  
  // Parse JSON from HTTP reply
  const char* json = (const char*) Ethernet::buffer + 384;
  JsonObject& root = jsonBuffer.parseObject(json);
  String state = String((const char*) root["state"]);

  // Determine state of LED
  if (state.equals("true")) {
    Serial.println("turn on");
    digitalWrite(RELAY_PIN, HIGH);
  } else if (state.equals("false")) {
    Serial.println("turn off");
    digitalWrite(RELAY_PIN, LOW);  
  } else {
    Serial.println("no state parsed, stay");
  } 
  
  jsonBuffer.clear();
}

void setup () {
  // Setup pins
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(OPTO_PIN, INPUT);
  
  // Setup Serial
  Serial.begin(57600);
  Serial.println(F("\n[webClient]"));

  // Setup DHCP
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0) 
    Serial.println(F("Failed to access Ethernet controller"));
  if (!ether.dhcpSetup())
    Serial.println(F("DHCP failed"));

  // Setup IP addresses
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);  
  ether.printIp("DNS: ", ether.dnsip);  

  char websiteIP[] = "206.189.92.99";
  ether.parseIp(ether.hisip, websiteIP);
    
  ether.printIp("SRV: ", ether.hisip);
}

void loop () {
  ether.packetLoop(ether.packetReceive());
  
  if (millis() > timer) {
    timer = millis() + 1000;
    
    boolean opto_state = digitalRead(OPTO_PIN);
    const char *link_t = "get_state?name=adaptor1&opto_state=true";
    const char *link_f = "get_state?name=adaptor1&opto_state=false";
    const char *link = opto_state ? link_t : link_f;
    
    Serial.println();
    Serial.println(link);
    Serial.print("<<< REQ ");
    ether.browseUrl(PSTR("/adaptor/"), link, "", my_callback);
  }
}
