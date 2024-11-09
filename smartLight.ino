#define BLYNK_TEMPLATE_ID "TMPL7hdOYmBk"    //mendefinisikan id tamplate dari blynk
#define BLYNK_DEVICE_NAME "SmartLight2" // nama device 
#define BLYNK_AUTH_TOKEN "REclxBHfI34GPOFWvDuByQdga4MFM-Ld" // token blynk yang ingin dikonekkan

#define BLYNK_PRINT Serial  //
#include <ESP8266WiFi.h>  // library untuk wifi esp 8266
#include <BlynkSimpleEsp8266.h> ///library untuk blynk esp 8266
#include <Wificlient.h> // lbrary wifi untuk thingspeak
#include <ThingSpeak.h> //library untuk thinkspeak

char auth[] = BLYNK_AUTH_TOKEN; // memnggil token blynk
char ssid[] = "realme 7"; // nama wifi
char pass[] = "12345677"; //pass wifi

// informasi thingspeak
char* tulis = "P6UIUVWIM0TEIFNY";
char* baca = "QXG9ALBL7YW159BB";  
const long channelID = 2001847;

WiFiClient client; //thinkspeaknya bisa connect

int Relay = 2; //deklarasi pin 2 menjadi relay
int PIR = 16; //deklarasi pin 16 menjadi PIR

void setup()
{
  Serial.begin(115200); //memulai serial dengan 
  Blynk.begin(auth, ssid, pass); //memulai memanggil informaasi dan token blynk dan wifi agar bisa terconnet dengan akun blynk
  
  pinMode(Relay, OUTPUT); //menjadikan relay sebagai output
  pinMode(PIR, INPUT); //menjadikan PIR sebagai input
}

void loop()
{

  int value = digitalRead(PIR); //membaca sensor PIR sebagai value
  ThingSpeak.begin(client); //memulai coding thinkspeak
  
  if (value == HIGH){ //jika value(PIR) bernilai high maka coding dibawah akan aktif
    Serial.println("Lampu Menyala"); //menampilkan tulisan lampu menyala dalam serial monitor
    digitalWrite(Relay, LOW); //relay akan menjadi low dan lamppu akakn menyala
    Blynk.logEvent("Light"); //memanggil log event pada akun blynk yang sudah disediakan terlebih dahulu
    ThingSpeak.writeField (channelID, 1, value, tulis); //mengirim dan mencatat data pada thinkspeak 
    delay(500); //jeda setengah detik
    }
  else { 
    Serial.println("Lampu Mati"); //menampilkan tulisan lampu mati dalam serial monitor
    digitalWrite(Relay, HIGH); //relay akan high dan lampu akan mati
    ThingSpeak.writeField (channelID, 1, value, tulis); //mengirim dan mencatat data pada thinkspeak
    delay(500); //jeda setenngah detik
 
  Blynk.run(); //untuk menjalankan perintah blynk
  }
  
}
