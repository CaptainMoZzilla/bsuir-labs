import time
from os import system, name 
from datetime import datetime

import mysql.connector
from mysql.connector import Error
import pandas as pd

from test_data import fill_tables
from sql_helper import tables, insert_queries,\
                       table_columns
from config import HOST_NAME, DATABASE,\
                   USER_NAME, PASSWORD,\
                   IS_COLD_START


def clear(): 
    system('cls') if name == 'nt' else system('clear')


def get_database():
    try:
        database = mysql.connector.connect(host=HOST_NAME, database=DATABASE,
                                           user=USER_NAME, password=PASSWORD)
        if database.is_connected():
            return database
    except Error as e:
        print("Error while connecting to MySQL", e)
        exit()

    print("Error while connecting to MySQL")
    exit()


def print_start_menu():
    print('Главное меню\nДля выбора пункта меню - введите его номер\n')
    print('1 Добавить данные в таблицы')
    print('2 Удаление данных из таблиц')
    print('3 Найти id элемента')
    print('4 Вывести таблицы')
    print('5 За(от)крепить машину')
    print('6 Изменить данные в таблицах')
    print('0 Для выхода')


###############################################################################
##### INSERT, DELETE, EXIST, GET_ID, SELECT, UPDATE
###############################################################################


def insert(query, values):
    cursor = database.cursor()
    try:
        cursor.execute(query, values)
        database.commit()
    except Exception as e:
        print(e)
        print('Это значение уже пристутствует')
        database.rollback()
        time.sleep(2)


def exist(column_name, column_value, table_name):
    cursor = database.cursor()
    cursor.execute(f'SELECT count(1) FROM {table_name} WHERE {column_name}="{column_value}";')
    value = cursor.fetchone()
    if value[0]:
        return True
    else:
        return False


def delete(table_name, idx):
    cursor = database.cursor()
    cursor.execute(f'DELETE FROM {table_name} WHERE id = "{idx}";')
    database.commit()
    input('Нажмите enter чтобы продолжить')


def get_last_id():
    cursor = database.cursor()
    cursor.execute('SELECT LAST_INSERT_ID();')
    return cursor.fetchone()[0]


def get_id(column_name, column_value, table_name):
    cursor = database.cursor()
    cursor.execute(f'SELECT id FROM {table_name} WHERE {column_name}="{column_value}";')
    return cursor.fetchone()[0]


def add_value(table_name):
    if table_name not in {'car', 'driver', 'brand', 'color'}:
        value = input('Введите новое значение: ')
        insert(insert_queries[table_name], (value,))
    
    elif table_name == 'brand':
        full_name = input('Введите полное имя: ')
        short_name = input('Введите сокращенное имя: ')
        insert(insert_queries[table_name], (full_name, short_name))

    elif table_name == 'color':
        code = input('Введите код цвета: ')
        color_name = input('Введите имя цвета(можно оставить пустым): ')
     
        if not len(color_name):
            color_name = '#' + str(code)
        insert(insert_queries[table_name], (color_name, code))
    
    elif table_name == 'driver':
        clear()
        print('Если Ф.И.О. остуствует в базе, \nто оно будет добавлено автоматически.\n'
              'Номер водительского должен быть уникальным!!!\n')
        name = input('Введите имя: ')
        surname = input('Введите фамилию: ')
        patronymic = input('Введите отчество: ')
        passport_number = input('Введите номер паспорта: ')
        adoption_date = datetime.today().strftime('%Y-%m-%d %H:%M:%S')
        phone_number = input('Введите номер телефона: ')
        license_number = input('Введите номер водительского: ')

        if not exist('name', name, 'name'):
            insert(insert_queries['name'], (name,))
            name_id = get_last_id()
        else:
            name_id = get_id('name', name, 'name')

        if not exist('surname', surname, 'surname'):
            insert(insert_queries['surname'], (surname,))
            surname_id = get_last_id()
        else:
            surname_id = get_id('surname', surname, 'surname')

        if not exist('patronymic', patronymic, 'patronymic'):
            insert(insert_queries['patronymic'], (patronymic,))
            patronymic_id = get_last_id()
        else:
            patronymic_id = get_id('patronymic', patronymic, 'patronymic')

        values = (name_id, surname_id, patronymic_id, passport_number,
                  adoption_date, phone_number, license_number)

        insert(insert_queries[table_name], values)  
    elif table_name == "car":
        clear()
        print('Номер автомобиля должен быть уникальным!!!\n')

        brand = None
        while True:
            brand = input('Введите марку автомобиля(-1 чтобы выйти): ')
            try:
                brand_id = get_id('brand_name', brand, 'brand')
                break
            except:
                if brand == '-1':
                    return
                print('Не существует такой марки.')
                input('Enter чтобы продолжить')
                return

        model = None
        while True:
            model = input('Введите модель автомобиля(-1 чтобы выйти): ')
            try:
                model_id = get_id('model_name', model, 'model')
                break
            except:
                if model == '-1':
                    return
                print('Не существует такой модели.')
                input('Enter чтобы продолжить')
                return

        color_code = None
        while True:
            color_code = input('Введите код цвета(-1 чтобы выйти): ')
            try:
                color_id = get_id('color_code', color_code, 'color')
                break
            except:
                if color_code == '-1':
                    return
                print('Не существует такго цвета.')
                input('Enter чтобы продолжить')
                return
 
        number = input('Введите номер автомобиля: ')
        
        oil_type = None
        while oil_type not in {'б', 'д', 'э'}:
            oil_type = input('Введите тип топлива(б-Бензин, д-Дизель, Э-электро): ')

        if oil_type == 'б':
            oil_type = 'petrol'
        elif oil_type == 'д':
            oil_type = 'diesel'
        else:
            oil_type = 'electro'
        
        values = (brand_id, model_id, color_id, number, oil_type)
        insert(insert_queries[table_name], values)
    input('Нажмите enter чтобы продолжить')


