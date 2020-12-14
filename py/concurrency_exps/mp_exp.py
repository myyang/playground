#!/usr/bin/env python

import time
import multiprocessing as mp

import worker

if __name__ == '__main__':
    tasks = [1, 2, 3]
    n = time.time()
    pool = mp.Pool(2)
    res = pool.map_async(worker.worker, tasks)
    print('Tasks applied')
    pool.close()
    pool.join()
    print('Tasks done in {} seconds'.format(time.time() - n))
