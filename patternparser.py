import sys
from PIL import Image, ImageSequence, GifImagePlugin

# Fix GIFS
GifImagePlugin.LOADING_STRATEGY = GifImagePlugin.LoadingStrategy.RGB_ALWAYS

# Pattern and target filepaths.
pattern = ""
target = ""

# List stores processed frames.
res = []

# If no file is provided.
try:
    pattern = sys.argv[1]
    target = f"{sys.argv[1].split('.')[0]}.txt";
except IndexError:
    print("Provide a pattern file in the argument!")
    sys.exit();

# If a target file is provided.
try:
    target = sys.argv[2]
except IndexError:
    pass

with Image.open(pattern) as im:
    print(f"File: {pattern}")
    print(f"Image: {im.format}, {im.size}, {im.mode}")
    print(f"Target: {target}")
    
    for frame in ImageSequence.Iterator(im):
        frame_res = []
        pixels = frame.getdata()
        
        # Expected input is a 8x8 texture that has 4x4 sized layers.
        
        # Expected output is four subarrays that correspond to each layer, per frame.
        # Each subarray is arranged into two bytes each corresponding to a 4x2 area.
        
        for layer in range(0, 4):
            # Get lower bounds for pixel coordinates.
            x_lower = (layer % 2) * 4
            y_lower = (layer // 2) * 4
            
            top_byte = "00000000"
            bottom_byte = "00000000"
            for y in range(0, 4):
                for x in range(0, 4):
                    pixel_index = 0;
                    
                    if (layer == 0):
                        pixel_index = y * 8 + x
                    elif (layer == 1):
                        pixel_index = y * 8 + x + 4
                    elif (layer == 2):
                        pixel_index = y * 8 + x + 32
                    elif (layer == 3):
                        pixel_index = y * 8 + x + 32 + 4
                        
                    # Get the value of the pixels red channel, 1 if white, 0 if black.
                    val = bool(pixels[pixel_index][0])
                    
                    if (not val):
                        continue
                    
                    bit_index = 0
                    
                    if (y < 2):
                        bit_index = y * 4 + x
                        
                        # Flip that bit (don't mind the string spaghetti)
                        top_byte = f"{top_byte[:bit_index]}1{top_byte[bit_index + 1:]}"
                        
                    else:
                        bit_index = (y - 2) * 4 + x
                        
                        bottom_byte = f"{bottom_byte[:bit_index]}1{bottom_byte[bit_index + 1:]}"

            # print(bin(top_byte))
            # print(bin(bottom_byte))
            frame_res.append(f"0b{top_byte}")
            frame_res.append(f"0b{bottom_byte}")
            
        # Compile all frames into one big array
        res.append(frame_res)
        
with open(target, "w+") as out:
        
    content = repr(res)
    content = content.replace("[", "{")
    content = content.replace("]", "}")
    content = content.replace("'", "")
    content = content.lower()
    
    out.write(content)