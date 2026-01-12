import os
import glob

for file_path in glob.glob('**/main.exe', recursive=True):
    os.remove(file_path)
print("successfully cleared main.exe files")