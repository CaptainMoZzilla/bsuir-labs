import os


if __name__ == '__main__':
    biggest_file_name = None
    biggest_file_size = 1024 # by default

    for root, dirs, files in os.walk('.'):
        for file in files:
            file_path = os.path.join(root, file)
            clusters_count = os.path.getsize(file_path)
            if clusters_count > biggest_file_size:
                biggest_file_size = clusters_count
                biggest_file_name = file_path

    print(f'File path: {biggest_file_name}')    
   