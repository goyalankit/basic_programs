import asyncio
import datetime


"""
Following code executes `anything` forever.

if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_forever()

what does it call?
whatever you tell it to
"""


def anything(i):
  print(i, datetime.datetime.now())

if __name__ == '__main__':
  loop = asyncio.get_event_loop()
  loop.call_later(2, loop.stop)
  for i in range(1,5):
    loop.call_soon(anything, i)
  try:
    loop.run_forever()
  finally:
    loop.close()
