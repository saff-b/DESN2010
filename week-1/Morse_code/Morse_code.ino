// blinking external LED
// based on blink example sketch

int ledPin = 13;
int unit = 300;
int dotLength = unit;
int dashLength = unit * 3;
int letterSpace = unit * 2;
int wordSpaceLength = unit * 6;
String message = "Hello World!";

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  message.toUpperCase();
}

void loop() {
  // put your main code here, to run repeatedly:
  spelling(message);
}

void spelling(String s) {
  int n = s.length();
  // favourite trick: iterating through an array
  for (int i = 0; i < n; i++) {
    // theres probably a cleverer way of doing this but oh wel
    char current = s.charAt(i);
    switch (current) {
      case 'A': 
        m_a(); 
        delay(letterSpace); 
        break;
      case 'B': 
        m_b(); 
        delay(letterSpace); 
        break;
      case 'C': 
        m_c(); 
        delay(letterSpace); 
        break;
      case 'D': 
        m_d(); 
        delay(letterSpace); 
        break;
      case 'E': 
        m_e(); 
        delay(letterSpace); 
        break;
      case 'F': 
        m_f(); 
        delay(letterSpace); 
        break;
      case 'G': 
        m_g(); 
        delay(letterSpace); 
        break;
      case 'H': 
        m_h(); 
        delay(letterSpace); 
        break;
      case 'I': 
        m_i(); 
        delay(letterSpace); 
        break;
      case 'J': 
        m_j(); 
        delay(letterSpace); 
        break;
      case 'K': 
        m_k(); 
        delay(letterSpace); 
        break;
      case 'L': 
        m_l(); 
        delay(letterSpace); 
        break;
      case 'M': 
        m_m(); 
        delay(letterSpace); 
        break;
      case 'N': 
        m_n(); 
        delay(letterSpace); 
        break;
      case 'O': 
        m_o(); 
        delay(letterSpace); 
        break;
      case 'P': 
        m_p(); 
        delay(letterSpace); 
        break;
      case 'Q': 
        m_q(); 
        delay(letterSpace); 
        break;
      case 'R': 
        m_r(); 
        delay(letterSpace); 
        break;
      case 'S': 
        m_s(); 
        delay(letterSpace); 
        break;
      case 'T': 
        m_t(); 
        delay(letterSpace); 
        break;
      case 'U': 
        m_u(); 
        delay(letterSpace); 
        break;
      case 'V': 
        m_v(); 
        delay(letterSpace); 
        break;
      case 'W': 
        m_w(); 
        delay(letterSpace); 
        break;
      case 'X': 
        m_x(); 
        delay(letterSpace); 
        break;
      case 'Y': 
        m_y(); 
        delay(letterSpace); 
        break;
      case 'Z': 
        m_z();
        delay(letterSpace); 
        break;
      default: 
        delay(wordSpaceLength);
    }
  }
}

// dot and dash
void dot() {
  digitalWrite(ledPin,HIGH);
  delay(dotLength);
  digitalWrite(ledPin,LOW);
  delay(unit);
}

void dash() {
  digitalWrite(ledPin,HIGH);
  delay(dashLength);
  digitalWrite(ledPin,LOW);
  delay(unit);
}
// functions for all the letters lol
void m_a() {
  dot();
  dash();
}

void m_b() {
  dash();
  dot();
  dot();
  dot();
}

void m_c() {
  dash();
  dot();
  dash();
  dot();
}

void m_d() {
  dash();
  dot();
  dot();
}

void m_e() {
  dot();
}

void m_f() {
  dot();
  dot();
  dash();
  dot();
}

void m_g() {
  dash();
  dash();
  dot();
}

void m_h() {
  dot();
  dot();
  dot();
  dot();
}

void m_i() {
  dot();
  dot();
}

void m_j() {
  dot();
  dash();
  dash();
  dash();
}

void m_k() {
  dash();
  dot();
  dash();
}

void m_l() {
  dot();
  dash();
  dot();
  dot();
}

void m_m() {
  dash();
  dash();
}

void m_n() {
  dash();
  dot();
}

void m_o() {
  dash();
  dash();
  dash();
}

void m_p() {
  dot();
  dash();
  dash();
  dot();
}

void m_q() {
  dash();
  dash();
  dot();
  dash();
}

void m_r() {
  dot();
  dash();
  dot();
}

void m_s() {
  dot();
  dot();
  dot();
}

void m_t() {
  dash();
}

void m_u() {
  dot();
  dot();
  dash();
}

void m_v() {
  dot();
  dot();
  dot();
  dash();
}

void m_w() {
  dot();
  dash();
  dash();
}

void m_x() {
  dash();
  dot();
  dot();
  dash();
}

void m_y() {
  dash();
  dot();
  dash();
  dash();
}

void m_z() {
  dash();
  dash();
  dot();
  dot();
}
