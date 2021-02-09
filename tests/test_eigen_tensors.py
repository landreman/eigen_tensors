#!/usr/bin/env python3

import unittest
import eigen_tensors as et

class MainTest(unittest.TestCase):
    def test_make_tensor3(self):
        t = et.make_tensor3();
        self.assertEqual(t.shape, (2, 3, 4))

        index = 0.0
        for j in range(2):
            for k in range(3):
                for l in range(4):
                    self.assertAlmostEqual(t[j, k, l], index)
                    index += 0.1

if __name__ == '__main__':
    unittest.main()
