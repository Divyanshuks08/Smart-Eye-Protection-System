#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// ===== PINS ===== 
int pir = 8; 
int trigPin = 9; 
int echoPin = 10; 
int ldr1 = A0; 
int ldr2 = A1; 
int buzzer = 11; 
  // Ambient light 
  // Screen light 
// ===== STATES ===== 
bool personPresent = false; 
bool timerRunning = false; 
// ===== TIMERS ===== 
unsigned long startTime = 0; 
unsigned long lastMotionTime = 0; 
 
// ===== STABILITY CONTROL ===== 
int lastDistance = 0; 
int leaveCounter = 0; 
const int leaveConfirmLimit = 5; 
 
// ===== CONSTANTS ===== 
int safeDistance = 30; 
int distanceThreshold = 10; 
int lightThreshold = 80; 
 
unsigned long holdTime = 8000; 
unsigned long leaveTimeout = 20000; 
 
// ===== SETUP ===== 
void setup() { 
  pinMode(pir, INPUT); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzer, OUTPUT); 
 
  lcd.init(); 
  lcd.backlight(); 
 
  showMessage("Smart System", "Starting..."); 
  delay(2000); 
  lcd.clear(); 
} 
 
// ===== LOOP ===== 
void loop() { 
 
  bool detected = isPersonPresent(); 
 
  if (detected) { 
 
    leaveCounter = 0; 
    personPresent = true; 
 
    startTimer(); 
    displayTime(); 
 
    int distance = getDistanceFiltered(); 
    int lightState = checkBrightness(); 
 
    if (distance < safeDistance) { 
      lcd.setCursor(0, 1); 
      lcd.print("Too Close      "); 
      buzzerFast(); 
    } 
    else if (lightState == 1) { 
      lcd.setCursor(0, 1); 
      lcd.print("Low Brightness "); 
      buzzerSlow(); 
    } 
    else if (lightState == 2) { 
      lcd.setCursor(0, 1); 
      lcd.print("High Brightness"); 
      buzzerSlow(); 
    } 
    else { 
      lcd.setCursor(0, 1); 
      lcd.print("All Good       "); 
      noTone(buzzer); 
    } 
  } 
 
  else { 
 
    if (personPresent) { 
      leaveCounter++; 
 
      if (leaveCounter >= leaveConfirmLimit && 
          millis() - lastMotionTime > leaveTimeout) { 
        resetSystem(); 
      } 
    } 
  } 
 
  delay(150); 
} 
 
// ===== PRESENCE DETECTION (STABLE LOGIC) ===== 
bool isPersonPresent() { 
 
  int motion = digitalRead(pir); 
  int currentDistance = getDistanceFiltered(); 
 
  if (currentDistance > 200 || currentDistance <= 0) { 
    return false; 
  } 
 
  if (motion == HIGH || abs(currentDistance - lastDistance) > 4) { 
    lastMotionTime = millis(); 
    lastDistance = currentDistance; 
    return true; 
  } 
 
  if (millis() - lastMotionTime < holdTime) { 
    return true; 
  } 
 
  if (currentDistance < 150 && 
      abs(currentDistance - lastDistance) <= distanceThreshold) { 
    return true; 
  } 
 
  return false; 
} 
 
// ===== ULTRASONIC FILTER ===== 
int getDistanceFiltered() { 
 
  int d1 = getDistance(); 
  delay(10); 
  int d2 = getDistance(); 
  delay(10); 
  int d3 = getDistance(); 
 
  int arr[3] = {d1, d2, d3}; 
 
  for (int i = 0; i < 2; i++) { 
    for (int j = i + 1; j < 3; j++) { 
      if (arr[i] > arr[j]) { 
        int t = arr[i]; 
        arr[i] = arr[j]; 
        arr[j] = t; 
      } 
    } 
  } 
 
  return arr[1]; 
} 
 
// ===== DISTANCE ===== 
int getDistance() { 
 
  long duration; 
 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
 
  duration = pulseIn(echoPin, HIGH, 20000); 
 
  if (duration == 0) return 400; 
 
  return duration * 0.034 / 2; 
} 
 
// ===== LIGHT CHECK ===== 
int checkBrightness() { 
 
  int ambient = analogRead(ldr1); 
  int screen = analogRead(ldr2); 
 
  if (screen < ambient - lightThreshold) return 1; 
  if (screen > ambient + lightThreshold) return 2; 
 
  return 0; 
} 
 
// ===== TIMER ===== 
void startTimer() { 
 
  if (!timerRunning) { 
    startTime = millis(); 
    timerRunning = true; 
    lcd.clear(); 
  } 
} 
 
// ===== DISPLAY TIMER ===== 
void displayTime() { 
 
  unsigned long elapsed = (millis() - startTime) / 1000; 
 
  int h = elapsed / 3600; 
  int m = (elapsed % 3600) / 60; 
  int s = elapsed % 60; 
 
  lcd.setCursor(0, 0); 
 
  if (h < 10) lcd.print("0"); 
  lcd.print(h); lcd.print(":"); 
 
  if (m < 10) lcd.print("0"); 
  lcd.print(m); lcd.print(":"); 
 
  if (s < 10) lcd.print("0"); 
  lcd.print(s); 
} 
 
// ===== BUZZER ===== 
void buzzerFast() { 
  tone(buzzer, 1000); 
  delay(50); 
  noTone(buzzer); 
} 
 
void buzzerSlow() { 
  tone(buzzer, 1000); 
  delay(150); 
  noTone(buzzer); 
} 
 
// ===== RESET SYSTEM ===== 
void resetSystem() { 
 
  personPresent = false; 
  timerRunning = false; 
  leaveCounter = 0; 
 
  noTone(buzzer); 
 
  showMessage("No Person", "00:00:00"); 
} 
 
// ===== LCD ===== 
void showMessage(String l1, String l2) { 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print(l1); 
lcd.setCursor(0, 1); 
lcd.print(l2); 
}
