#include <stdio.h>
#include <signal.h> //Signal 사용 헤더파일
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> //exit() 사용 헤더파일

#include <wiringPi.h>
#include <softPwm.h>

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

int main(void)
{

  int answer;
  printf("1. 워터펌프, 2. 팬, 3.LED Bar 제어, 4. LED Bar 제어(PWM), 5. 부저, 6. DC Motor, 7. RGB Led, 8. RGB Led (PWM), 9. 종료\n");
  scanf("%d", &answer);
  while (TRUE)
  {
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

/*** 워터펌프 동작 ***/
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
