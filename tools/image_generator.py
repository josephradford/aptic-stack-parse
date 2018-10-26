#!/usr/bin/env python3
"""Utility to create flashing image stacks for testing APTIC"""

import random
from PIL import Image
import numpy as np
import argparse

__author__ = "Joseph Radford"
__license__ = "GPL-3.0"
__maintainer__ = "Joseph Radford"
__email__ = "joeradford@gmail.com"

class FlashObject(object):
    """
    FlashObject contains all information about a flash in the image stack
    coordinates is (x,y) or (col,row)
    radius is the (rough) circle made around the coordinates
    frame_start and duration is when in the stack the flash begins and how long it stays for
    """
    def __init__(self, coordinates, radius, frame_start, duration):
        self.coordinates = coordinates
        self.radius      = radius
        self.frame_start = frame_start
        self.duration    = duration

    def is_in_frame(self, frame):
        if frame >= self.frame_start:
            if (frame - self.frame_start) < self.duration:
                return True
        return False

class FlashList(object):
    def __init__(self):
        self.min_row = np.NaN
        self.max_row = np.NaN
        self.min_col = np.NaN
        self.max_col = np.NaN
        self.flashes = []

    def add_flash(self, coordinates, radius, frame_start, duration):
        self.flashes.append(FlashObject(coordinates, radius, frame_start, duration))
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

def create_flash_coords(image_shape, num_flashes, flash_radius, num_frames, flash_duration_range):
    """
    Create an array of coordinates within the image_shape (width, height)
    Array is (num_flashes,2), with [col,row]
    """
    flashes = FlashList()
    for i in range(num_flashes):
        flashes.add_flash((random.randint(flash_radius, image_shape[0] - flash_radius - 1),
                           random.randint(flash_radius, image_shape[1] - flash_radius - 1)),
                          flash_radius, 
                          random.randint(0, num_frames - flash_duration_range[1]),
                          random.randint(flash_duration_range[0], flash_duration_range[1]))
    return flashes

def create_flash_array(flash_radius):
    A = np.arange(-flash_radius,flash_radius+1,dtype='uint8')**2
    dists = np.sqrt(A[:,None] + A)
    return (dists-flash_radius<=0.0).astype('uint8')*255

def create_image(image_shape, flashes, frame):
    imdata = np.zeros(image_shape, dtype='uint8')

    for flash in flashes.flashes:
        if flash.is_in_frame(frame) == False:
            continue
        flash_radius = flash.radius
        col_fl = flash.coordinates[0]
        row_fl = flash.coordinates[1]
        imdata[col_fl-flash_radius:col_fl+flash_radius+1, 
               row_fl-flash_radius:row_fl+flash_radius+1] = create_flash_array(flash_radius)

    return imdata

def create_image_stack(image_shape, num_frames, flashes):
    imdata = np.zeros((image_shape[0], image_shape[1], num_frames), dtype='uint8')
    for i in range(num_frames):
        imdata[:,:,i] = create_image(image_shape, flashes, i)
    return imdata

def generate_image_stack(height, width, frames, flashes, flash_radius):
    flash_coords = create_flash_coords((width, height), 
                                       flashes, 
                                       flash_radius,
                                       frames,
                                       (3, 5))
    imdata = create_image_stack((width, height), frames, flash_coords)
    
    for i in range(0,frames):
        im2 = Image.fromarray(imdata[:,:,i], mode="L")
        im2.save("test_{0}.bmp".format(i), format="BMP")
        #im2.save("test_{0}.jpg".format(i), format="JPEG")

def create_parser():
    parser = argparse.ArgumentParser(description='Create an image stack with some flashes.')
    parser.add_argument('height', type=int, help='the height of the image')
    parser.add_argument('width', type=int, help ='the width of the image')
    parser.add_argument('frames', type=int, help = 'the number of frames in the image stack')
    parser.add_argument('flashes', type=int, help='the number of flashes across the stack')
    parser.add_argument('flash_radius', type=int, help='the size of the flashes to generate')
    return parser


if __name__== "__main__":
    parser = create_parser()
    args = parser.parse_args()
    generate_image_stack(args.height, args.width, args.frames, args.flashes, args.flash_radius)

