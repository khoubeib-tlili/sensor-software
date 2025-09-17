#include "LoRaRadio.h"

LoRaRadio::LoRaRadio(uint8_t nss, uint8_t dio0, uint8_t nreset, SPIClass& spi)
    : _module(nss, dio0, nreset, -1, spi),   // construct Module first
      _radio(&_module)
{}

bool LoRaRadio::init(float freq, int bandwidth, int spreadingFactor, int codingRate, int gain) {
    Serial.println("[DEBUG] LoRaRadio::init() starting...");

    int state = _radio.begin();
    if (state != RADIOLIB_ERR_NONE) {
        Serial.print("[ERROR] RadioLib begin failed, code: "); Serial.println(state);
        logRadioError("RadioLib begin failed", state);
        return false;
    }
    Serial.println("[DEBUG] begin() OK");

    state = _radio.setFrequency(freq);
    if (state != RADIOLIB_ERR_NONE) { Serial.print("[ERROR] setFrequency failed, code: "); Serial.println(state); logRadioError("setFrequency", state); return false; }
    Serial.print("[DEBUG] Frequency set to "); Serial.println(freq);

    state = _radio.setBandwidth(bandwidth);
    if (state != RADIOLIB_ERR_NONE) { Serial.print("[ERROR] setBandwidth failed, code: "); Serial.println(state); logRadioError("setBandwidth", state); return false; }
    Serial.print("[DEBUG] Bandwidth set to "); Serial.println(bandwidth);

    state = _radio.setSpreadingFactor(spreadingFactor);
    if (state != RADIOLIB_ERR_NONE) { Serial.print("[ERROR] setSpreadingFactor failed, code: "); Serial.println(state); logRadioError("setSpreadingFactor", state); return false; }
    Serial.print("[DEBUG] SpreadingFactor set to "); Serial.println(spreadingFactor);

    state = _radio.setCodingRate(codingRate);
    if (state != RADIOLIB_ERR_NONE) { Serial.print("[ERROR] setCodingRate failed, code: "); Serial.println(state); logRadioError("setCodingRate", state); return false; }
    Serial.print("[DEBUG] CodingRate set to "); Serial.println(codingRate);

    state = _radio.setGain(gain);
    if (state != RADIOLIB_ERR_NONE) { Serial.print("[ERROR] setGain failed, code: "); Serial.println(state); logRadioError("setGain", state); return false; }
    Serial.print("[DEBUG] Gain set to "); Serial.println(gain);

    Serial.println("[DEBUG] LoRa init complete!");
    return true;
}

void LoRaRadio::setTransmitMode(float freq, int power) {
    int state = _radio.setFrequency(freq);
    if (state != RADIOLIB_ERR_NONE) { logRadioError("setFrequency (TX)", state); }
    state = _radio.setOutputPower(power);
    if (state != RADIOLIB_ERR_NONE) { logRadioError("setOutputPower", state); }

    addElementToFile("LoRa", "Transmit mode set");
}

void LoRaRadio::setReceiveMode(float freq) {
    int state = _radio.setFrequency(freq);
    if (state != RADIOLIB_ERR_NONE) { logRadioError("setFrequency (RX)", state); }
    state = _radio.startReceive();
    if (state != RADIOLIB_ERR_NONE) { logRadioError("startReceive", state); }

    addElementToFile("LoRa", "Receive mode set");
}

int LoRaRadio::transmitData(const char* data) {
    int state = _radio.startTransmit(data);
    if (state == RADIOLIB_ERR_NONE) {
        String msg = String("Transmitted: ") + String(data);
        addElementToFile("LoRa", msg.c_str());
    } else {
        logRadioError("startTransmit", state);
    }
    return state;
}

int LoRaRadio::readData(String& str) {
    int state = _radio.readData(str);
    if (state > 0) {
        String msg = String("Received: ") + str;
        addElementToFile("LoRa", msg.c_str());
    } else if (state != RADIOLIB_ERR_NONE) {
        // optional error log
    }
    return state;
}

int LoRaRadio::readData(uint8_t* buf, size_t bufLen, size_t* outLen) {
    int state = _radio.readData(buf, bufLen);
    if (state > 0) {
        if (outLen) *outLen = (size_t)state;
        addElementToFile("LoRa", "Received binary data");
    } else if (state != RADIOLIB_ERR_NONE) {
        logRadioError("readData(uint8_t*)", state);
    }
    return state;
}

int LoRaRadio::getRSSI() {
    int rssi = _radio.getRSSI();
    String msg = String("RSSI: ") + String(rssi);
    addElementToFile("LoRa", msg.c_str());
    return rssi;
}

float LoRaRadio::getSNR() {
    float snr = _radio.getSNR();
    String msg = String("SNR: ") + String(snr, 2);
    addElementToFile("LoRa", msg.c_str());
    return snr;
}

void LoRaRadio::setPacketReceivedAction(void (*func)(void)) {
    _radio.setPacketReceivedAction(func);
    addElementToFile("LoRa", "Packet received handler set");
}

void LoRaRadio::setPacketSentAction(void (*func)(void)) {
    _radio.setPacketSentAction(func);
    addElementToFile("LoRa", "Packet sent handler set");
}

int LoRaRadio::startReceive() {
    int state = _radio.startReceive();
    if (state != RADIOLIB_ERR_NONE) {
        logRadioError("startReceive (manual)", state);
    }
    return state;
}

SX1278& LoRaRadio::getRadio() {
    return _radio;
}

void LoRaRadio::printStatus() {
    Serial.println("---- LoRa Status ----");
    Serial.print("RSSI: "); Serial.println(getRSSI());
    Serial.print("SNR: "); Serial.println(getSNR());
    Serial.println("---------------------");
}

void LoRaRadio::logRadioError(const String& context, int code) {
    String msg = context + " failed, RadioLib code: " + String(code);
    addElementToFile("LoRaError", msg.c_str());
}
