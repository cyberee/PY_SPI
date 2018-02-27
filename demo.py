#!/usr/bin/python
#import L6740_Driver
import PY_Spi

import json
from pprint import pprint


class motor(object):
    
    def __init__(self, name, CS, rot):
        self.name = name
        self.CS = CS
        self.rot = rot


#json_data=open('motor.cfg').read()
with open('motor.cfg', 'r') as f:
    json_data = json.load(f)

pprint(json_data)

#cfg_data = json.loads(open('setup.cfg'))
#pprint(cfg_data)
for spi in json_data[ 'SPI_cfg' ]:
    spi_port= spi['port']
    spi_speed = spi['speed']



motors=[]
for motor_cfg in json_data[ 'motor' ]:
    print motor_cfg['name']
    print motor_cfg['CS']
    print motor_cfg['Rot']
    temp = motor(motor_cfg['name'], motor_cfg['CS'], motor_cfg['Rot'])
    motors.append(temp)

for m in motors:
    print m.name
    print m.CS
    print m.rot


print PY_Spi.version()
print PY_Spi.spi_set_port("/dev/spidev0.0")
print PY_Spi.spi_open()
print hex(PY_Spi.spi_get_mode())
print PY_Spi.spi_write(4)
print PY_Spi.spi_read(1)




