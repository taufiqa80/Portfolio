#!/usr/bin/env python
import paho.mqtt.client as mqtt
#from CameraTrap import func
from time import sleep
import os

sleep(90)

print ("Starting connection")

mqtt_topic = "TrapNotif"
mqtt_broker_ip = "raspizerow.local"

client = mqtt.Client()

def on_connect(client, userdata, rc, a):
    print ("Connected!", str(rc))
    client.subscribe(mqtt_topic)
    
def on_message(client, userdata, msg):
	T,ID = msg.payload.decode().split(" ")
	if (T == "Trigger"):
		print ("Topic: ", msg.topic + "\nTrigger: " + T + "\nID: " + ID)
		os.system("ls")
		#func()

client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker_ip, 1883)

client.loop_forever()
client.disconnect()
