//---------------------------------------------#include part---------------------------------------------
// 중복되는 헤더파일은 제외함
/* sensor */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>
#include <wiringPiSPI.h>

/* actuator */
#include <wiringPi.h>
#include <softPwm.h>
#include <signal.h> //Signal 사용 헤더파일

//---------------------------------------------#define part---------------------------------------------
/* sensor */
#define FLAME_IN 5  // gpio7
#define MOYION_IN 0 // gpio17
#define MAXTIMINGS 85
#define CS_MCP3208 8 // GPIO 8
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000 // 1Mhz
#define LIGHTSEN_OUT 2    // gpio27 - J13 connect
#define trigPin 1         // gpio 21
#define echoPin 29        // gpio 18
#define SOUND_IN 2        // gpio27
#define COLLISION 2       // gpio27 - J13 connect

/* actuator */
#define PUMP 21   // BCM_GPIO 5
#define FAN 22    // BCM_GPIO 6
#define LEDBAR 24 // BCM_GPIO 12
//#define MOTORCONTROL  22	//GPIO 6 - Motor
#define LEDCONTROL 24 // LED Bar (ledbarsoftpwm)
// const int LEDCONTROL 21 //
#define BUZCONTROL 28  // GPIO 20
#define DCMOTOR 23     // BCM_GPIO 13
#define RGBLEDPOWER 24 // BCM_GPIO 19
#define RED 7          // 27
#define GREEN 8        // 28
#define BLUE 9         // 29

//---------------------------------------------global variables part---------------------------------------------
/* sensor */
// the event counter
volatile int eventCounter = 0;
int ret_humid, ret_temp;
unsigned char humandetect = 0;
int counter = 0;

static int DHTPIN = 7;
// static int DHTPIN = 11;
static int dht22_dat[5] = {0, 0, 0, 0, 0};
unsigned char soundFlag = 0;

//---------------------------------------------함수 원형 part---------------------------------------------
/* sensor */
int sounddetect(void);
int neardetect(void);
int flamedetect(void);
int gasdetect(void);
int get_humidity(void);    //습도
int get_temperature(void); //온도
int get_humitemp(void);    //온습도
int getlightsensor(void);
int lightdetect(void);
int ultrasonic(void); //초음파

/* actuator */
void func_pumpon();
void func_fanon();
void func_ledbar();
void func_ledbarsoftpwm();
int wiringPicheck(void);
void Bpluspinmodeset(void);

void func_buzcontrol();
void func_dcmotoron();
void func_rgbtest();
void func_allrgbcolor();
void Bpluspinmodeset_RGB(void);
void setRGB(int r, int g, int b);

void sig_handler(int signo); // 마지막 종료 함수

/***
파일 실행 형식 : ./sym.out
파일 작성 시, 주석 지우지 말 것 (파일 제출 시, 라인별로 어떤 작업을 수행하는지 필히 작성해야함)
***/

