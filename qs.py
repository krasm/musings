#!/usr/bin/env python3

import unittest
import random

def partition(a, l, r):
    if l < r:
        pivot = l
        l = l + 1
        r = r - 1
        while l <= r:
            while l <= r and a[l] <= a[pivot]:
                l = l + 1
            while a[r] > a[pivot]:
                r = r - 1
            if l < r:
                a[l], a[r] = a[r], a[l]
        a[r], a[pivot] = a[pivot], a[r]

    return r

def qs(a, l, r):
    if l < r:
        p = partition(a, l, r)
        qs(a, l, p)
        qs(a, p+1, r)
    return a


class TestMethods(unittest.TestCase):

    def test_partition(self):
        actual = []
        self.assertEqual(partition(actual, 0, len(actual)), 0, msg="empty is okay")

        actual = [1, 2, 3, 4, 5]
        self.assertEqual(partition(actual, 0, len(actual)), 0, msg="sorted shoudl be preserved")

        actual = [5, 4, 3, 2, 1]
        self.assertEqual(partition(actual, 0, len(actual)), 4, msg="partition sorted in reversed")

        actual = [3, 2, 5, 4, 1]
        self.assertEqual(partition(actual, 0, len(actual)), 2 , msg="pivot shoudl end up in the final position")

    def test_qs(self):
        actual = [3, 2, 5, 4, 1]
        self.assertEqual(qs(actual, 0, len(actual)), [1, 2, 3, 4, 5] , msg="pivot shoudl end up in the final position")

    def test_qs_rand(self):
        n = 10034
        for i in range(0, 17):
            actual = [random.randint(-3*n, 3*n) for x in range(0, n)]
            expected = sorted(actual)
            self.assertEqual(qs(actual, 0, len(actual)), expected)


if __name__ == '__main__':
    unittest.main()
