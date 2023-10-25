# macropad-arduino


node red
```
[
    {
        "id": "2c6873d2.992abc",
        "type": "mqtt out",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "led/control",
        "qos": "2",
        "retain": "false",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "407a01e4.6b637",
        "x": 1530,
        "y": 320,
        "wires": []
    },
    {
        "id": "1bb4bb8dedb94317",
        "type": "inject",
        "z": "fcb6a21e80097fe7",
        "name": "ON/OFF",
        "props": [
            {
                "p": "payload"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "{ \"state\": \"init\" }",
        "payloadType": "json",
        "x": 140,
        "y": 40,
        "wires": [
            [
                "7752287cf6411178"
            ]
        ]
    },
    {
        "id": "bfe98c5812b7f748",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "function 1",
        "func": "var globalValue = context.global.myGlobalVar;\nif (msg.payload == true && globalValue == \"ON\") {\n        msg.payload = \"OFF\";\n        globalValue = \"OFF\";\n         return msg;\n    } \n    else {\n        msg.payload = \"ON\";\n        globalValue = \"ON\";\n        return msg;\n    }\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 500,
        "y": 40,
        "wires": [
            [
                "313b0bd39470d5e0"
            ]
        ]
    },
    {
        "id": "7752287cf6411178",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "function 2",
        "func": "// Initialize context variable if it doesn't exist\nif (context.get('currentState') === undefined) {\n    context.set('currentState', true);\n}\n\n// Toggle the state between true and false\ncontext.set('currentState', !context.get('currentState'));\n\n// Set the payload to the current state\nmsg.payload = context.get('currentState');\n\nreturn msg;\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 320,
        "y": 40,
        "wires": [
            [
                "bfe98c5812b7f748"
            ]
        ]
    },
    {
        "id": "313b0bd39470d5e0",
        "type": "debug",
        "z": "fcb6a21e80097fe7",
        "name": "debug 1",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 660,
        "y": 40,
        "wires": []
    },
    {
        "id": "fa421fcee79581df",
        "type": "aedes broker",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "mqtt_port": 1883,
        "mqtt_ws_bind": "port",
        "mqtt_ws_port": "",
        "mqtt_ws_path": "",
        "cert": "",
        "key": "",
        "certname": "",
        "keyname": "",
        "dburl": "",
        "usetls": false,
        "x": 990,
        "y": 60,
        "wires": [
            [],
            []
        ]
    },
    {
        "id": "bf6d98a4f55a734a",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "change state when b is pushed",
        "func": "\nif (msg.payload.characteristics[1].value == true) {\n    msg.payload = { On: false }; \n\n} else {\n    msg.payload = { On: true };   \n\n}\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 890,
        "y": 280,
        "wires": [
            [
                "5e433b2dec9570bc"
            ]
        ]
    },
    {
        "id": "1b9fc50f1639f26d",
        "type": "mqtt in",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "button/pressed/1",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "407a01e4.6b637",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 440,
        "y": 280,
        "wires": [
            [
                "57528a2e7cf32302"
            ]
        ]
    },
    {
        "id": "5e433b2dec9570bc",
        "type": "homekit-service",
        "z": "fcb6a21e80097fe7",
        "isParent": true,
        "hostType": "0",
        "bridge": "b27b9d3c0bb1a11c",
        "accessoryId": "",
        "parentService": "",
        "name": "Lamp Desk",
        "serviceName": "Lightbulb",
        "topic": "",
        "filter": false,
        "manufacturer": "NRCHKB",
        "model": "1.5.0",
        "serialNo": "Default Serial Number",
        "firmwareRev": "1.5.0",
        "hardwareRev": "1.5.0",
        "softwareRev": "1.5.0",
        "cameraConfigVideoProcessor": "ffmpeg",
        "cameraConfigSource": "",
        "cameraConfigStillImageSource": "",
        "cameraConfigMaxStreams": 2,
        "cameraConfigMaxWidth": 1280,
        "cameraConfigMaxHeight": 720,
        "cameraConfigMaxFPS": 10,
        "cameraConfigMaxBitrate": 300,
        "cameraConfigVideoCodec": "libx264",
        "cameraConfigAudioCodec": "libfdk_aac",
        "cameraConfigAudio": false,
        "cameraConfigPacketSize": 1316,
        "cameraConfigVerticalFlip": false,
        "cameraConfigHorizontalFlip": false,
        "cameraConfigMapVideo": "0:0",
        "cameraConfigMapAudio": "0:1",
        "cameraConfigVideoFilter": "scale=1280:720",
        "cameraConfigAdditionalCommandLine": "-tune zerolatency",
        "cameraConfigDebug": false,
        "cameraConfigSnapshotOutput": "disabled",
        "cameraConfigInterfaceName": "",
        "characteristicProperties": "{}",
        "waitForSetupMsg": false,
        "outputs": 2,
        "x": 1130,
        "y": 280,
        "wires": [
            [],
            [
                "d42dc3243659c0c2"
            ]
        ]
    },
    {
        "id": "d42dc3243659c0c2",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "Homekit ",
        "func": "\nif (msg.payload.On == true) {\n    msg.payload = \"ON\";\n    return msg;\n}\nelse {\n    msg.payload = \"OFF\";\n    return msg;\n}\n",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 1300,
        "y": 280,
        "wires": [
            [
                "2c6873d2.992abc"
            ]
        ]
    },
    {
        "id": "57528a2e7cf32302",
        "type": "homekit-status",
        "z": "fcb6a21e80097fe7",
        "serviceNodeId": "5e433b2dec9570bc",
        "name": "status lamp desk",
        "outputs": 1,
        "x": 650,
        "y": 280,
        "wires": [
            [
                "bf6d98a4f55a734a"
            ]
        ]
    },
    {
        "id": "9038cf704760603c",
        "type": "mqtt in",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "connected/true",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "407a01e4.6b637",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 440,
        "y": 360,
        "wires": [
            [
                "f16aee28aac510bb"
            ]
        ]
    },
    {
        "id": "f16aee28aac510bb",
        "type": "homekit-status",
        "z": "fcb6a21e80097fe7",
        "serviceNodeId": "5e433b2dec9570bc",
        "name": "status lamp desk",
        "outputs": 1,
        "x": 670,
        "y": 360,
        "wires": [
            [
                "705ba1f770623d96"
            ]
        ]
    },
    {
        "id": "705ba1f770623d96",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "set value on restart",
        "func": "\nif (msg.payload.characteristics[1].value == true) {\n    msg.payload = \"ON\"; \n    \n} else {\n    msg.payload = \"OFF\";   \n    \n}\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 970,
        "y": 360,
        "wires": [
            [
                "2c6873d2.992abc"
            ]
        ]
    },
    {
        "id": "ed2d8340.e1d5d8",
        "type": "homekit-service",
        "z": "fcb6a21e80097fe7",
        "isParent": true,
        "hostType": "0",
        "bridge": "b27b9d3c0bb1a11c",
        "accessoryId": "",
        "parentService": "",
        "name": "Lamp Bri",
        "serviceName": "Lightbulb",
        "topic": "",
        "filter": false,
        "manufacturer": "Default Manufacturer",
        "model": "Default Model",
        "serialNo": "Default Serial Number",
        "firmwareRev": "",
        "hardwareRev": "",
        "softwareRev": "",
        "cameraConfigVideoProcessor": "",
        "cameraConfigSource": "",
        "cameraConfigStillImageSource": "",
        "cameraConfigMaxStreams": "",
        "cameraConfigMaxWidth": "",
        "cameraConfigMaxHeight": "",
        "cameraConfigMaxFPS": "",
        "cameraConfigMaxBitrate": "",
        "cameraConfigVideoCodec": "",
        "cameraConfigAudioCodec": "",
        "cameraConfigAudio": false,
        "cameraConfigPacketSize": "",
        "cameraConfigVerticalFlip": false,
        "cameraConfigHorizontalFlip": false,
        "cameraConfigMapVideo": "",
        "cameraConfigMapAudio": "",
        "cameraConfigVideoFilter": "",
        "cameraConfigAdditionalCommandLine": "",
        "cameraConfigDebug": false,
        "cameraConfigInterfaceName": "",
        "characteristicProperties": "{\"Brightness\":true}",
        "waitForSetupMsg": false,
        "outputs": 2,
        "x": 1120,
        "y": 620,
        "wires": [
            [
                "71e17ac6.d31024"
            ],
            []
        ]
    },
    {
        "id": "1bc33e3a.60be9a",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "Brightness to HomeKit",
        "func": "var input = msg.payload;\nif (input < 101){\n    if (input < 1) {\n        msg.payload = {\n        \"On\": false\n    }\n    }\n    else {\n        msg.payload = {\n        \"Brightness\": input,\n        \"On\": true\n    }\n    }\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 740,
        "y": 620,
        "wires": [
            [
                "ed2d8340.e1d5d8"
            ]
        ]
    },
    {
        "id": "71e17ac6.d31024",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "Brightness to Integer",
        "func": "var b = context.get('b')||0;\nif(msg.payload.Brightness){\n    b = msg.payload.Brightness;\n    context.set('b',b);\n    msg.payload=b\n}\n\n// Uncomment lines 9 and 20 to prevent looping\n//if (msg.hap.context !== undefined) {\n    if(msg.payload.Brightness === 0){\n        msg.payload = -1\n    }\n    if(msg.payload.On === false){\n        msg.payload = 0\n    }\n    if(msg.payload.On === true){\n        msg.payload = b\n    }\n    return msg\n//}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 1300,
        "y": 620,
        "wires": [
            [
                "d8c726f175dcc380"
            ]
        ]
    },
    {
        "id": "c9205543.2990f8",
        "type": "inject",
        "z": "fcb6a21e80097fe7",
        "name": "Send brightness",
        "props": [
            {
                "p": "payload"
            },
            {
                "p": "topic",
                "vt": "str"
            }
        ],
        "repeat": "",
        "crontab": "",
        "once": false,
        "onceDelay": 0.1,
        "topic": "",
        "payload": "20",
        "payloadType": "num",
        "x": 460,
        "y": 620,
        "wires": [
            [
                "1bc33e3a.60be9a"
            ]
        ]
    },
    {
        "id": "d8c726f175dcc380",
        "type": "mqtt out",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "led/control",
        "qos": "2",
        "retain": "false",
        "respTopic": "",
        "contentType": "",
        "userProps": "",
        "correl": "",
        "expiry": "",
        "broker": "407a01e4.6b637",
        "x": 1530,
        "y": 580,
        "wires": []
    },
    {
        "id": "5ca76c34af68a61c",
        "type": "mqtt in",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "connected/true",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "407a01e4.6b637",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 440,
        "y": 520,
        "wires": [
            [
                "c9e90afd3de340ab"
            ]
        ]
    },
    {
        "id": "c9e90afd3de340ab",
        "type": "homekit-status",
        "z": "fcb6a21e80097fe7",
        "serviceNodeId": "ed2d8340.e1d5d8",
        "name": "status lamp bri",
        "outputs": 1,
        "x": 660,
        "y": 520,
        "wires": [
            [
                "3e883965a02750ce"
            ]
        ]
    },
    {
        "id": "3e883965a02750ce",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "set brightness value on restart",
        "func": "if(msg.payload.characteristics[2].value > 0) {\n    msg.payload = msg.payload.characteristics[2].value;\n}\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 1250,
        "y": 520,
        "wires": [
            [
                "d8c726f175dcc380"
            ]
        ]
    },
    {
        "id": "770ac5188603a44c",
        "type": "comment",
        "z": "fcb6a21e80097fe7",
        "name": "LED CONTROL",
        "info": "",
        "x": 220,
        "y": 320,
        "wires": []
    },
    {
        "id": "91a19990bf34d4f5",
        "type": "comment",
        "z": "fcb6a21e80097fe7",
        "name": "LED BRIGHT CONTROL",
        "info": "",
        "x": 230,
        "y": 640,
        "wires": []
    },
    {
        "id": "e63be234a58e87f0",
        "type": "mqtt in",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "button/pressed/2",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "407a01e4.6b637",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 440,
        "y": 700,
        "wires": [
            [
                "e8f64ee27bd1e594"
            ]
        ]
    },
    {
        "id": "e8f64ee27bd1e594",
        "type": "homekit-status",
        "z": "fcb6a21e80097fe7",
        "serviceNodeId": "ed2d8340.e1d5d8",
        "name": "status lamp bri",
        "outputs": 1,
        "x": 660,
        "y": 700,
        "wires": [
            [
                "842a53d39b1ee9e5"
            ]
        ]
    },
    {
        "id": "842a53d39b1ee9e5",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "change state when b is pushed",
        "func": "\nif (msg.payload.characteristics[1].value == true) {\n    msg.payload = {\n        \"On\": false\n    }   \n\n} else {\n    if (msg.payload.characteristics[2].value == 0) {\n        msg.payload = {\n            \"Brightness\": 100,\n            \"On\": true\n        }  \n    }\n    else {\n        msg.payload = {\n            \"On\": true\n        }  \n    }\n\n}\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 890,
        "y": 700,
        "wires": [
            [
                "ed2d8340.e1d5d8"
            ]
        ]
    },
    {
        "id": "1bd0588f259cdb39",
        "type": "comment",
        "z": "fcb6a21e80097fe7",
        "name": "RGB CONTROL",
        "info": "",
        "x": 240,
        "y": 960,
        "wires": []
    },
    {
        "id": "3a5aefaaa55621a2",
        "type": "mqtt in",
        "z": "fcb6a21e80097fe7",
        "name": "",
        "topic": "analog/read",
        "qos": "2",
        "datatype": "auto-detect",
        "broker": "407a01e4.6b637",
        "nl": false,
        "rap": true,
        "rh": 0,
        "inputs": 0,
        "x": 430,
        "y": 780,
        "wires": [
            [
                "1a7ec296090a59dd"
            ]
        ]
    },
    {
        "id": "1a7ec296090a59dd",
        "type": "function",
        "z": "fcb6a21e80097fe7",
        "name": "Brightness to HomeKit",
        "func": "var input = msg.payload;\nif (input < 101) {\n    if (input < 1) {\n        msg.payload = {\n            \"On\": false\n        }\n    }\n    else {\n        msg.payload = {\n            \"Brightness\": input,\n            \"On\": true\n            \n        }\n    }\n    return msg;\n}",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 780,
        "y": 780,
        "wires": [
            [
                "ed2d8340.e1d5d8"
            ]
        ]
    },
    {
        "id": "407a01e4.6b637",
        "type": "mqtt-broker",
        "name": "",
        "broker": "localhost",
        "port": "1883",
        "clientid": "",
        "autoConnect": true,
        "usetls": false,
        "protocolVersion": "4",
        "keepalive": "60",
        "cleansession": true,
        "birthTopic": "",
        "birthQos": "0",
        "birthPayload": "",
        "birthMsg": {},
        "closeTopic": "",
        "closePayload": "",
        "closeMsg": {},
        "willTopic": "",
        "willQos": "0",
        "willPayload": "",
        "willMsg": {},
        "userProps": "",
        "sessionExpiry": ""
    },
    {
        "id": "b27b9d3c0bb1a11c",
        "type": "homekit-bridge",
        "bridgeName": "Lamp Desk",
        "pinCode": "598-06-187",
        "port": "",
        "advertiser": "bonjour-hap",
        "allowInsecureRequest": false,
        "manufacturer": "NRCHKB",
        "model": "1.5.0",
        "serialNo": "Default Serial Number",
        "firmwareRev": "1.5.0",
        "hardwareRev": "1.5.0",
        "softwareRev": "1.5.0",
        "customMdnsConfig": false,
        "mdnsMulticast": true,
        "mdnsInterface": "",
        "mdnsPort": "",
        "mdnsIp": "",
        "mdnsTtl": "",
        "mdnsLoopback": true,
        "mdnsReuseAddr": true,
        "allowMessagePassthrough": true
    }
]
```