//---------------------------------------------main function part---------------------------------------------
int main(void)
{
  // int answer;
  // printf("1. 사운드 센서, 2. 근접 센서, 3. 불꽃 센서, 4. 가스 센서, 5. 습도 센서, 6. 온도 센서, 7. 온습도 센서 8. 조도 센서, 9, 초음파 센서 ///// 10.워터펌프, 11. 팬, 12.LED Bar 제어, 13. LED Bar 제어(PWM), 14. 부저, 15. DC Motor, 16. RGB Led, 17. RGB Led (PWM), 0. 종료\n");
  // scanf("%d", &answer);
  char* userName;
  char* userStuID;
  int userID;

  // 1. 프로그램이 시작했음을 알림
  printf("---------------------------------------------\n");
  printf("          Setting Your Raspberry-Pi          \n");
  printf("---------------------------------------------\n\n\n\n");

  // 2. web에서 login한 후, 그때 사용한 본인의 이름, 학번 입력
  printf("[홈페이지에서 입력한 본인의 이름, 학번을 입력해주세요]");
  printf("이름 : ");
  scanf("%s", userName);
  printf("학번 : ");
  scanf("%s", userStuID);

  // 3. 위의 정보를 이용하여, id 확인 (get-user-id.php / pramName : name, stunum)
  // 4. 받은 정보를 'userID'에 저장
  
  while (TRUE)
  {
    // 5. 'IP-address:port/is-exe.php?id='userID'로부터 int형으로 값 받기

    // 6. 해당 값에 따라 원하는 device 동작함수 실행 (단, 0이면 사용자가 어떤 디바이스를 동작할지 선택하지 않음 - continue)
    if (answer == 1)
      sounddetect();
    else if (answer == 2)
      neardetect();
    else if (answer == 3)
      flamedetect();
    else if (answer == 4)
      gasdetect();
    else if (answer == 5)
      get_humidity();
    else if (answer == 6)
      get_temperature();
    else if (answer == 7)
      get_humitemp();
    else if (answer == 8)
      lightdetect();
    else if (answer == 9)
      ultrasonic();
    else if (answer == 10)
      func_pumpon();
    else if (answer == 11)
      func_fanon();
    else if (answer == 12)
      func_ledbar();
    else if (answer == 13)
      func_ledbarsoftpwm();
    else if (answer == 14)
      func_buzcontrol();
    else if (answer == 15)
      func_dcmotoron();
    else if (answer == 16)
      func_rgbtest();
    else if (answer == 17)
      func_allrgbcolor();
    else if (answer == 0)
      return 0; //종료
  }

  /* device 함수 안에서의 로직 */
  // 1. 함수 안에서 실제 값을 출력하는 부분 or 동작하게 해주는 while/for문이 있으면
  // 2. putty에 출력값 또는 actuator에 경우에는 'actuator name이 동작중입니다'라고 출력
  // 3. is-stop.php?id='userID'로부터 int형으로 값을 받기(0: 반복문 계속 실행 / 1: 반복문 break)
  // 3-1. 1을 받았으면, init-stop.php?id='userID'&stop=0(int) 실행
  // 3-2. 반복문 stop


  neardetect();
  return 0;
}

//---------------------------------------------function definiton part---------------------------------------------
/* sensor */
// myInterrupt:  called every time an event occurs
void myInterrupt(void)
{
  eventCounter++;
}

static uint8_t sizecvt(const int read)
{
  /* digitalRead() and friends from wiringpi are defined as returning a value
  < 256. However, they are returned as int() types. This is a safety function */

  if (read > 255 || read < 0)
  {
    printf("Invalid data from wiringPi library\n");
    exit(EXIT_FAILURE);
  }
  return (uint8_t)read;
}

int read_dht22_dat()
{
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i;

  dht22_dat[0] = dht22_dat[1] = dht22_dat[2] = dht22_dat[3] = dht22_dat[4] = 0;

  // pull pin down for 18 milliseconds
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, HIGH);
  delay(10);
  digitalWrite(DHTPIN, LOW);
  delay(18);
  // then pull it up for 40 microseconds
  digitalWrite(DHTPIN, HIGH);
  delayMicroseconds(40);
  // prepare to read the pin
  pinMode(DHTPIN, INPUT);

  // detect change and read data
  for (i = 0; i < MAXTIMINGS; i++)
  {
    counter = 0;
    while (sizecvt(digitalRead(DHTPIN)) == laststate)
    {
      counter++;
      delayMicroseconds(1);
      if (counter == 255)
      {
        break;
      }
    }
    laststate = sizecvt(digitalRead(DHTPIN));

    if (counter == 255)
      break;

    // ignore first 3 transitions
    if ((i >= 4) && (i % 2 == 0))
    {
      // shove each bit into the storage bytes
      dht22_dat[j / 8] <<= 1;
      if (counter > 16)
        dht22_dat[j / 8] |= 1;
      j++;
    }
  }

  // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
  // print it out if data is good
  if ((j >= 40) &&
      (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF)))
  {
    float t, h;

    h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
    h /= 10;
    t = (float)(dht22_dat[2] & 0x7F) * 256 + (float)dht22_dat[3];
    t /= 10.0;
    if ((dht22_dat[2] & 0x80) != 0)
      t *= -1;

    ret_humid = (int)h;
    ret_temp = (int)t;
    // printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t );
    // printf("Humidity = %d Temperature = %d\n", ret_humid, ret_temp);

    return ret_humid;
  }
  else
  {
    printf("Data not good, skip\n");
    return 0;
  }
}

