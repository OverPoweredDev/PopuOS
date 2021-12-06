# PopuOS

### Overview
A mini OS-Simulator that can run programs built in a Custom Language. Archived as of December 6, 2021.

#### Language
- `GD` Get Data
- `PD` Print Data
- `LR` Load Register
- `SR` Store Register
- `CR` Compare Register
- `BT` Transfer to Line
- `H ` Halt

The `AMJ<batch-num><instr-count><data-count>` is simply to specify the number of lines and start of program

<br>

### Sample Programs
Put these in Input.txt and run

<br>

```
$AMJ000100030001
GD10
PD10
H
$DTA
Hello
$END0001
```
Prints Hello

<br>

```
$AMJ000200030001
GD10
LR12
SR15
PD10
H
$DTA
I LIKE THIS PEN OF
$END0002
```
Should Print "I LIKE THIS PEN OF HIS"

<br>

```
$AMJ000300120001
GD20
PD20
GD30
PD30
GD40
GD50
LR20
CR30
BT11
PD50
H
PD40
H
$DTA
VIIT
VIIT
IS SAME
IS NOT SAME
$END0003
```
Compares strings given at line 38 and 39 (in this case VIIT and VIIT)
