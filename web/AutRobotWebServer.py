import readchar
import serial

myser = serial.Serial('/dev/ttyUSB0',38400)

serNode = serial.Serial('/dev/ttyUSB1',9600)

y=0
x=10
z=0
c=0
backMoving= 0
while True:
    #input=readchar.readchar()
    input = serNode.readline().decode('utf-8')
    print(input)
    input = input[0]

    try:
        if(input=="w" or input=="W"):
            if(y<200):
                y = y + 180
            s0 = 'S{} {}\n'.format(y, y)
            myser.write(bytes(s0,'utf-8'))
            print("moving forward")

        elif(input=="s" or input=="S"):
            if(backMoving > -100):
                backMoving = backMoving -x
            s1 = 'S{} {}\n'.format(backMoving, backMoving)
            myser.write(bytes(s1,'utf-8'))
            print("moving backward")


        elif(input=="e" or input=="E"):
            myser.write(b'S35 90\n')
            print('e is pressed')


        elif(input=="q" or input=="Q"):
            myser.write(b'S90 35\n')
            print("q is pressed")

        elif(input=="a" or input=="A"):
            if(z >-100):
                z = z - x
            if(c<100):
                c = c + x
            s2= 'S{} {}\n'.format(c, z)
            myser.write(bytes(s2, 'utf-8'))
            print('a is pressed')

        elif(input=="d" or input=="D" ):
            if(y < 100):
                y += x
            s3='S{} {}\n'.format(-y, y)
            myser.write(bytes(s3, 'utf-8'))
            print('d is pressed')

        elif(input=="\x03"):
            break

        else:
            y = 0
            backMoving = 0
            z = 0
            myser.write(b'S0 0\n')

    except:
        print("heeeeeeey")
