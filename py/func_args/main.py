import datetime
import time

from fastapi import Query

# ======================= API query string default value

#@api.get("/refuel/quote")
def _get_quote(ts: int = Query(alias="quoteTime", default=int(time.time()))) -> int:
    return ts.default


#print(datetime.datetime.fromtimestamp(_get_quote()))
#print("sleeping for 1 second...")
#time.sleep(1)
#print(datetime.datetime.fromtimestamp(_get_quote()))


# ======================= function default value

def _ts(now: int = {}) -> int:
    now[int(time.time())] = True
    return now

def _ts2() -> int:
    return int(time.time())

print(_ts())
time.sleep(1)
print(_ts())


#print(datetime.datetime.fromtimestamp(_ts()))
#print(datetime.datetime.fromtimestamp(_ts()))
#print(datetime.datetime.fromtimestamp(_ts()))
#print(datetime.datetime.fromtimestamp(_ts2()))

# ======================= function args

def _pos_only(one, two, /):
    print(one, two)

def _kw_only(*, one, two):
    print(one, two)

def _kw_only2(*, one, two, **kwargs):
    print(one, two, kwargs)

def _args_kwargs(a, /, *args, b, c,  **kwargs):
    print(a, args, b, c, kwargs)

# _args_kwargs(1, 2, 3, 4, b=5, c=6, d=7, e=8)

# ======================= function args

def _args(one, two, /, three, four=4, *, five, six, **kwags):
    print(one, two, three, four, five, six, kwags)

# X. _args(1, 2, 3, 4, 5, 6)
# O. _args(1, 2, 3, 4, five=5, six=6)
# O. _args(1, 2, four=4, three=3, five=5, six=6)
# X. _args(one=1, two=2, three=3, four=4, five=5, six=6)
# O. _args(1, 2, three=3, four=4, five=5, six=6, seven=7)
# -. _args(1, 2, three=3, five=5, six=6, seven=7)
