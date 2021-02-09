#!/usr/bin/env python3

import unittest
import numpy as np
import eigen_tensors as et

class MainTest(unittest.TestCase):
    def test_make_tensor3(self):
        t = et.make_tensor3();
        self.assertEqual(t.shape, (2, 3, 4))

        val = 0.0
        for j in range(2):
            for k in range(3):
                for l in range(4):
                    self.assertAlmostEqual(t[j, k, l], val)
                    val += 0.1
        print("# of tests:", int(val * 10))

    def test_modify_tensor3(self):
        index = 0
        for d1 in range(4):
            for d2 in range(4):
                for d3 in range(4):
                    t1 = np.random.rand(d1, d2, d3)
                    t2 = et.modify_tensor3(t1)
                    val = 0.0
                    for j in range(d1):
                        for k in range(d2):
                            for l in range(d3):
                                """
                                print('{} {} {} - {} {} {} - {} {} {}'.format(d1, d2, d3,
                                                                           j, k, l,
                                                                              t1[j, k, l],
                                                                              t2[j, k, l],
                                                                              val))
                                """
                                self.assertAlmostEqual(t2[j, k, l],
                                                       t1[j, k, l] + val)
                                val += 0.1
                                index += 1
                                
        print("# of tests:", index)
                    
if __name__ == '__main__':
    unittest.main()
