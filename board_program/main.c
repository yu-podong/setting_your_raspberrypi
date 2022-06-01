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
#define FLAME_IN 5  //gpio7
#define MOYION_IN 0  //gpio17
#define MAXTIMINGS 85
#define CS_MCP3208 8 //GPIO 8 
#define SPI_CHANNEL 0 
#define SPI_SPEED 1000000 //1Mhz
#define LIGHTSEN_OUT 2  //gpio27 - J13 connect
#define trigPin 1	//gpio 21
#define echoPin 29	//gpio 18

/* actuator */
#define PUMP 21   // BCM_GPIO 5
#define FAN 22    // BCM_GPIO 6
#define LEDBAR 26 // BCM_GPIO 12
//#define MOTORCONTROL  22	//GPIO 6 - Motor
#define LEDCONTROL 26 // LED Bar (ledbarsoftpwm)
// const int LEDCONTROL 21 //
#define BUZCONTROL 28 // GPIO 20
#define DCMOTOR 23    // BCM_GPIO 13
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
//static int DHTPIN = 7;
static int DHTPIN = 11;
static int dht22_dat[5] = { 0,0,0,0,0 };


//---------------------------------------------함수 원형 part---------------------------------------------
/* sensor는 함수원형 작성 필요 */

/* actuator */
void func_pumpon();
void func_fanon();
void func_ledbar();
//하나파일
void func_ledbarsoftpwm();
int wiringPicheck(void);
void Bpluspinmodeset(void);
//

void func_buzcontrol();
void func_dcmotoron();
void func_rgbtest();

//하나 파일
void func_allrgbcolor();
void Bpluspinmodeset_RGB(void);
void setRGB(int r, int g, int b);
//

void sig_handler(int signo); // 마지막 종료 함수


//---------------------------------------------main function part---------------------------------------------
int main(void)
{
  int answer;
  
  printf("1. 워터펌프, 2. 팬, 3.LED Bar 제어, 4. LED Bar 제어(PWM), 5. 부저, 6. DC Motor, 7. RGB Led, 8. RGB Led (PWM), 9. 종료\n");
  scanf("%d", &answer);
  
  while (TRUE)
  {
  	// sensor도 아래처럼 작성 필요 
  	
  	// actuator 
    if (answer == 1)
      func_pumpon();
    else if (answer == 2)
      func_fanon();
    else if (answer == 3)
      func_ledbar();
    else if (answer == 4)
      func_ledbarsoftpwm();
    else if (answer == 5)
      func_buzcontrol();
    else if (answer == 6)
      func_dcmotoron();
    else if (answer == 7)
      func_rgbtest();
    else if (answer == 8)
      func_allrgbcolor();
    else if (answer == 9)
      return 0; //종료
  }

  return 0;
}


//---------------------------------------------function definiton part---------------------------------------------
/* sensor */
// myInterrupt:  called every time an event occurs
void myInterrupt(void) {
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
    for (i = 0; i < MAXTIMINGS; i++) {
        counter = 0;
        while (sizecvt(digitalRead(DHTPIN)) == laststate) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = sizecvt(digitalRead(DHTPIN));

        if (counter == 255) break;

        // ignore first 3 transitions
        if ((i >= 4) && (i % 2 == 0)) {
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
        (dht22_dat[4] == ((dht22_dat[0] + dht22_dat[1] + dht22_dat[2] + dht22_dat[3]) & 0xFF))) {
        float t, h;

        h = (float)dht22_dat[0] * 256 + (float)dht22_dat[1];
        h /= 10;
        t = (float)(dht22_dat[2] & 0x7F) * 256 + (float)dht22_dat[3];
        t /= 10.0;
        if ((dht22_dat[2] & 0x80) != 0)  t *= -1;

        ret_humid = (int)h;
        ret_temp = (int)t;
        //printf("Humidity = %.2f %% Temperature = %.2f *C \n", h, t );
        //printf("Humidity = %d Temperature = %d\n", ret_humid, ret_temp);

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

int flamedetect(void) {
    // sets up the wiringPi library
    if (wiringPiSetup() < 0) {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }

    // set Pin 17/0 generate an interrupt on high-to-low transitions
    // and attach myInterrupt() to the interrupt
    if (wiringPiISR(FLAME_IN, INT_EDGE_FALLING, &myInterrupt) < 0) {
        fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
        return 1;
    }

    // display counter value every second.
    while (1) {
        printf("%d\n", eventCounter);
        //eventCounter = 0;
        delay(1000); // wait 1 second
    }

    return 0;
}

int gasdetect(void) {
    // sets up the wiringPi library
    if (wiringPiSetup() < 0) {
        fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
        return 1;
    }

    // set Pin 17/0 generate an interrupt on high-to-low transitions
    // and attach myInterrupt() to the interrupt
    if (wiringPiISR(MOYION_IN, INT_EDGE_FALLING, &myInterrupt) < 0) {
        fprintf(stderr, "Unable to setup ISR: %s\n", strerror(errno));
        return 1;
    }

    // display counter value every second.
    while (1) {
        printf("%d\n", eventCounter);
        //eventCounter = 0;
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

int getlightsensor(void) {

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

        //printf("Humiity = %u temparature = %u\n", adcValue_humi, adcValue_temp);
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
        //printf( "%d\n", eventCounter );
        //eventCounter = 0;

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

        while (digitalRead(echoPin) == LOW);

        startTime = micros();

        while (digitalRead(echoPin) == HIGH);
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
  digitalWrite(DCMOTOR, 0);
  digitalWrite(RED, 0);
  digitalWrite(BLUE, 0);
  digitalWrite(GREEN, 0);
  exit(0);
}