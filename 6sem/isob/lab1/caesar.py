class Caesar:
    def __init__(self, k: int):
        self.__k = k

    def encode(self, text):
        return ''.join(map(self.__encode_char, text))

    def decode(self, text):
        return ''.join(map(self.__decode_char, text))

    def __is_english(self, char):
        i = ord(char)
        return (97 <= i <= 122) or (65 <= i <= 90)

    def __get_shift(self, char):
        if self.__is_english(char):
            return 65 if char.isupper() else 97

        return 1040 if char.isupper() else 1072

    def __encode_char(self, char):
        if not char.isalpha():
            return char

        shitf = self.__get_shift(char)
        n = 26 if self.__is_english(char) else 32

        return chr((ord(char) - shitf + self.__k) % n + shitf)

    def __decode_char(self, char):
        if not char.isalpha():
            return char

        shitf = self.__get_shift(char)
        n = 26 if self.__is_english(char) else 32

        return chr((ord(char) - shitf - self.__k + n) % n + shitf)
