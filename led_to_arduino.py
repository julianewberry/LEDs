from imgproc import *
import serial
import time

# Create a camera
cam = Camera(320, 240)

# use the camera's width and height to set the viewer size
view = Viewer(cam.width, cam.height, "Blob finding")

# endlessly loop until the user exits
while True:
    # grab an image from the camera
    image = cam.grabImage()

    # we will put our remaining code in here
    red, green, blue = image[160, 120];
    red_string = str(red)
    green_string = str(green)
    blue_string = str(blue)
   
    view.displayImage(image)
   
    if __name__ == '__main__':
        ser = serial.Serial('/dev/ttyACM0', 9600)
        ser.flush()
   
        for i in range(3):
            ser.write((red_string + " " + green_string + " " + blue_string + "\n").encode('utf-8'))
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            time.sleep(0.03)
