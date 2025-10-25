## On Linux:
### Testing with virtual serial ports
- Install socat
- Create 2 virtual serial ports: ``` socat -d -d pty,raw,echo=0 pty,raw,echo=0 ```
- Run the serial tester on the first port (./serial_tester "portname" "baudrate"), eg.: ``` ./serial_tester /dev/pts/1 9600 ```
- In another terminal, simulate a device sending lines on the other pair, eg: ``` while true; do echo "WGT $(shuf -i1-999 -n1 | awk '{printf "%.2f", $1/100}')"; sleep 1; done > /dev/pts/2 ```
