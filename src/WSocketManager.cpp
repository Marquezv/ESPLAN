#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "SecretKeys.h"
#include "WSocketManager.h"

WSocketManager::WSocketManager(){
  topic_mqtt = TOPIC;
  topic_server_mqtt = TOPIC_SERVER;
  WebSocketsServer webSocket = WebSocketsServer(81);

}

char* formatTopic(const char* sessionId, const char* action, const char *device){
  // Tamanho total necessário para a string retornada
  size_t totalLength = strlen(device) + strlen(sessionId) + strlen(action) + 5; // 2 para o caractere de separação e o caractere nulo
  // Alocando memória para o array de caracteres e copiando os valores
  char* format = new char[totalLength];
  snprintf(format, totalLength, "/%s/%s/%s", device, sessionId, action);
  return format;
}

// JSON
const char **deserializationJson(const char* payload){
  // Allocate JsonBuffer
  StaticJsonDocument<200> doc;

  // Deserialize o JSON
  DeserializationError error = deserializeJson(doc, payload);

    // Verifica se houve erro no processo de deserialização
  if (error) {
      Serial.print("Falha ao deserializar JSON: ");
      Serial.println(error.c_str());
      return {};
  }
  const char* sessionId = doc["session_Id"]; 
  const char* action = doc["action"];

  char* send = formatTopic(sessionId, action, TOPIC);
  char* receive = formatTopic(sessionId, action, TOPIC_SERVER);

  static const char *topic[] = {send, receive}; 
  
  return topic;
}

void event(uint8_t num, WStype_t type, uint8_t* payload, size_t length){
    switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED:
      {
        // IPAddress ip = webSocket.remoteIP(num);
        // Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] Received text: %s\n", num, payload);
    //   const char **topics = deserializationJson((char*)payload);
      // Send a response back to the client
      Serial.printf("[%u] Connected from %d.%d.%d.%d\n", num);
      String echoMessage = "Received:  " + String((char*)payload);
    //   webSocket.sendTXT(num, echoMessage);
    //   messageOverMqtt(topics[0], (char*)payload);
    //   mqttClient.subscribe(topics[1]);
    //   Serial.println(topics[0]);
    //   Serial.println(topics[1]);
      break;
  }
}


void WSocketManager::setup() {
    WebSocketsServer webSocket = webSocket;
    webSocket.begin();
    webSocket.onEvent(event);
}

void WSocketManager::loop() {
    WebSocketsServer webSocket = webSocket;
    webSocket.loop();
}
