import random

def dangerous_call(x):
    print("received a " + str(x))
    if x==5:
        print("Ew, we hate 5s. How dare you!")
        raise ValueError
    print("Lovely number!")

try:
  asplode = random.randint(1,10)
  dangerous_call(asplode)
  print("whew... made it.")
except ValueError:
  print("**>_KABOOM_<**")
print("on the other side.")
