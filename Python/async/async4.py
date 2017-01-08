import asyncio
import datetime
from contextlib import suppress


class Periodic:
    def __init__(self, func, time):
        self.func = func
        self.time = time
        self.is_started = False
        self._task = None

    async def start(self):
        if not self.is_started:
            self.is_started = True
            # Start task to call func periodically:
            self._task = asyncio.ensure_future(self._run())

    async def stop(self):
        if self.is_started:
            self.is_started = False
            # Stop task and await it stopped:
            self._task.cancel()
            with suppress(asyncio.CancelledError):
                await self._task

    async def _run(self):
        while True:
            print ('Running collector %s' % self.time)
            await asyncio.sleep(self.time)
            output = self.func()
            print ('posting output to someplace %s' % output)


def collector():
    return datetime.datetime.now()


async def main():
    p1 = Periodic(collector, 2)
    p2 = Periodic(collector, 2)

    try:
        print('Start')

        await p1.start()
        await p2.start()

    finally:
        await p1.stop()  # we should stop task finally
        await p2.stop()  # we should stop task finally


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    p1 = Periodic(collector, 1)
    p2 = Periodic(collector, 2)
    task1 = loop.create_task(p1.start())
    task2 = loop.create_task(p2.start())

    sleep(5)
    task1.cancel()
    # loop.run_until_complete(asyncio.wait([task1, task2]))
    loop.run_forever()
