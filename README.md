# Descripe progress
This project is processing signal PPG and PCG by C language on the PC. After that i will embedded this 
code into ESP32 to calculate the heart rate, blood pressure. 
Before i implement this project i processing PPG and PCG signal by Python language. So i have algorthim
to processing signal.
This is PPG anfd PCG signal


- What is PPG
    - **PPG** is the light on the skin of human. When blood run into the body of human, blood will make the color on the skin changes.
    - We use MAX30102 sensor to measure PPG signal. We set up sensor on the surface of finger.
- What is PCG
    - **PCG** is the sound of heart. When the heart operate will make the sound. So we use microphone place it on the chest.
    - We use INMP441 sensor to measure the sound of heart. But the sound of heart is very small so the sensor can't collect data from heart. So we use medical stethosope to amplifier the sound.
- Synchronize data
    - When measure PPG and PCG signal, the first PPG value and the first PCG value is same time ?
    - The result is not same time. So we need to synchronize data.
## The goal after this project done
i wil write code C to calculate SPO2 and display the heart rate, blood pressure, SPO2 on TFT display. 

