import time
from pimoroni_i2c import PimoroniI2C
import breakout_scd41

# SDA and SCL pins for the Pico Plus 2 QW/ST connector
PINS_PICO_PLUS_2 = {"sda": 4, "scl": 5}

# Setup an instance of I2C and BME68X
i2c = PimoroniI2C(**PINS_PICO_PLUS_2)
breakout_scd41.init(i2c)

# Start the SCD41 sensor
breakout_scd41.start()


while True:

    # Grab the readings if the sensor is ready.
    if breakout_scd41.ready():
        co2, temperature, humidity = breakout_scd41.measure()

        # Print the latest measurements, you'll be able to see this in Thonny's shell.
        print("CO2: {} PPM\nTemperature: {}°C\nHumidity: {} %RH\n\n".format(co2, temperature, humidity))

    # Now we take a little nap before the next reading ZzzzZz
    time.sleep(3)
