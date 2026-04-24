# WiFi FPV RC CAR using ESP32-CAM 

## What is this project
this project is a wifi controller rc car build using esp32-cam for main chasis and esp32 for controller
instead of using traditional remote, i make my own custom controller using esp32, joystick and screen

## How its works
the esp32 of controller and esp32-cam are connected via wifi and send signals like:

joystick -> controller [esp32] -> esp32 cam -> move / stop motor
camera -> esp32cam -> controller -> show on screen


##BOM

| Component                         | Purpose                                                    | Quantity | Total Cost (USD) | Link                                                                                                                                                                                                                                                           | Distributor       |
| --------------------------------- | ---------------------------------------------------------- | -------- | ---------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ----------------- |
| 3S Battery Holder                 | Holds 3×18650 cells in series (≈11.1V for motors + system) | 1        | 0.30             | [https://robocraze.com/products/18650-3-cell-holder-charger-without-cover](https://robocraze.com/products/18650-3-cell-holder-charger-without-cover)                                                                                                           | Robocraze         |
| 2S Battery Holder                 | Holds 2×18650 cells for controller power                   | 1        | 0.37             | [https://robocraze.com/products/18650-2-cell-holder](https://robocraze.com/products/18650-2-cell-holder)                                                                                                                                                       | Robocraze         |
| 4700µF 25V Electrolytic Capacitor | Stabilizes power and reduces motor noise                   | 1        | 1.05             | [https://robocraze.com/products/4700uf-25v-electrolytic-capacitor](https://robocraze.com/products/4700uf-25v-electrolytic-capacitor)                                                                                                                           | Quartz Components |
| Buck Converter (LM2596)           | Steps down ~11.1V to 5V/3.3V for ESP32 boards              | 2        | 1.20             | [https://robocraze.com/products/lm2596-dc-dc-buck-module](https://robocraze.com/products/lm2596-dc-dc-buck-module)                                                                                                                                             | Robocraze         |
| 18650 3.7V Battery Cells          | Power source (3 for car, 2 for controller)                 | 5        | 7.60             | [https://robocraze.com/products/18650-2200mah-3-7v-battery-cylinder-type-blue](https://robocraze.com/products/18650-2200mah-3-7v-battery-cylinder-type-blue)                                                                                                   | Robocraze         |
| ESP32-CAM                         | Main car controller + camera streaming                     | 1        | 6.00             | [https://robokits.co.in/wireless-solutions/iot-esp-module/esp32-cam-development-board-wifi-bluetooth-with-ov2640-camera-module](https://robokits.co.in/wireless-solutions/iot-esp-module/esp32-cam-development-board-wifi-bluetooth-with-ov2640-camera-module) | Robokits          |
| TB6612FNG Motor Driver            | Controls direction and speed of DC motors                  | 1        | 1.70             | [https://robocraze.com/products/tb6612fng-dual-dc-motor-driver](https://robocraze.com/products/tb6612fng-dual-dc-motor-driver)                                                                                                                                 | Robocraze         |
| DC Motors (12V, ~1000RPM)         | Drive wheels for movement                                  | 4        | 7.54             | [https://robu.in/product/1000rpm-12v-low-noise-dc-motor-with-metal-gears-grade-a/](https://robu.in/product/1000rpm-12v-low-noise-dc-motor-with-metal-gears-grade-a/)                                                                                           | Robu              |



### System flow

![System Flow](image/circuit/car.png)

The basic plan for comunication between the controller and cas is as follows:

- read input from joystick esp32 [controller]
- send the command over wifi to ep32cam [chasis]
- esp32 cam will send the execute the command and send command to motor driver and its move the car

- esp32 cam will capture video
- send over wifi to esp32 [controller] and then showed on screen
- 

### controller design

![Controller CAD](image/cad/controller/body.png)
![Controller Components](image/cad/controller/components.png)

the controller have following compoents:

- esp32
- dual joystick
- tft screen


### Car Design


<img width="1512" height="982" alt="Screenshot 2026-04-08 at 3 59 20 PM" src="https://github.com/user-attachments/assets/95652409-0f2b-4569-8e94-55672e0f3507" />

<img width="1512" height="982" alt="Screenshot 2026-04-08 at 3 57 22 PM" src="https://github.com/user-attachments/assets/3ddd3f24-135c-42bc-a1c6-cfa944a9f308" />

<img width="1512" height="982" alt="Screenshot 2026-04-08 at 3 56 59 PM" src="https://github.com/user-attachments/assets/6586fd46-9378-4f66-b407-0553907b10b1" />




The car is designed using the following components:

- ESP32-CAM
- Motor driver
- 4 DC motors
- Battery system

---

### Circuit Setup

![Circuit](image/circuit/controller.png)

- motor driver connected to esp32-cam
- buck converter used to decrease the voltage for esp32
- capacitor reduce motor noice
## Code

### Car (`car.cpp`)
- runs HTTP server
- receives commands
- controls motors
- captures image 

### Controller (`controller.cpp`)
- read joystick input
- converts them into commands
- send over wifi

## learnings
- reduced design from 3 boards to 2 boards [in start my idea was to use 3 boards 2 for chasis so that esp32-cam send signal to car esp32 then controller esp32]
- fixed motor noice using capactors
- learned esp32 wifi comunication
- learned how screen and esp32-cam works

## How to run
1. Upload `car.cpp` to ESP32-CAM
2. Upload `controller.cpp` to ESP32
3. Connect both to same WiFi
4. Update IP in controller
5. Power both
6. Use joystick


how it should look after build
<img width="1512" height="982" alt="Screenshot 2026-04-08 at 4 30 43 PM" src="https://github.com/user-attachments/assets/55dfd37e-2460-4e56-82d4-07e1aff73da2" />

