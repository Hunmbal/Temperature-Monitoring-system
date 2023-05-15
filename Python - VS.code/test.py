import serial, os, threading, sys, time
import matplotlib.pyplot as plt
import matplotlib.animation as animation

#Serial takes these two parameters: serial device and baudrate
ser = serial.Serial('COM5', 9600)
current = []
fig = plt.figure()                                     
ax = fig.add_subplot(111)
ax.set_ylabel('Temp')



def animate(i, current, ser):
    global max,min
    if ser.in_waiting:
        os.system("cls")
        data = ser.readline()
        print("Temperature logger")
        print("^^^^^^^^^^^^^^^^^^")
        print(data.decode('utf'))
        print("Display mode: " + get_mode(mode))
        input_list = data.split()
        current.append(float(input_list[1]))
        max = float(input_list[3])
        min = float(input_list[5])
        
    
    ax.clear()  # clear the plot before drawing new data
    ax.plot(current)
    ax.set_ylim(min-5, max+5)
    ax.set_xlim(len(current)-30, len(current)+30)
    ax.set_title('Max = ' + str(max) + '     Min = ' + str(min))
    



def read_input():
    global mode
    mode = '0'
    while True:
        mode = input("")  # read input from the terminal
        ser.write(mode.encode('utf'))
        sys.stdout.write('Entering ' + str(get_mode(mode)) + ' mode')  # write output to the terminal

def get_mode(z):
    if z=='1':
        return ' (1) max '
    elif z=='2':
        return ' (2) min'
    else:
        return 'default'
    



    
   


# main -------------------------------------------------------------------------------------------------------------------------

# create a new thread to run the read_input function
input_thread = threading.Thread(target=read_input)
input_thread.daemon = True
input_thread.start()



while not ser.in_waiting:
    pass

   
ani = animation.FuncAnimation(fig, animate, frames=60, fargs=(current, ser), interval=500) 
plt.show()
