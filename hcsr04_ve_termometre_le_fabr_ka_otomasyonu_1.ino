#include <LiquidCrystal.h>
LiquidCrystal lcd(9, 10, 11, 12, 13, 3);

int led_kirmizi = 4;
int led_yesil = 5;
int buzz_pin = 6;
int trig_pin = 7;
int echo_pin = 8;
int dht_pin = A0;

int sise = 0;
int sise_hafiza = 0;
int sensor;
int sure;
int a = 0;
float mesafe;
double sonuc_3;
double sicaklik;

void setup(){
  pinMode(led_yesil,OUTPUT);
  pinMode(led_kirmizi,OUTPUT);
  pinMode(buzz_pin,OUTPUT);
  pinMode(trig_pin,OUTPUT);
  pinMode(echo_pin,INPUT);
  pinMode(dht_pin,INPUT);
  
  lcd.begin(16, 2);
  Serial.begin(9600);}


void loop(){
  sensor = analogRead(dht_pin);
  digitalWrite(trig_pin,HIGH);
  delayMicroseconds(15000);
  digitalWrite(trig_pin,LOW);
 
  
  sure = pulseIn(echo_pin,HIGH);
  
  sicaklik = (double)sensor/ 1024;       
  sicaklik = sicaklik * 5;                 
  sicaklik = sicaklik - 0.5;               
  sicaklik = sicaklik * 100;
  dalga_hesap();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dusen Sise: ");
  lcd.print(sise);
  lcd.setCursor(2, 1);
  
  lcd.setCursor(0, 1);
  lcd.print("Sicaklik: ");
  lcd.print(sicaklik);
  lcd.print("c");
  
    
 
  if ((a ==10) &&(sise>7)){
    a =0;
    sure = sure - 1000;
  }
  
  if(mesafe<6){
    digitalWrite(led_yesil,HIGH);
    digitalWrite(buzz_pin,LOW);
    Serial.println("DURUM NORMAL");
  	a+=1;}
  else if (mesafe >6){
    sise +=1;
    digitalWrite(led_yesil,LOW);
    digitalWrite(led_kirmizi,HIGH);
    digitalWrite(buzz_pin,HIGH);
   
    a+=1;}
  delay(1000);
}

/* alttaki fonksiyonda sürekli sıcaklık durumu alınır 
ve ortam sıcaklıgına göre ses dalgasının yayılma hızı sürekli hesaplanır.
Bunun nedeni hassas ölçüm yapılması içindir.*/

void dalga_hesap(){
  float hesap_1 = 331 *(sqrt(1+(sicaklik/273))); //ses dalgasının yayılım hızı hesaplanır metre/saniye
 
  float hesap_2 = (hesap_1*100); // cıkan deger önce santimetreye cevrilir.
  double sonuc_2 = (hesap_2 / 1000000); // daha sonra bulunan değer mikro saniye değerine bölünür.
  sonuc_3 = 1/ sonuc_2; // cikan değerin tersi alınır
  Serial.println(sonuc_3); // ve bulunan değer bizi bulunan ortam sıcaklıgında ses dalgasını yayılım hızıdır.
  uzaklik_bul(); // uzaklik_bul fonksiyonu tetiklenir
}

void uzaklik_bul(){
  mesafe = (sure/2) /sonuc_3; //sure sesin gidip-gelmesinden doalyı 2 ye bölünür ve dalga dagılma hızına bölünür.
  Serial.print("Cisme olan uzaklık: ");
  Serial.println(mesafe);
  Serial.println("--------------");
}