int read_mcp3208_adc(unsigned char adcChannel)
{

  unsigned char buff[3];
  int adcValue = 0;

  buff[0] = 0x06 | ((adcChannel & 0x07) >> 2);
  buff[1] = ((adcChannel & 0x07) << 6);
  buff[2] = 0x00;

  digitalWrite(CS_MCP3208, 0);
  wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

  buff[1] = 0x0f & buff[1];
  adcValue = (buff[1] << 8) | buff[2];

  digitalWrite(CS_MCP3208, 1);

  return adcValue;
}

int sounddetect(void)
{
  unsigned char adcChannel_sound = 0;

  int adcValue_sound = 0;

  printf("start");

  if (wiringPiSetupGpio() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi :%s\n", strerror(errno));
    return 1;
  }

  if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
  {
    fprintf(stdout, "wiringPiSPISetup Failed :%s\n", strerror(errno));
    return 1;
  }

  pinMode(CS_MCP3208, OUTPUT);

  while (1)
  {
    adcValue_sound = read_mcp3208_adc(adcChannel_sound);

    printf("sound = %u\n", adcValue_sound);

    delay(100);
  }
}

int neardetect(void)
{
  if (wiringPiSetup() < 0)
  {
    fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }

  pinMode(COLLISION, INPUT);

  // display counter value every second.
  while (1)
  {
    // printf( "%d\n", eventCounter );
    // eventCounter = 0;

    if (digitalRead(COLLISION) == 0)
      printf("Carefull~~~~ oops \n");
    if (digitalRead(COLLISION) == 1)
      printf("Not Collioson... \n");

    delay(200); // wait 1 second
  }
}

