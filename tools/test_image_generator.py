import unittest
from image_generator import *

class TestImageGenerator(unittest.TestCase):

    def test_flash_width_no_flash_radius(self):
        width = 2
        max_col = width - 1
        min_col = 0
        flash_coords = create_flash_coords((width,5), 40, 0)
        self.assertLessEqual(   max(flash_coords[:,0]), max_col)
        self.assertGreaterEqual(min(flash_coords[:,0]), min_col)
        
    def test_flash_width_with_flash_radius(self):
        width = 7
        flash_radius = 2
        max_col = width - flash_radius - 1
        min_col = flash_radius
        flash_coords = create_flash_coords((width,5), 40, flash_radius)
        self.assertLessEqual(   max(flash_coords[:,0]), max_col)
        self.assertGreaterEqual(min(flash_coords[:,0]), min_col)
        
    def test_flash_height_no_flash_radius(self):
        height = 2
        max_row = height - 1
        min_row = 0
        flash_coords = create_flash_coords((5,height), 40, 0)
        self.assertLessEqual(   max(flash_coords[:,1]), max_row)
        self.assertGreaterEqual(min(flash_coords[:,1]), min_row)

    def test_flash_height_with_flash_radius(self):
        height = 6
        flash_radius = 1
        max_row = height - flash_radius - 1
        min_row = flash_radius
        flash_coords = create_flash_coords((5,height), 40, flash_radius)
        self.assertLessEqual(   max(flash_coords[:,1]), max_row)
        self.assertGreaterEqual(min(flash_coords[:,1]), min_row)

    def test_num_flashes(self):
        num_flashes = 20
        flash_coords = create_flash_coords((5,5), num_flashes, 0)
        self.assertEqual(len(flash_coords), num_flashes)


if __name__ == '__main__':
    unittest.main(exit=False)
