from math import atan, cos, sin, radians

from termcolor import colored
import numpy as np

from Matrix import Matrix

if __name__ == "__main__":
    matrix = np.array([[3.0, -1.0, 1.0],
                       [-1.0, 4.0, -1.0],
                       [1.0, -1.0, 5.0]])

    vectorB = np.array([1, -1, 1])
    unit_matrix_list = []

    transfMatrix = matrix.transpose()


    if not np.array_equal(matrix, transfMatrix):
        print(colored("Матрица не симметрична, домножим на трансп.", 'green'))
        transfMatrix = matrix @ transfMatrix
        print("\nПосле трансформации:")
        print(colored(transfMatrix, 'blue'))


    counter = 0

    while not Matrix.check_conditions(transfMatrix):
        indexes = Matrix.findMax(transfMatrix)
        i = indexes[0]
        j = indexes[1]

        fi = 0.5 * atan(2 * transfMatrix[i][j]
                        / (transfMatrix[i][i] - transfMatrix[j][j]))

        unit_matrix = Matrix.create_unit_matrix(len(matrix))

        unit_matrix[i][i] = cos(radians(fi))
        unit_matrix[j][i] = sin(radians(fi))

        unit_matrix[i][j] = -sin(radians(fi))
        unit_matrix[j][j] = cos(radians(fi))

        unit_matrix_list.append(unit_matrix)

        transfMatrix = unit_matrix.transpose() @ transfMatrix @ unit_matrix
        counter+=1

    print("Count:" + str(count))

    print("\n\nСобственные значения")
    for i in range(len(transfMatrix)):
        print(colored(transfMatrix[i][i], 'blue'), end=" ")

    unit_matrix = unit_matrix_list[0]
    for i in range(1, len(unit_matrix_list)):
        unit_matrix = unit_matrix @ unit_matrix_list[i]

    print("\n\nСобственные вектора:")
    print(colored(unit_matrix, 'blue'))

    # print(np.linalg.eig(transfMatrix)[0])
    # print(np.linalg.eig(transfMatrix)[1])