def find_value_id(table_name):
    column_name = table_name
    if table_name in {'brand', 'model', 'color'}:
        column_name += '_name'   
        value = input('Введите значение: ')
        try:
            idx = get_id(column_name, value, table_name)
        except:
            print('Такого элемента не существует')
            input('\nНажмите любую клавишу чтобы продолжить...')
            return
    elif table_name == 'car':
        car_number = input('Введите номер машины: ')
        try:
            idx = get_id('number', car_number, table_name)
        except:
            print('Такого элемента не существует')
            input('\nНажмите любую клавишу чтобы продолжить...')
            return
    elif table_name == 'driver':
        passport_number = input('Введите номер паспотра: ')
        try:
            idx = get_id('passport_number', passport_number, table_name)
        except:
            print('Такого элемента не существует')
            input('\nНажмите любую клавишу чтобы продолжить...')
            return
    else:
        value = input('Введите значение: ')
        try:
            idx = get_id(table_name, value, table_name)
        except:
            print('Такого элемента не существует')
            input('\nНажмите любую клавишу чтобы продолжить...')
            return
    print('ID элемента: ', idx)
    input('\nНажмите любую клавишу чтобы продолжить...')


def show_one_table(table_name):
    cursor = database.cursor()
    # if table_name == 'driver':
    #     val = input('Отсортировать по:\n1 Имя\n2 Фамилия\n3 Отчество\n4 Дате принятия на работу')
    #     quety = 'Order by <SomeColumn> Offset {offset} ROWS LIMIT 10;'
    #     if val in set(range(1, 4)):

    if table_name not in {'car', 'driver', 'pinned_car'}:
        query = f'SELECT * FROM {table_name};'
    elif table_name == 'car':
        query =  ('SELECT car.id, brand.brand_name, model.model_name, color.color_name, number, oil_type '
                  'FROM car_agency.car '
                  'LEFT OUTER JOIN brand ON brand.id = car.brand_id '
                  'LEFT OUTER JOIN model ON model.id = car.model_id '
                  'LEFT OUTER JOIN color ON color.id = car.color_id;')
    elif table_name == 'driver':
        sort_val = None
        while sort_val not in set(['1', '2', '3', '4']):
            sort_val = input('Отсортировать по:\n1 Имя\n2 Фамилия\n3 Отчество\n4 Дате принятия на работу\n > ')

        query = ('SELECT driver.id, name, surname.surname, patronymic.patronymic, '
	             'passport_number, adoption_date, phone_number, driver_license_number '
                 'FROM car_agency.driver '
                 'LEFT OUTER JOIN name ON name.id = driver.name_id '
                 'LEFT OUTER JOIN surname ON surname.id = driver.surname_id '
                 'LEFT OUTER JOIN patronymic ON patronymic.id = driver.patronymic_id')
        if sort_val == '1':
            query += ' ORDER BY name;'
        elif sort_val == '2':
            query += ' ORDER BY surname;'
        elif sort_val == '3':
            query += ' ORDER BY patronymic;'
        else: 
            query += ' ORDER BY adoption_date;'
    elif table_name == 'pinned_car':
        filter_val = None
        while filter_val not in set(['1', '2']):
            filter_val = input('Вывести:\n1 Только активные закрепления\n2 Все закрепления\n > ')

        query = ('SELECT pinned_car.id, name, surname, patronymic, brand_name, '
                '        model_name, car.number, is_active '
                'FROM car_agency.pinned_car '
                'INNER JOIN car ON car.id = pinned_car.car_id '
                '    LEFT OUTER JOIN  brand ON car.brand_id = brand.id '
                '    LEFT OUTER JOIN  model ON car.model_id = model.id '
                'INNER JOIN driver ON driver.id = pinned_car.driver_id '
                '    LEFT OUTER JOIN  name ON driver.name_id = name.id '
                '    LEFT OUTER JOIN  surname ON driver.surname_id = surname.id '
                '    LEFT OUTER JOIN  patronymic ON driver.patronymic_id = patronymic.id')
        
        if filter_val == '1':
            query += ' WHERE is_active=1;'
        elif filter_val == '2':
            query += ';'

    cursor.execute(query)
    data = cursor.fetchall()

    for offset in range(0, 10*10000, 10):
        df = pd.DataFrame(data=data[offset: offset + 10], columns=table_columns[table_name])
        if not len(df):
            input('Конец. Нажмите enter чтобы продолжить')
            break
        print(df)
        
        user_input = input('Enter чтобы дальше, 0 чтобы закончить')
        if user_input == '0':
            break


