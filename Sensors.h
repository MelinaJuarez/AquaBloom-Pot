class Sensors {
public:
    Sensors();  // Constructor predeterminado
    void StartSensors();
    float readTemperature();
    float readHumidity();
    bool analyze();
};