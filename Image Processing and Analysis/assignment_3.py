
####################################################################
# Bruno Berndt Lima -  12542550                                    #
# SCC0251 - Image Processing and Analysis                          #
# 2024.1                                                           #                    
# Assignment 3: Color & Segmentation & Morphology                  #
####################################################################

import numpy as np
import imageio.v3 as imageio
 
def convert_to_grayscale(img):
    """
    Convert an RGB image to grayscale.

    Args:
        img: The input image array.

    Returns:
        The grayscale image array.
    """

    # If it is RGB, it converts it to Gray, otherwise it just keeps it
    if len(img.shape) > 2:
        img = np.dot(img, [0.2989, 0.5870, 0.1140]).astype(np.int64)
    
    return img

def convert_to_binary(img):
    """
    Convert an image to binary using Otsu's thresholding method.

    Args:
        img: The input image array.

    Returns:
        The binary image array.
    """
    return otsu_threshold(img.copy(), 256)

def thresholding(img, L):
    """
    Apply thresholding to an image.

    Args:
        img: The input image array.
        L: The threshold value.

    Returns:
        The thresholded image array.
    """

    # Create a new image with zeros
    img_tr = np.zeros_like(img, dtype=np.uint8)
    # Setting to 1 the pixels above or equal to the threshold
    img_tr[np.where(img >= L)] = 1
    
    return img_tr


def otsu_threshold(img, max_L):
    """
    Apply Otsu's thresholding method to an image.

    Args:
        img: The input image array.
        max_L: The maximum threshold value to search for.

    Returns:
        The binary image array after thresholding.
    """

    # List to store the minimum variance values
    min_var = []
    # Histogram of the image
    hist_t, _ = np.histogram(img, bins=256, range=(0, 256))
    # Normalization of the histogram
    hist_t = hist_t / np.sum(hist_t)

    for L in range(1, max_L):
        # Computing weights of first class(w_a) and second class(w_b)
        w_a = np.sum(hist_t[:L])
        w_b = np.sum(hist_t[L:])

        # Check if weights are zero
        if w_a == 0 or w_b == 0:
            # Append infinity if either weight is zero
            min_var.append(np.inf)
            continue

        # Computing variances
        sig_a = np.var(img[np.where(img < L)])
        sig_b = np.var(img[np.where(img >= L)])

        # Compute the within-class variance and append it to the list
        min_var.append(w_a * sig_a + w_b * sig_b)

    if len(min_var) == 0:
        raise ValueError("No valid threshold found. All weights are zero.")

    # Find the threshold that minimizes the within-class variance
    img_t = thresholding(img, np.argmin(min_var) + 1)
    
    return img_t


def erosion(img, M, N):
    """
    Perform erosion operation on a binary image using a 3x3 structuring element.

    Args:
        img: The input binary image array.
        M: Number of rows in the image.
        N: Number of columns in the image.

    Returns:
        The eroded binary image array.
    """

    # Define the structuring element (3x3 kernel)
    kernel = np.array([[1, 1, 1],
                       [1, 1, 1],
                       [1, 1, 1]])

    # Create a new image with zeros
    eroded_img = np.zeros_like(img, dtype=np.uint8)
    for i in range(1, M - 1):
        for j in range(1, N - 1):
            # Apply erosion operation by taking the minimum value of the neighborhood
            eroded_img[i, j] = np.min(img[i - 1:i + 2, j - 1:j + 2] * kernel)
    
    return eroded_img


def dilation(img, M, N):
    """
    Perform dilation operation on a binary image using a 3x3 structuring element.

    Args:
        img: The input binary image array.
        M: Number of rows in the image.
        N: Number of columns in the image.

    Returns:
        The dilated binary image array.
    """
    
    # Define the structuring element (3x3 kernel)
    kernel = np.array([[1, 1, 1],
                       [1, 1, 1],
                       [1, 1, 1]])

    # Create a new image with zeros                   
    dilated_img = np.zeros_like(img, dtype=np.uint8)
    for i in range(1, M - 1):
        for j in range(1, N - 1):
            # Apply dilation operation by taking the maximum value of the neighborhood
            dilated_img[i, j] = np.max(img[i - 1:i + 2, j - 1:j + 2] * kernel)
    
    return dilated_img


def apply_morphology_to_img(img, operations):
    """
    Apply morphological operations to an image according to the specified cycle.

    Args:
        img: The input binary image array.
        operations: A list specifying the sequence of morphological operations to apply.
               Each element in the list indicates a specific operation:
               1 for erosion, 2 for dilation.

    Returns:
        The image array after applying the specified morphological operations.
    """
    

    M, N = img.shape

    for operation in operations:
        if operation == 1:
            # Erosion cycle (Expands the area of interest (black) and reduces the non-interest area (white) -> Returns to the original size without noise)
            img = erosion(img, M, N)
        elif operation == 2:
            # Dilation cycle (Expands the area of non-interest (white) and reduces the area of interest (black) -> Noise reduction)
            img = dilation(img, M, N)
    
    return img

