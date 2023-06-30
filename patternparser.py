import sys
from PIL import Image, ImageSequence, GifImagePlugin

# Fix GIFS
GifImagePlugin.LOADING_STRATEGY = GifImagePlugin.LoadingStrategy.RGB_ALWAYS

LAYER_SIZE = 4

# Pattern and target filepaths
pattern = ""
target = ""

# List stores processed frames
res = []

try:
    pattern = sys.argv[1]
    target = f"{sys.argv[1].split('.')[0]}.txt";
except IndexError:
    print("Provide a pattern file in the argument!")
    sys.exit();

try:
    target = sys.argv[2]
except IndexError:
    pass
    
with Image.open(pattern) as im:
    print(f"File: {pattern}")
    print(f"Image: {im.format}, {im.size}, {im.mode}")
    
    for frame in ImageSequence.Iterator(im):
        frame_res = [[], [], [], []]
        pixels = frame.getdata()
        
        for y in range(0, 4):
            for x in range(0, 4):
                frame_res[0].append(bool(pixels[(2 * LAYER_SIZE * y) + x][0]))
                frame_res[1].append(bool(pixels[(2 * LAYER_SIZE * y) + x + LAYER_SIZE][0]))
                frame_res[2].append(bool(pixels[(2 * LAYER_SIZE * y) + x + (2 * LAYER_SIZE * LAYER_SIZE)][0]))
                frame_res[3].append(bool(pixels[(2 * LAYER_SIZE * y) + x + (2 * LAYER_SIZE * LAYER_SIZE) + LAYER_SIZE][0]))
        
        # Flattens the list
        res.append([item for sub_list in frame_res for item in sub_list])
        
with open(target, "w+") as out:
    content = repr(res)
    content = content.replace("[", "{")
    content = content.replace("]", "}")
    content = content.lower()
    
    out.write(content)
    
# print(res)
        
        