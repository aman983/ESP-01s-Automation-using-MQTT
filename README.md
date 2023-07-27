# ESP-01s-Automation
Firmware for ESP 01 S relay development board to control relays using MQTT. The code connects to a Wi-Fi network, subscribes to an MQTT topic, and toggles the relays based on received messages.

## Requirements

- Arduino IDE
- ESP 01 S relay development board
- MQTT broker (e.g., mqtt.eclipseprojects.io)

## Getting Started

1. Connect your  ESP 01 S relay development board to your computer.
2. Open the Arduino IDE and install the required libraries:
   - Arduino Core for ESP8266 (should be installed by default for ESP8266 boards)
   - ESP8266WiFi library
   - PubSubClient library
3. Replace the placeholders in the code with your Wi-Fi credentials (`ssid` and `password`) and MQTT broker address (`mqtt_broker`) if needed.
4. Upload the sketch to your ESP8266 board.
5. Open the Serial Monitor to see the connection status and IP address.

## How It Works

The code connects the ESP8266 to the specified Wi-Fi network (`connectify` function) and MQTT broker (`reconnect` function). It subscribes to the "Relay" topic and waits for messages. The `callback` function processes incoming messages and controls the relays based on the message content (`action` function).

You can publish messages to the "Relay" topic with the following payloads to control the relays:
- "1on": Turn on Relay 1
- "1off": Turn off Relay 1
- "2on": Turn on Relay 2
- "2off": Turn off Relay 2

## Functions

- `connectify(const char* network, const char* pass)`: Connects the device to the specified Wi-Fi network.
- `action(String topic, String message)`: Modifies this function to take action when a specified message is published on a particular topic.
- `callback(String topic, byte* message, unsigned int length)`: Receives the message information from the topic and calls the `action` function.
- `sublist()`: Adds topics to listen to (in this case, it subscribes to the "Relay" topic).
- `reconnect()`: Reconnects the device to the MQTT broker if disconnected.
- `setup()`: Connects to Wi-Fi, the MQTT broker, and sets the callback function.
- `loop()`: Checks for connection status and reconnects if disconnected.

## License

This project is licensed under the [MIT License](LICENSE).

## Author

- Aman Shaikh
- Contact: amanshaikhw@gmail.com
- Firmware Version: 0.1
