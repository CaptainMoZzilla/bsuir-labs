from caesar import Caesar
from vigenere import Vigenere


with open('./data.txt', 'r') as f:
    text = f.read()

k = 1
phrase = 'aaaaaaa'
caesar = Caesar(k)
vigenere = Vigenere(phrase)

print(f'Original text: {text}')
print('Caesar\n', '=' * 20, f'\nK: {k}', f'\nEncoded: {caesar.encode(text)}', sep='')
print('\nVigenere\n', '=' * 20, f'\nPhrase: {phrase}', f'\nEncoded: {vigenere.encode(text)}', sep='')