def gaussian_filter(P, Q):
    """
    Generate a 2D Gaussian filter.

    Args:
        P: Size of the filter along the vertical direction.
        Q: Size of the filter along the horizontal direction.

    Returns:
        The 2D Gaussian filter array.
    """
    
    sigma1 = P  # Standard deviation along the vertical direction
    sigma2 = Q  # Standard deviation along the horizontal direction

    filter = np.zeros((P, Q))  # Initialize the filter array with zeros

    for u in range(P):  
        for v in range(Q):
            x = (((u - P / 2) ** 2) / (2 * sigma1 ** 2)) + (((v - Q / 2) ** 2) / (2 * sigma2 ** 2))
            filter[u, v] = np.exp(-x)

    return filter  

def map_value_to_color(value, min_val, max_val, colormap):
    """
    Map a numerical value to a color based on a colormap.

    Args:
        value: The numerical value to be mapped.
        min_val: The minimum value of the range.
        max_val: The maximum value of the range.
        colormap: The colormap represented as a list of RGB tuples.

    Returns:
        The color corresponding to the mapped value.
    """
    
    # Scale the value to the range [0, len(colormap) - 1]
    scaled_value = (value - min_val) / (max_val - min_val) * (len(colormap) - 1)
    
    # Determine the two closest colors in the colormap
    idx1 = int(scaled_value)
    idx2 = min(idx1 + 1, len(colormap) - 1)
   
    # Interpolate between the two colors based on the fractional part
    frac = scaled_value - idx1
    color = [
        (1 - frac) * colormap[idx1][0] + frac * colormap[idx2][0],  # Red component
        (1 - frac) * colormap[idx1][1] + frac * colormap[idx2][1],  # Green component
        (1 - frac) * colormap[idx1][2] + frac * colormap[idx2][2]   # Blue component
    ]
    
    return color


def RMSE(H, G):    
    """
    Calculate the Root Mean Squared Error (RMSE) between two images.

    Args:
        H: The input image array.
        G: The reference image array.

    Returns:
        The RMSE value between the two images.
    """

    M = H.shape[0]
    N = H.shape[1]
    
    sum_squared_diff = np.sum((H - G) ** 2)
    mean_squared_diff = sum_squared_diff / (M * N)
            
    return np.sqrt(mean_squared_diff)

def blend_images_with_heatmap(grayscale_img, heatmap_colors, morph_img, alpha=0.3):
    """
    Generate a result image by blending a grayscale image with a heatmap and a binary morphological image.

    Args:
        grayscale_img: The grayscale input image array.
        heatmap_colors: The list of RGB tuples representing heatmap colors.
        morph_img: The binary morphological image array.
        alpha: represents the blending factor or opacity. A value of 0 means the grayscale image is completely 
               transparent, while a value of 1 means the grayscale image is completely opaque.

    Returns:
        The result image array.
    """

    mask = morph_img

    # Generate Gaussian distribution for color blending
    M, N = mask.shape[0], mask.shape[1]
    color_distribution = gaussian_filter(M, N)
    
    min_val = np.min(np.array(color_distribution))
    max_val = np.max(np.array(color_distribution))

    # Generate heatmap image
    heatmap_image = np.zeros([M, N, 3])  # Empty RGB image
    for i in range(M):
        for j in range(N):
            heatmap_image[i, j] = map_value_to_color(color_distribution[i, j], min_val, max_val, heatmap_colors)

    # Colorize the regions outside the morphological image
    img_color = np.ones([M, N, 3])  # Empty RGB image
    indexes = np.where(mask == 0)
    img_color[indexes] = heatmap_image[indexes]

    # Normalize grayscale image
    gray_image = grayscale_img
    gray_image_normalized = gray_image / np.max(gray_image)

    # Mix the grayscale image and heatmap using alpha compositing (70% original image and 30% colored mask)
    mixed_image = (1 - alpha) * gray_image_normalized[..., None] + alpha * img_color
    mixed_image *= 255  # Normalize
    mixed_image = mixed_image.astype(np.uint8)

    return mixed_image

def main():
    #Read inputs
    img_filename = str(input()).rstrip()
    ref_img_filename = str(input()).rstrip()
    line = input()
    numbers_str = line.split()
    indices = [int(num) for num in numbers_str]

    # Input image
    I = imageio.imread(img_filename)
    # Reference image
    H = imageio.imread(ref_img_filename)

    # Convert image to grayscale
    grayscale_img = convert_to_grayscale(I)
    # Binarize the grayscale image
    binary_img = convert_to_binary(grayscale_img)
    # Transform the binary image using Morphological Operations
    morph_img = apply_morphology_to_img(binary_img, indices)

    # Visible Spectrum
    heatmap_colors = [
        [1, 0, 1],   # Pink
        [0, 0, 1],   # Blue
        [0, 1, 0],   # Green
        [1, 1, 0],   # Yellow
        [1, 0, 0]    # Red
    ]

    # Get the result image 
    result_img = blend_images_with_heatmap(grayscale_img, heatmap_colors, morph_img)

    # Calcula o erro para cada canal de cor
    error_R = RMSE(result_img[:,:,0], H[:,:,0])
    error_G = RMSE(result_img[:,:,1], H[:,:,1])
    error_B = RMSE(result_img[:,:,2], H[:,:,2])
    error = (error_R + error_G + error_B) / 3

    print(f"{error:.4f}")


if __name__ == '__main__':
    main()