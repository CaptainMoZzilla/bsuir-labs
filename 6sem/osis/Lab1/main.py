# First variant
import os


surname = 'volkov'

def sxor(s1,s2):    
    return ''.join(chr(ord(a) ^ ord(b)) for a,b in zip(s1,s2))

if __name__ == "__main__":
    base_filename = input()
    target_filename = input()

    for root, dirs, files in os.walk('.'):
        for file in files:
            if file == target_filename:
                print('WARNING! Target file exists')
    
    for root, dirs, files in os.walk('.'):
        for file in files:
            if file == base_filename:
                with open(f'./{target_filename}', 'w') as target_file:
                    with open(os.path.join(root, file), 'r') as base_file:
                        text = base_file.read()
                        xor = sxor(text, surname * (len(text) // len(surname) + 1))
                        target_file.write(xor)
                        print('SUCCESS!')
                        exit()
    print('ERROR! There is no source file')
                   