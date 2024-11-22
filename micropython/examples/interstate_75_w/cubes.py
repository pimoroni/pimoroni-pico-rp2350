import time
import math
from random import randint, randrange
from interstate75 import Interstate75, DISPLAY_INTERSTATE75_128X128

# Setup for the display
i75 = Interstate75(
    display=DISPLAY_INTERSTATE75_128X128, stb_invert=False, panel_type=Interstate75.PANEL_GENERIC)
display = i75.display
WIDTH, HEIGHT = display.get_bounds()

BLACK = display.create_pen(0, 0, 0)
WHITE = display.create_pen(255, 255, 255)


class Cube(object):
    # The corners of the cube
    vertices = [[-1, -1, 1],
                [1, -1, 1],
                [1, -1, -1],
                [-1, -1, -1],
                [-1, 1, 1],
                [1, 1, 1],
                [1, 1, -1],
                [-1, 1, -1]]

    # The corners that will be connected together to make a cube :)
    edges = [(0, 1), (1, 2), (2, 3), (3, 0),
             (4, 5), (5, 6), (6, 7), (7, 4),
             (0, 4), (1, 5), (2, 6), (3, 7)]

    def __init__(self, fov, distance, x, y, speed):
        self.tick = time.ticks_ms() / 1000.0
        self.cos = math.cos(self.tick)
        self.sin = math.sin(self.tick)
        self.fov = fov
        self.distance = distance
        self.pos_x = x
        self.pos_y = y
        self.speed = speed

        self.cube_points = []

    # Project our points
    def to_2d(self, x, y, z, pos_x, pos_y, fov, distance):
        factor = fov / (distance + z)
        x = x * factor + pos_x
        y = -y * factor + pos_y

        return int(x), int(y)

    def return_tick(self):
        return self.tick

    # Clear our points and recalculate the sin and cos values
    def _update(self):

        self.cube_points = []

        self.tick = time.ticks_ms() / (self.speed * 1000)
        self.cos = math.cos(self.tick)
        self.sin = math.sin(self.tick)

    def set_fov(self, fov):
        self.fov = fov

    def set_distance(self, distance):
        self.distance = distance

    def set_speed(self, speed):
        self.speed = speed

    def set_x(self, x):
        self.pos_x = x

    def set_y(self, y):
        self.pos_y = y

    def get_fov(self):
        return self.fov

    # Rotate on XYZ and save the new points in our list
    def rotate(self):

        for v in self.vertices:

            start_x, start_y, start_z = v

            # X
            y = start_y * self.cos - start_z * self.sin
            z = start_y * self.sin + start_z * self.cos

            # Y
            x = start_x * self.cos - z * self.sin
            z = start_x * self.sin + z * self.cos

            # Z
            n_y = x * self.sin + y * self.cos
            n_x = x * self.cos - y * self.sin

            y = n_y
            x = n_x

            point = self.to_2d(x, y, z, self.pos_x, self.pos_y, self.fov, self.distance)
            self.cube_points.append(point)

    # Draw the edges of the cube so we can see it on screen!
    def draw(self):

        for edge in self.edges:
            display.line(self.cube_points[edge[0]][0], self.cube_points[edge[0]][1], self.cube_points[edge[1]][0], self.cube_points[edge[1]][1])

        self._update()


# Setup the first 3 cubes.
cubes = [Cube(16, 8, WIDTH / 2, HEIGHT / 2, 1.0), Cube(32, 8, 100, 100, 0.9), Cube(32, 8, 100, 100, 0.5)]

# Set our initial pen colour
pen = display.create_pen_hsv(1.0, 1.0, 1.0)

while 1:

    # We'll use this for cycling through the rainbow
    t = time.ticks_ms() / 1000

    # Set the layer we're going to be drawing to.
    display.set_layer(0)

    # Clear the screen and set the pen colour for the cubes
    display.set_pen(BLACK)
    display.clear()
    display.set_pen(WHITE)
    display.text("Flying Cubes!", 33, 55, WIDTH, 1)
    display.reset_pen(pen)
    pen = display.create_pen_hsv(t, 1.0, 1.0)
    display.set_pen(pen)

    # Now we go through each Cube object we have in 'cubes'
    # and increase the FOV angle so it appears closer to the screen.
    # We'll also rotate the cube during this loop too.
    for i, cube in enumerate(cubes):
        fov = cube.get_fov()
        fov += 3
        cube.set_fov(fov)
        cube.rotate()
        cube.draw()

        # We want the cubes to disappear randomly as they appear close to the screen, so we'll decide when this happens based on the current FOV
        # We'll replace that cube with a new one and start the process from the beginning!
        if fov > randint(250, 600):
            cubes[i] = Cube(8, 8, randint(10, WIDTH), randint(10, HEIGHT), randrange(4, 9) / 10)

    # Finally we update the display with our changes :)
    i75.update()
    time.sleep(0.03)
