#!/usr/bin/env python

import asyncio
import time

import worker


async def main():
    await asyncio.gather(
        worker.worker_async(1),
        worker.worker_async(2),
        worker.worker_async(3),
    )


n = time.time()
print('Tasks applied')
asyncio.run(main())
print('Tasks done in {} seconds'.format(time.time() - n))
