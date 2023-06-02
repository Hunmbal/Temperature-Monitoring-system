import serial, os, threading, sys, time
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#Serial takes these two parameters: serial device and baudrate
ser = serial.Serial('COM5', 9600)
current = []
fig = plt.figure()                                     
ax = fig.add_subplot(111)
ax.set_ylabel('Distance')



def animate(i, current, ser):
    global max,min
    if ser.in_waiting:
        os.system("cls")
        data = ser.readline()
        print("Current level: " + data.decode('utf'))
        input_list = data.split()
        if float(input_list[1]) > 0:
            current.append(float(input_list[1]))
        
    
    ax.clear()  # clear the plot before drawing new data
    ax.plot(current)
    ax.set_ylim(0, 110)
    ax.set_xlim(len(current)-30, len(current)+30)
    
  


# main -------------------------------------------------------------------------------------------------------------------------

while not ser.in_waiting:
    pass

   
ani = animation.FuncAnimation(fig, animate, frames=60, fargs=(current, ser), interval=500) 
plt.show()
