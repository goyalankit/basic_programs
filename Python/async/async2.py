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


def anything(i):
  print(i, datetime.datetime.now())
  time.sleep(i) # This will slow everything down. Use PYTHONASYNCIODEBUG=1 python async2.py

if __name__ == '__main__':
  loop = asyncio.get_event_loop()
  loop.call_later(2, loop.stop)

  for i in range(1,5):
    loop.call_soon(anything, i)
  try:
    loop.run_forever()
  finally:
    loop.close()
