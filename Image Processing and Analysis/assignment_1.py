import numpy as np
import imageio.v3 as imageio

# Calculate the histogram of image pixels
def histogram(A, no_levels):
    N = A.shape[0]
    M = A.shape[1]

    hist = np.zeros(no_levels).astype(int)

    for i in range(no_levels):
        # Sum the number of pixels with value i
        npixel_value_i = np.sum(A == i)
        hist[i] = npixel_value_i

    return hist    

# Perform the accumulate histogram pixelwise transformation of the image
def histogram_equalization(A, no_levels, hist):

    # Cumulative histogram
    histC = np.zeros(no_levels).astype(int)
    
    histC[0] = hist[0]
    for i in range(1, no_levels):
        histC[i] = hist[i] + histC[i-1]

    N = A.shape[0]
    M = A.shape[1]

    # Create the img to store the equalized version
    A_eq = np.zeros([N,M]).astype(np.uint16)

    # Loop through every intensity value possible and tranform all those (z) in the image
    for z in range(no_levels):
        s = ((no_levels - 1) / float(M * N)) * histC[z]

        # For every coordinate in which A == z, replace it with s
        A_eq[np.where(A == z)] = s

    
    return A_eq

# Create the new image with a higher resolution version 
def compose_new_img(l1, l2, l3, l4):
    # Create the new image with the double resolution
    L = np.zeros(((2 * l1.shape[0], 2 * l1.shape[1]))).astype(np.uint16)    
    N = L.shape[0]

    # Fill the cells with the values from the lower resolution images
    for i in range(N):
        for j in range(N):
            if(i % 2 == 0 and j % 2 == 0):
                L[i, j] = l1[int(i/2), int(j/2)]
            elif(i % 2 == 0 and j % 2 != 0):
                L[i, j] = l3[int(i/2), int(j/2)]
            elif(i % 2 != 0 and j % 2 == 0):
                L[i, j] = l2[int(i/2), int(j/2)]
            elif(i % 2 != 0 and j % 2 != 0):
                L[i, j] = l4[int(i/2), int(j/2)]
    return L

# Calculate the root mean squared error to compare
# the enhanced image against reference image
def RMSE(img, img_enhanced):    
    N = img.shape[0]
    sum_squared_diff = np.sum((img - img_enhanced) ** 2)
    mean_squared_diff = sum_squared_diff / (N * N)
            
    return np.sqrt(mean_squared_diff)

# Calculate the Gamma Correction
def gamma_function(L, gamma):
    L = (255 * ((L / 255.0) ** (1 / gamma))) // 1

    return L

# Calculate the error between the reference image and the new image
# composed by other four lower resolution images without enhancement
def option_0(img_low0, img_low1, img_low2, img_low3, img_high):
    H_new = compose_new_img(img_low0, img_low1, img_low2, img_low3)

    return round(RMSE(img_high, H_new), 4)

# Calculate the error between the reference image and the new image
# that first was performed an enhancement to the four lower resolution images,
# then was composed a higher resolution image, and finally a new enhancement
# in this last image
def option_1(img_low0, img_low1, img_low2, img_low3, img_high):
    hist_low0 = histogram(img_low0, 256)
    hist_low1 = histogram(img_low1, 256)
    hist_low2 = histogram(img_low2, 256)
    hist_low3 = histogram(img_low3, 256)

    img_eq1 = histogram_equalization(img_low0, 256, hist_low0)
    img_eq2 = histogram_equalization(img_low1, 256, hist_low1)
    img_eq3 = histogram_equalization(img_low2, 256, hist_low2)
    img_eq4 = histogram_equalization(img_low3, 256, hist_low3)

    new_img = compose_new_img(img_eq1, img_eq2, img_eq3, img_eq4)

    hist_new_img = histogram(new_img, 256)
    H_new = histogram_equalization(new_img, 256, hist_new_img)

    return round(RMSE(img_high, H_new), 4)

# Calculate the error between the reference image and after applied an 
# enhancement to the composed image
def option_2(img_low0, img_low1, img_low2, img_low3, img_high):
    new_img = compose_new_img(img_low0, img_low1, img_low2, img_low3)

    hist_new_img = histogram(new_img, 256)
    H_new = histogram_equalization(new_img, 256, hist_new_img)

    return round(RMSE(img_high, H_new), 4)

# Calculate the error between the reference image and after applied 
# the gamma correction to the image
def option_3(img_low0, img_low1, img_low2, img_low3, img_high, gamma):
    new_img = compose_new_img(img_low0, img_low1, img_low2, img_low3)
    
    H_new = gamma_function(new_img, gamma)

    return round(RMSE(img_high, H_new), 4)


def main():
    img_low_filename = str(input()).rstrip()
    img_high_filename = str(input()).rstrip()
    F = int(input())
    gamma = float(input())

    img_low0 = imageio.imread(img_low_filename + '0.png')
    img_low1 = imageio.imread(img_low_filename + '1.png')
    img_low2 = imageio.imread(img_low_filename + '2.png')
    img_low3 = imageio.imread(img_low_filename + '3.png')
    img_high = imageio.imread(img_high_filename)

    if(F == 0):
        print(option_0(img_low0, img_low1, img_low2, img_low3, img_high))
    elif(F == 1):
        print(option_1(img_low0, img_low1, img_low2, img_low3, img_high))
    elif(F == 2):
        print(option_2(img_low0, img_low1, img_low2, img_low3, img_high))
    elif(F == 3):
        print(option_3(img_low0, img_low1, img_low2, img_low3, img_high, gamma))

if __name__ == '__main__':
    main()