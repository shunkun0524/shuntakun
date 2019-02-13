#include<stdio.h>
#include<handy.h>
#include<stdlib.h>
#include<time.h> //乱数のために
#include<stdbool.h> //乱数のために
#include<math.h> //pow関数のために

#define CIRCLEMAXCOUNT 20
#define WINDOWSIZE 600
#define TIME 10

void Initialize();/*初期化*/
void DrawCircle();/*円を描く関数*/
void MouseDraged();/*マウスドラッグを検知する関数*/
void Run();/*全体の処理を行う関数*/
bool isEvent();/*イベントが発生したかを決める関数*/
void FinishProcess();/*終わりの処理*/
void MoveCircle();/*円を動かす関数*/
void AcceleChange();
bool isEndType();/*キーボードが叩かれると終了する関数*/
void RangeControl();/*円の描く範囲を決定する関数*/
bool CollisionJudgement();/*マウスが円と衝突したか判定する関数*/
bool isCollision(int i);/*マウスが円と衝突したか判定する関数*/
void GameStart();/*ゲームを始める前に行う処理をする関数*/
void GameOver();/*Game Overを表示させる関数*/
bool isContinue();/*ゲームを続けるかどうか判定する関数*/
void Timer();
void CircleNumberInitialize(int number);/*円をそれぞれ初期化する関数*/
void TimerUP();/*10秒たったら+10する関数*/
void MouseFollow();/*マウスを円が追いかける設定をする関数*/

struct circle{
  int x;
  int y;
  int r;
  int vx;
  int vy;
  int color;
};
struct circle cc[CIRCLEMAXCOUNT];

struct userpoint{
  int x;
  int y;
};
struct userpoint up;

hgevent *event;
int circlecount;
int timer=0;
/*円の初期化を呼び出す関数*/
void CircleInitialize(){
  for(int i=0;i< circlecount;i++){
    CircleNumberInitialize(i);
  }
}
/*円をそれぞれ初期化する関数*/
void CircleNumberInitialize(int number) {
    cc[number].x = rand()%500;
    cc[number].y = rand()%500;
    cc[number].r = rand()%150;
    cc[number].color=rand()%5;
    cc[number].vx=(rand()%40)-20;
    cc[number].vy=(rand()%40)-20;
}
/*マウスを円が追いかける設定をする関数*/  
void MouseFollow(){
  int x=up.x-cc[0].x;
  int y=up.y-cc[0].y;

  if(x!=up.x){
    if(x>=0){
      cc[0].x+=5;
    }else{
      cc[0].x-=5;
    }    
  }
  if(y!=up.y){
    if(y>=0){
      cc[0].y+=5;
    }else{
      cc[0].y-=5; 
    }    
  }
}
/*初期化*/
void Initialize(){
  HgSetIntervalTimer(TIME);
  circlecount=2;
  srand(time(NULL));
  CircleInitialize();
}


