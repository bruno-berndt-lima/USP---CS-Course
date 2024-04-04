import numpy as np
import matplotlib.pyplot as plt
import imageio.v3 as imageio

def low_pass_filter(F, r):
    """
    Creates a low-pass filter in the frequency domain.

    Args:
        F: The Fourier transformed image.
        r: The radius for the filter.

    Returns:
        A 2D numpy array representing the low-pass filter.
    """

    n = F.shape[0]
    m = F.shape[1]

    filter = np.zeros((n,m))
    
    for u in range(n):
        for v in range(m):
            if(np.sqrt(D(u, v, n, m)) <= r):
                filter[u,v] = 1
            else:
                filter[u,v] = 0
    
    return filter

def high_pass_filter(F, r):
    """
    Creates a high-pass filter in the frequency domain.

    Args:
        F: The Fourier transformed image.
        r: The radius for the filter.

    Returns:
        A 2D numpy array representing the high-pass filter.
    """

    n = F.shape[0]
    m = F.shape[1]

    filter = np.ones((n,m))

    for u in range(n):
        for v in range(m):
            if(np.sqrt(D(u, v, n, m)) <= r):
                filter[u,v] = 0
            else:
                filter[u,v] = 1
    
    return filter

def band_stop_filter(F, r0, r1):
    """
    Creates a band-stop filter in the frequency domain.

    Args:
        F: The Fourier transformed image.
        r0: The bigger radius of the stop band.
        r1: The smaller radius of the stop band.

    Returns:
        A 2D numpy array representing the band-stop filter.
    """

    n = F.shape[0]
    m = F.shape[1]

    filter = np.ones((n,m))

    for u in range(n):
        for v in range(m):
            if(r1 < np.sqrt(D(u, v, n, m)) <= r0):
                filter[u,v] = 0
            else:
                filter[u,v] = 1

    return filter


def laplacian_filter(F):
    """
    Creates a Laplacian filter in the frequency domain.

    Args:
        F: The Fourier transformed image.

    Returns:
        A 2D numpy array representing the Laplacian filter.
    """

    n = F.shape[0]
    m = F.shape[1]

    filter = np.zeros((n,m))

    for u in range(n):
        for v in range(m):
            filter[u,v] = -4 * (np.pi ** 2) * D(u, v, n, m)
          
    return filter

def gaussian_filter(F, sigma1, sigma2):
    """
    Creates a Gaussian filter in the frequency domain.

    Args:
        F: The Fourier transformed image.
        sigma1: The standard deviation along the x-axis.
        sigma2: The standard deviation along the y-axis.

    Returns:
        A 2D numpy array representing the Gaussian filter.
    """

    n = F.shape[0]
    m = F.shape[1]

    filter = np.zeros((n,m))

    for u in range(n):
        for v in range(m):
             x = (((u - n/2) ** 2) / (2*sigma1 ** 2)) + (((v - m/2) ** 2) / (2*sigma2 ** 2))
             filter[u,v] = np.exp(-x)

    return filter

def frequency_domain_filter(image, filter_type):
    """
    Apply frequency domain filtering to the given image.

    Args:
        image: Input image array.
        filter_type: Type of filter to apply (e.g., low-pass, high-pass).

    Returns:
        Filtered image array.
    """

    F = np.fft.fftshift(np.fft.fft2(image))
    img_filtered = np.multiply(F, filter_type)
    F_1 = np.fft.ifft2(np.fft.ifftshift((img_filtered)))

    return F_1

def D(u, v, P, Q):
    """
    Calculate the distance between a point (u, v) and the center (P/2, Q/2).

    Args:
        u: The horizontal coordinate of the point.
        v: The vertical coordinate of the point.
        P: The width of the image.
        Q: The height of the image.

    Returns:
        The distance between the point (u, v) and the center (P/2, Q/2).
    """

    return ((u - P/2) ** 2) + ((v - Q/2) ** 2)


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


def main():
    #Read inputs
    img_filename = str(input()).rstrip()
    ref_img_filename = str(input()).rstrip()

    # Input image
    I = imageio.imread(img_filename)
    # Reference image
    H = imageio.imread(ref_img_filename)

    index = int(input())
    # Choose which filter will be used
    match index:
        case 0:
            r = int(input())
            filter = low_pass_filter(I, r)

        case 1:
            r = int(input())
            filter = high_pass_filter(I, r)
        case 2:
            r0 = int(input())
            r1 = int(input())
            filter = band_stop_filter(I, r0, r1)
        case 3:
            filter = laplacian_filter(I)
        case 4:
            sigma0 = int(input())
            sigma1 = int(input())
            filter = gaussian_filter(I, sigma0, sigma1)
            
    
    # Restored image
    G = np.real(frequency_domain_filter(I, filter))
    # Normalized G
    norm_G = ((G - np.min(G)) * (255 / (np.max(G) - np.min(G)))).astype(np.uint8)

    print(RMSE(H, norm_G))
    

if __name__ == '__main__':
    main()
