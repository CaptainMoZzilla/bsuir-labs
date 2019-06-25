import numpy as np


class Matrix:

    @staticmethod
    def findMax(matrix):
        max_element = -10000000000000
        max = [0, 1]

        for i in range(0, len(matrix)):
            for j in range(i + 1, len(matrix)):
                if abs((matrix[i][j])) > max_element:
                    max = [i, j]
                    max_element = abs(matrix[i][j])
        return max

    @staticmethod
    def create_unit_matrix(size):
        matrix = np.array( [[0.0] * size for i in range(size)])

        for i in range(0, size):
            matrix[i][i] = 1.0

        return matrix

    @staticmethod
    def check_conditions(matrix):
        eps = 0.000001

        for i in range(0, len(matrix)):
            for j in range(0, len(matrix)):
                if i == j:
                    continue
                elif abs(matrix[i][j]) > eps:
                    return False
        return True
