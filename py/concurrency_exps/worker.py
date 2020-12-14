#!/usr/bin/env python

import asyncio
import time


def worker(number):
    print('task {number}: started'.format(number=number))
    n = 1
    while n < 3:
        print('task {number}: round {n}'.format(number=number, n=n))
        time.sleep(number)
        n += 1
    print('task {number}: terminated'.format(number=number))


async def worker_async(number):
    print('task {number}: started'.format(number=number))
    n = 1
    while n < 3:
        print('task {number}: round {n}'.format(number=number, n=n))
        await asyncio.sleep(number)
        n += 1
    print('task {number}: terminated'.format(number=number))
