EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Amplifier_Operational:LM358 U1
U 2 1 5FB0786F
P 3300 1850
F 0 "U1" H 3400 2200 50  0000 C CNN
F 1 "LM358" H 3400 2100 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 3300 1850 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3300 1850 50  0001 C CNN
	2    3300 1850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5FB16C4E
P 2550 2250
F 0 "R2" H 2620 2296 50  0000 L CNN
F 1 "3.3k" H 2620 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2480 2250 50  0001 C CNN
F 3 "~" H 2550 2250 50  0001 C CNN
	1    2550 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5FB17628
P 2400 1350
F 0 "R1" H 2470 1396 50  0000 L CNN
F 1 "4.7k" H 2470 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2330 1350 50  0001 C CNN
F 3 "~" H 2400 1350 50  0001 C CNN
	1    2400 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5FB18587
P 2400 1750
F 0 "RV1" H 2330 1796 50  0000 R CNN
F 1 "10k" H 2330 1705 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3386C_Horizontal" H 2400 1750 50  0001 C CNN
F 3 "~" H 2400 1750 50  0001 C CNN
	1    2400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1600 2400 1500
$Comp
L power:GND #PWR02
U 1 1 5FB48619
P 2400 2600
F 0 "#PWR02" H 2400 2350 50  0001 C CNN
F 1 "GND" H 2405 2427 50  0000 C CNN
F 2 "" H 2400 2600 50  0001 C CNN
F 3 "" H 2400 2600 50  0001 C CNN
	1    2400 2600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J4
U 1 1 5FB4C28D
P 1150 1100
F 0 "J4" H 1258 1189 50  0000 C CNN
F 1 "FBout" H 1258 1190 50  0001 C CNN
F 2 "Connector_Pin:Pin_D0.7mm_L6.5mm_W1.8mm_FlatFork" H 1150 1100 50  0001 C CNN
F 3 "~" H 1150 1100 50  0001 C CNN
	1    1150 1100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 5FB4CD62
P 1150 1300
F 0 "J5" H 1258 1389 50  0000 C CNN
F 1 "VCC" H 1258 1390 50  0001 C CNN
F 2 "Connector_Pin:Pin_D0.7mm_L6.5mm_W1.8mm_FlatFork" H 1150 1300 50  0001 C CNN
F 3 "~" H 1150 1300 50  0001 C CNN
	1    1150 1300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 5FB4D825
P 1150 1500
F 0 "J6" H 1258 1589 50  0000 C CNN
F 1 "GND" H 1258 1590 50  0001 C CNN
F 2 "Connector_Pin:Pin_D0.7mm_L6.5mm_W1.8mm_FlatFork" H 1150 1500 50  0001 C CNN
F 3 "~" H 1150 1500 50  0001 C CNN
	1    1150 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5FB54396
P 1450 1600
F 0 "#PWR01" H 1450 1350 50  0001 C CNN
F 1 "GND" H 1455 1427 50  0000 C CNN
F 2 "" H 1450 1600 50  0001 C CNN
F 3 "" H 1450 1600 50  0001 C CNN
	1    1450 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 1500 1450 1500
Wire Wire Line
	1450 1500 1450 1600
Text GLabel 2750 1950 0    50   Input ~ 0
FBin
Wire Wire Line
	2750 1950 2900 1950
Text GLabel 1700 2250 2    50   Input ~ 0
FBin
Text GLabel 1700 2450 2    50   Input ~ 0
OFFon
Text GLabel 4450 1600 1    50   Input ~ 0
FBout
Text GLabel 1650 1100 2    50   Input ~ 0
FBout
Wire Wire Line
	1650 1100 1350 1100
Text GLabel 1650 1300 2    50   Input ~ 0
VCC
Wire Wire Line
	1350 1300 1650 1300
Text GLabel 2400 1050 1    50   Input ~ 0
OUT
Wire Wire Line
	2400 1200 2400 1050
Text GLabel 1650 900  2    50   Input ~ 0
OUT
$Comp
L Connector:Conn_01x01_Male J1
U 1 1 5FB7B930
P 1150 900
F 0 "J1" H 1258 989 50  0000 C CNN
F 1 "OUT+" H 1258 990 50  0001 C CNN
F 2 "Connector_Pin:Pin_D0.7mm_L6.5mm_W1.8mm_FlatFork" H 1150 900 50  0001 C CNN
F 3 "~" H 1150 900 50  0001 C CNN
	1    1150 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 900  1350 900 
