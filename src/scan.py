import os
import json

all_files = []

def process_all_files(root_folder):
    global all_files
    for dirpath, dirnames, filenames in os.walk(root_folder):
        for filename in filenames:
            file_path = os.path.join(dirpath, filename)
            # print(f"Processing file: {file_path}")  # Replace with your actual processing logic
            if (file_path.endswith(".cpp")): all_files.append(file_path)

# Example usage
process_all_files('./')

print(json.dumps(all_files, indent=4))
print(len(all_files))

found_text = []

for file_name in all_files:
    with open(file_name, "r") as fp:
        for line in fp:
            if line not in found_text:
                found_text.append(line)

print(len(found_text))
        
