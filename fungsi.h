// Curah hujan 1 mm adl jml air hujan yang jatuh di permukaan per satuan luas (m2) dengan volume sbnyk 1 liter tanpa ada yang menguap, meresap/mengalir.

// Tinggi curah hujan (cm) = volume yang dikumpulkan (mL) / area pengumpulan (cm2)
// Luas kolektor phi x r kuadrat 3.14 x (3.55x3.55) = 39,57 cm2
// Koleksi per ujung tip kami dapat dengan cara menuangkan 100ml air ke kolektor kemudian menghitung berapa kali air terbuang dari tip,
// Dlm perhitungan yang kami lakukan air terbuang sebanyak 70 kali. 100ml / 70= 1.42mL per tip.
// Jadi 1 tip bernilai 1.42 / 39,57 = 0,03cm atau 0.30 mm curah hujan.

// - Per tip 0,30 mm.
// - Tegangan 5v/3.3v.
// - Menggunakan pin interrupt.


#ifndef PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#define PENDETEKSI_KEBAKARAN_HUTAN_FUNGSI_H
#include <config.h>

// MEMBACA SENSOR DHT
void readDhtSensor(float &temp, float &humd)
{
    // DHT22
    temp = dht.readTemperature();
    humd = dht.readHumidity();
    
}

// MEMBACA SENSOR MOISTURE
void readMoistureSensor(float &moisture){
    // moisture
    float result = 0;
    float value = 0;

    for (int i = 0; i < 30; i++)
    {
        float readValue = analogRead(MOISTUREPIN)-1690;
        if (readValue < 0){
            readValue = 0;
        }

        Serial.println(readValue);
        value += readValue;
        delay(1000);
    }

    result = value / 30;
    // persentase moisture dengan nilai max 2050
    moisture = (100 - ( (result/2405.00) * 100 ));
}

// MENGHITUNG JUMLAH TIP PADA RAIN GAUGE
void readTip(){
    jumlah_tip++;
}

// MEMBACA SENSOR MQ4
void readMQ4(float &co){
    float value = 0;

    for (int i = 0; i < 20; i++)
    {
        mq2.update();
        float readValue = mq2.readSensor();

        Serial.println(readValue);
        value += readValue;
        delay(1000);
    }

    co = value / 20;
}

// MENGIRIM DATA MELALUI LORA
void sendDataLora(float temp, float humd, float moisture, float co, int jumlahTip){

    //display to serial monitor
    Serial.println("====== Data ======");
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humd);
    Serial.print("Moisture: ");
    Serial.println(moisture);
    Serial.print("CO: ");
    Serial.println(co);
    Serial.print("Jumlah Tip: ");
    Serial.println(jumlahTip);
    Serial.println("====== End Data ======");
    // LoRa
    // String data = String(temp) + "," + String(humd) + "," + String(moisture) + "," + String(co) + "," + String(jumlahTip);
    // LoRa.beginPacket();
    // LoRa.print(data);
    // LoRa.endPacket();
    // Serial.println("====== Paket Send =======");
    // Serial.print("Mengirim Data: " + data);
    // Serial.println("\n====== End Paket =======");
    
}

#endif
