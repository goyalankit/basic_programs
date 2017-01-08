import asyncio
import datetime
import time


"""
Following code executes nothing forever.

if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_forever()

what does it call?
whatever you tell it to
"""

# To solve the problem in async2.py, we create a coroutine.
async def anything(i):
  print(i, datetime.datetime.now())
  await asyncio.sleep(i)
  return i, datetime.datetime.now()


#
# coroutine function = anything
# coroutune = anything(1) <- this has a state. already instantiated.
#

"""
if __name__ == '__main__':
  loop = asyncio.get_event_loop()
  loop.call_later(2, loop.stop)

  for i in range(1,5):
      loop.create_task(anything(i)) # We need to create a task to launch coroutines.
      # asyncio create an instance of Task(anything(1), loop=loop)
      # Inside Task: self._loop.call_soon(self._step)
      # Tasks have steps: may be one job from generator. next(_self.coro)
      # It calls coroutines again and again.
  try:
    loop.run_until_complete(anything(1)) # So that we don't exit before we have finished.
  finally:
    loop.close()
"""

if __name__ == '__main__':
  loop = asyncio.get_event_loop()
  tasks = [loop.create_task(anything(i)) for i in range(1,5)]
  try:
    loop.run_until_complete(
            asyncio.wait(tasks)) # So that we don't exit before we have finished.

    for task in tasks:
        print(*task.result())

  finally:
    loop.close()

