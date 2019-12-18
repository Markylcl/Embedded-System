import paho.mqtt.client as mqtt
import time
prev = -1
curr = -1
broker="192.168.4.1"
port = 1883
listener = mqtt.Client()
state = 0
color=-1

def color_on_message(client,userdata,msg):
    global color
    int_payload = (msg.payload).decode('utf-8')
    #print (type(int_payload))
    if int_payload == "1":
        color = 1
    elif int_payload == "2":
        color = 2
    else:
        color = -1
    print('result')
    print(color)

def arm_on_message(client, userdata, msg):
    global state
    global color
    state =state+1
    if state == 1:
        listener.publish("/cc3200/PIXYCmd","ack")
        listener.publish("/cc3200/PIXYCmd","ack")
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":2,\"angle\":100,\"speed\":3}")
    elif state == 2:
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":0,\"angle\":107,\"speed\":3}")
    elif state == 3:
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":1,\"angle\":12,\"speed\":3}")   
    elif state == 4:
        print("final result")
        print(color)
        if color == 1:
            listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":3,\"angle\":60,\"speed\":3}")
        elif color ==2:
            listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":3,\"angle\":120,\"speed\":3}")
        else:
            listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"reset\"}")
            state=-10
    elif state == 5:       
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":1,\"angle\":100,\"speed\":3}")  
    elif state == 6:       
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"reset\"}")
        state = -10
        
def lidar_on_message(client,userdata,msg):
    global state
    #payload_int=int(msg.payload)
    #left
    f=open('dhgoe.txt', 'r')

    dir_str = f.read()
    
    while len(dir_str)==0:
        f.close
        time.sleep(0.1)
        print('emm')
        f=open('dhgoe.txt', 'r')
        dir_str = f.read()

        
    payload_int =int(dir_str)
    if payload_int == 0:
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":3,\"angle\":160,\"speed\":3}")
        state = 0
    #right
    if payload_int == 1:
        listener.publish("/cc3200/RobotArmCmd", "{\"cmd\":\"angle\",\"servo\":3,\"angle\":0,\"speed\":3}")
        state = 0
    
def main():
    #listener = mqtt.Client()
    listener.connect(broker, port)
    listener.loop_start()
    listener.subscribe("/cc3200/lidar", qos=1)
    listener.subscribe("/cc3200/RobotArmState", qos=1)
    listener.subscribe("/cc3200/colorcmd",qos=1)
    listener.message_callback_add("/cc3200/lidar", lidar_on_message)
    listener.message_callback_add("/cc3200/RobotArmState", arm_on_message)
    listener.message_callback_add("/cc3200/colorcmd",color_on_message)
    while True:
        pass


if __name__=="__main__":
    main()