int flamedetect(void)
{
  // sets up the wiringPi library
  if (wiringPiSetup() < 0)
  {
    fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  if (wiringPiISR(FLAME_IN, INT_EDGE_FALLING, &myInterrupt) < 0)
  {
    fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
    return 1;
  }

  // display counter value every second.
  while (1)
  {
    printf("%d\n", eventCounter);
    // eventCounter = 0;
    delay(1000); // wait 1 second
  }

  return 0;
}

int gasdetect(void)
{
  // sets up the wiringPi library
  if (wiringPiSetup() < 0)
  {
    fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  if (wiringPiISR(MOYION_IN, INT_EDGE_FALLING, &myInterrupt) < 0)
  {
    fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
    return 1;
  }

  // display counter value every second.
  while (1)
  {
    printf("%d\n", eventCounter);
    // eventCounter = 0;
    delay(1000); // wait 1 second
  }

  return 0;
}

int get_humidity(void)
{
  int received_humid;

  DHTPIN = 11;

  if (wiringPiSetup() == -1)
    exit(EXIT_FAILURE);

  if (setuid(getuid()) < 0)
  {
    perror("Dropping privileges failed\n");
    exit(EXIT_FAILURE);
  }
  while (read_dht22_dat() == 0)
  {
    delay(500); // wait 1sec to refresh
  }
  received_humid = ret_humid;
  printf("Humidity = %d\n", received_humid);

  return 0;
}

int get_temperature(void)
{
  int received_temp;

  if (wiringPiSetup() == -1)
    exit(EXIT_FAILURE);

  if (setuid(getuid()) < 0)
  {
    perror("Dropping privileges failed\n");
    exit(EXIT_FAILURE);
  }
  while (read_dht22_dat() == 0)
  {
    delay(500); // wait 1sec to refresh
  }
  received_temp = ret_temp;
  printf("Temperature = %d\n", received_temp);

  return 0;
}

int get_humitemp(void)
{

  if (wiringPiSetup() == -1)
    exit(EXIT_FAILURE);

  if (setuid(getuid()) < 0)
  {
    perror("Dropping privileges failed\n");
    exit(EXIT_FAILURE);
  }

  while (read_dht22_dat() == 0)
  {
    delay(1000); // wait 1sec to refresh
  }

  return 0;
}

int getlightsensor(void)
{

  unsigned char adcChannel_light = 0;

  int adcValue_light = 0;

  float vout_light;
  float vout_oftemp;
  float percentrh = 0;
  float supsiondo = 0;

  printf("start");

  if (wiringPiSetupGpio() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi :%s\n", strerror(errno));
    return 1;
  }

  if (wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1)
  {
    fprintf(stdout, "wiringPiSPISetup Failed :%s\n", strerror(errno));
    return 1;
  }

  pinMode(CS_MCP3208, OUTPUT);

  while (1)
  {
    adcValue_light = read_mcp3208_adc(adcChannel_light);

    // printf("Humiity = %u temparature = %u\n", adcValue_humi, adcValue_temp);
    printf("light sensor = %u\n", adcValue_light);

    delay(100);
  }
  return 0;
}

int lightdetect(void)
{
  // sets up the wiringPi library
  if (wiringPiSetup() < 0)
  {
    fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
    return 1;
  }

  pinMode(LIGHTSEN_OUT, INPUT);

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  /*if ( wiringPiISR (LIGHTSEN_OUT, INT_EDGE_RISING, &myInterrupt) < 0 )
  {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }*/

  // display counter value every second.
  while (1)
  {
    // printf( "%d\n", eventCounter );
    // eventCounter = 0;

    if (digitalRead(LIGHTSEN_OUT) == 0)
      printf("light full ! \n");
    if (digitalRead(LIGHTSEN_OUT) == 1)
      printf("dark \n");

    delay(200); // wait 1 second
  }

  return 0;
}

int ultrasonic(void)
{
  int distance = 0;
  int pulse = 0;

  long startTime;
  long travelTime;

  if (wiringPiSetup() == -1)
  {
    printf("Unable GPIO Setup");
    return 1;
  }

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (;;)
  {
    digitalWrite(trigPin, LOW);
    usleep(2);
    digitalWrite(trigPin, HIGH);
    usleep(20);
    digitalWrite(trigPin, LOW);

    while (digitalRead(echoPin) == LOW)
      ;

    startTime = micros();

    while (digitalRead(echoPin) == HIGH)
      ;
    travelTime = micros() - startTime;

    int distance = travelTime / 58;

    printf("Distance: %dcm\n", distance);
    delay(200);
  }
}

/* actuator */
// 워터펌프 동작
void func_pumpon()
{
  signal(SIGINT, (void *)sig_handler); //시그널 핸들러 함수

  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
  }

  pinMode(PUMP, OUTPUT);

  for (;;)
  {
    printf("here - pump on\n");
    digitalWrite(PUMP, 1); // On

    delay(2000); // ms

    digitalWrite(PUMP, 0); // Off

    delay(2000);
  }
}

void func_fanon()
{
  signal(SIGINT, (void *)sig_handler); //시그널 핸들러 함수

  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
  }

  pinMode(FAN, OUTPUT);

  for (;;)
  {
    // printf("here - FAN on\n");
    digitalWrite(FAN, 1); // On
  }
}

void func_ledbar()
{
  signal(SIGINT, (void *)sig_handler); //시그널 핸들러 함수

  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
  }

  pinMode(LEDBAR, OUTPUT);

  for (;;)
  {
    printf("here - Led Bar on on\n");
    digitalWrite(LEDBAR, 1); // On

    delay(200); // ms

    printf("here - Led Bar on on\n");
    digitalWrite(LEDBAR, 0); // Off

    delay(200);
  }
}

