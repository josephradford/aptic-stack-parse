import unittest
from image_generator import *

class TestImageGenerator(unittest.TestCase):

    def test_flash_width_no_flash_radius(self):
        width = 2
        max_col = width - 1
        min_col = 0
        flash_coords = create_flash_coords((width,5), 40, 0, 1, (1, 1))
        self.assertLessEqual(   flash_coords.max_col, max_col)
        self.assertGreaterEqual(flash_coords.min_col, min_col)
        
    def test_flash_width_with_flash_radius(self):
        width = 7
        flash_radius = 2
        max_col = width - flash_radius - 1
        min_col = flash_radius
        flash_coords = create_flash_coords((width,5), 40, flash_radius, 1, (1, 1))
        self.assertLessEqual(   flash_coords.max_col, max_col)
        self.assertGreaterEqual(flash_coords.min_col, min_col)
        
    def test_flash_height_no_flash_radius(self):
        height = 2
        max_row = height - 1
        min_row = 0
        flash_coords = create_flash_coords((5,height), 40, 0, 1, (1, 1))
        self.assertLessEqual(   flash_coords.max_row, max_row)
        self.assertGreaterEqual(flash_coords.min_row, min_row)

    def test_flash_height_with_flash_radius(self):
        height = 6
        flash_radius = 1
        max_row = height - flash_radius - 1
        min_row = flash_radius
        flash_coords = create_flash_coords((5,height), 40, flash_radius, 1, (1, 1))
        self.assertLessEqual(   flash_coords.max_row, max_row)
        self.assertGreaterEqual(flash_coords.min_row, min_row)

    def test_num_flashes(self):
        num_flashes = 20
        flash_coords = create_flash_coords((5,5), num_flashes, 0, 1, (1, 1))
        self.assertEqual(flash_coords.length(), num_flashes)

    def test_flash_shape_2(self):
        flash_radius = 2
        flash_array = create_flash_array(flash_radius)
        flash_array_test = np.array([[  0,   0, 255,   0,   0],
                                     [  0, 255, 255, 255,   0],
                                     [255, 255, 255, 255, 255],
                                     [  0, 255, 255, 255,   0],
                                     [  0,   0, 255,   0,   0]])
        self.assertTrue(np.allclose(flash_array, flash_array_test))

    def test_flash_shape_1(self):
        flash_radius = 1
        flash_array = create_flash_array(flash_radius)
        flash_array_test = np.array([[  0, 255,   0],
                                     [255, 255, 255],
                                     [  0, 255,   0]])
        self.assertTrue(np.allclose(flash_array, flash_array_test))

    def test_image_size(self):
        image_shape = (5,5)
        flash_coords = create_flash_coords(image_shape, 1, 0, 1, (1, 1))
        imdata = create_image(image_shape, flash_coords, 0)
        self.assertEqual(imdata.shape, image_shape)

    def test_image_flash_location(self):
        flash_coords = FlashList()
        flash_coords.add_flash((2, 2), 1, 0, 1)
        imdata = create_image((5,5), flash_coords, 0)
        flash_array_test = np.array([[  0, 255,   0],
                                     [255, 255, 255],
                                     [  0, 255,   0]])
        self.assertTrue(np.allclose(imdata[1:4,1:4], flash_array_test))

    def test_out_of_frame_flash_not_in_image(self):
        flash_coords = FlashList()
        flash_coords.add_flash((1, 1), 1, 0, 1)
        imdata = create_image((3,3), flash_coords, 1)
        self.assertTrue(np.allclose(imdata, np.zeros((3,3), dtype='uint8')))

    def test_flash_frame_start(self):
        max_duration = 5
        num_frames = 10
        max_frame_start = num_frames - max_duration
        flash_coords = create_flash_coords((1,1), 40, 0, num_frames, (1, max_duration))
        for flash in flash_coords.flashes:
            self.assertLessEqual(flash.frame_start, max_frame_start)
        
    def test_flash_duration(self):
        max_duration = 5
        flash_coords = create_flash_coords((1,1), 40, 0, 10, (1, max_duration))
        for flash in flash_coords.flashes:
            self.assertLessEqual(flash.duration, max_duration)
    
    def test_flash_frame_start_duration_overflow(self):
        num_frames = 10
        for max_duration in range(1,num_frames):
            with self.subTest(max_duration=max_duration):
                flash_coords = create_flash_coords((1,1), 40, 0, num_frames, (1, max_duration))
                for flash in flash_coords.flashes:
                    self.assertLessEqual(flash.frame_start + flash.duration, num_frames)

    def test_flash_is_in_frame(self):
        flash = FlashObject((1,1), 0, 3, 3)
        for frame in range(0,10):
            if frame >= 3 and frame < 6:
                self.assertTrue(flash.is_in_frame(frame))
            else:
                self.assertFalse(flash.is_in_frame(frame))

    def test_image_stack_shape(self):
        flashes = FlashList()
        max_dim = 10
        for x in range(1,max_dim):
            for y in range(1,max_dim):
                for n in range(1,max_dim):
                    with self.subTest(x=x,y=y,n=n):
                        imdata = create_image_stack((x,y), n, flashes)
                        self.assertEqual(imdata.shape, (x,y,n))

    def test_image_stack_flash_frame(self):
        flashes = FlashList()
        frame_start = 3
        duration = 2
        num_frames = 10
        flashes.add_flash((2, 2), 0, frame_start, duration)
        imdata = create_image_stack((3,3), num_frames, flashes)
        for frame in range(0,10):
            if frame >= frame_start and frame < frame_start + duration:
                self.assertEqual(imdata[2,2,frame], 255)
            else:
                self.assertEqual(imdata[2,2,frame], 0)

    def test_parse_args(self):
        parser = create_parser()
        parsed = parser.parse_args(['1', '2', '3', '4', '5'])
        self.assertEqual(parsed.height, 1)
        self.assertEqual(parsed.width, 2)
        self.assertEqual(parsed.frames, 3)
        self.assertEqual(parsed.flashes, 4)
        self.assertEqual(parsed.flash_radius, 5)

    def test_generate_image_stack(self):
        self.skipTest('Test that generate_image_stack saves files correctly')

if __name__ == '__main__':
    unittest.main(exit=False)
