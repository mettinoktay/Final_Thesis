/*  YILDIZ TEKNİK ÜNİVERSİTESİ
 *  MEKATRONİK MÜHENDİSLİĞİ BÖLÜMÜ
 *  
 *  LİSANS BİTİRME TEZİ
 *  
 *  KÜÇÜK ÇAPLI RÜZGAR TÜRBİNİ YAW VE PITCH KONTROLÜ
 *  
 *  METİN OKTAY YILMAZ
 *  11067027
 *  
 *  DANIŞMAN: YRD. DOÇ. DR. HATİCE MERCAN
 *  
 *  Yazar: Metin Oktay Yılmaz
 *  Tarih: 08.06.2016
 */

/* Bu kısımda, kullanılacak kütüphaneler ekleniyor. */
#include "Servo.h"
#include "WindTurbine.h"
#include "DRV8825.h"
#include "PID_v1.h"

/* Debug ederken kullanılacak komutların aktif edilmesi için
 * aşağıdaki satırdaki yorumu kaldırın.
 */
//#define   DEBUG

double windSpeed = 0.0,           // Rüzgar hızının saklanacağı değişken
       AoA = 0.0,                 // Hücum açısının      "         "
       yawSetPoint = 0,           // Yaw ekseni referans noktası
       windDirectionError = 0.0,  // Rüzgar yönü hatasının saklanacağı değişken
       yawOutput,                 // Yaw ekseni motoruna gönderilecek çıkış değeri
       yawKp = 2.0,               // PID - P katsayısı
       yawKi = 0.0,               // PID - I katsayısı
       yawKd = 1.0;               // PID - D katsayısı

/* Servo, DRV8825, WindTurbine ve PID instance'ları */
Servo pitchServo;
DRV8825 stepper;
WindTurbine myTurbine;
PID PID_yawAxis(&windDirectionError, &yawOutput, &yawSetPoint, yawKp, yawKi, yawKd, DIRECT);

void setup() {
  /* Serial kütüphanesi, Arduino'nun bilgisayar ile iletişim kurmasına olanak sağlar. */
  Serial.begin(57600);
  Serial.flush();
  
  /* pinMode fonksiyonu Atmega pinlerini giriş veya çıkış olarak ayarlar. */
  /* Kullanılan parametrelerin ne işe yaradıklarını anlamak için pins.h dosyasına bakınız. */
  pinMode (M2,    OUTPUT);
  pinMode (M1,    OUTPUT);
  pinMode (M0,    OUTPUT);
  pinMode (FLT,   INPUT);
  pinMode (STEP,  OUTPUT);
  pinMode (DIR,   OUTPUT);
  pinMode (SERVO, OUTPUT);
  
  /* Servo, DRV8825 ve PID instance'ları başlatılıyor. */
  pitchServo.attach(SERVO);
  stepper.Enable();
  stepper.microStepping(FULL);
  PID_yawAxis.SetOutputLimits(-1000,1000);
}

void loop() {
  /* Eğer DRV8825'te donanımsal bir hata varsa türbin kontrolü durdurulur. */
  while(stepper.isFaulty()){
    stepper.Disable();
    Serial.println("TURBINE HALTED DUE TO DRV8825 MALFUNCTION");    
  }
  
  myTurbine.readWindSpeed(&windSpeed);
  
  /* Rüzgar hızı cut-off hızını aştığında rotor durdurulur. */
  if (windSpeed > 10) {
    pitchServo.write(NO_LIFT);
    Serial.println("TURBINE HALTED DUE TO WIND SPEED");
    myTurbine.computeDirectionError(&windDirectionError);
    PID_yawAxis.Compute();
  }
  /* Rüzgar hızı operasyon sınırları içindeyse kontrol kısmına geçilir. */
  else {
    pitchServo.write(MAX_LIFT);
    Serial.println("TURBINE IS NORMALLY OPERATING");
    myTurbine.computeDirectionError(&windDirectionError);
    PID_yawAxis.Compute();
  }

  stepper.Drive(yawOutput);
  
  #ifdef DEBUG
    Serial.print("Wind Speed: ");
    Serial.println(windSpeed);
    Serial.print("Wind Direction Error: ");
    Serial.println(windDirectionError);
    Serial.print("Yaw Output: ");
    Serial.println(yawOutput);
  #endif
}
