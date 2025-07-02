#include "TaskWebserver.h"  // led_on(), led_off(), extern int led_mode

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

String createHTML() {
    String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>ESP32 Sensor Dashboard</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { font-family: Arial, sans-serif; background: #f0f4f8; margin: 0; padding: 0; }
        .container { max-width: 400px; margin: 40px auto; background: #fff; border-radius: 12px; box-shadow: 0 4px 24px rgba(0,0,0,0.08); padding: 32px 24px; }
        h1 { color: #007acc; margin-bottom: 24px; }
        table { width: 100%; border-collapse: collapse; margin-bottom: 24px; }
        th, td { border: 1px solid #e0e0e0; padding: 10px 0; text-align: center; }
        th { background: #f7fafc; color: #333; }
        .switch-group { display: flex; flex-direction: column; gap: 18px; align-items: center; }
        .switch-label { font-size: 1.1em; margin-right: 12px; }
        .switch {
            position: relative; display: inline-block; width: 48px; height: 26px; vertical-align: middle;
        }
        .switch input { opacity: 0; width: 0; height: 0; }
        .slider {
            position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
            background-color: #ccc; transition: .4s; border-radius: 26px;
        }
        .slider:before {
            position: absolute; content: ""; height: 20px; width: 20px; left: 3px; bottom: 3px;
            background-color: white; transition: .4s; border-radius: 50%;
        }
        input:checked + .slider { background-color: #007acc; }
        input:checked + .slider:before { transform: translateX(22px); }
        .color-grid {
            display: none;
            grid-template-columns: repeat(3, 40px);
            gap: 10px;
            justify-content: center;
            margin-top: 18px;
        }
        .color-btn {
            width: 40px; height: 40px; border-radius: 8px; border: 2px solid #eee; cursor: pointer;
            outline: none; transition: border 0.2s;
        }
        .color-btn.selected { border: 2px solid #007acc; }
        .color-red { background: #ff0000; }
        .color-orange { background: #ff9900; }
        .color-yellow { background: #ffff00; }
        .color-green { background: #00cc00; }
        .color-blue { background: #0066ff; }
        .color-indigo { background: #4b0082; }
        .color-purple { background: #9900cc; }
        .color-white { background: #fff; }
        .color-black { background: #000; }
    </style>
</head>
<body>
    <div class="container">
        <h1>ESP32 Sensor Dashboard</h1>
        <table>
            <tr><th>Sensor</th><th>Value</th></tr>
            <tr><td>Temp</td><td id="temp">--</td></tr>
            <tr><td>Humi</td><td id="humi">--</td></tr>
            <tr><td>Soil</td><td id="soil">--</td></tr>
            <tr><td>Distance</td><td id="distance">--</td></tr>
            <tr><td>Light</td><td id="light">--</td></tr>
        </table>
        <div class="switch-group">
            <label class="switch-label">LED Power
                <span class="switch">
                    <input type="checkbox" id="ledSwitch" onchange="toggleLedSwitch()">
                    <span class="slider"></span>
                </span>
            </label>
            <label class="switch-label">RGB Mode
                <span class="switch">
                    <input type="checkbox" id="rgbModeSwitch" onchange="toggleRgbModeSwitch()">
                    <span class="slider"></span>
                </span>
            </label>
            <div id="colorGrid" class="color-grid">
                <button class="color-btn color-red"    onclick="setColor('red')"    title="Red"></button>
                <button class="color-btn color-orange" onclick="setColor('orange')" title="Orange"></button>
                <button class="color-btn color-yellow" onclick="setColor('yellow')" title="Yellow"></button>
                <button class="color-btn color-green"  onclick="setColor('green')"  title="Green"></button>
                <button class="color-btn color-blue"   onclick="setColor('blue')"   title="Blue"></button>
                <button class="color-btn color-indigo" onclick="setColor('indigo')" title="Indigo"></button>
                <button class="color-btn color-purple" onclick="setColor('purple')" title="Purple"></button>
                <button class="color-btn color-white"  onclick="setColor('white')"  title="White"></button>
                <button class="color-btn color-black"  onclick="setColor('black')"  title="Black"></button>
            </div>
        </div>
    </div>
    <script>
        let ws;
        function connectWS() {
            ws = new WebSocket('ws://' + location.hostname + '/ws');
            ws.onopen = function() {
                fetchData();
            };
            ws.onmessage = function(event) {
                let d = JSON.parse(event.data);
                document.getElementById('temp').innerText = d.temp;
                document.getElementById('humi').innerText = d.humi;
                document.getElementById('soil').innerText = d.soil;
                document.getElementById('distance').innerText = d.distance;
                document.getElementById('light').innerText = d.light;
                // Cập nhật trạng thái switch nếu có d.led hoặc d.mode
                if (typeof d.led !== 'undefined')
                    document.getElementById('ledSwitch').checked = d.led;
                if (typeof d.mode !== 'undefined') {
                    document.getElementById('rgbModeSwitch').checked = d.mode;
                    document.getElementById('colorGrid').style.display = d.mode ? 'grid' : 'none';
                }
            };
            ws.onclose = function() {
                setTimeout(connectWS, 1000);
            };
        }
        function fetchData() {
            if (ws && ws.readyState === 1) ws.send('get_data');
        }
        setInterval(fetchData, 1000);
        window.onload = connectWS;

        function toggleLedSwitch(){
            let val = document.getElementById('ledSwitch').checked ? 1 : 0;
            if (ws && ws.readyState === 1) ws.send('led_switch:' + val);
        }
        function toggleRgbModeSwitch(){
            let val = document.getElementById('rgbModeSwitch').checked ? 1 : 0;
            if (ws && ws.readyState === 1) ws.send('mode_switch:' + val);
            document.getElementById('colorGrid').style.display = val ? 'grid' : 'none';
        }
        function setColor(color){
            if (ws && ws.readyState === 1) ws.send('color:' + color);
            document.querySelectorAll('.color-btn').forEach(btn => btn.classList.remove('selected'));
            let btn = Array.from(document.querySelectorAll('.color-btn')).find(b => b.title.toLowerCase() === color);
            if(btn) btn.classList.add('selected');
        }
    </script>
</body>
</html>
    )rawliteral";
    return html;
}

String getSensorJson() {
    String json = "{";
    json += "\"temp\":" + String(temp) + ",";
    json += "\"humi\":" + String(humi) + ",";
    json += "\"soil\":" + String(soil) + ",";
    json += "\"distance\":" + String(distance) + ",";
    json += "\"light\":" + String(light) + ",";
    // json += "\"led\":" + String(led_is_on ? 1 : 0) + ",";
    json += "\"mode\":" + String(led_mode ? 1 : 0);
    json += "}";
    return json;
}

// Xử lý sự kiện WebSocket
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    if (type == WS_EVT_CONNECT) {
        // Gửi dữ liệu lần đầu khi client kết nối
        client->text(getSensorJson());
    } else if (type == WS_EVT_DATA) {
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
            String msg = String((char *)data);
            if (msg == "get_data") {
                client->text(getSensorJson());
            } else if (msg.startsWith("led_switch:")) {
                int val = msg.substring(11).toInt();
                if (val == 1) {
                    led_on();
                } else {
                    led_off();
                }
                client->text(getSensorJson());
            } else if (msg.startsWith("mode_switch:")) {
                led_mode = msg.substring(11).toInt();
                client->text(getSensorJson());
            } else if (msg.startsWith("color:")) {
                String color = msg.substring(6);
                if (color == "red")
                    led_color = red;
                else if (color == "orange")
                    led_color = orange;
                else if (color == "yellow")
                    led_color = yellow;
                else if (color == "green")
                    led_color = green;
                else if (color == "blue")
                    led_color = blue;
                else if (color == "indigo")
                    led_color = indigo;
                else if (color == "purple")
                    led_color = purple;
                else if (color == "white")
                    led_color = white;
                else if (color == "black")
                    led_color = black;
            }
        }
    }
}

void handleRoot(AsyncWebServerRequest *request) {
    request->send(200, "text/html", createHTML());
}

void initWebserver() {
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);
    server.on("/", HTTP_GET, handleRoot);
    server.begin();
    Serial.println("WebServer + WebSocket started");
}