Text GLabel 2750 2900 0    50   Input ~ 0
OFFon
$Comp
L Diode:1N4148 D1
U 1 1 5FB15130
P 3950 1850
F 0 "D1" H 4000 1700 50  0000 L CNN
F 1 "1N4148" H 3650 1750 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 3950 1675 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3950 1850 50  0001 C CNN
	1    3950 1850
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:LM358 U1
U 1 1 5FB06203
P 3300 3000
F 0 "U1" H 3300 3367 50  0000 C CNN
F 1 "LM358" H 3300 3276 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 3300 3000 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 3300 3000 50  0001 C CNN
	1    3300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2200 5150 2050
Wire Wire Line
	5150 1300 5150 1450
Text GLabel 5150 1300 1    50   Input ~ 0
VCC
$Comp
L power:GND #PWR03
U 1 1 5FB47A71
P 5150 2200
F 0 "#PWR03" H 5150 1950 50  0001 C CNN
F 1 "GND" H 5155 2027 50  0000 C CNN
F 2 "" H 5150 2200 50  0001 C CNN
F 3 "" H 5150 2200 50  0001 C CNN
	1    5150 2200
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LM358 U1
U 3 1 5FB0A672
P 5250 1750
F 0 "U1" H 5208 1796 50  0001 L CNN
F 1 "LM358" H 5208 1705 50  0001 L CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 5250 1750 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 5250 1750 50  0001 C CNN
	3    5250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 3000 3600 3000
Wire Wire Line
	3000 3100 2900 3100
Wire Wire Line
	2900 3100 2900 3300
Wire Wire Line
	2900 3300 3700 3300
Wire Wire Line
	3700 3300 3700 3000
$Comp
L Device:C C1
U 1 1 5FB19081
P 3250 2350
F 0 "C1" V 2998 2350 50  0000 C CNN
F 1 "150p" V 3089 2350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.08x0.95mm_HandSolder" H 3288 2200 50  0001 C CNN
F 3 "~" H 3250 2350 50  0001 C CNN
	1    3250 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 1750 3000 1750
Wire Wire Line
	2750 2900 3000 2900
$Comp
L Diode:1N4148 D2
U 1 1 5FFB7D1F
P 3950 3000
F 0 "D2" H 4050 2850 50  0000 L CNN
F 1 "1N4148" H 3700 2900 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 3950 2825 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 3950 3000 50  0001 C CNN
	1    3950 3000
	-1   0    0    1   
$EndComp
Wire Wire Line
	3800 3000 3700 3000
Connection ~ 3700 3000
Wire Wire Line
	3800 1850 3700 1850
Wire Wire Line
	4100 3000 4450 3000
Wire Wire Line
	4450 3000 4450 1850
Wire Wire Line
	4100 1850 4450 1850
Connection ~ 4450 1850
Wire Wire Line
	4450 1850 4450 1600
Wire Wire Line
	3400 2350 3700 2350
Wire Wire Line
	3700 2350 3700 1850
Connection ~ 3700 1850
Wire Wire Line
	3700 1850 3600 1850
Wire Wire Line
	3100 2350 2900 2350
Wire Wire Line
	2900 2350 2900 1950
Connection ~ 2900 1950
Wire Wire Line
	2900 1950 3000 1950
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5FFEB818
P 1250 2350
F 0 "J2" H 1168 2025 50  0000 C CNN
F 1 "Ctrl" H 1168 2116 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1250 2350 50  0001 C CNN
F 3 "~" H 1250 2350 50  0001 C CNN
	1    1250 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	1700 2250 1450 2250
Wire Wire Line
	1700 2450 1450 2450
$Comp
L power:GND #PWR04
U 1 1 5FFF12FD
P 1550 2600
F 0 "#PWR04" H 1550 2350 50  0001 C CNN
F 1 "GND" H 1555 2427 50  0000 C CNN
F 2 "" H 1550 2600 50  0001 C CNN
F 3 "" H 1550 2600 50  0001 C CNN
	1    1550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 2600 1550 2350
Wire Wire Line
	1550 2350 1450 2350
$Comp
L Device:R R3
U 1 1 5FFB019F
P 2250 2250
F 0 "R3" H 2320 2296 50  0000 L CNN
F 1 "4.7k" H 2320 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad0.98x0.95mm_HandSolder" V 2180 2250 50  0001 C CNN
F 3 "~" H 2250 2250 50  0001 C CNN
	1    2250 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2050 2250 2050
Wire Wire Line
	2250 2050 2250 2100
Wire Wire Line
	2400 1900 2400 2050
Wire Wire Line
	2550 2100 2550 2050
Wire Wire Line
	2550 2050 2400 2050
Connection ~ 2400 2050
Wire Wire Line
	2250 2400 2250 2500
Wire Wire Line
	2250 2500 2400 2500
Wire Wire Line
	2550 2500 2550 2400
Wire Wire Line
	2400 2600 2400 2500
Connection ~ 2400 2500
Wire Wire Line
	2400 2500 2550 2500
$EndSCHEMATC
