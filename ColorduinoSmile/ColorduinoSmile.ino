#include <Colorduino.h> // 匯入Colorduino程式庫

// 定義按鈕開關的腳位
#define BUTTON_LEFT_PIN 2
#define BUTTON_RIGHT_PIN 5

// 定義顏色值
PixelRGB COLOR_BLACK = {0, 0, 0};
PixelRGB COLOR_RED = {255, 0, 0};
PixelRGB COLOR_GREEN = {0, 255, 0};
PixelRGB COLOR_BLUE = {0, 0, 255};

// pic_winner二維陣列儲存勝利時應顯示的圖案，pic_loser則是輸掉時
PixelRGB pic_winner[ColorduinoScreenWidth][ColorduinoScreenHeight] = {
  {COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_GREEN}, 
  {COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK}, 
  {COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK}, 
  {COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK}, 
  {COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_GREEN}, 
  {COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_GREEN, COLOR_BLACK},
};

PixelRGB pic_loser[ColorduinoScreenWidth][ColorduinoScreenHeight] = {
  {COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED}, 
  {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK}, 
  {COLOR_BLACK, COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_RED}, 
  {COLOR_RED, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_BLACK, COLOR_RED, COLOR_BLACK}, 
};

// 傳入含有想要顯示圖案的資料，此函式負責將資料透過Colorduino程式庫顯示在LED矩陣
void displayPixelRGBData(PixelRGB pic[ColorduinoScreenWidth][ColorduinoScreenHeight])
{
  int w, h, p;
  for(w = 0; w < ColorduinoScreenWidth; w++){
    for(h = 0; h < ColorduinoScreenHeight; h++){
      Colorduino.SetPixel(w, h, pic[w][h].r, pic[w][h].g, pic[w][h].b);
    }
  }
  Colorduino.FlipPage();
}

// 程式一開始會執行一次的設定函式setup()
void setup()
{
  pinMode(BUTTON_LEFT_PIN, INPUT);
  pinMode(BUTTON_RIGHT_PIN, INPUT);
  
  Serial.begin(57600);
  
  // 初始化Colorduino物件，並設定白平衡
  Colorduino.Init();
  // R, G, B的值介於0~63
  unsigned char whiteBalVal[3] = {36,63,63};
  Colorduino.SetWhiteBal(whiteBalVal);
}

// 不斷重複執行的loop()，在此測試程式裡
// 會讀取按鈕開關的狀態，輸出到序列埠
// 也會重複輪流顯示勝利與輸掉時的圖案（笑臉與哭臉）
void loop()
{
  int button_left_status = digitalRead(BUTTON_LEFT_PIN);
  int button_right_status = digitalRead(BUTTON_RIGHT_PIN);
  if(button_left_status == HIGH){
    Serial.println("Left button pressed");
  }
  if(button_right_status == HIGH){
    Serial.println("Right button pressed");
  }
  
  displayPixelRGBData(pic_loser);
  delay(1000);
  displayPixelRGBData(pic_winner);
  delay(1000);
}


