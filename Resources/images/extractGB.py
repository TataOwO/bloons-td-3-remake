from PIL import Image
import numpy as np

def extract_red_channel(input_path, output_path):
    """
    Read an image, set all green and blue values to 0 (keeping only red),
    and save the result to a new location.
    
    Args:
        input_path (str): Path to the input image
        output_path (str): Path where the modified image will be saved
    """
    try:
        # Open the image and convert to RGB mode (in case it's not already)
        img = Image.open(input_path).convert('RGBA')
        img.seek(0)
        
        # Convert to numpy array for easier manipulation
        img_array = np.array(img)
        
        # Set green and blue channels to 0
        # RGB is represented as [r, g, b] in the last dimension
        img_array[:, :, 1] = 0  # Green channel
        img_array[:, :, 2] = 0  # Blue channel
        
        # Convert back to PIL Image
        red_only_img = Image.fromarray(img_array)
        
        # Save the modified image
        red_only_img.save(output_path)
        
        print(f"Successfully processed image and saved to {output_path}")
        return True
        
    except Exception as e:
        print(f"Error processing image: {e}")
        return False

# Example usage
if __name__ == "__main__":
    # Replace these with your actual file paths
    monke_name = "boomerang"
    file_type = "png"
    input_image_path = rf"./monke/{monke_name}.{file_type}"
    output_image_path = rf"./monke/{monke_name}_red.{file_type}"
    
    extract_red_channel(input_image_path, output_image_path)