#!/usr/bin/env python3
"""Utility to create flashing image stacks for testing APTIC"""

import random
from PIL import Image
import numpy as np

__author__ = "Joseph Radford"
__license__ = "GPL-3.0"
__maintainer__ = "Joseph Radford"
__email__ = "joeradford@gmail.com"

class FlashObject(object):
    """
    FlashObject contains all information about a flash in the image stack
    coordinates is (x,y) or (col,row)
    """
    def __init__(self, coordinates, radius, duration):
        self.coordinates = coordinates
        self.radius      = radius
        self.duration    = duration

class FlashList(object):
    def __init__(self):
        self.min_row = np.NaN
        self.max_row = np.NaN
        self.min_col = np.NaN
        self.max_col = np.NaN
        self.flashes = []

    def add_flash(self, coordinates, radius, duration):
        self.flashes.append(FlashObject(coordinates,radius,duration))
        col = coordinates[0]
        row = coordinates[1]
        if (np.isnan(self.min_row) or self.min_row > row):
            self.min_row = row
        if (np.isnan(self.max_row) or self.max_row < row):
            self.max_row = row
        if (np.isnan(self.min_col) or self.min_col > col):
            self.min_col = col
        if (np.isnan(self.max_col) or self.max_col < col):
            self.max_col = col

    def length(self):
        return len(self.flashes)

def create_flash_coords(image_shape, num_flashes, flash_radius, duration=1):
    """
    Create an array of coordinates within the image_shape (width, height)
    Array is (num_flashes,2), with [col,row]
    """
    flashes = FlashList()
    for i in range(num_flashes):
        flashes.add_flash((random.randint(flash_radius, image_shape[0] - flash_radius - 1),
                           random.randint(flash_radius, image_shape[1] - flash_radius - 1)),
                          flash_radius, duration)
    return flashes


def main():
    input_width = 20
    input_height = 20
    input_num_flashes = 2
    input_flash_radius = 2
    flash_coords = create_flash_coords((input_width, input_height), input_num_flashes, input_flash_radius)

if __name__== "__main__":
    main()