def update(column_name, column_value, table_name, idx):
    cursor = database.cursor()
    cursor.execute(f'UPDATE {table_name} SET {column_name}="{column_value}" WHERE id={idx};')
    database.commit()


def pin_car():
    user_input = None
    while user_input not in ('0', '1'):
        user_input = input('0 Сменить значение\n1 Добавить\n')
    
    if user_input == '0':
        idx = input('Введите id элемента: ')
        if not exist('id', idx, 'pinned_car'):
            print('Нет такого элемента.')
            input('\nНажмите любую клавишу чтобы продолжить...')
            return

        new_value = None
        while new_value not in {'0', '1'}:
            new_value = input('Введите новое значение:\n0 Активное закрепление'
                              '\n1 Неактивное закрепление\n')
        update('is_active', new_value == '0', 'pinned_car', idx)
    else:
        driver_id = input('Введите id водителя: ')   
        if not exist('id', driver_id, 'driver'):
            print('Нет такого водителя')
            time.sleep(2)
            return

        car_id = input('Введите id машины: ')
        if not exist('id', car_id, 'car'):
            print('Нет такой машины')
            time.sleep(2)
            return

        insert(insert_queries['pinned_car'], (driver_id, car_id, True))
    input('\nНажмите любую клавишу чтобы продолжить...')