void AcceleChange(){
  for(int i=0; i< circlecount; i++) {
    cc[i].vx=(rand()%40)-20;
    cc[i].vy=(rand()%40)-20;
  }
}
/*円の描く範囲を決定する関数*/
void RangeControl() {
  for(int i=0; i< circlecount; i++) {
    if(cc[i].x<=0 || cc[i].x>=WINDOWSIZE) {
      cc[i].x=cc[i].x-cc[i].vx;
    }
    if(cc[i].y<=0 || cc[i].y>=WINDOWSIZE) {
      cc[i].y=cc[i].y-cc[i].vy;
    }
  }
}
/*円を動かす関数*/
void MoveCircle() {
  AcceleChange();
  for(int i=1; i< circlecount; i++) {
    cc[i].x=cc[i].x+cc[i].vx;
    cc[i].y=cc[i].y+cc[i].vy;
  }
}
/*円の色を決定する関数*/
void ColorDetermination(int i) {
    switch(cc[i].color){
      case 0:
	HgSetFillColor(HG_RED);
	break;
      case 1:
	HgSetFillColor(HG_GREEN);
	break;
      case 2:
	HgSetFillColor(HG_BLUE);
	break;
      case 3:
	HgSetFillColor(HG_BLACK);
	break;
      case 4:
	HgSetFillColor(HG_WHITE);
	break;
    }
}
/*円を描く関数*/
void DrawCircle() {
  HgClear();
  for(int i=0;i< circlecount;i++){
    ColorDetermination(i);
    HgCircleFill(cc[i].x,cc[i].y,cc[i].r,1);
  }
  HgSleep(0.05);
}
/*ゲームを始める前に行う処理をする関数*/
void GameStart() {
  for(;;) {
    HgSetFillColor(HG_BLUE);
    HgBoxFill(0,0,WINDOWSIZE,WINDOWSIZE,1);
    char array[]="マウスを置いてください";
    if(isEvent()){
      up.x=(int)event->x;
      up.y=(int)event->y;
      if((up.x>(WINDOWSIZE/10)*3 || up.x<(WINDOWSIZE/10)*3) && (up.y>(WINDOWSIZE/10)*4 || up.x< (WINDOWSIZE/10)*6)) {
	break;
      }
    }
    HgSetFont(HG_M,50.0);
    HgSetColor(HG_RED);
    HgText((WINDOWSIZE/60)*1,(WINDOWSIZE/10)*6,array);
    HgSleep(0.05);
  }
}
/*マウスドラッグを検知する関数*/
void MouseDraged(){
  up.x=(int)event->x;
  up.y=(int)event->y;
  printf("%d %d\n",up.x,up.y);
}
/*マウスがウィンドウの外に出たか判定する関数*/
bool OutOfWindow(){
  return (up.x<0 || up.x>WINDOWSIZE) || (up.y<0 || up.y>WINDOWSIZE);
}
/*マウスが円と衝突したか判定する関数*/
bool isCollision(int i){
  if((pow(up.x-cc[i].x,2)+pow(up.y-cc[i].y,2))<= pow(cc[i].r,2)){
    return true;
  }else{
    return false;
  }
}
/*マウスが円と衝突したか判定する関数*/
bool CollisionJudgement() {
  for(int i=0;i< circlecount;i++){
    if(isCollision(i)){
      HgBeep();
      printf("%d 衝突\n",i);
      return true;
    }
  }
  return false;
}  
/*イベントが発生したかを決める関数*/
bool isEvent(){
  HgSetEventMask(HG_MOUSE_MOVE | HG_KEY_DOWN);
  event = HgEventNonBlocking();
  return event != NULL;
}
/*キーボードが叩かれると終了する関数*/
bool isEndType(){
  if(event->type == HG_KEY_DOWN){
    return true;
  }else{
    return false;
  }
}
/*10秒たったら+10する関数*/
void TimerUP(){
  if(event->type == HG_TIMER_FIRE){
    timer=timer+10;
  }
}

/*全体の処理を行う関数*/
void Run(){
  while(1){
    if(isEvent()){
      TimerUP();
      if(event->type == HG_TIMER_FIRE && circlecount<CIRCLEMAXCOUNT){
	circlecount++;
	CircleNumberInitialize(circlecount-1);
	HgBeep();
	printf("難易度UP\n");
      }else if(isEndType() || OutOfWindow()){
	printf("%d秒逃げました\n",timer);
	break;
      }else if(event->type == HG_MOUSE_MOVE){
	MouseDraged();
      }
    }else{
      MouseFollow();
      MoveCircle();
      RangeControl();
      DrawCircle();
      if(CollisionJudgement()) {
	printf("%d秒逃げました\n",timer);
	break;
      }
    }
  }
}

/*ゲームを続けるかどうか判定する関数*/
bool isContinue() {
  if(HgAlert("コンテニューしますか?","はい","いいえ",NULL)==0) {
    up.x=0;
    up.y=0;
    return true;
  }else {
    return false;
  }
}
/*Game Overを表示させる関数*/
void GameOver(int timer) {
  char array[]="Game Over";
  HgClear();
  HgSetFont(HG_BLACK,100.0);
  HgText(50,300,array);
}
/*終わりの処理*/
void FinishProcess() {
  HgClose();
}
int main() {
  HgOpen(WINDOWSIZE,WINDOWSIZE);
  for(;;) {
    GameStart();
    Initialize();
    Run();
    GameOver(timer);
    if(isContinue()==false) {
      break;
    }
  }
  FinishProcess();
  return 0;
}