void func_ledbarsoftpwm()
{
  if (wiringPicheck())
    printf("Fail\n");

  signal(SIGINT, (void *)sig_handler);

  pinMode(LEDCONTROL, OUTPUT);

  softPwmCreate(LEDCONTROL, 0, 100);

  int i;
  int delaytime = 300;
  while (1)
  {
    printf("here \n");

    softPwmWrite(LEDCONTROL, 10);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 20);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 30);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 40);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 50);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 60);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 70);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 80);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 90);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 100);
    delay(delaytime);
    softPwmWrite(LEDCONTROL, 0);
    delay(delaytime);
  }
}

int wiringPicheck(void)
{
  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
    exit(1);
  }
}

void Bpluspinmodeset(void)
{
  pinMode(LEDCONTROL, OUTPUT);
}

void func_buzcontrol()
{
  if (wiringPicheck())
    printf("Fail\n");

  signal(SIGINT, (void *)sig_handler);

  int i;
  while (1)
  {
    printf("here \n");

    pinMode(BUZCONTROL, OUTPUT);

    // delay(1000);

    digitalWrite(BUZCONTROL, 1);
    delay(1000);
    digitalWrite(BUZCONTROL, 0);
    delay(1000);
  }
}

void func_dcmotoron()
{
  signal(SIGINT, (void *)sig_handler); //시그널 핸들러 함수

  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
  }

  pinMode(DCMOTOR, OUTPUT);

  for (;;)
  {
    // printf("here - DCMOTOR on\n");
    digitalWrite(DCMOTOR, 1); // On
  }
}

void func_rgbtest()
{
  signal(SIGINT, (void *)sig_handler); //시그널 핸들러 함수

  if (wiringPiSetup() == -1)
  {
    fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
  }

  pinMode(RGBLEDPOWER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  int i;

  for (i = 0; i < 10; i++)
  {

    digitalWrite(RGBLEDPOWER, 1);

    digitalWrite(RED, 1);
    digitalWrite(BLUE, 0);
    digitalWrite(GREEN, 0);

    delay(1000);

    digitalWrite(RED, 0);
    digitalWrite(BLUE, 1);
    digitalWrite(GREEN, 0);

    delay(1000);

    digitalWrite(RED, 0);
    digitalWrite(BLUE, 0);
    digitalWrite(GREEN, 1);

    delay(1000);
  }
  digitalWrite(GREEN, 0);
}

void func_allrgbcolor()
{
  if (wiringPicheck())
    printf("Fail");

  Bpluspinmodeset_RGB();

  signal(SIGINT, (void *)sig_handler);

  int i;
  digitalWrite(RGBLEDPOWER, 1);

  while (1)
  {

    int i = 0, j = 0, k = 0;
    printf("RGB LED Various Color");

    softPwmCreate(RED, 0, 255);
    softPwmCreate(GREEN, 0, 255);
    softPwmCreate(BLUE, 0, 255);

    for (i = 0; i <= 250; i = i + 10)
    {
      for (j = 0; j <= 250; j = j + 10)
      {
        for (k = 0; k <= 250; k = k + 10)
        {
          setRGB(i, j, k);
          delay(50);
          printf("R:%d G:%d B:%d\n", i, j, k);
        }
      }
    }

    setRGB(0, 0, 0); // clear LED
    delay(50);
  }
}
void setRGB(int r, int g, int b)
{
  softPwmWrite(RED, 255 - r);
  softPwmWrite(GREEN, 255 - g);
  softPwmWrite(BLUE, 255 - b);
}

void Bpluspinmodeset_RGB(void)
{
  pinMode(RGBLEDPOWER, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}
//////////////종료 함수/////////////////
void sig_handler(int signo)
{
  printf("process stop\n");
  // All Actuator Off
  digitalWrite(PUMP, 0);
  digitalWrite(FAN, 0);
  digitalWrite(BUZCONTROL, 0);
  digitalWrite(LEDCONTROL, 0);
  digitalWrite(RGBLEDPOWER, 0);
  digitalWrite(DCMOTOR, 0);
  digitalWrite(RED, 0);
  digitalWrite(BLUE, 0);
  digitalWrite(GREEN, 0);
  exit(0);
}