// Số lượng led
const int numLEDs = 7;

// Chân nhận tín hiệu chế độ nút ấn
const int buttonPin = 9;

// Chân nhận tín hiệu từ chiết áp
const int potPin = A0;

// Các chân output
int ledPins[] = {2, 3, 4, 5, 6, 7, 8};

int buttonState = 0;
int previousButtonState = 0;
int mode = 1;
int speed;
bool modeComplete = false;

// Biến cờ để điều khiển hiệu ứng mờ dần
bool isFading = false;

void setup()
{
    for (int i = 0; i < numLEDs; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
    pinMode(buttonPin, INPUT_PULLUP);
    // Khởi tạo giao tiếp Serial để in thông báo (tuỳ chọn)
    Serial.begin(9600);
}

void loop()
{
    buttonState = digitalRead(buttonPin);
    if (buttonState != previousButtonState && buttonState == LOW)
    {
        if (mode == 1)
        {
            mode = 2;
        }
        else
        {
            mode = 1;
        }
        // Bật hiệu ứng mờ dần khi chuyển đổi chế độ
        isFading = true;
    }
    previousButtonState = buttonState;

    // speed = map(analogRead(potPin), 0, 1023, 50, 1000);
    speed = map(analogRead(potPin), 0, 1023, 100, 2000);
    Serial.print("Chế độ chạy:");
    Serial.println(mode);
    Serial.print("Speed hiện tại:");
    Serial.println(speed);

    if (modeComplete)
    {
        modeComplete = false;
        while (digitalRead(buttonPin) == HIGH)
        {
            // Hiệu ứng mờ dần khi chuyển đổi chế độ
            for (int i = numLEDs - 1; i >= 0; i--)
            {
                analogWrite(ledPins[i], 0);
                delay(50);
            }
            isFading = false;
            Serial.println("Chờ lệnh mới...");
        }
    }
    else
    {
        if (isFading)
        {
            // Hiệu ứng mờ dần khi bắt đầu chế độ mới
            // for (int i = 0; i < numLEDs; i++) {
            //   analogWrite(ledPins[i], 255);
            //   delay(50);
            // }
            isFading = false;
        }

        if (mode == 1)
        {
            // Chế độ 1: Nháy từ LED 1 đến LED 7
            for (int i = 0; i < numLEDs; i++)
            {
                digitalWrite(ledPins[i], HIGH);
                delay(100);
                digitalWrite(ledPins[i], LOW);
                delay(speed);
            }
        }
        else
        {
            // Chế độ 2: Nháy từ LED 7 đến LED 1
            for (int i = numLEDs - 1; i >= 0; i--)
            {
                digitalWrite(ledPins[i], HIGH);
                delay(100);
                digitalWrite(ledPins[i], LOW);
                delay(speed);
            }
        }
        modeComplete = true;
    }
}