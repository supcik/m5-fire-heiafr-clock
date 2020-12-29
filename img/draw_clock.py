from PIL import Image, ImageDraw
import math

def f1(x):
    return 8*x

def f(x):
    return (f1(x[0]), f1(x[1]))

im = Image.new("RGB", f((320,240)), "black")
draw = ImageDraw.Draw(im)
draw.ellipse([f((40, 0)), f((280, 240))], fill="white")

l0 = 90
l1 = 107
l2 = 117

for a in range(60):
    x0 = 160 + l1 * math.sin(a*math.pi/30)
    y0 = 120 + l1 * math.cos(a*math.pi/30)

    x1 = 160 + l2 * math.sin(a*math.pi/30)
    y1 = 120 + l2 * math.cos(a*math.pi/30)

    draw.line([f((x0,y0)), f((x1,y1))], fill="black", width=f1(3))


for a in range(12):
    x0 = 160 + l0 * math.sin(a*math.pi/6)
    y0 = 120 + l0 * math.cos(a*math.pi/6)

    x1 = 160 + l2 * math.sin(a*math.pi/6)
    y1 = 120 + l2 * math.cos(a*math.pi/6)

    draw.line([f((x0,y0)), f((x1,y1))], fill="black", width=f1(7))

im.show()

with open("clock.png", "wb") as f:
    im.save(f, "PNG")
    
