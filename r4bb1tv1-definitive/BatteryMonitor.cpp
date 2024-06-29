#include "BatteryMonitor.h"

BatteryMonitor::BatteryMonitor(int pin) : _pin(pin) {}

void BatteryMonitor::begin() {
    pinMode(_pin, INPUT);
}

float BatteryMonitor::readVoltage() {
    // Leitura analógica do pino (0 a 1023)
    int sensorValue = analogRead(_pin);
    // Calcular a tensão da bateria a partir do valor do sensor
    float voltage = sensorValue * (3.7 / 280.0);
    return voltage;
}

float BatteryMonitor::getBatteryVoltage() {
    return readVoltage();
}

int BatteryMonitor::getBatteryPercentage() {
    const float minVoltage = 3.0; // Tensão mínima para 0%
    const float maxVoltage = 4.1; // Tensão máxima para 100%
    const int threshold = 5; // Limiar de mudança para atualizar a porcentagem (por exemplo, 5%)
    
    float voltage = getBatteryVoltage();
    int newPercentage = (int)((voltage - minVoltage) / (maxVoltage - minVoltage) * 100);
    newPercentage = max(min(newPercentage, 100), 0); // Garante que a porcentagem esteja entre 0 e 100

    static int lastPercentage = -1; // Valor inicial inválido para forçar a primeira atualização

    // Atualiza somente se a mudança for maior que o limiar ou se for a primeira leitura
    if (lastPercentage == -1 || abs(lastPercentage - newPercentage) >= threshold) {
        lastPercentage = newPercentage;
        // Atualiza a barra de bateria aqui ou retorna o valor para ser usado em outro lugar
    }

    return lastPercentage;
}