#!/usr/bin/env python3
"""Utility to create flashing image stacks for testing APTIC"""

import random
from PIL import Image
import numpy as np

__author__ = "Joseph Radford"
__license__ = "GPL-3.0"
__maintainer__ = "Joseph Radford"
__email__ = "joeradford@gmail.com"

def create_flash_coords(image_shape, num_flashes, flash_radius):
    """
    Create an array of coordinates within the image_shape (width, height)
    Array is (num_flashes,2), with [col,row]
    """
    flash_coords = np.empty((num_flashes,2), dtype=int)
    for i in range(num_flashes):
        flash_coords[i][0] = random.randint(flash_radius, image_shape[0] - flash_radius - 1)
        flash_coords[i][1] = random.randint(flash_radius, image_shape[1] - flash_radius - 1)
    return flash_coords

def main():
    input_width = 20
    input_height = 20
    input_num_flashes = 2
    input_flash_radius = 2
    flash_coords = create_flash_coords((input_width, input_height), input_num_flashes, input_flash_radius)

if __name__== "__main__":
    main()

