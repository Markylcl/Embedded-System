import paho.mqtt.client as mqtt
import matplotlib.pyplot as plt
import datetime
import numpy as np
import math

angle = np.array(range(360))
dist = np.zeros(360, dtype = int)
block = 2

Ip_address = "192.168.4.1"
port = 1883
pi_data = " "
count = 0

plt.ion()
fig = plt.figure()
data = plt.polar(np.deg2rad(angle), dist, '.')[0]

data2 = plt.subplot(111, projection = 'polar')
#.bar(0 * 10, 2900, np.pi / 18, bottom = 0.0, alpha = 0.5)

plt.show()
plt.axis([0,2*math.pi,1,3000])

a=0
attempte=0
success=0
miss=0



def on_connect(client, userdata, flags, rc):
   print("Connected With Result Code " (rc))
   
def on_message_from_PI(client, userdata, message):
   #a += 1
    #global T1T2, T1T3, T2T1, T2T3, T3T2, T3T1, count, fig
    global dist, count
   # print("/cc3200/TOPICT2")
   # print("Message Recieved from PI: " + str(message.payload))
    pi_data = str(message.payload)
    
    if len(pi_data) < 24:
        return
    
    angl_str = pi_data[9:13]
    dist_str = pi_data[20:24]
    
    #print(angl_str)
    #print(dist_str)
    
    

    angle_float = float(angl_str) / 10
    angle_int = int(angle_float)
    
    dist_float = float(dist_str) 
    dist_int = int(dist_float)
    
    #print(angle_int)
    #print(dist_int)
    
    if  angle_int < 360 and dist_int >150:
        #log = open("log.txt", "a")
        #log.write(str(message.payload)[2:-1] + "\n")
        #log.close()
        dist[359 - angle_int] = dist_int
        
        count = count + 1
        if count == 300:
            
            data.set_ydata(dist)
            data.set_xdata(np.deg2rad(angle))
            
            ct = 0
            #interList = [] # 0 - 35
            interList = np.zeros(block, dtype = int)
            newList = np.zeros(block, dtype = int)
            for a in range(360):
                index = a / (360/block)
                i2 = int(index)
                #print(i2)
                if dist[a] > 0 and dist[a] < 3000:
                    interList[i2] = interList[i2] + dist[a]
                    newList[i2] = newList[i2] + 1
            
            

                
            #print(interList)
            
            direction = 0
            amax = 0
            for b in range(block):
               
                if interList[b]/ newList[b] > amax:
                    print(amax)
                    amax = interList[b] / newList[b]
                    direction = b
            print("direciton = ")
            print(direction)
            
            dist_direction = np.zeros(360, dtype = int)
            
                
            for c in range(int(360/block)):
                this_direction = c + direction
            data2.bar(direction * int(360/block), 2900, np.pi * 2, bottom = 0.0, alpha = 1, color = 'white')

            data2.bar(direction * int(360/block) / 360 * np.pi * 2 +(int(360/block) / 360 * np.pi ), 2900, np.pi / block * 2, bottom = 0.0, alpha = 0.5, color ='red')

            f = open('dhgoe.txt', 'w')
            f.write(str(direction))
            f.close
                    
            fig.canvas.draw()
            fig.canvas.flush_events()
            dist = np.zeros(360, dtype = int)
            count = 0;
        

def on_message(client, userdata, message):
   print("Message Recieved from Others: "+ str(message.payload.decode("utf-8")))
   
   
def main():
    #np.array()
    log = open("log.txt", "w")
    client = mqtt.Client()
    client.on_connect = on_connect
###json working###
#payload=json.dumps({"CliendId": "T1", "Message": "hi"})
#encoder_pay
#To Process Every Other Message
    client.on_message = on_message
    client.connect(Ip_address, port, 60) 

    client.subscribe("/cc3200/TOPICT2", qos=1)

    client.message_callback_add("/cc3200/TOPICT2", on_message_from_PI)

    client.loop_forever()

if __name__ == '__main__':
    main()