def update_table(table_name):
    idx = input('Введите id элемента: ')
    if not exist('id', idx, table_name):
        print('Такого элемента не существует')
        input('Enter чтобы продолжить...')
        return
    
    if table_name not in {'car', 'driver', 'brand', 'color', 'pinned_car'}:
        column_name = table_name
        new_value = input('Введите новое значение: ')
        if table_name == 'model':
            column_name = table_name + '_name'
        update(column_name, new_value, table_name, idx)
    
    elif table_name == 'brand':
        user_input = None
        while user_input not in {'1', '2'}:
            user_input = input('Выберите:\n1 Полное имя\n2 Сокращенное имя\n')
        
        new_value = input('Введите новое значение: ')
        column_name = 'brand_name' if user_input == '1' else 'short_brand_name'
        update(column_name, new_value, table_name, idx)        

    elif table_name == 'color':
        user_input = None
        while user_input not in {'1', '2'}:
            user_input = input('Выберите:\n1 Имя цвета\n2 Код цвета\n')
     
        new_value = input('Введите новое значение: ')
        column_name = 'color_name' if user_input == '1' else 'color_code'
        update(column_name, new_value, table_name, idx)
   
    elif table_name == 'driver':
        print('Номер водительского должен быть уникальным!!!\n')

        user_input = None
        while user_input not in set(map(str, range(1, 7))):
            print('Выберите:\n1 Имя\n2 Фамилия\n3 Отчество')
            print('4 Номер паспорта\n5 Номер телефона\n6 Номер водительского')
            user_input = input('> ')

        if user_input == '1':
            column_name = 'name'
        elif user_input == '2':
            column_name = 'surname'
        elif user_input == '3':
            column_name = 'patronymic'
        elif user_input == '4':
            column_name = 'passport_number'
        elif user_input == '5':
            column_name = 'phone_number'
        elif user_input == '6':
            column_name = 'driver_license_number'
        
        new_value = input('Введите новое значение: ')
        if user_input in {'1', '2', '3'}:
            if not exist(column_name, new_value, column_name):
                input('Такого значения не существует.\nEnter чтобы продолжить..')
                return
            else:
                new_value_idx = get_id(column_name, new_value, column_name)
            update(column_name+'_id', new_value_idx, table_name, idx)
        else:
            update(column_name, new_value, table_name, idx)

    elif table_name == "car":
        print('Номер автомобиля должен быть уникальным!!!\n')
        user_input = None
        while user_input not in set(map(str, range(1, 6))):
            print('Выберите:\n1 Марка\n2 Модель\n3 Цвет')
            print('4 Номер\n5 Тип топлива')
            user_input = input('> ')

        if user_input == '1':
            column_name = 'brand'
        elif user_input == '2':
            column_name = 'model'
        elif user_input == '3':
            column_name = 'color'
        elif user_input == '4':
            column_name = 'number'
        elif user_input == '5':
            column_name = 'oil_type'
        
        new_value = input('Введите новое значение: ')
        if user_input in {'1', '2', '3'}:
            if not exist(column_name + '_name', new_value, column_name):
                input('Такого значения не существует.\nEnter чтобы продолжить..')
                return
            else:
                new_value_idx = get_id(column_name + '_name', new_value, column_name)
            update(column_name+'_id', new_value_idx, table_name, idx)
        else:
            update(column_name, new_value, table_name, idx)
    input('\nНажмите любую клавишу чтобы продолжить...')



###############################################################################
##### WRAPPERS 
###############################################################################


def remove_value(table_name):
    idx = input('Введите id элемента: ')
    delete(table_name, idx)


def show_tables():
    print('Выберите таблицу')
    print('1 Имена\n2 Фамилии \n3 Отчества')
    print('4 Марки машин\n5 Модели машин \n6 Цвета машин')
    print('7 Машины\n8 Водители')


def add_new_data():
    clear()
    show_tables()

    user_input = input()
    if user_input in tables:
        add_value(tables[user_input])
    else:
        add_new_data()


def remove_data():
    clear()
    show_tables()
    print('9 Закрепленные машины')


    user_input = input()
    if user_input in tables:
        remove_value(tables[user_input])
    else:
        remove_data()


def find_id():
    clear()
    show_tables()
    user_input = input('Выберите таблицу: ')
    
    if user_input in tables:
        find_value_id(tables[user_input])
    else:
        find_id()


def show_data():
    clear()
    show_tables()
    print('9 Закрепленные машины')
    user_input = input()

    if user_input in tables:
        show_one_table(tables[user_input])
    else:
        show_data()


def update_table_data():
    show_tables()
    clear()
    show_tables()
    user_input = input('Выберите таблицу: ')
    print('\n')
    if user_input in tables:
        update_table(tables[user_input])
    else:
        update_table_data()



if __name__ == '__main__':
    database = get_database()

    if IS_COLD_START:
        fill_tables(database)

    functions = {
        '0': exit,
        '1': add_new_data,
        '2': remove_data,
        '3': find_id,
        '4': show_data,
        '5': pin_car,
        '6': update_table_data
    }

    while True:
        clear()
        print_start_menu()
        choise = input()
        clear()
        if choise in functions:
            functions[choise]()
